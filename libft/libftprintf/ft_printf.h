/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:26:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/02 13:28:16 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft.h"

/*	leftpad -> 1 for left justify, 2 left pad with zeroes
	pre		-> 1 for force sign, 2 blank, 3 0x
	size	-> used for counting elements and size of printout
*/

typedef struct s_flags
{
	int			leftpad;
	int			width;
	int			precision;
	int			pre;
	int			size;
	int			i;
	int			zero;
	char		*tmp;
}	t_flags;

typedef void	t_cnv_func(va_list args, t_flags *flags, int i, int spec);

typedef struct s_cnv
{
	t_cnv_func	*func;
}	t_cnv;

// ft_printf_utils1.c
int		get_index(char c, char *index);
int		check_tag(const char *format);
int		calc_elemcount(const char *c);
int		power(int base, int exp);
int		minmax(int n, ...);

// ft_printf_utils2.c
char	*alloc_elem(int size, int zero, int nullcase, int i);
void	cnv_case(char *s, int lcase);
t_flags	*init_flags(const char *format, t_flags *flags);
int		getdigits(unsigned long int nbr, int *nbrptr, int base);
int		getnumsize(const char *format);

// ft_printf_utils3.c
int		getsize(t_flags *flags, int *arg, unsigned long int uarg, int base);
void	signcopy(char *s, int nbr, int size, int base);
void	unsigncopy(char *s, unsigned long int nbr, int size, int base);
void	formatnbr(char *s, char *sign, int zeroes, int nbr);
void	formatunbr(char *s, char *sign, int zeroes, unsigned long int nbr);

// ft_printf_utils4.c

int		s_helper(t_flags *flags, int len, char *arg);
void	p_helper(va_list args, t_flags *flags, unsigned long int *arg);

// ft_print_convert1.c
void	cnv_c(va_list args, t_flags *flags, int i, int spec);
void	cnv_s(va_list args, t_flags *flag, int i, int spec);
void	cnv_d(va_list args, t_flags *flags, int i, int spec);
void	cnv_x(va_list args, t_flags *flags, int i, int spec);
void	cnv_u(va_list args, t_flags *flags, int i, int spec);

int		ft_printf(const char *format, ...);

#endif /* FT_PRINTF_H */
