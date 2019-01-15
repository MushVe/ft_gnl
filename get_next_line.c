/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:45:20 by cseguier          #+#    #+#             */
/*   Updated: 2019/01/15 16:04:18 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static char		*join_free(char *s1, char *s2)
{
	int		i;
	char	*res;
	int		t1;
	int		t2;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	t1 = ft_strlen(s1);
	t2 = ft_strlen(s2);
	if (!(res = (char*)ft_memalloc(sizeof(char) * (t1 + t2 + 1))))
		return (0);
	while (++i < t1)
		res[i] = s1[i];
	while (i < t1 + t2)
	{
		res[i] = s2[i - t1];
		i++;
	}
	res[i] = '\0';
	if (s1)
		free(s1);
	return (res);
}

static char		*strc_dup_cpy(char *dest, char const *src, char c, int id)
{
	int		i;
	char	*s;
	char	*res;

	if (id == 1)
	{
		i = 0;
		while (src[i] != c)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
	if (id == 2)
	{
		if (!(s = (char*)ft_memalloc((sizeof(char) * (ft_strlen(src) + 1)))))
			return (0);
		res = strc_dup_cpy(s, src, c, 1);
		return (res);
	}
	return (NULL);
}

static int		norme2(char **line, char **s)
{
	char	*tmp;

	if (!(*line = strc_dup_cpy(NULL, *s, '\n', 2)))
		return (-1);
	if (!(tmp = ft_strdup(1 + ft_strchr(*s, '\n'))))
		return (-1);
	free(*s);
	*s = tmp;
	tmp = NULL;
	return (1);
}

static ssize_t	norme(char **s, char **line, int fd, char *buff)
{
	ssize_t	lu;

	lu = 1;
	while (!(ft_strchr(*s, '\n')) && lu > 0)
	{
		lu = read(fd, buff, BUFF_SIZE);
		buff[BUFF_SIZE] = '\0';
		if (!(*s = join_free(*s, buff)))
			return (-1);
		ft_memset(buff, 0, BUFF_SIZE);
	}
	if (lu != 0)
	{
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		if (!norme2(line, s))
			return (-1);
	}
	return (lu);
}

int				get_next_line(int const fd, char **line)
{
	static char	**s;
	char		buff[BUFF_SIZE + 1];
	ssize_t		lu;

	if (fd < 0)
		return (-1);
	if (s == NULL)
	{
		if (!(s = (char**)ft_memalloc((sizeof(char*) * 1))))
			return (-1);
		if (!(*s = (char*)ft_memalloc((sizeof(char) * 1))))
			return (-1);
	}
	lu = norme(s, line, fd, buff);
	if (lu > 0)
		return (1);
	if (lu < -1)
		return (-1);
	free(*s);
	free(s);
	free(*line);
	return (0);
}
