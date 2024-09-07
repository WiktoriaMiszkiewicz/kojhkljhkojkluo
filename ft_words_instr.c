/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_instr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaniec <wdaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:26:08 by wdaniec           #+#    #+#             */
/*   Updated: 2024/07/20 16:14:32 by wdaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putcharacter_length(char character, int *length) // wypisuje znak i liczy ze jeden znak zostal wypisany
{
	write(1, &character, 1);
	(*length)++;
}

void	ft_string(char *args, int *length) // wypisuje caly ciag znakow i liczy ile zostalo wypisanych
{
	size_t i;

	i = 0;
	if (!args)
	{
		write(1, "(null)", 6);
		(*length) += 6;
		return ;
	}
	while (args[i] != '\0')
	{
		ft_putcharacter_length(args[i], length);
		i++;
	}
}