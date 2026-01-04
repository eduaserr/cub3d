/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:05:59 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/04 07:52:21 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr_gnl(char *str, ssize_t start, ssize_t len)
{
	char	*substr;
	ssize_t	i;

	i = -1;
	if (start >= ft_strlen(str))
		return (NULL);
	if (len + start > ft_strlen(str))
		len = ft_strlen(str) - start;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	while (++i < len)
		substr[i] = str[i + start];
	substr[i] = '\0';
	return (substr);
}

static char	*handle_null_strings(char **s1, char **s2, int *f)
{
	if (!*s1)
	{
		*s1 = ft_strdup("");
		if (!*s1)
			return (NULL);
	}
	if (!*s2)
	{
		*f = 1;
		*s2 = ft_strdup("");
		if (!*s2)
			return (NULL);
	}
	return (*s1);
}

static void	ft_cpystr(char *dest, char *s1, char *s2)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	int		f;

	f = 0;
	if (!handle_null_strings(&s1, &s2, &f))
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
	{
		s1 = ft_free_str(&s1);
		if (f)
			free(s2);
		return (NULL);
	}
	ft_cpystr(s3, s1, s2);
	s1 = ft_free_str(&s1);
	if (f)
		free(s2);
	return (s3);
}
