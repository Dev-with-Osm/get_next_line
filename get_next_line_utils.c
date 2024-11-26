/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:28:56 by okhourss          #+#    #+#             */
/*   Updated: 2024/11/25 21:28:56 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dustr;
	size_t	i;

	i = 0;
	dustr = malloc(ft_strlen(s) + 1);
	if (!dustr)
		return (NULL);
	while (s[i])
	{
		dustr[i] = s[i];
		i++;
	}
	dustr[i] = '\0';
	return (dustr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ls;

	ls = ft_strlen(src);
	if (size == 0)
		return (ls);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ls);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ls;
	size_t	ld;

	i = 0;
	ls = ft_strlen(src);
	if (size == 0)
		return (ls);
	ld = ft_strlen(dst);
	if (size <= ld)
		return (ls + size);
	while (src[i] && i < size - ld - 1)
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ls + ld);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (new_str);
}


size_t ft_strlen(const char *s)
{
	size_t	len;

	if(!s)
		return(0);
	len = 0;
	while (s[len])
		len++;
	return(len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	sub_str = (char *)malloc(len + 1);
	if (!sub_str)
		return (NULL);
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[len] = '\0';
	return (sub_str);
}
