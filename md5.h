#ifndef MD5_H
#define MD5_H

typedef	struct	s_md5
{
	size_t				new_len;
	unsigned short int	hash0;
	unsigned short int	hash1;
	unsigned short int	hash2;
	unsigned short int	hash3;
	unsigned char		*res;
	size_t				offset;
	unsigned short int *r;
	unsigned short int *k;
	unsigned short int	h0;
	unsigned short int	h1;
	unsigned short int	h2;
	unsigned short int	h3;
	unsigned short int	a;
	unsigned short int	b;
}				t_md5;

#endif