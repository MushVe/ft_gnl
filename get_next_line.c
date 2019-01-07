/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:45:20 by cseguier          #+#    #+#             */
/*   Updated: 2019/01/07 16:52:04 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static char	*join_free(char *s1, char *s2)
{
	char *line;

	if (!(line = ft_strjoin(s1, s2)))
		return (NULL);
	return (line);
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

	if (!(s = (char*)ft_memalloc((sizeof(*s) * (ft_strlen(src) + 1)))))
		return (0);
	return (strccpy(s, src, c));
}

int			get_next_line(int const fd, char **line)
{
	static char	*s;
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
		s = ft_strdup(1 + ft_strchr(s, '\n'));
	}
	if (0 < lu)
		return (1);
	return (0);
}
