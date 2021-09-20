/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_param_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:23:20 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 07:59:28 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_param_name	*init_list_name(t_param_name *new1, t_param_name *new2)
{
	if (!create_new_name(&new1, "R "))
		return (0);
	if (!create_new_name(&new2, "NO "))
		return (free_param_lst(new1));
	new2->next = new1;
	if (!create_new_name(&new1, "SO "))
		return (free_param_lst(new2));
	new1->next = new2;
	if (!create_new_name(&new2, "EA "))
		return (free_param_lst(new1));
	new2->next = new1;
	if (!create_new_name(&new1, "WE "))
		return (free_param_lst(new2));
	new1->next = new2;
	if (!create_new_name(&new2, "S "))
		return (free_param_lst(new1));
	new2->next = new1;
	if (!create_new_name(&new1, "C "))
		return (free_param_lst(new2));
	new1->next = new2;
	if (!create_new_name(&new2, "F "))
		return (free_param_lst(new1));
	new2->next = new1;
	return (new2);
}

t_param_name	*free_param_lst(t_param_name *lst)
{
	t_param_name	*temp1;
	t_param_name	*temp2;

	temp1 = lst;
	while (temp1)
	{
		temp2 = temp1->next;
		free(temp1->name);
		free(temp1);
		temp1 = temp2;
	}
	return (0);
}

int	create_new_name(t_param_name **new, char *str)
{
	int	len;

	*new = malloc(sizeof(t_param_name));
	if (!*new)
		return (0);
	len = ft_len_nl(str, 0) + 1;
	(*new)->name = malloc(sizeof(char) * len);
	if (!((*new)->name))
	{
		free(*new);
		return (0);
	}
	ft_memmove((*new)->name, str, len);
	(*new)->next = 0;
	return (1);
}

/*
	delete_entry_list : If no list, we don't enter in the loop.

	Entering the first if statement is only possible if it's the FIRST node
	of the list that has to be deleted.

	When we delete the only remaining node, it's at the front of the list.
	*lst (map.word_list) is then set to 0.
*/

void	delete_entry_list(t_param_name **lst, char *name)
{
	t_param_name	*temp1;
	t_param_name	*temp2;

	temp1 = *lst;
	while (temp1)
	{
		if (temp1->name == name)
		{
			*lst = temp1->next;
			free(temp1->name);
			free(temp1);
			return ;
		}
		else if (temp1->next->name == name)
		{
			temp2 = temp1->next;
			temp1->next = temp2->next;
			free(temp2->name);
			free(temp2);
			return ;
		}
		else
			temp1 = temp1->next;
	}
}
