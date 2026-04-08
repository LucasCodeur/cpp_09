/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 19:15:03 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <map>

BitcoinExchange::BitcoinExchange (void)
{
	// std::cout << "BitcoinExchange Default constructeur called\n";
}

BitcoinExchange::BitcoinExchange (const BitcoinExchange &other)
{
	// std::cout << "BitcoinExchange Copy constructeur called\n";
	if (this != &other)
		this->_database = other._database;
}

BitcoinExchange::BitcoinExchange (const std::map<std::string, double>& database) : _database(database)
{
	// std::cout << "BitcoinExchange Parameterized constructeur called\n";
}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange &other)
{
	if (this != &other)
		this->_database = other._database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange (void)
{
	// std::cout << "BitcoinExchange Destructeur called\n";
}

void BitcoinExchange::buildDatabase(const char* inputFile)
{
	std::ifstream	file(inputFile);
	std::string		str;
	std::string		strDate;
	std::string		strNumber;	

	file.exceptions(std::ifstream::badbit);
	std::getline(file, str);
	if (str.empty() == false)
		this->checkHeader(str, ',', "date", "exchange_rate", false);
	else
		throw std::runtime_error("Error: csv is empty");
	while (std::getline(file, str))
	{
		this->splitLine(str, strDate, strNumber, ',', false);
		this->parsing(strDate, strNumber, false);
		this->_database.insert(std::pair<std::string, double>(strDate, strConvert<double>(strNumber)));
	}
	if (this->_database.empty() == true)
		throw std::runtime_error("Error: empty database");
}

void	BitcoinExchange::convert(const char* inputFile)
{
	std::ifstream	file(inputFile);
	std::string		str;
	std::string		strDate;
	std::string		strNumber;	

	file.exceptions(std::ifstream::badbit);
	std::getline(file, str);
	if (str.empty() == false)
		this->checkHeader(str, ' ', "date", "value", true);
	else
		throw std::runtime_error("Error: empty file");
	while (std::getline(file, str))
	{
		if (this->splitLine(str, strDate, strNumber, ' ', true) == false)
			continue ;
		if (this->parsing(strDate, strNumber, true) == false)
			continue ;
		std::map<std::string, double>::iterator it = this->_database.lower_bound(strDate);
		if (it != this->_database.begin() && strDate != it->first)
			--it;
		double number = strConvert<double>(strNumber); 
		if (number > 1000)
		{
			PRINT("Error: too large a number.");
			continue ;
		}
		std::cout << strDate << " => " << strNumber << " = " << it->second * number << std::endl;
	}
}
