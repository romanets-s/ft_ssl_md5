/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:28:20 by sromanet          #+#    #+#             */
/*   Updated: 2018/09/01 15:28:24 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "sha256.h"
#include "ft_ssl.h"

int		error(char *input)
{
	if (input == NULL)
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(input);
		ft_putstr("' is an invalid command.\n");
		ft_putstr("\nStandard commands:\n\n");
		ft_putstr("Message Digest commands:\nmd5\nsha256\n");
		ft_putstr("\nCipher commands:\n");
	}
	return (1);
}

char	*gnl_not_gnl(int fd)
{
	char	buff[2];
	char	*res;
	char	*tmp;

	ft_memset(buff, 0, 2);
	res = ft_strdup("");
	while (read(fd, buff, 1) > 0)
	{
		tmp = res;
		res = ft_strjoin(res, buff);
		free(tmp);
	}
	return (res);
}

t_ssl	*init_ssl(char *func)
{
	t_ssl	*ssl;

	ssl = (t_ssl *)malloc(sizeof(t_ssl));
	ssl->p = 0;
	ssl->q = 0;
	ssl->r = 0;
	ssl->s = 0;
	ssl->one_s_exist = 0;
	ssl->input = NULL;
	ssl->ssl_struct = NULL;
	if (!ft_strcmp(func, "md5"))
	{
		ssl->ssl_init = &init_ft_md5;
		ssl->ssl_func = &ft_md5;
		ssl->func_name = "MD5";
	}
	else
	{
		ssl->ssl_init = &init_ft_sha256;
		ssl->ssl_func = &ft_sha256;
		ssl->func_name = "SHA256";
	}
	return (ssl);
}

int		main(int c, char **v)
{
	if (c < 2)
		return (error(NULL));
	else if (!ft_strcmp(v[1], "md5") || !ft_strcmp(v[1], "sha256"))
		get_input(c, v);
	else
		return (error(v[1]));
	return (0);
}
