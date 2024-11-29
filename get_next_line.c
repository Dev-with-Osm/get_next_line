/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:55:07 by okhourss          #+#    #+#             */
/*   Updated: 2024/11/28 17:55:07 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*saved_data;
	char		*read_buffer;
	char		*line_to_return;

	line_to_return = NULL;
	read_buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_resources(&read_buffer, &saved_data));
	if (!read_buffer)
		return (NULL);
	saved_data = read_and_store(fd, saved_data, read_buffer);
	if (saved_data[0] == '\0')
	{
		free(saved_data);
		saved_data = NULL;
		return (NULL);
	}
	line_to_return = extract_line(saved_data, line_to_return);
	saved_data = trim_saved_data(saved_data);
	return (line_to_return);
}

char	*trim_saved_data(char *saved_data)
{
	int		i;
	int		len;
	char	*new_saved_data;

	if (!saved_data)
		return (NULL);
	len = 0;
	while (saved_data[len] != '\n' && saved_data[len])
		len++;
	if (saved_data[len] == '\n')
		len++;
	new_saved_data = malloc(ft_strlen(saved_data) - len + 1);
	if (!new_saved_data)
		return (NULL);
	i = 0;
	while (saved_data[i + len])
	{
		new_saved_data[i] = saved_data[i + len];
		i++;
	}
	new_saved_data[i] = '\0';
	free(saved_data);
	return (new_saved_data);
}

char	*extract_line(char *saved_data, char *line)
{
	int		i;
	int		len;

	if (!saved_data)
		return (NULL);
	len = 0;
	while (saved_data[len] != '\n' && saved_data[len])
		len++;
	if (saved_data[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = saved_data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_and_store(int fd, char *saved_data, char *read_buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!saved_data)
		saved_data = ft_strdup("");
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		saved_data = ft_strjoin(saved_data, read_buffer);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (saved_data);
}

void	*free_resources(char **read_buffer, char **saved_data)
{
	free(*read_buffer);
	free(*saved_data);
	*read_buffer = NULL;
	*saved_data = NULL;
	return (NULL);
}
