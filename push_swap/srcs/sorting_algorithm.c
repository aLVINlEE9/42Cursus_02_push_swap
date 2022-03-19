/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:07:59 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/19 21:29:31 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	merge_best_actions(t_datas *datas)
{
	t_list				*a_stack;
	t_list				*b_stack;

	a_stack = datas->a_stack;
	b_stack = datas->b_stack;
	datas->b_acts.a[1] = a_stack->count - datas->b_acts.a[0];
	datas->b_acts.b[1] = b_stack->count - datas->b_acts.b[0];
	merge_best_actions_sub(datas, 0, 0);
	merge_best_actions_sub(datas, 0, 1);
	merge_best_actions_sub(datas, 1, 0);
	merge_best_actions_sub(datas, 1, 1);
}

/*
Function Explanation (choose_best_actinos)

	parameter : (int)`DATA` == a_stack top(7)
				`B_STACK->MIN` == min vlaue from b_stack(2)
				tmp == temporaray value to find max value
	
	1. while -> case 1) count max value from top of b_stack
	
					{`B_STACK->MIN` > `DATA`} : If this condition is true, 
					It means the `DATA` from a_stack is minimum value 
					compare with b_stack
					-> It just need to sort descending order
					{now->data >= tmp} : just sort b_stack descending order
					
					
				case 2) count the right place (which `DATA` is going to be)
						from top of b_stack
					
					{`B_STACK->MIN` < `DATA`} : If this condition is true,
					It means there's value that is less than `DATA` from a_stack
					-> It need to find the number that is less than `DATA` but 
					biggest number of them
					{now->data >= tmp} : This condition is to find biggest number
					{now->data < `DATA`} : This condition is to limit the biggest
					number to not over the `DATA`

		-------------------------
		|			|			|
		|			|			|
		|	*	7	|			|
		|		3	|			|
		|		5	|		2	|
		|			|		9	|
		|	a_stack	|	b_stack	|
		--------------------------	pb
		-------------------------
		|			|			|
		|			|			|
		|			|			|
		|	*	3	|		7	|
		|		5	|		2	|
		|			|		9	|
		|	a_stack	|	b_stack	|
		-------------------------- rb - pb
		-------------------------
		|			|			|
		|			|			|
		|			|		3	|
		|			|		2	|
		|	*	5	|		9	|
		|			|		7	|
		|	a_stack	|	b_stack	|
		-------------------------- pb
	
	2. merge_best_actions : compare all available commands and make it most 
							efficient way
*/

void	choose_best_actions_sub(t_datas *datas, int data)
{
	t_node			*now;
	int				tmp;
	int				i;

	now = datas->b_stack->head->next;
	tmp = INT_MIN;
	i = 0;
	while (now != datas->b_stack->tail && ++i)
	{
		if (datas->b_stack->min > data && now->data >= tmp)
		{
			tmp = now->data;
			datas->b_acts.b[0] = i - 1;
		}
		if (datas->b_stack->min < data && now->data >= tmp && now->data < data)
		{
			tmp = now->data;
			datas->b_acts.b[0] = i - 1;
		}
		now = now->next;
	}
	merge_best_actions(datas);
}

/*
Function Explanation (choose_best_actinos)

	1. set_min_value : get min number in b_stack (It will be 2)
	2. while -> count all command(ra, rra) to each all numbers in a_stack 
		that makes to top for PB

		-------------------------
		|			|			|
		|			|			|
		|	*	7	|			|
		|		3	|			|
		|		5	|		2	|
		|			|		9	|
		|	a_stack	|	b_stack	|
		--------------------------

		(if now->data is 7 then RA is gonna be 0 times, also RRA is gonna be 3 times)
		
		a. save RA RRA count temporary in t_best_actions struct

		b. choose_best_actions_sub : count command(rb, rrb) from b_stack
*/

void	choose_best_actions(t_datas *datas)
{
	t_list			*a_stack;
	t_node			*now;
	int				cnt;

	a_stack = datas->a_stack;
	now = a_stack->head->next;
	cnt = -1;
	set_min_value(datas->b_stack);
	while (++cnt < a_stack->count)
	{
		datas->b_acts.a[0] = cnt;
		choose_best_actions_sub(datas, now->data);
		now = now->next;
	}
}

/*
Function Explanation (insertion_sort)

	1. set_max_array : get 3 max numbers in a_stack
	2. PB 2 times : move two top numbers(9, 2) in a_stack to b_stack

		-------------------------
		|			|			|
		|			|			|
		|		7	|			|
		|		3	|		2	|
		|		5	|		9	|
		|			|			|
		|	a_stack	|	b_stack	|
		--------------------------

	3. choose_best_actions : best actions make least time complexity
	
	(If RA is like 3 times and RB is like 4 times, it's totally 7 times but
	if you use this function then it merge commands effiectly and the result
	will be totally 4 times(better than 7) cause {RA 3 RB 3} -> RR 3, RB 1)
*/

void	insertion_sort(t_datas *datas)
{
	t_list	*a_stack;

	a_stack = datas->a_stack;
	action_exe(datas, "pb", 2);
	while (a_stack->count)
	{
		init_datas(datas);
		choose_best_actions(datas);
		exe_best_actions(datas);
		action_exe(datas, "pb", 1);
	}
}

/*
There's two stack in this sorting algorithm
		-------------------------
		|		9	|			|
		|		2	|			|
		|		7	|			|
		|		3	|			|
		|		5	|			|
		|			|			|
		|	a_stack	|	b_stack	|
		--------------------------
	using b_stack to sort numbers
*/

void	sorting_algorithm(t_datas *datas)
{
	t_list	*a_stack;

	a_stack = datas->a_stack;
	if (a_stack->count == 2)
		sort_2(datas);
	else if (a_stack->count == 3)
		sort_3(datas);
	else if (a_stack->count > 3)
		insertion_sort(datas);
	print_node(datas->a_stack);
	printf("\\\\\\\\\\\\\\\\");
	print_node(datas->b_stack);
}
