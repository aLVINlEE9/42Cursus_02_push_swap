/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:44:23 by seungsle          #+#    #+#             */
/*   Updated: 2021/12/31 14:34:39 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	count_idx(char **argv)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
				count++;
			j++;
		}
		count++;
		i++;
	}
	return (count);
}

void	get_arr(char **splited_char, long long *arr)
{
	int i;
	char *buf;
	long long num;

	i = 0;
	while (splited_char[i])
	{
		buf = splited_char[i];
		if (exception_checker_1(buf))
			free_and_exit(splited_char, arr);
		num = ft_atoi(buf);
		if (exception_checker_2(num))
			free_and_exit(splited_char, arr);
		arr[i++] = num;
	}
	return ;
}

long long	*parsing(char **argv)
{
	char		**splited_char;
	long long	*arr;
	int			idx;

	idx = count_idx(argv);
	splited_char = (char **)malloc(sizeof(char *) * (idx + 1));
	arr = (long long *)malloc(sizeof(long) * idx);
	if (!arr || !splited_char)
		exit (1);
	ft_split(argv, splited_char, 0, 1);
	get_arr(splited_char, arr);
	if (exception_checker_3(arr, idx))
		free_and_exit(splited_char, arr);
	free_splited_char(splited_char);
	for(int i = 0; i < idx; i++)
	{
		printf("%lld\n", arr[i]);
	}
	return (arr);
}
