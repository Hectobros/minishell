/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 20:33:46 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/10 20:53:18 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int fd;

	fd = 0;
	fd = open("./HERE", O_RDWR);
	printf("fd:%d\n", fd);
	fd = open("./HERE", O_RDWR);
	printf("fd:%d\n", fd);
//	close(fd);
	return (0);
}
