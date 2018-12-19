/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:39:40 by cseguier          #+#    #+#             */
/*   Updated: 2018/12/19 17:09:13 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <sys/stat.h>
#include <fcntl.h>

static char	*join_free(char *s1, char *s2)
{
	char *line;
	
	if (!(line = ft_strjoin(s1, s2)))
		return (NULL);
//	free(s1);
//	free(s2);
	return (line);
}

int	get_next_line(int const fd, char **line)
{
	static char	*s;
	char		buff[BUFF_SIZE + 1];
	size_t		lu;

	if (fd < 0)
		return (-1);
	if (s == NULL)
		s = "\0";
	lu = 1;
//	ft_putnbr(101);		ft_putstr("\n");
	while (!(ft_strchr(s, '\n')) && lu > 0)
	{
//		ft_putnbr(202);		ft_putstr("\n");
		lu = read(fd, buff, BUFF_SIZE);
//		ft_putstr("\n");
//		ft_putnstr(buff, BUFF_SIZE);
//		ft_putstr("\n");
//		ft_putnbr(303);		ft_putstr("\n");
		buff[BUFF_SIZE] = '\0';
		if (!(s = join_free(s, buff)))
			return (-1);
//		ft_putstr(s);		ft_putstr("\n");
	}
//	ft_putnbr(404);		ft_putstr("\n");
//	ft_putstr(s);		ft_putstr("\n");

	if (lu != 0)
	{
		*line = ft_strcdup(s, '\n');
		s = ft_strdup(1 + ft_strchr(s, '\n'));
	}
		//	ft_putnbr(808);		ft_putstr("\n");
//	ft_putstr(*line);
//	ft_putnbr(707);		ft_putstr("\n");
	if (lu > 0)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	char *line;
	int i = 1;
	int fd = open(av[1], O_RDONLY);
//	ft_putstr("  +++ Pulogulam Sutaato +++  \n");
	while (i == 1)
	{
		i = get_next_line(fd, &line);
		ft_putnbr(i);
		//ft_putstr("\n");
//		ft_putnbr(606);		ft_putstr("\n");
		ft_putstr(line);		ft_putstr("\n");
	}
//	ft_putstr("\n  +++ Pulogulam Endo +++  \n");

	return 0;
}
