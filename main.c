/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:36:39 by cseguier          #+#    #+#             */
/*   Updated: 2019/01/15 15:27:00 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft/libft.h"

int main(int ac, char **av)
{
	(void)ac;
	char *line;
	int i = 1;
	int fd = open(av[1], O_RDONLY);
	while (i == 1)
	{
		i = get_next_line(fd, &line);
				ft_putnbr(i);
		//		ft_putstr("\n");
		if (!i)
			break;
		ft_putstr(line);
		ft_putstr("\n");
	}
	return 0;
}
