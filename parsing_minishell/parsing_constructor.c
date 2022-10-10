/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_constructor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:31:52 by anfreire          #+#    #+#             */
/*   Updated: 2022/10/10 17:35:09 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*realloc_string(char *ptr, char *str, int flag) //ALLOCS OR APPENDS     ==    FLAG=0 -> ALLOCS  ||  FLAG=1 -> APPENDS
{
	char	*tmp;

	if (flag == 0)
	{
		ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
		ft_strlcpy(ptr, str, ft_strlen(str) + 1);
	}
	else
	{
		tmp = malloc(sizeof(char) * (ft_strlen(ptr) + ft_strlen(str) + 1));
		ft_strlcpy(tmp, ptr, ft_strlen(ptr) + 1);
		ft_strlcat(tmp, str, ft_strlen(str) + ft_strlen(ptr) + 1);
		free(ptr);
		ptr = tmp;
	}
	return (ptr);
	
}

char	**realloc_list(char **ptr, int len) //ALLOCS OR APPENDS STRINGS TO LIST
{											//LEN -> lenght of string. if len=1 -> Allocs  ||  len > 1 -> appends
	char	**tmp;
	int		i;
	
	if (len == 1)
	{
		ptr = malloc(sizeof(char *) + 1);
	}
	else
	{
		tmp = malloc(sizeof(char *) * (len + 1));
		i = -1;
		while (ptr[++i])
		{
			tmp[i] = malloc(sizeof(char) * ft_strlen(ptr[i]) + 1);
			ft_strlcpy(tmp[i], ptr[i], ft_strlen(ptr[i]) + 1);
			free(ptr[i]);
		}
		free(ptr);
		ptr = tmp;
	}
	return (ptr);
}

char	**build_list(int len, char **ptr, char *str)
{
	static int	i = 0;
	
	if (i == len - 1)
	{
		ptr = realloc_list(ptr, len);
		ptr[i] = realloc_string(ptr[i], str, 0);
		i++;
	}
	else
		ptr[len - 1] = realloc_string(ptr[len - 1], str, 1);

	return (ptr);
}