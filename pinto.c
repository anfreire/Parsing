/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char	*substring(char *s, int start, int len)
{
	int		i;
	int		fulen;
	char	*ptr;

	i = -1;
	fulen = 0;
	while (s[fulen])
		fulen++;
	if (fulen - start < len && start < fulen)
	{
		ptr = (char *)malloc((fulen - start + 1) * sizeof(char));
		len = fulen - start;
	}
	else if (fulen - start >= len)
	{
		ptr = (char *)malloc((len + 1) * sizeof(char));
		ptr[len] = 0;
	}
	start--;
	while (++start < fulen && ++i < len)
		ptr[i] = s[start];
	return (ptr);
}

int	count_rows(char *s, char c)
{
	int	how_many;
	int	i;
	int	flag;

	i = -1;
	how_many = 0;
	flag = 0;
	while (s[++i])
	{
		if (s[i] == c)
			flag = 1;
		while (s[i] == c)
			i++;
		if (flag == 0)
			continue ;
		how_many++;
		flag = 0;
		if (s[i] == '\0')
			break ;
	}
	return (how_many + 1);
}

int	find_c(char *s, char c, int index)
{
	int	i;

	i = index + 1;
	while (!(s[i] == c || s[i] == '\0'))
		i++;
	return (i);
}

int	find_len(char *s, char c, int index)
{
	int	i;
	int	size;

	size = 0;
	i = index;
	while (!(s[i] == c || s[i] == '\0'))
	{
		i++;
		size++;
	}
	return (size);
}

char	**spliting(char *s, char c)
{
	int		i;
	int		index;
	char	**matrix;

	matrix = (char **)malloc((count_rows(s, c) + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	index = 0;
	i = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		if (s[index] == '\0')
			break ;
		matrix[i] = substring(s, index, find_len(s, c, index));
		i++;
		index = find_c(s, c, index);
		index++;
		if (s[index - 1] == '\0')
			break ;
	}
	matrix[i] = NULL;
	return (matrix);
}

int remove_two_sequencial_char(char *line, char c) // Removes the character's first and next occurrences from the string and then returns the string. 
{
	char	*ptr1;
	int     distance;
	char	*ptr2;

	ptr1 = strchr(line, c);
	ptr2 = strchr((ptr1 + 1), c);
	if (ptr1 == NULL || ptr2 == NULL)
		return (0);
	else
	{
		distance = ptr1 - line;
		printf("\n0MEMOVE: %s\n", line);
		memmove(&line[distance], &line[distance + 1], strlen(line) - distance);
		distance = strchr(ptr1, c) - line;
		memmove(&line[distance], &line[distance + 1], strlen(line) - distance);
		printf("\n2MEMOVE: %s\n", &line[distance]);
		char * string = malloc(sizeof(char) * distance);
		string = strncpy(string, line, distance);
		printf("\nString: [%s], %d\n", string, distance);
		free(string);
		return (distance);
	}
}
void string_can_be_parsed_v1(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if ((strchr(&string[i], '\'') != NULL && strchr(strchr(&string[i], '\'') + 1, '\'') != NULL) && \
			((strchr(&string[i], '\'') - &string[i] < strchr(&string[i], '\"') - &string[i]) || strchr(&string[i], '\"') == NULL) && \
			((strchr(&string[i], '\'') - &string[i] < strchr(&string[i], ' ') - &string[i]) || strchr(&string[i], ' ') == NULL))
			i += remove_two_sequencial_char(&string[i], '\'');
		else if ((strchr(&string[i], '\"') != NULL && strchr(strchr(&string[i], '\"') + 1, '\"') != NULL) && \
			((strchr(&string[i], '\"') - &string[i] < strchr(&string[i], '\'') - &string[i]) || strchr(&string[i], '\'') == NULL) && \
			((strchr(&string[i], '\"') - &string[i] < strchr(&string[i], ' ') - &string[i]) || strchr(&string[i], ' ') == NULL))
			i += remove_two_sequencial_char(&string[i], '\"');
		else if (string[i] == ' ')
			string[i] = 5;
		else
			i++;
	}
}


int main()
{
	char teste[] = " \'ex\"                                     \"port             t est\" \"\"e\"\'\"\" \"  \"\'  \'";
   	string_can_be_parsed_v1(teste);
	// printf("\n\n~%s~\n", teste);
	char **dbl_ptr = spliting(teste, 5);
	// printf("\n\n~%s~\n", teste);
	(void)dbl_ptr;
	size_t i = 0;
	while (dbl_ptr[i])
	{
		printf("\n\n~%s~%ld\n", dbl_ptr[i], strlen(dbl_ptr[i]));
		i++;
	}
	// printf("\n\n~%s~%d\n", dbl_ptr[1], strlen(dbl_ptr[1]));
	// printf("\n\n~%s~%d\n", dbl_ptr[2], strlen(dbl_ptr[2]));
	// printf("\n\n~%s~%d\n", dbl_ptr[3], strlen(dbl_ptr[3]));
}
