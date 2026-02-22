/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeParsing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 09:06:46 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 11:11:28 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>

static bool isGoodFormatNumber(const std::string& s);

void	BitcoinExchange::parsing(std::string& strDate, std::string& strNumber)
{
	struct tm		tm;
	 
	PRINT(strDate);
	PRINT(strNumber);
	if (!strptime(strDate.c_str(), "%Y-%m-%d", &tm) || strDate.length() != 10) 
		throw std::runtime_error("Date format isn't correct");
	else if (tm.tm_mday > 31 || tm.tm_mday < 1 || tm.tm_mon + 1 < 1 || tm.tm_mon + 1 > 12 || tm.tm_year + 1900 > 2050 || tm.tm_year + 1900 < 2009)
		throw std::runtime_error("Date format isn't correct");
	else if (detectMultipleCharacters(strNumber, '.') == true)
		throw std::runtime_error("Multiple dots");
	else if (strNumber[0] == '-')
		throw std::runtime_error("Number is negative");
	else if (isGoodFormatNumber(strNumber) == false)
		throw std::runtime_error("Number format isn't correct");
}

void	BitcoinExchange::splitLine(std::string& str, std::string& strDate, std::string& strNumber, char c)
{
	size_t	i;

	i = str.find(c);
	if (i != std::string::npos)
	{
		strDate = str.substr(0, i);
		while (str[i] == '|' || str[i] == ',' || std::isspace(str[i])) 
			i++;
		strNumber = str.substr(i, str.length());
	}
	else
	{
		std::string message;

		message = "Error Database, not find : ";
		message = message + c;
		throw std::runtime_error(message);
	}
}

void	BitcoinExchange::checkHeader(std::string header, const char c, const std::string toCheck1, const std::string toCheck2)
{
	std::string str1;
	std::string str2;

	this->splitLine(header, str1, str2, c);
	if (str1 == toCheck1 && str2 == toCheck2)
		return ;
	throw std::runtime_error("Header format isn't correct");
}

bool	BitcoinExchange::detectMultipleCharacters(const std::string& str, const char c)
{
	short int nb_dots= 0;

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == c)	
			nb_dots++;
	}
	if (nb_dots > 1)
		return (true);
	return (false);
}

static bool isGoodFormatNumber(const std::string& str)
{
	if (str.empty())
		return (false);

	std::string::const_iterator it = str.begin();

	while (it != str.end() && (std::isdigit(*it) || *it == '.')) 
		++it;
	return (it == str.end());
}
