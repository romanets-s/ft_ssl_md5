/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:28:40 by sromanet          #+#    #+#             */
/*   Updated: 2018/09/01 15:28:42 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void						*init_ft_sha256(char *input, size_t len)
{
	t_sha256	*hash;

	hash = (t_sha256 *)malloc(sizeof(t_sha256));
	ft_memset(hash->message_w, 0x00, sizeof(hash->message_w));
	ft_memcpy(hash->ah, g_h, sizeof(hash->ah));
	hash->buffer = (t_state *)malloc(sizeof(t_state));
	hash->buffer->ptr = (unsigned char *)input;
	hash->buffer->len = len;
	hash->buffer->len_total = len;
	hash->buffer->is_one_finish = 0;
	hash->buffer->is_finish = 0;
	return (hash);
}

void						calculate_message_w(t_sha256 *hash, int i)
{
	const unsigned char	*p;

	p = hash->chunk;
	i = -1;
	while (++i < 16)
	{
		hash->message_w[i] = (unsigned int)p[0] << 24 |
					(unsigned int)p[1] << 16 | (unsigned int)p[2] << 8 |
					(unsigned int)p[3];
		p += 4;
	}
	i = 15;
	while (++i < 64)
	{
		hash->s0 = right_rot(hash->message_w[i - 15], 7) ^
							right_rot(hash->message_w[i - 15], 18) ^
								(hash->message_w[i - 15] >> 3);
		hash->s1 = right_rot(hash->message_w[i - 2], 17) ^
							right_rot(hash->message_w[i - 2], 19) ^
								(hash->message_w[i - 2] >> 10);
		hash->message_w[i] = hash->message_w[i - 16] + hash->s0 +
								hash->message_w[i - 7] + hash->s1;
	}
}

void						calculate_ah(t_sha256 *hash, int i, unsigned int c,
																unsigned int m)
{
	unsigned int	tmp0;
	unsigned int	tmp1;

	while (++i < 64)
	{
		hash->s1 = right_rot(hash->ah[4], 6) ^ right_rot(hash->ah[4], 11) ^
												right_rot(hash->ah[4], 25);
		c = (hash->ah[4] & hash->ah[5]) ^ (~hash->ah[4] &
															hash->ah[6]);
		tmp0 = hash->ah[7] + hash->s1 + c + g_k[i] +
														hash->message_w[i];
		hash->s0 = right_rot(hash->ah[0], 2) ^ right_rot(hash->ah[0], 13) ^
												right_rot(hash->ah[0], 22);
		m = (hash->ah[0] & hash->ah[1]) ^ (hash->ah[0] &
								hash->ah[2]) ^ (hash->ah[1] & hash->ah[2]);
		tmp1 = hash->s0 + m;
		hash->ah[7] = hash->ah[6];
		hash->ah[6] = hash->ah[5];
		hash->ah[5] = hash->ah[4];
		hash->ah[4] = hash->ah[3] + tmp0;
		hash->ah[3] = hash->ah[2];
		hash->ah[2] = hash->ah[1];
		hash->ah[1] = hash->ah[0];
		hash->ah[0] = tmp0 + tmp1;
	}
}

void						ft_sha256(void *input)
{
	size_t			n;
	int				i;
	t_sha256		*hash;

	hash = (t_sha256 *)input;
	while (calculate_chunk(hash))
	{
		calculate_message_w(hash, 0);
		calculate_ah(hash, -1, 0, 0);
		i = -1;
		while (++i < 8)
			g_h[i] += hash->ah[i];
	}
	i = -1;
	n = 0;
	while (++i < 8)
	{
		hash->hash[n++] = (unsigned char)(g_h[i] >> 24);
		hash->hash[n++] = (unsigned char)(g_h[i] >> 16);
		hash->hash[n++] = (unsigned char)(g_h[i] >> 8);
		hash->hash[n++] = (unsigned char)(g_h[i] >> 0);
	}
	free(hash->buffer);
	print_sha256(hash->hash);
}

void						print_sha256(unsigned char hash[32])
{
	size_t	i;

	i = 0;
	while (i < 32)
	{
		ft_putstr(ft_itoa_base(hash[i], 16));
		i++;
	}
}
