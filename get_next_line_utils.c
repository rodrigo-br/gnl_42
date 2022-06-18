/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-b <ralves-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:48:53 by ralves-b          #+#    #+#             */
/*   Updated: 2022/06/16 19:42:15 by ralves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	while (index + 1 < size && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	if (size > 0)
		dst[index] = '\0';
	else if (size == 0)
	{
		while (dst[len])
			len++;
		dst[len] = '\0';
	}
	len = 0;
	while (src[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	index_aux;
	size_t	result;
	size_t	len;

	index = 0;
	index_aux = 0;
	len = 0;
	while (src[len])
		len++;
	while (dst[index])
		index++;
	result = index + len;
	if (size <= index)
		result = len + size;
	while (src[index_aux] && index + 1 < size)
	{
		dst[index] = src[index_aux];
		index++;
		index_aux++;
	}
	dst[index] = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		index;
	int		s_len;

	index = 0;
	s_len = 0;
	while (s[s_len])
		s_len++;
	new_str = malloc((s_len + 1) * sizeof(char));
	if (!new_str)
		return (new_str);
	while (s[index])
	{
		new_str[index] = s[index];
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	s_len;
	unsigned int	max_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len > start)
		max_len = s_len - start;
	else
		max_len = 0;
	if (max_len > len)
		max_len = len;
	new_str = (char *)malloc((max_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s + start, max_len + 1);
	return (new_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2])
		len_s2++;
	new_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, len_s1 + 1);
	ft_strlcat(new_str, s2, len_s1 + len_s2 + 1);
	return (new_str);
}
