/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfdpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:59:26 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/17 14:15:46 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	write_in_pipe(int fdp[2])
{
	write(fdp[1], "a", 1);
	write(fdp[1], "a", 1);
	write(fdp[1], "a", 1);
	write(fdp[1], "a", 1);
	close(fdp[1]);
	close(fdp[0]);

	printf("1:%d\n", fdp[0]);
	return (fdp[0]);
}

int	main(void)
{
	int	fdp[2];
//	int	test;

	pipe(fdp);
//	test = write_in_pipe(fdp);
//	write_in_pipe(fdp);
	printf("1:%d\n", fdp[1]);
	printf("2:%d\n", fdp[0]);

	close(fdp[1]);
	close(fdp[0]);
//	close(test);
	

	return (0);
}
