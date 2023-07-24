/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadzic <ahadzic@42.tr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:27:01 by ahadzic           #+#    #+#             */
/*   Updated: 2022/10/31 17:27:07 by ahadzic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(char *str)
{
	int	sign;
	int	number;

	number = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		number = *str - '0' + (number * 10);
		str++;
	}
	return (sign * number);
}

void	send_binary(int pid, unsigned char c)
{
	int	binary[8];
	int	i;

	i = 0;
	while (i < 8)
	{
		binary[i] = 0;
		i++;
	}
	while (i-- > 0)
	{
		if (c % 2 == 0)
			binary[i] = 0;
		else if (c % 2 == 1)
			binary[i] = 1;
		c /= 2;
	}
	while (i++ < 8)
	{
		if (binary[i] == 0)
			kill(pid, SIGUSR1);
		else if (binary[i] == 1)
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid < 1)
			return (1);
		while (argv[2][i] != '\0')
		{
			send_binary(pid, argv[2][i++]);
		}
	}
	return (0);
}
