/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:30:44 by anfreire          #+#    #+#             */
/*   Updated: 2022/10/10 18:06:03 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	parse_double_quotes(char ***dbl_ptr, char *line, int args)
{
	int		i;
	char	*str;

	str = ft_substr(line, 1, (ft_strchr(&line[1], '\"') - line - 1));
	i = ft_strlen(str) + 2;
	str = is_string_expandable(str);
	*dbl_ptr = build_list(args, *dbl_ptr, str);
	free(str);
	return (i);
}

static int	parse_single_quotes(char ***dbl_ptr, char *line, int args)
{
	int		i;
	char	*str;

	str = ft_substr(line, 1, (ft_strchr(&line[1], '\'') - line - 1));
	i = ft_strlen(str) + 2;
	*dbl_ptr = build_list(args, *dbl_ptr, str);
	free(str);
	return (i);
}

static int	parse_chars(char ***dbl_ptr, char *line, int args)
{
	int		i;
	int		flag;
	char	append[2];
	char	*str;

	append[0] = 0;
	append[1] = 0;
	flag = 0;
	i = 0;
	while (line[i] != ' ' && !is_str_in_quotes(&line[i], '\'') && !is_str_in_quotes(&line[i], '\"') && line[i] != 0)
	{
		append[0] = line[i];
		str = realloc_string(str, append, flag);
		flag = 1;
		i++;
	}
	str = is_string_expandable(str);
	*dbl_ptr = build_list(args, *dbl_ptr, str);
	free(str);
	return (i);
}

char	**parse_line(char *line)
{
	int		i;
	int		args;
	char	*str;
	char	**dbl_ptr;

	trim_spaces(line);
	i = 0;
	args = 1;
	while (line[i])
	{
		if (is_str_in_quotes(&line[i], '\"'))
			i += parse_double_quotes(&dbl_ptr, &line[i], args);
		else if (is_str_in_quotes(&line[i], '\''))
			i += parse_single_quotes(&dbl_ptr, &line[i], args);
		else if (line[i] == ' ')
		{
			args++;
			while (line[i] == ' ')
				i++;
		}
		else
			i += parse_chars(&dbl_ptr, &line[i], args);
	}
	return (dbl_ptr);
}


int	main()
{
	char	str[] = " $into2defde\"pedro\" \'teste\' ";
	char	*new_line;
	char	**list;
	
	
	// printf("Before -> |%s|\n", str);
	// trim_spaces(str);
	// printf("After -> |%s|\n", str); //TRIM OK

	// new_line = realloc_line(new_line, str, 0);
	// printf("\n\nBefore -> |%s|\n", new_line);
	// new_line = realloc_line(new_line, str, 1);
	// printf("After -> |%s|\n", new_line);

	list = parse_line(str);
	printf("\n\n\n|%s|", list[0]);
	printf("\n\n\n|%s|", list[1]);

	

	
}