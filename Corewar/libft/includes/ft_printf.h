/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:19:31 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/27 14:26:02 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include "libft.h"

# define H	0
# define L	1
# define Z	2
# define J	3
# define LL	4
# define HH	5

# define BUFF 4096

# define INIT	"\033[H\033[J"
# define TOP	"\033[H"
# define BLK	"\x1B[30m"
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define EOC	"\x1B[0m"

typedef struct		s_form
{
	char			minus;
	char			plus;
	char			space;
	char			zero;
	char			hash;
	int				width;
	int				pre;
	int				preflag;
	int				length;
	int				nul;
	int				apo;
	int				dolls;
}					t_form;

typedef struct		s_data
{
	int				buff;
	char			buffer[BUFF];
	int				index;
	char			field;
	int				length;
	int				error;
	int				fd;
	va_list			ap_cpy;
	va_list			ap_svg;
	char			*sprintf;
}					t_data;

typedef struct		s_fct
{
	char			c;
	int				(*f)(va_list ap, t_form* form, t_data* data);
}					t_fct;

int					ft_printf(char *fmt, ...);
int					ft_dprintf(int fd, char *fmt, ...);
int					ft_sprintf(char *str, char *fmt, ...);
int					parser(t_data *data, char **str, t_form *form, va_list ap);
int					field(t_data *data, char **str);
int					print_int(va_list ap, t_form *form, t_data *data);
int					print_str(va_list ap, t_form *form, t_data *data);
int					print_ptr(va_list ap, t_form *form, t_data *data);
int					print_int(va_list ap, t_form *form, t_data *data);
int					print_bin(va_list ap, t_form *form, t_data *data);
int					print_oct(va_list ap, t_form *form, t_data *data);
int					print_hex(va_list ap, t_form *form, t_data *data);
int					get_len(va_list ap, t_form *form, t_data *data);
int					print_uns_int(va_list ap, t_form *form, t_data *data);
int					print_hex_low(va_list ap, t_form *form, t_data *data);
int					print_hex_up(va_list ap, t_form *form, t_data *data);
int					print_char(va_list ap, t_form *form, t_data *data);
int					num_field(t_data *data, char **str);
int					str_field(t_data *data, char **str);
int					flags(char **str, t_form *form);
int					width(va_list ap, char **str, t_form *form);
int					precision(va_list ap, char **str, t_form *form);
int					length(char **str, t_form *form);
void				dolls(t_form *form, char **str);
void				lst_arg(t_data *data, int i);
wchar_t				unicode(wchar_t wc, t_data *data);
void				fwp_int(long long nb, t_form *form, t_data *data);
void				fwp_u_int(unsigned long long nb, t_form *form,
															t_data *data);
void				fwp_bin(unsigned long nb, t_form *form, t_data *data);
void				fwp_oct(unsigned long nb, t_form *form, t_data *data);
void				fwp_hex(unsigned long long nb, t_form *form, t_data *data);
void				fwp_ptr(unsigned long ptr, t_form *form, t_data *data);
void				fwp_char(int c, t_form *form, t_data *data);
void				fwp_str(char *str, t_form *form, t_data *data);
int					fwp_wchar(wchar_t wc, t_form *form, t_data *data);
int					fwp_wstr(wchar_t *w, t_form *form, t_data *data);
long long			unsigned_cast(long long val, int mod);
long long			signed_cast(long long val, int mod);
int					addchar(t_data *data, char c, int pos);
int					addwc(t_data *data, wchar_t wc, int pos, int len);
int					ft_nblen(long long nb);
int					ft_nblen_b(unsigned long long nb, int base);
int					ft_u_nblen(unsigned long long nb);
long int			ft_power(int n, unsigned int p);
unsigned long int	ft_u_power(int n, unsigned int p);
/*
**int				ft_fprintf(FILE *stream, char *fmt, ...);
*/

#endif
