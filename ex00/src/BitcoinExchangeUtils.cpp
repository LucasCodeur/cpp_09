/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeUtils.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:32:59 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 09:58:16 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <iomanip>

void BitcoinExchange::printMap()
{
	for (std::map<std::string, double>::const_iterator it = this->_database.begin(); it != this->_database.end(); ++it)
	{
		std::cout << std::setprecision(7) << it->first << " = " << it->second << "\n";
	}
	std::cout << std::endl;
}
