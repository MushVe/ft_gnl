/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:38:31 by cseguier          #+#    #+#             */
/*   Updated: 2019/02/08 10:02:54 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static char		*join_free(char *s, char *buff)
{
	int		i;
	char	*res;
	int		ts;
	int		tbuff;

	i = -1;
	if (!s || !buff)
		return (NULL);
	ts = ft_strlen(s);
	tbuff = ft_strlen(buff);
	if (!(res = (char*)ft_memalloc(sizeof(char) * (ts + tbuff + 1))))
		return (0);
	while (++i < ts)
		res[i] = s[i];
	while (i < ts + tbuff)
	{
		res[i] = buff[i - ts];
		i++;
	}
	res[i] = '\0';
	if (*s)
		ft_memdel((void*)&s);
	return (res);
}

static char		*strc_dup_cpy(char const *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char*)ft_memalloc((sizeof(char) * (ft_strlen(src) + 1)))))
		return (0);
	while (src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int		copyinline(char **line, char **s)
{
	char	*tmp;

	tmp = "\0";
	if (ft_strchr(*s, '\n'))
	{
		if (!(*line = strc_dup_cpy(*s, '\n')))
			return (0);
		if (!(tmp = ft_strdup(1 + ft_strchr(*s, '\n'))))
			return (0);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
			return (0);
	}
	free(*s);
	*s = tmp;
	return (1);
}

static ssize_t	readfile(char **s, char **line, int fd, char *buff)
{
	ssize_t	lu;

	ft_memset(buff, 0, BUFF_SIZE + 1);
	lu = 1;
	while (0 < (lu = read(fd, buff, BUFF_SIZE)))
	{
		if (!(*s = join_free(*s, buff)))
			return (-1);
		ft_memset(buff, 0, BUFF_SIZE + 1);
	}
	if (lu == -1)
		return (-1);
	if (**s)
	{
		if (!copyinline(line, s))
			return (-1);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char	*s;
	char		buff[BUFF_SIZE + 1];
	ssize_t		lu;

	if (fd < 0 || !line)
		return (-1);
	if (s == NULL)
		s = "\0";
	lu = readfile(&s, line, fd, buff);
	if (lu > 0)
		return (1);
	if (lu < 0)
		return (-1);
	return (0);
}
