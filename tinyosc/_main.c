/**
 * Copyright (c) 2015, Martin Roth (mhroth@gmail.com)
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "tinyosc.h"

#include "osc_rtv1.h"

//	On va remplis les deux premiere trame, 
//		si on a directement 

//	pour toujours aller chercher sa valeur au cas ou elle aurrait ete modifier
//	par une fonciton exterieur
static volatile bool	g_keepRunning = 1;

// handle Ctrl+C
static void sigintHandler(int x) {
	g_keepRunning = 0;
	// on pourrai aussi fermer proprement et faire un exit(0)...
}

int		get_var_id(char *var)
{
	int				i;
	int				tab_size;
	const	char	tab_var_name[][32] = {
										"float_acc",
										"float_acc_x",
										"float_acc_y",
										"float_acc_z",
										"float_roll",
										"float_pitch",
										"float_yaw",
										"float_trigger",
										"button_up",
										"button_down",
										"button_right",
										"button_left",
										"button_a",
										"button_1",
										"button_2",
										"button_plus",
										"button_minus",
										"button_start",
											};

	tab_size = sizeof(tab_var_name) / (sizeof(char) * 32);
	for (i = 0; i < tab_size; i++)
	{
		if (strcmp(&(tab_var_name[i][0]), var) == 0)
			return (i);
	}
	return (-1);
}

int		get_oscvalue(tosc_message *msg)
{
	int		ret;
	float	retf;
	char	*type;

	// on chope le type
	// on recupere l'int ou le float qu'on caste un int
	if (!(type = tosc_getFormat(msg)))
		return (-1);	
	if (*type == 'i')
		ret = tosc_getNextInt32(msg);
	else if (*type == 'f')
	{
		retf = tosc_getNextFloat(msg);
		ret = *((int*)(&retf));
	}
	else
		ret = 0;
	return (ret);
}

int		osc_init_conection(int port, struct sockaddr_in *sin)
{
	// open a socket to listen for datagrams (i.e. UDP packets) on port 9000
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	// register the SIGINT handler (Ctrl+C)
	signal(SIGINT, &sigintHandler);

	fcntl(fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
	sin->sin_family = AF_INET;
	sin->sin_port = htons(9000);
	sin->sin_addr.s_addr = INADDR_ANY;
	bind(fd, (struct sockaddr *) sin, sizeof(struct sockaddr_in));
	printf("tinyosc is now listening on port %d.\n", port);
	printf("Press Ctrl+C to stop.\n");

	return	fd;
}

void	test_osc()
{
	char				buffer[2048]; // declare a 2Kb buffer to read packet data into
	printf("Starting write tests:\n");
	int len = 0;
	char blob[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	len = tosc_writeMessage(buffer, sizeof(buffer), "/address", "fsibTFNI",
			1.0f, "hello world", -1, sizeof(blob), blob);
	tosc_printOscBuffer(buffer, len);
	printf("done.\n");
}


void	osc_trv1_push_tram(t_wiimote *tram)
{
	// la on est dans le rtv1
}

void	osc_make_rtv1_trame(tosc_message *osc)
{
	static	t_wiimote	tram;
	static	int			prev_id = -1;
	static	int			last_id = -1;
	static	int			first_id = -1;
	int					id;

	id = get_var_id(tosc_getAddress(osc));
	if (last_id < 0)
	{
		if (first_id < 0)
			first_id = id;
		else if (id == first_id)
		{
			last_id = prev_id;
			// si on ne push pas ici la data, on la premiere sera ecraser
			osc_trv1_push_tram(&tram);
			// on envoie les bail <<<<<<<<<<<< ------------
			bzero(&tram, sizeof(tram));
//			tosc_printMessage(&osc);
			return ;
		}
		prev_id = id;
	}
	
	((int*)(&tram))[id] = get_oscvalue(osc); // on ajoute le message
	if (id == last_id)
	{
		// on envoie les bail <<<<<<<<<<<< ------------
		bzero(&tram, sizeof(tram));
	}

	tosc_printMessage(osc);
}

void	osc_rtv1(t_osc *o)

{
	// ici on va former les trame et les 
	char				buffer[2048]; // declare a 2Kb buffer to read packet data into
	int					len;
	tosc_message 		osc;
	fd_set				readSet;
	struct	sockaddr	sa; // can be safely cast to sockaddr_in
	struct	tosc_bundle	bundle;

	FD_ZERO(&readSet);
		FD_SET(o->fd, &readSet);
		if (select(o->fd + 1, &readSet, NULL, NULL, &(o->timeout)) > 0)
		{
			len = 0;
			while ((len = (int) recvfrom(o->fd, buffer, sizeof(buffer), 0, &sa, &o->sa_len)) > 0)
			{
				if (tosc_isBundle(buffer))
				{
					printf("YALA\n");
			//		uint64_t timetag  = tosc_getTimetag(&bundle);
					tosc_parseBundle(&bundle, buffer, len);
					while (tosc_getNextMessage(&bundle, &osc))
						osc_make_rtv1_trame(&osc);
				}
				else
				{
				//	osc.timetag = 0;
					tosc_parseMessage(&osc, buffer, len);
					osc_make_rtv1_trame(&osc);
				}
			}
		}
}

void	init_dirty(socklen_t *sa_len, int *port,
		struct timeval *timeout, int *fd, struct sockaddr_in *sin)
{
	*sa_len = sizeof(struct sockaddr_in);
	*port = 9000;
	*timeout = (struct timeval){0, 1000}; // select times out after 1 mili second
	*fd = osc_init_conection(*port, sin);
}


/**
 * A basic program to listen to port 9000 and print received OSC packets.
 */
int main(int argc, char *argv[])
{
	static	int					port = 0;
	static	struct	sockaddr_in sin = {0, 0, 0, 0};
	static	struct	timeval 	timeout = {0, 0};
	struct	sockaddr			sa; // can be safely cast to sockaddr_in
	static	socklen_t			sa_len = 0;
	static	tosc_bundle 		bundle = {};
	static	int					first_run = 1;
	static	t_osc				osc;

	if (first_run)
	{
		first_run = 0;
		init_dirty(&(osc.sa_len), &port, &(osc.timeout), &(osc.fd), &sin);
	}
	/// begin treatment 	
	while (g_keepRunning)
	{
		osc_rtv1(&osc);
	}

	// close the UDP socket
	close(osc.fd);
	return 0;
}
