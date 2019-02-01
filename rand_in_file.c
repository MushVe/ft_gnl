/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enfer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 09:21:51 by cseguier          #+#    #+#             */
/*   Updated: 2019/02/01 09:37:22 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft/libft.h"

int main(int ac, char **av)
{
	(void)ac;
	int size = 1000000;
	char mdr[1000000] = { 0 };
	int fd = open(av[1], O_WRONLY);

	for (int i = 0; i < size; i++)
	{
		mdr[i] = (rand() % 126) + 1;
	}
		write(fd, mdr, size);

	return 0;
}
