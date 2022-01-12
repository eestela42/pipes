/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:20:25 by eestela           #+#    #+#             */
/*   Updated: 2022/01/10 19:20:56 by eestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	free_comm(char **command)
{
	int	i;

	i = 1;
	free(command[0]);
	while (command[i] != 0)
	{
		free(command[i]);
		i++;
	}
	free(command);
}
