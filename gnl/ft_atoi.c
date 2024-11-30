/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:48:36 by mquero            #+#    #+#             */
/*   Updated: 2024/11/29 10:50:17 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	hexa(const char *str, int *i, int hold)
{
	*i = *i + 2;
	while ((str[*i] >= '0' && str[*i] <= '9') ||
		   (str[*i] >= 'a' && str[*i] <= 'f') ||
		   (str[*i] >= 'A' && str[*i] <= 'F'))
	{
		if (str[*i] >= '0' && str[*i] <= '9')
			hold = hold * 16 + (str[*i] - '0');
		else if (str[*i] >= 'a' && str[*i] <= 'f')
			hold = hold * 16 + (str[*i] - 'a' + 10);
		else if (str[*i] >= 'A' && str[*i] <= 'F')
			hold = hold * 16 + (str[*i] - 'A' + 10);
		*i = *i + 1;
	}
	return (hold);
}
int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	hold;

	i = 0;
	n = 1;
	hold = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			n = -1;
	}
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		hold = hexa(str, &i, hold);
	else
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			hold = (hold * 10) + (str[i] - '0');
			i++;
		}
	}
	return ((int)(hold * n));
}
