/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadzic <ahadzic@42.tr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:27:46 by ahadzic           #+#    #+#             */
/*   Updated: 2022/10/31 17:27:51 by ahadzic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	print_pid(void)
{
	int		pid;
	int		i;
	char	a[11];

	i = 0;
	pid = getpid();
	if (pid == 0)
		write(1, "0", 1);
	while (pid > 0)
	{
		a[i++] = pid % 10;
		pid /= 10;
	}
	while (i >= 1)
	{
		pid = a[i-- - 1] + 48;
		write(1, &pid, 1);
	}
	write(1, "\n", 1);
}

void	print_binary(int signum)
{
	static int	prnt = 0;
	static int	digit = 0;

	prnt *= 2;
	if (signum == SIGUSR1)
		digit++;
	if (signum == SIGUSR2)
	{
		prnt += 1;
		digit++;
	}
	if (digit == 8)
	{
		write(1, &prnt, 1);
		prnt = 0;
		digit = 0;
	}
}

int	main(void)
{
	print_pid();
	signal(SIGUSR1, print_binary);
	signal(SIGUSR2, print_binary);
	while (1)
	{
		pause();
	}
}
