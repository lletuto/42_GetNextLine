/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:35:01 by lle-tuto          #+#    #+#             */
/*   Updated: 2024/12/12 12:20:46 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *str, int tofind)
{
	int				i;
	unsigned char	*sstr;
	unsigned char	stofind;

	sstr = (unsigned char *)str;
	stofind = (unsigned char)tofind;
	i = 0;
	while (sstr[i])
	{
		if (sstr[i] == stofind)
		{
			return ((char *)&sstr[i]);
		}
		i++;
	}
	if (stofind == 0)
		return ((char *)&sstr[i]);
	return ((void *)0);
}

static char	*free_her(char *s)
{
	free(s);
	s = NULL;
	return (s);
}

static char	*cut_line(char *line)
{
	ssize_t	i;
	char	*left;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (!line[i] || !line[i + 1])
		return (NULL);
	left = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!*left)
		left = free_her(left);
	line[i + 1] = '\0';
	return (left);
}

static char	*fill_line(int fd, char *left, char *buf)
{
	char	*temp;
	ssize_t	size;

	size = 1;
	while (size != 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (left = free_her(left));
		else if (size == 0)
			break ;
		buf[size] = '\0';
		if (!left)
			left = ft_strdup("");
		temp = left;
		left = ft_strjoin(temp, buf);
		temp = free_her(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (left);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*left;
	char		*line;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		left = free_her(left);
		buf = free_her(buf);
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = fill_line(fd, left, buf);
	buf = free_her(buf);
	if (!line)
		return (NULL);
	left = cut_line(line);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*res;

	res = NULL;
	fd = open("texte_test.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("resultat = %s\n", res);
	res = get_next_line(fd);
	printf("resultat = %s\n", res);
	res = get_next_line(fd);
	printf("resultat = %s\n", res);
	res = get_next_line(fd);
	printf("resultat = %s\n", res);
	res = get_next_line(fd);
	printf("resultat = %s\n", res);
	return (0);
}*/