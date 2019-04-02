/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:52:18 by sromanet          #+#    #+#             */
/*   Updated: 2018/09/01 16:52:21 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	*init_ft_md5(char *input, size_t len)
{
	t_md5			*hash;
	unsigned int	tmp;

	tmp = 8 * len;
	hash = (t_md5 *)malloc(sizeof(t_md5));
	hash->h0 = 0x67452301;
	hash->h1 = 0xefcdab89;
	hash->h2 = 0x98badcfe;
	hash->h3 = 0x10325476;
	hash->new_len = ft_new_len(len);
	hash->res = (unsigned char *)ft_strnew(hash->new_len + 64);
	ft_memcpy(hash->res, input, len);
	hash->res[len] = 128;
	ft_memcpy(hash->res + hash->new_len, &tmp, 4);
	hash->offset = 0;
	return ((void *)hash);
}

void	data_manipulation_end(t_md5 *hash, int i, unsigned int x,
															unsigned int y)
{
	unsigned int z;

	z = hash->d;
	hash->d = hash->c;
	hash->c = hash->b;
	hash->b = hash->b + LEFTROTATE((hash->a + x + g_k_md5[i] + hash->tmp[y]),
																	g_r_md5[i]);
	hash->a = z;
}

void	data_manipulation(t_md5 *hash, int i, unsigned int x, unsigned int y)
{
	while (++i < 64)
	{
		if (i < 16)
		{
			x = (hash->b & hash->c) | ((~hash->b) & hash->d);
			y = i;
		}
		else if (i < 32)
		{
			x = (hash->d & hash->b) | ((~hash->d) & hash->c);
			y = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			x = hash->b ^ hash->c ^ hash->d;
			y = (3 * i + 5) % 16;
		}
		else
		{
			x = hash->c ^ (hash->b | (~hash->d));
			y = (7 * i) % 16;
		}
		data_manipulation_end(hash, i, x, y);
	}
}

void	print_md5(unsigned int h, int i)
{
	unsigned char	*str;
	char			*res;

	str = (unsigned char *)&h;
	while (++i < 4)
	{
		res = ft_itoa_base(str[i], 16);
		ft_putstr(res);
		ft_strdel(&res);
	}
}

void	ft_md5(void *input)
{
	t_md5	*hash;

	hash = (t_md5 *)input;
	while (hash->offset < hash->new_len)
	{
		hash->tmp = (unsigned int *)(hash->res + hash->offset);
		hash->a = hash->h0;
		hash->b = hash->h1;
		hash->c = hash->h2;
		hash->d = hash->h3;
		data_manipulation(hash, -1, 0, 0);
		hash->h0 += hash->a;
		hash->h1 += hash->b;
		hash->h2 += hash->c;
		hash->h3 += hash->d;
		hash->offset += (512 / 8);
	}
	free(hash->res);
	print_md5(hash->h0, -1);
	print_md5(hash->h1, -1);
	print_md5(hash->h2, -1);
	print_md5(hash->h3, -1);
}
