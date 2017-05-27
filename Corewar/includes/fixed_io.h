/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:05:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/22 14:17:07 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_IO_H
# define FIXED_IO_H

# include "libft.h"

ssize_t				fixed_write(int fildes, const void *buf, size_t nbyte);
unsigned int		fixed_read_32(int fildes);
unsigned short		fixed_read_16(int fildes);

#endif
