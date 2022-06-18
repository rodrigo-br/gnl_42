/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-b <ralves-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:48:56 by ralves-b          #+#    #+#             */
/*   Updated: 2022/06/16 20:27:12 by ralves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strchr(char *s)
{
	size_t	counter;

	counter = 0;
	if (s == NULL)
		return (0);
	while (s[counter] != '\n' && s[counter])
		counter++;
	if (s[counter] == '\n')
		return (counter + 1);
	else
		return (0);
}

char	*ft_last_line(char *line_parsed)
{
	if (*line_parsed)
		return (line_parsed);
	free(line_parsed);
	return (NULL);
}

char	*ft_saved_lines(int fd, char *line_parsed)
{
	static char	*save[1024];
	char		*line_result;
	char		*temp;

	if (!(save[fd]))
		save[fd] = NULL;
	if (!line_parsed)
		return (NULL);
	if (save[fd])
	{
		temp = ft_strjoin(save[fd], line_parsed);
		free(line_parsed);
		line_parsed = NULL;
		line_parsed = temp;
		free(save[fd]);
		save[fd] = NULL;
	}
	if (!ft_strchr(line_parsed))
		return (ft_last_line(line_parsed));
	line_result = ft_substr(line_parsed, 0, ft_strchr(line_parsed));
	save[fd] = ft_strdup(&line_parsed[ft_strchr(line_parsed)]);
	free(line_parsed);
	line_parsed = NULL;
	return (line_result);
}

char	*ft_read_file(int fd, char *buffer)
{
	long int	count;
	char		*line_parsing;
	char		*temp;

	count = read(fd, buffer, BUFFER_SIZE);
	if (count == -1)
	{
		free(buffer);
		return (NULL);
	}
	line_parsing = ft_strdup("");
	while (count && count != -1)
	{
		buffer[count] = '\0';
		temp = ft_strjoin(line_parsing, buffer);
		free(line_parsing);
		line_parsing = temp;
		if (ft_strchr(line_parsing))
			break ;
		count = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	buffer = NULL;
	return (line_parsing);
}

char	*get_next_line(int fd)
{
	char	*line_to_parse;

	if (fd > 1024 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_to_parse = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line_to_parse)
		return (NULL);
	*line_to_parse = '\0';
	line_to_parse = ft_read_file(fd, line_to_parse);
	line_to_parse = ft_saved_lines(fd, line_to_parse);
	return (line_to_parse);
}
