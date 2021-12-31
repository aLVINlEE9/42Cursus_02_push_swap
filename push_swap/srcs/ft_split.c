/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:28:00 by seungsle          #+#    #+#             */
/*   Updated: 2021/12/31 13:51:55 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_malloc_error(char **ret)
{
	int		i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return ;
}

int	ft_idx(char *buf, char c)
{
	int		idx;
	char	*tmp;

	idx = 0;
	while (1)
	{
		if (!*buf)
			break ;
		if (*buf == c)
		{
			buf++;
			continue ;
		}
		tmp = ft_strchr(buf, c);
		if (!(tmp))
		{
			while (*buf++)
				;
			idx++;
			break ;
		}
		idx++;
		buf = tmp + 1;
	}
	return (idx);
}

void	ft_split(char **argv, char **ret, int idx, int i)
{
	char	*buf;
	char	*s;

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
				ret[idx] = (char *)malloc(sizeof(char) * (s - buf + 1) + 1);
				if (!ret[idx])
					return (ft_malloc_error(ret));
				ft_strlcpy(ret[idx++], buf, (s - buf + 1));
			}
			else
				s++;
		}
		i++;
	}
	return ;
}
