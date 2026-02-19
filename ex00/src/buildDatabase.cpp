/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildDatabase.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:23:54 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/19 13:50:26 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <bits/stdc++.h>
#include <stdexcept>

static bool isNumber(const std::string& s);
static type detectPositiveNumber(std::string& number);

void BitcoinExchange::buildDatabase(const char* inputFile)
{
	std::ifstream	file(inputFile);
	std::string	s;
	std::string	strDate;
	std::string	strNumber;	
	size_t		i = 0;

	file.exceptions(std::ifstream::badbit);
	while (std::getline(file, s))
	{
		i = s.find(",");
		if (i != std::string::npos)
		{
			strDate = s.substr(0, i);
			strNumber = s.substr(i + 1, s.length());
		}
		else
			return ;
		if (strDate == "date" && strNumber == "exchange_rate")
			continue ;
		struct tm tm;
		if (!strptime(strDate.c_str(), "%Y-%m-%d", &tm)) 
		{
			std::cout << "Database is corrupted\n";
		}
		type ret = detectPositiveNumber(strNumber);
		if (ret == CHAR || ret == NUL)
			throw std::runtime_error("Not a positive Number");
		this->_database.insert( std::pair<std::string, std::string>(strDate, strNumber));
	}
	file.close();
}

static bool isNumber(const std::string& s)
{

	if (s.empty())
		return (false);
	std::string::const_iterator it = s.begin();

	// if (*it == '-')
	// 	++it;
	while (it != s.end() && std::isdigit(*it)) 
		++it;
	return (it == s.end());
}

static type	detectPositiveNumber(std::string& number)
{
	type	ret = NUL;
	size_t	i = 0;
	
	// if (number == "nan"  || number == "inf" || number == "-inf" || number == "+inf" || number == "NaN")
	// 	return (DOUBLE);
	// else if (number == "nanf" || number == "inff" || number == "-inff" || number == "+inff")
	// 	return (FLOAT);
	i = number.find(".");
	if (i != std::string::npos && number.c_str()[i] == '.' && number[0] != '-')
	{
		i = number.rfind("f");
		if (i != std::string::npos && number.c_str()[i] != 'f')
			ret = DOUBLE;
		else
			ret = FLOAT;
	}
	else
	{
		if (isNumber(number) == true)
			ret = INT;
		else if (number.length() < 2 && !std::isdigit(number.c_str()[0]))
			ret = CHAR;
	}
	return (ret);
}
