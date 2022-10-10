/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 07:51:44 by anfreire          #+#    #+#             */
/*   Updated: 2022/10/10 17:36:14 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	trim_spaces(char *str) //removes spaces from beggining and end of str
{
	int	i;
	
	if (str[0] == ' ')
	{
		while (str[0] == ' ')
		{
			ft_memmove(&str[0], &str[1], ft_strlen(str));
		}
	}
	i = ft_strlen(str)- 1;
	if (str[i] == ' ')
	{
		while (str[i] == ' ')
		{
			str[i] = 0;
			i--;
		}
	}	
}

int	is_str_in_quotes(char *str, char c)// Returns 1 if index is a char as another occurence of the same char after
{
	if (str[0] == c && ft_strchr(&str[1], c) != NULL)
		return (1);
	else
		return (0);
}

char	*is_string_expandable(char *str)
{
	int	i;
	char	*it_is;

	it_is = malloc(sizeof(char) * 7);
	it_is[0] = 'L';
	it_is[1] = 'O';
	it_is[2] = 0;

	i = 0;
	if (str[0] == '$')
	{
		free(str);
		return (it_is);
	}
	else
		return (str);
	
}