/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:16:36 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/06 19:56:01 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	temp;

	i = 0;
	if (!dst && !(char *)src)
		return (0);
	temp = ft_strlen(src);
	if (!size)
		return (temp);
	while (i + 1 < size && (char)src[i])
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
	return (temp);
}

long long	ft_atol(const char *str)
{
	long long	ret;
	long long	p;

	ret = 0;
	p = 1;
	while (*str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			p *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += (p * (*str - '0'));
		str++;
	}
	return (ret);
}

int	append_node(tlist *Astack, char *buf, size_t size)
{
	long long	ret;
	char	sliced;
	tnode	*newNode;
	
	newNode = NULL;
	ft_strlcpy(&sliced, buf, size);
	if (exception_parsing_string(&sliced))
		return (1);
	else
	{
		ret = ft_atol(&sliced);
		if (exception_parsing_number(ret))
			return (1);
		else
		{
			newNode = create_node((int)ret);
			if (newNode == NULL)
				return (1);
			Astack->tail->prev->next = newNode;
			newNode->prev = Astack->tail->prev;
			newNode->next = Astack->tail;
			Astack->tail->prev = newNode;
			Astack->count++;
		}
	}
	return (0);
}

int	split_to_stack(char **argv, tlist *Astack)
{
	char	*buf;
	char	*s;
	int	i;

	i = 1;
	while (argv[i])
	{
		s = argv[i];
		while (*s)
		{
			if (*s != ' ')
			{
				buf = (char *)s;
				while (*s && *s != ' ')
					s++;
				if (append_node(Astack, buf, s - buf + 1))
					return (1);
			}
			else
				s++;
		}
		i++;
	}
	if (exception_parsing_sort(Astack))
		return (1);
	return (0);
}