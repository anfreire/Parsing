/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   total_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 07:51:44 by anfreire          #+#    #+#             */
/*   Updated: 2022/10/09 15:10:33 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	trim_spaces(char *str)
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
		tmp = ft_strjoin(ptr, str);
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

static char **string_can_be_parsed(char *string)
{
	char	**dbl_ptr;
	char	*str;
	int		i;
	int		args;
	char	append[2];

	append[0] = 0;
	append[1] = 0;
	trim_spaces(string);
	i = 0;
	args = 1;
	while (string[i])
	{
		if (string[i] == '\"' && ft_strchr(&string[i + 1], '\"') != NULL)
		{
			str = ft_substr(&string[i], 1, (ft_strchr(&string[i + 1], '\"') - &string[i] - 1));
			dbl_ptr = build_list(args, dbl_ptr, str);
			i += ft_strlen(str) + 2;
		}
		else if (string[i] == '\'' && ft_strchr(&string[i + 1], '\'') != NULL)
		{
			str = ft_substr(&string[i], 1, (ft_strchr(&string[i + 1], '\'') - &string[i] - 1));
			dbl_ptr = build_list(args, dbl_ptr, str);
			i += ft_strlen(str) + 2;
			free(str);
		}
		else if (string[i] == ' ')
		{
			args++;
			while (string[i] == ' ')
			{
				string[i] = 6;
				i++;
			}
		}
		else
		{
			append[0] = string[i];
			dbl_ptr = build_list(args, dbl_ptr, append);
			i++;
		}
		
	}
	return (dbl_ptr);
}


int	main()
{
	char	str[] = " \"$123\"    teste1    123 pinto ";
	char	*new_string;
	char	**list;
	
	
	// printf("Before -> |%s|\n", str);
	// trim_spaces(str);
	// printf("After -> |%s|\n", str); //TRIM OK

	// new_string = realloc_string(new_string, str, 0);
	// printf("\n\nBefore -> |%s|\n", new_string);
	// new_string = realloc_string(new_string, str, 1);
	// printf("After -> |%s|\n", new_string);

	list = string_can_be_parsed(str);
	printf("|%s|\n", list[0]);
	printf("|%s|\n", list[1]);
	printf("|%s|\n", list[2]);
	printf("|%s|\n", list[3]);
	// list = build_list(2, list, str);
	// printf("\n\n\n%s", list[1]);
	// list = build_list(2, list, str);
	// printf("\n\n\n%s", list[1]);
	// list = build_list(3, list, str);
	// printf("\n\n\n%s", list[2]);
	

	
}