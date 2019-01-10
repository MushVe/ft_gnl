/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:45:20 by cseguier          #+#    #+#             */
/*   Updated: 2019/01/10 18:08:11 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static char	*join_free(char *s1, char *s2)
{
	int		i;
	char	*res;
	int		t1;
	int		t2;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	t1 = ft_strlen(s1);
	t2 = ft_strlen(s2);
	if (!(res = (char*)ft_memalloc(sizeof(char) * (t1 + t2 + 1))))
		return (0);
	while (i < t1)
	{
		res[i] = s1[i];
		i++;
	}
//	if (t1 > 0)
//		free(s1);
	while (i < t1 + t2)
	{
		res[i] = s2[i - t1];
		i++;
	}
//	if (t2 > 0)
//		free(s2);
	res[i] = '\0';
	return (res);
}

static char	*strccpy(char *dest, char const *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*strcdup(char const *src, char c)
{
	char	*s;
	char	*res;

	if (!(s = (char*)ft_memalloc((sizeof(*s) * (ft_strlen(src) + 1)))))
		return (0);
	res = strccpy(s, src, c);
	return (res);
}

int			get_next_line(int const fd, char **line)
{
	static char	*s;
	char		*tmp;
	char		buff[BUFF_SIZE + 1];
	size_t		lu;

	if (fd < 0)
		return (-1);
	if (s == NULL)
		s = "\0";
	lu = 1;
	while (!(ft_strchr(s, '\n')) && lu > 0)
	{
		lu = read(fd, buff, BUFF_SIZE);
		buff[BUFF_SIZE] = '\0';
		if (!(s = join_free(s, buff)))
			return (-1);
	}
	if (lu != 0)
	{
		*line = strcdup(s, '\n');
		tmp = ft_strdup(1 + ft_strchr(s, '\n'));
		free(s);
		s = tmp;
//		free(tmp);
		tmp = NULL;

	}
	if (0 < lu)
		return (1);
	return (0);
}
