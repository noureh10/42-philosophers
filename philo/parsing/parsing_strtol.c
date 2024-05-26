/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_strtol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:24:52 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/21 15:43:55 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int	is_valid_char(char c, int base)
{
	if ((base <= 10 && (c >= '0' && c < '0' + base))
		|| (base > 10 && ((c >= '0' && c <= '9')
				|| (c >= 'a' && c < 'a' + base - 10)
				|| (c >= 'A' && c < 'A' + base - 10))))
		return (1);
	return (0);
}

static int	get_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (0);
}

static void	handle_sign_and_prefix(const char **s, int *sign, int *base)
{
	while (is_whitespace(**s))
		(*s)++;
	if (**s == '-')
	{
		*sign = -1;
		(*s)++;
	}
	else if (**s == '+')
	{
		*sign = 1;
		(*s)++;
	}
	if ((*base == 0 || *base == 16) && **s == '0')
	{
		*s += 1;
		if (**s == 'x' || **s == 'X')
		{
			*s += 1;
			*base = 16;
		}
		else
			*base = 8;
	}
	if (*base == 0)
		*base = 10;
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*s;
	long		result;
	int			sign;
	int			digit;

	s = nptr;
	result = 0;
	sign = 1;
	handle_sign_and_prefix(&s, &sign, &base);
	while (is_valid_char(*s, base))
	{
		digit = get_digit_value(*s++);
		result = result * base + digit;
	}
	if (endptr)
		*endptr = (char *)s;
	return (result * sign);
}
