/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 11:09:58 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

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

BitcoinExchange::BitcoinExchange (const std::map<std::string, double>& database) : _database(database)
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

void BitcoinExchange::buildDatabase(const char* inputFile)
{
	std::ifstream	file(inputFile);
	std::string		str;
	std::string		strDate;
	std::string		strNumber;	

	file.exceptions(std::ifstream::badbit);
	std::getline(file, str);
	this->checkHeader(str, ',', "date", "exchange_rate");
	while (std::getline(file, str))
	{
		this->splitLine(str, strDate, strNumber, ',');
		this->parsing(strDate, strNumber);
		this->_database.insert( std::pair<std::string, double>(strDate, strConvert<double>(strNumber)));
	}
}

void	BitcoinExchange::convert(const char* inputFile)
{
	std::ifstream	file(inputFile);
	std::string		str;
	std::string		strDate;
	std::string		strNumber;	

	file.exceptions(std::ifstream::badbit);
	std::getline(file, str);
	this->checkHeader(str, ' ', "date", "value");
	while (std::getline(file, str))
	{
		this->splitLine(str, strDate, strNumber, ' ');
		this->parsing(strDate, strNumber);
	}
}
