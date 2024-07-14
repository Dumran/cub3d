/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:15:13 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:15:14 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_c(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_c(char *str)
{
	int	i;

	if (str == NULL)
		return (ft_putstr_c("(null)"));
	i = 0;
	while (*str)
	{
		i += ft_putchar_c(*str);
		str++;
	}
	return (i);
}

int	ft_putnbr_c(long n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		i += ft_putchar_c('-');
		n *= -1;
	}
	if (n > 9)
		i += ft_putnbr_c(n / 10);
	i += ft_putchar_c((n % 10) + '0');
	return (i);
}

int	ft_puthex_c(unsigned int n, char op)
{
	char	*c;
	int		i;

	if (op == 'x')
		c = "0123456789abcdef";
	else
		c = "0123456789ABCDEF";
	i = 0;
	if (n > 15)
		i += ft_puthex_c(n / 16, op);
	i += ft_putchar_c(c[n % 16]);
	return (i);
}
