/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 21:20:43 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 09:19:07 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_KEY_H
# define MLX_KEY_H

# ifdef OS_DARWIN_H
#  include "key_mac.h"
# endif

# ifdef OS_LINUX_H
#  include "key_linux.h"
# endif

#  include "key_linux.h"

#endif
