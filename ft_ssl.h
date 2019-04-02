/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:06:51 by sromanet          #+#    #+#             */
/*   Updated: 2018/10/21 20:06:54 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include <fcntl.h>
# include "libft/libft.h"
# include "sha256.h"
# include "md5.h"

typedef	struct	s_ssl
{
	void	*ssl_struct;
	char	*input;
	void	*(*ssl_init)(char *input, size_t len);
	void	(*ssl_func)(void *ssl);
	int		p;
	int		q;
	int		r;
	int		s;
	char	*file_name;
	char	*func_name;
	int		one_s_exist;
}				t_ssl;

int				error(char *input);
char			*gnl_not_gnl(int fd);
t_ssl			*init_ssl(char *func);
void			pre_start(t_ssl *ssl);
void			check_result(t_ssl *ssl);
int				read_file(t_ssl *ssl, int i, int c, char **v);
void			check_flag(int c, char **v, t_ssl *ssl);
void			get_input(int c, char **v);

#endif
