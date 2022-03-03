/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:25:46 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/03 21:19:46 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	int idx;
	long long	*arr;
	tlist *Astack;
	tlist *Bstack;
	tcommand *command;

	Astack = NULL;
	Bstack = NULL;
	idx = count_idx(argv);
	arr = parsing(argc, argv, idx);
	initList(Astack);
	initList(Bstack);
	initNode(Astack, arr, idx);
	initCommand(command);
	if (Astack->count <= 3)
		simple_sort(Astack, Bstack);
	else
		sort(Astack, Bstack, command);
	return (0);
}
