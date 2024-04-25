/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:00:54 by mliyuan           #+#    #+#             */
/*   Updated: 2024/03/24 22:10:58 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uint_helper(va_list args)
{
	unsigned long	num;

	num = va_arg(args, unsigned int);
	return (ft_printuint(num));
}

static unsigned long	ft_nbrlen(unsigned long n)
{
	unsigned long	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_nbr(unsigned long n)
{
	int		len;
	char	*nbrstr;

	len = ft_nbrlen(n);
	nbrstr = malloc(sizeof(char) * (len + 1));
	if (nbrstr == NULL)
		return (NULL);
	nbrstr[len] = '\0';
	while (len--)
	{
		nbrstr[len] = 48 + (n % 10);
		n /= 10;
	}
	return (nbrstr);
}

int	ft_printuint(unsigned long num)
{
	int		strlen;
	char	*str;

	str = ft_nbr(num);
	strlen = ft_strlen(str);
	if (str == NULL)
	{
		ft_printstr("(null)");
		return (-1);
	}
	ft_printstr(str);
	free(str);
	return (strlen);
}
