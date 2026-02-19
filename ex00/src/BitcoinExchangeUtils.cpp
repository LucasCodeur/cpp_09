/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeUtils.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:32:59 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/19 13:49:43 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void BitcoinExchange::printMap()
{
	for (std::map<std::string, std::string>::const_iterator it = this->_database.begin(); it != this->_database.end(); ++it)
		std::cout << it->first << " = " << it->second << std::endl;
	std::cout << '\n';
}

const BitcoinExchange& BitcoinExchange::getDatabase(void) const
{
	return (this->_database);
}
