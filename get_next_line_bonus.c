/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gat_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:22:08 by okhourss          #+#    #+#             */
/*   Updated: 2024/11/29 01:22:08 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*saved_data[MAXIMUM_FD];
	char		*line_to_return;
	char		*read_buffer;

	line_to_return = NULL;
	read_buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (free_resources(&saved_data[fd], &read_buffer));
	if (!read_buffer)
		return (NULL);
	saved_data[fd] = read_and_store(fd, saved_data[fd], read_buffer);
	if (saved_data[fd][0] == '\0')
	{
		free(saved_data[fd]);
		saved_data[fd] = NULL;
		return (NULL);
	}
	line_to_return = extract_line(saved_data[fd], line_to_return);
	saved_data[fd] = trim_saved_data(saved_data[fd]);
	return (line_to_return);
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

char	*extract_line(char *saved_data, char *line_to_return)
{
	int	i;
	int	len;

	if (!saved_data)
		return (NULL);
	len = 0;
	while (saved_data[len] != '\n' && saved_data[len])
		len++;
	if (saved_data[len] == '\n')
		len++;
	line_to_return = malloc(len + 1);
	if (!line_to_return)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line_to_return[i] = saved_data[i];
		i++;
	}
	line_to_return[i] = '\0';
	return (line_to_return);
}

char	*trim_saved_data(char *saved_data)
{
	int		i;
	int		len;
	char	*remaining_data;

	if (!saved_data)
		return (NULL);
	len = 0;
	while (saved_data[len] != '\n' && saved_data[len])
		len++;
	if (saved_data[len] == '\n')
		len++;
	remaining_data = malloc(ft_strlen(saved_data) - len + 1);
	if (!remaining_data)
		return (NULL);
	i = 0;
	while (saved_data[i + len])
	{
		remaining_data[i] = saved_data[i + len];
		i++;
	}
	remaining_data[i] = '\0';
	free(saved_data);
	return (remaining_data);
}

void	*free_resources(char **saved_data, char **read_buffer)
{
	free(*saved_data);
	free(*read_buffer);
	*saved_data = NULL;
	*read_buffer = NULL;
	return (NULL);
}
