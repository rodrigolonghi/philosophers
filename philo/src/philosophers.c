/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:13:56 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/08 22:51:28 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

static int	is_valid_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (FALSE);
		j = 0;
		while (argv[i][j] && ft_atoi(argv[i]) == 0)
		{
			if (!ft_isdigit(argv[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		printf("To few arguments!\n");
	else if (argc > 6)
		printf("To many arguments!\n");
	else if (!is_valid_arguments(argv))
		printf("Invalid arguments!\n");
	else if (argv)
		printf("Hello philosophers!\n");
	return (0);
}
