/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:16:19 by sromanet          #+#    #+#             */
/*   Updated: 2019/01/26 18:16:23 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	pre_start(t_ssl *ssl)
{
	if (!ssl->input)
		ssl->input = gnl_not_gnl(0);
	ssl->ssl_struct = ssl->ssl_init(ssl->input, ft_strlen(ssl->input));
	if (ssl->p && ft_strlen(ssl->input) && !ssl->s)
		ft_putstr(ssl->input);
	else if (ssl->s && !ssl->r && !ssl->q)
	{
		ft_putstr(ssl->func_name);
		ft_putstr(" (");
		if (ssl->file_name)
			ft_putstr(ssl->file_name);
		else
		{
			ft_putstr("\"");
			ft_putstr(ssl->input);
			ft_putstr("\"");
		}
		ft_putstr(") = ");
	}
}

void	check_result(t_ssl *ssl)
{
	pre_start(ssl);
	ssl->ssl_func(ssl->ssl_struct);
	if (ssl->s && ssl->r && !ssl->q)
	{
		ft_putstr(" ");
		if (ssl->file_name)
			ft_putstr(ssl->file_name);
		else
		{
			ft_putstr("\"");
			ft_putstr(ssl->input);
			ft_putstr("\"");
		}
	}
	ft_putstr("\n");
	ft_strdel(&ssl->input);
}

int		read_file(t_ssl *ssl, int i, int c, char **v)
{
	int fd;

	ssl->file_name = NULL;
	if (ssl->s || i == c - 1 || ssl->one_s_exist)
	{
		if ((fd = open(v[i], O_RDONLY)) < 0 && !ssl->s)
		{
			ft_putstr("./ft_ssl: ");
			ft_putstr(v[i]);
			ft_putstr(" : No such file or directory\n");
			return (1);
		}
		if (fd > 0)
		{
			ssl->input = gnl_not_gnl(fd);
			close(fd);
			ssl->file_name = v[i];
		}
		else
			ssl->input = ft_strdup(v[i]);
	}
	else
		ssl->input = gnl_not_gnl(0);
	ssl->s = 1;
	return (0);
}

void	check_flag(int c, char **v, t_ssl *ssl)
{
	int	i;

	i = 1;
	if (i + 1 == c)
	{
		check_result(ssl);
		i++;
	}
	while (++i < c)
	{
		if (!ft_strcmp(v[i], "-q"))
			ssl->q = 1;
		else if (!ft_strcmp(v[i], "-r"))
			ssl->r = 1;
		else if (!ft_strcmp(v[i], "-p"))
			ssl->p = 1;
		else
			break ;
	}
	if (i == c)
		check_result(ssl);
}

void	get_input(int c, char **v)
{
	t_ssl	*ssl;
	int		i;

	ssl = init_ssl(v[1]);
	check_flag(c, v, ssl);
	i = 1;
	while (++i < c)
	{
		ssl->s = 0;
		if (!ft_strcmp(v[i], "-p"))
			ssl->p = 1;
		else if (!ft_strcmp(v[i], "-r") || !ft_strcmp(v[i], "-q"))
			continue ;
		else if (!ft_strcmp(v[i], "-s") && !ssl->one_s_exist)
		{
			ssl->one_s_exist = 1;
			ssl->s = 1;
			if (read_file(ssl, ++i, c, v))
				continue ;
		}
		else if (read_file(ssl, i, c, v))
			continue;
		check_result(ssl);
	}
}
