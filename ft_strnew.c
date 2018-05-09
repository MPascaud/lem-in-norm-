/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:24:16 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/02 17:47:11 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char	*ft_strnew(size_t size)
{
	char	*bla;
	size_t	i;

	i = 0;
	if (!(bla = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		bla[i] = '\0';
		i++;
	}
	bla[i] = '\0';
	return (bla);
}
