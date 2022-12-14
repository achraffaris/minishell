/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:52:58 by afaris            #+#    #+#             */
/*   Updated: 2022/11/08 22:08:37 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cp;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	cp = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!cp)
		return (NULL);
	if (!s1)
	{
		free(cp);
		return (NULL);
	}
	while (s1[i])
	{
		cp[i] = s1[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
