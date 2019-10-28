/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:45:14 by akhossan          #+#    #+#             */
/*   Updated: 2019/10/28 20:45:18 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#define MISSMATCH_ERROR	write(1, "brackets missmatch!\n", 20)
#define BRACKETS_MATCH	write(1, "brackets match!\n", 16)

typedef struct		s_stack
{
	char			c;
	struct s_stack	*next;
}					t_stack;

int		push(t_stack	**stack, char c)
{
	t_stack		*elem;

	if (!*stack)
	{
		if (!(*stack = (t_stack*)malloc(sizeof(t_stack))))
			return (0);
		(*stack)->c = c;
		(*stack)->next = NULL;
		return (1);
	}
	if (!(elem = (t_stack*)malloc(sizeof(t_stack))))
		return (0);
	elem->c = c;
	elem->next = *stack;
	*stack = elem;
	return (1);
}

char	pop(t_stack **stack)
{
	char	top;
	t_stack	*tmp;
	
	if (!*stack)
		return (0);
	top = (*stack)->c;		
	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	return (top);
}

void	free_mismatch(t_stack **stack)
{
	t_stack		*tmp;

	while (*stack)
	{
		tmp = (*stack);
		*stack = (*stack)->next;
		free(tmp);
	}
	*stack = NULL;
	write(1, "KO\n", 3);
}

int		main(int ac, char **av)
{
	char	*s;
	int		i;
	int		j;
	char	br;
	t_stack	*stack;
	int		flg;

	if (ac < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	stack = NULL;
	s = av[1];	
	j = 0;
	while (av[++j])
	{
		flg = 0;
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] == '[' || av[j][i] == '{' || av[j][i] == '(')
				push(&stack, av[j][i]);
			else if (av[j][i] == ']' || av[j][i] == '}' || av[j][i] == ')')
				if (!(br = pop(&stack)) || (br == '[' && av[j][i] != ']')\
					|| (br == '{' && av[j][i] != '}') || (br == '(' && av[j][i] != ')'))
				{
					flg = 1;
					free_mismatch(&stack);
					break ;
				}
			i++;
		}
		if (!flg)
		{
			if (stack)
			{
				write(1, "KO\n", 3);	
				free(stack);
			}
			else
				write(1, "OK\n", 3);	
		}
	}
	return (0);
}
