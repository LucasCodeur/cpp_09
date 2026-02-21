/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeParseInput.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:09:48 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/21 19:35:54 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	BitcoinExchange::parseInput(const char* file)
{

}

static void	splitLine(std::string& str, std::string* strDate, std::string* strNumber)
{
	size_t			i = 0;

	i = str.find(" ");
	if (i != std::string::npos)
	{
		*strDate = str.substr(0, i);
		*strNumber = str.substr(i + 1, str.length());
	}
	else
		throw std::runtime_error("Error Database, not find : ','");
}
