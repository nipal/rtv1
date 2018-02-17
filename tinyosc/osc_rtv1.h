/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osc_rtv1.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:51:34 by fjanoty           #+#    #+#             */
/*   Updated: 2018/02/17 16:39:34 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSC_RTV1_H
# define OSC_RTV1_H

#include "tinyosc.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>



//	Les variable button_  sont des type bolean
//	-----------> float_ ----------->  flotant
//		==> toute les variable font 4 byte donc ont pourra faire un genre de trics d'ardresse
#define	BUFF_SMALL	32
typedef	struct	s_wiimote
{
	float	float_acc;
	float	float_acc_x;
	float	float_acc_y;
	float	float_acc_c;
	float	float_roll;
	float	float_pitch;
	float	float_yaw;
	float	float_trigger;
	int		button_up;
	int		button_down;
	int		button_right;
	int		button_left;
	int		button_a;
	int		button_1;
	int		button_2;
	int		button_plus;
	int		button_minus;
	int		button_start;
	int		actived_var;
}				t_wiimote;

typedef	struct	s_osc
{
	socklen_t				sa_len;
	struct timeval			timeout;
//	uint64_t				timetag;
	int 					fd;
}				t_osc;

int				get_var_id(char *var);
int				get_oscvalue(tosc_message *msg);
void			do_the_test();
#endif

