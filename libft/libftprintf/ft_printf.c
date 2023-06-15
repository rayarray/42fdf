/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:12:22 by rleskine          #+#    #+#             */
/*   Updated: 2023/04/26 11:58:11 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_cnv	g_cnv_arr[] = {{&cnv_c}, {&cnv_s}, {&cnv_x}, {&cnv_d},
{&cnv_d}, {&cnv_u}, {&cnv_x}, {&cnv_x}};

const char	*parseflags(const char *format, va_list args, t_flags *flags, int i)
{
	while (*format != 0 && get_index(*format, "-0+ #") > -1)
	{
		i = get_index(*(format++), "-0+ #");
		if (i < 2)
			flags->leftpad = i + 1;
		else
			flags->pre = i - 1;
	}
	if (*format != 0 && *format > 48 && *format < 58)
		flags->width = ft_atoi(format);
	if (*format != 0 && *format > 48 && *format < 58)
		format = format + getdigits(0, &(flags->width), 10);
	else if (*format != 0 && *format == '*' && format++)
		flags->width = va_arg(args, int);
	if (*format != 0 && *format == '.' && format++ && (flags->precision)++)
	{
		if (*format != 0 && *format == '*' && format++)
			flags->precision = va_arg(args, int);
		else if (format != 0 && *format > 47 && *format < 58)
		{
			flags->precision = ft_atoi(format);
			format = format + getdigits(0, &(flags->precision), 10);
		}
	}
	return (format);
}

const char	*parsetag(const char *format, va_list args, t_flags *flags)
{
	int	index;

	index = 0;
	flags = init_flags(NULL, flags);
	if (get_index(*format, "cspdiuxX%") < 0)
		format = parseflags(format, args, flags, 0);
	index = get_index(*format, "cspdiuxX%");
	if (index > -1)
	{
		if (index == 8)
			(*g_cnv_arr[0].func)(args, flags, 0, 1);
		else if (index == 2)
			(*g_cnv_arr[2].func)(args, flags, 0, 2);
		else
			(*g_cnv_arr[index].func)(args, flags, 0, 0);
		if (index == 7 && flags->tmp && *(flags->tmp) != ')')
			cnv_case(flags->tmp, 1);
		return (++format);
	}
	return (NULL);
}

const char	*getelem(const char *format, va_list args, t_flags *flags)
{
	char	*tmp;
	int		i;

	i = 0;
	if (*format == '%')
		return (parsetag(++format, args, flags));
	else
	{
		while (*(format + i) != 0 && *(format + i) != '%')
			i++;
		flags->tmp = (char *)malloc(sizeof(char) * (i + 1));
		if (flags->tmp == NULL)
			return (NULL);
		*(flags->tmp + i) = 0;
		tmp = flags->tmp;
		while (*format != 0 && *format != '%')
			*(tmp++) = *(format++);
		return (format);
	}
}

int	printelem(char **elem, char **tmp, t_flags *flags, int size)
{
	while (*elem != NULL)
	{
		if (**elem == ')' && ft_strncmp(")nULl(", *elem, 6) == 0)
		{
			flags->tmp = *elem + 6;
			while (*(flags->tmp) != 0)
			{
				if (*(flags->tmp) == '0')
					write(1, *elem + ft_strlen(*elem), 1);
				else
					write(1, flags->tmp, 1);
				(flags->tmp)++;
				size++;
			}
		}
		else
		{
			write(1, *elem, ft_strlen(*elem));
			size += ft_strlen(*elem);
		}
		free(*(elem++));
	}
	free(flags);
	free(tmp);
	return (size);
}

int	ft_printf(const char *format, ...)
{
	char	**elem[2];
	t_flags	*flags;
	va_list	args;

	flags = init_flags(format, NULL);
	va_start(args, format);
	elem[1] = (char **)malloc(sizeof(char *) * (flags->size + 1));
	if (elem [1] == NULL || format == NULL || flags->size < 1)
		return (0);
	*(elem[1] + flags->size) = NULL;
	elem[0] = elem[1];
	flags->size = 0;
	while (*format != 0)
	{
		format = getelem(format, args, flags);
		if (flags->tmp == NULL)
			return (-1);
		*elem[1] = flags->tmp;
		flags->size += ft_strlen(*(elem[1]++));
	}
	va_end(args);
	return (printelem(elem[0], elem[0], flags, 0));
}
