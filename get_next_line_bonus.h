/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gat_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:08:28 by okhourss          #+#    #+#             */
/*   Updated: 2024/11/29 01:08:28 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# ifndef MAXIMUM_FD
#  define MAXIMUM_FD 1024
# endif

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void	*free_resources(char **read_buffer, char **saved_data);
char	*read_and_store(int fd, char *saved_data, char *read_buffer);
char	*extract_line(char *saved_data, char *line);
char	*trim_saved_data(char *saved_data);

#endif