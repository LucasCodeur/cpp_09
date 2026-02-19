/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/19 13:31:15 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange (void)
{
	std::cout << "BitcoinExchange Default constructeur called\n";
}

BitcoinExchange::BitcoinExchange (const BitcoinExchange &other)
{
	std::cout << "BitcoinExchange Copy constructeur called\n";
	if (this != &other)
		this->_database = other._database;
}

BitcoinExchange::BitcoinExchange (const std::map<std::string, std::string>& database) : _database(database)
{
	std::cout << "BitcoinExchange Parameterized constructeur called\n";
}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange &other)
{
	if (this != &other)
		this->_database = other._database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange (void)
{
	std::cout << "BitcoinExchange Destructeur called\n";
}
