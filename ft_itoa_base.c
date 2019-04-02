/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:09:03 by sromanet          #+#    #+#             */
/*   Updated: 2018/10/21 20:09:05 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*ft_first_zero(char *s, int a, int b)
{
	char *new;

	if (!s)
		new = ft_strnew(1);
	else
		new = ft_strnew(ft_strlen(s) + 1);
	new[0] = '0';
	if (s)
		while (s[a])
			new[b++] = s[a++];
	if (s)
		free(s);
	return (new);
}

char	*ft_itoa_base(unsigned int value, int base)
{
	char	*res;
	int		n;

	res = NULL;
	if (value == 0)
		res = ft_first_zero(res, 0, 1);
	while (value)
	{
		res = ft_first_zero(res, 0, 1);
		n = value % base;
		if (n <= 9)
			res[0] = n + 48;
		else
			res[0] = n + 87;
		value /= base;
	}
	if (ft_strlen(res) == 1)
		res = ft_first_zero(res, 0, 1);
	return (res);
}
