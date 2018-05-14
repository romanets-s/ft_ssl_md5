#include "md5.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


size_t	new_len(size_t len)
{
	size_t new;
	
	new = len * 8 + 1;
	while (new % 512 != 448)
		new++;
	new /= 8;
	return (new);
}

void	init_struct(t_md5 *hash)
{
	hash->r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
				4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
				6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	
	hash->k[] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
}

 #define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

t_md5 *init_ft_md5(char *input, size_t len)
{
	t_md5				*hash;
	unsigned short int	tmp;
	
	hash = (t_md5 *)malloc(sizeof(t_md5 *) * 1);
	hash->hash0 = 0x67452301;
	hash->hash1 = 0xefcdab89;
	hash->hash2 = 0x98badcfe;
	hash->hash3 = 0x10325476;
	hash->h0 = 0;
	hash->h1 = 0;
	hash->h2 = 0;
	hash->h3 = 0;
	hash->a = 0;
	hash->b = 0;
	hash->new_len = new_len(len);
	hash->res = (unsigned char *)malloc(sizeof(unsigned char *) * (hash->new_len + 64));
	hash->res = ft_memset(hash->res, 0, hash->new_len + 64);
	ft_memcpy(hash->res, input, len);
	hash->res[hash->len] = 128;
	tmp = 8 * len;
	ft_memcpy(hash->res + hash->new_len, &tmp, 4);
	hash->offset = 0;
	init_struct(hash);
	return (hash);
}

void ft_md5(t_md5 *hash, int i)
{
	unsigned short int *ptr;
	unsigned short int tmp;
		
	while (hash->offset < hash->new_len)
	{
		ptr = (unsigned short int *)(hash->res + offset);
		hash->h0 = hash->hash0;
		hash->h1 = hash->hash1;
		hash->h2 = hash->hash2;
		hash->h3 = hash->hash3;
		i = -1;
		while (++i < 64)
		{
			if (i < 16)
			{
				hash->a = (hash->h1 & hash->h2) | ((~hash->h1) & hash->h3);
				hash->b = i;
			}
			else if (i < 32)
			{
				hash->a = (hash->h3 & hash->h1) | ((~hash->h3) & hash->h2);
				hash->b = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				hash->a = hash->h1 ^ hash->h2 ^ hash->h3;
				hash->b = (3 * i + 5) % 16;
			}
			else
			{
				hash->a = hash->h3 ^ (hash->h1 | (~hash->h3));
				hash->b = (7 * i) % 16;
			}
			tmp = hash->h3;
			hash->h3 = hash->h2;
			hash->h2 = hash->h1;
			hash->h1 = hash->h1 + LEFTROTATE((hash->h0 + hash->a + hash->k[i] + hash->w[g]), hash->r[i]);
			hash->h0 = tmp;
			
		}
		hash->offset++;
		hash->hash0 += hash->h0;
		hash->hash1 += hash->h1;
		hash->hash2 += hash->h2;
		hash->hash3 += hash->h3;
	}

	
	
	uint8_t *p;
     // display result
    p=(uint8_t *)&hash->hash0;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], hash->hash0);
 
    p=(uint8_t *)&hash->hash1;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], hash->hash1);
 
    p=(uint8_t *)&hash->hash2;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], hash->hash2);
 
    p=(uint8_t *)&hash->hash3;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], hash->hash3);
	
}