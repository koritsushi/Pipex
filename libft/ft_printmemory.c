/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmemory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:06:17 by mliyuan           #+#    #+#             */
/*   Updated: 2024/03/24 22:53:21 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_memory_helper(va_list args)
{
	uintptr_t	ptr;

	ptr = va_arg(args, uintptr_t);
	return (ft_printmemory(ptr));
}

int	ft_printmemory(uintptr_t ptr)
{
	int	strlen;

	strlen = ft_printstr("0x");
	if (ptr == 0)
		return (strlen + ft_printchar('0'));
	return (strlen + ft_printhexa_lower(ptr));
}
