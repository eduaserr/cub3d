/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:05:59 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/27 23:24:27 by eduaserr         ###   ########.fr       */
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

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = -1;
	if (!s1)
		s1 = ft_strdup("");
	if (!s1)
		return (NULL);
	if (!s2)
		s2 = ft_strdup("");
	if (!s2)
		return (NULL);
	s3 = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++j])
		s3[i++] = s2[j];
	s3[i] = '\0';
	s1 = ft_free_str(&s1);
	return (s3);
}
