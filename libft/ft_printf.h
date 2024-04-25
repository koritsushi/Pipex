/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:17:32 by mliyuan           #+#    #+#             */
/*   Updated: 2024/03/24 23:29:31 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

// main function
int	ft_printf(const char *str, ...);

//helper function
int	ft_char_helper(va_list args);
int	ft_str_helper(va_list args);
int	ft_num_helper(va_list args);
int	ft_uint_helper(va_list args);
int ft_hexa_upper_helper(va_list args);
int ft_hexa_lower_helper(va_list args);
int	ft_memory_helper(va_list args);

int	ft_printchar(const char chr);
int	ft_printstr(const char *str);
int	ft_printnum(int num);
int	ft_printuint(unsigned long num);
int	ft_printhexa_upper(unsigned long num);
int	ft_printhexa_lower(unsigned long num);
int	ft_printmemory(uintptr_t ptr);

#endif
