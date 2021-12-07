/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:34:41 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 19:58:41 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "./minilib/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <string.h>

typedef struct s_reponse
{
	char	spec;
	int		taille;
	int		point;
	int		precision;
	char	convertion;
	int		x;
	int		y;
	int		con;
	char	*base;
}				t_reponse;

int				ft_printf(const char *str, ...);
int				ft_start(int x, va_list ap, char *test, int *con);
t_reponse		*ft_reader(va_list ap, char *test, t_reponse *a);
t_reponse		*ft_spec(va_list ap, char *test, t_reponse *a);
t_reponse		*ft_taille(va_list ap, char *test, t_reponse *a);
t_reponse		*ft_conv(char *test, t_reponse *a);
t_reponse		*ft_precision(va_list ap, char *test, t_reponse *a);
void			ft_printrep(t_reponse *a);
int				*ft_maz(t_reponse *a);
int				ft_dconv(va_list ap, t_reponse *a, char *base);
int				ft_sizenb(int x, int tbase);
void			ft_putchar(char c, t_reponse *a);
void			ft_displayd(int x, int nbchar, t_reponse *a, int nbz);
void			ft_displays(char *s, int size, int nbchar, t_reponse *a);
void			ft_displaysmoins(char *s, int size, int nbchar, t_reponse *a);
int				ft_sconv(va_list ap, t_reponse *a);
void			ft_displayc(char x, t_reponse *a);
int				ft_cconv(va_list ap, t_reponse *a);
void			ft_etoile(va_list ap, t_reponse *a);
int				ft_pourconv(t_reponse *a);
void			ft_specspe(char *test, t_reponse *a);
void			ft_ndisp(int x, int nbchar, int nbz, t_reponse *a);
void			ft_tdisp(int x, int nbchar, int nbz, t_reponse *a);
void			ft_zdisp(int x, int nbchar, int nbz, t_reponse *a);
void			ft_putnbrebase(unsigned long x, char *base, t_reponse *a);
void			ft_pconv(va_list ap, t_reponse *a);
void			ft_putp(unsigned long x, char *base, t_reponse *a);
void			ft_displayp(unsigned long y, t_reponse *a);
void			ft_putstrspe(char *s, t_reponse *a);
void			ft_ndispx(unsigned int y, int nbchar, int nbz, t_reponse *a);
void			ft_tdispx(unsigned int y, int nbchar, int nbz, t_reponse *a);
void			ft_zdisx(unsigned int x, int nbchar, int nbz, t_reponse *a);
void			ft_displayx(unsigned int x, int nbchar, t_reponse *a, int nbz);
int				ft_sizenbx(unsigned long y, unsigned long x);
int				ft_xconv(va_list ap, t_reponse *a, char *base);
void			ft_sconverror(t_reponse *a, char *error, int x, int con);

#endif
