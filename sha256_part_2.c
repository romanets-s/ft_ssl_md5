/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_part_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:21:56 by sromanet          #+#    #+#             */
/*   Updated: 2019/01/26 18:21:59 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

unsigned int				right_rot(unsigned int value, unsigned int count)
{
	unsigned int	tmp;

	tmp = value >> count | value << (32 - count);
	return (tmp);
}

void						calculate_chunk_end(t_sha256 *hash, size_t space,
												unsigned char *tmp)
{
	size_t	len;
	int		i;

	if (space >= TOTAL_LEN_LEN)
	{
		len = hash->buffer->len_total;
		ft_memset(tmp, 0x00, space - TOTAL_LEN_LEN);
		tmp += space - TOTAL_LEN_LEN;
		tmp[7] = (unsigned char)(len << 3);
		len >>= 5;
		i = 6;
		while (i >= 0)
		{
			tmp[i] = (unsigned char)len;
			len >>= 8;
			i--;
		}
		hash->buffer->is_finish = 1;
	}
	else
		ft_memset(tmp, 0x00, space);
}

int							calculate_chunk_size(t_sha256 *hash,
													unsigned char *tmp)
{
	ft_memcpy(tmp, hash->buffer->ptr, CHUNK_SIZE);
	hash->buffer->ptr += CHUNK_SIZE;
	hash->buffer->len -= CHUNK_SIZE;
	return (1);
}

int							calculate_chunk(t_sha256 *hash)
{
	size_t			space;
	unsigned char	*tmp;

	tmp = hash->chunk;
	if (hash->buffer->is_finish)
		return (0);
	if (hash->buffer->len >= CHUNK_SIZE)
		return (calculate_chunk_size(hash, tmp));
	ft_memcpy(tmp, hash->buffer->ptr, hash->buffer->len);
	tmp += hash->buffer->len;
	space = CHUNK_SIZE - hash->buffer->len;
	hash->buffer->ptr += hash->buffer->len;
	hash->buffer->len = 0;
	if (!hash->buffer->is_one_finish)
	{
		*tmp++ = 0x80;
		space -= 1;
		hash->buffer->is_one_finish = 1;
	}
	calculate_chunk_end(hash, space, tmp);
	return (1);
}
