/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeParsing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 09:06:46 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 19:36:41 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <cctype>

static bool isGoodFormatNumber(const std::string& s);

bool	BitcoinExchange::parsing(std::string& strDate, std::string& strNumber, bool noThrow)
{
	std::string		message;

	if (checkDate(strDate, noThrow) == false)
		return (false);
	if (detectMultipleCharacters(strNumber, '.') == true)
	{
		message = "Error: multiples dots: ";
		message += strNumber;
		if (noThrow == false)
			throw std::runtime_error(message);
		else
			std::cout << message << std::endl;
		return (false);
	}
	else if (strNumber[0] == '-')
	{
		message = "Error: not a positive number.";
		if (noThrow == false)
			throw std::runtime_error(message);
		else
			std::cout << message << std::endl;
		return (false);
	}
	else if (isGoodFormatNumber(strNumber) == false)
	{
		message = "Error : number format isn't correct: ";
		message += strNumber;
		if (noThrow)
			throw std::runtime_error(message);
		else
			std::cout << message << std::endl;
		return (false);
	}
	return (true);
}

static int	splitDate(std::string& strDate);
static bool	checkFormatDate(struct tm tm, std::string& strDate, bool noThrow);

bool	BitcoinExchange::checkDate(std::string strDate, bool noThrow)
{
	struct tm		tm;
	std::string		message;
		
	if (!strptime(strDate.c_str(), "%Y-%m-%d", &tm) || strDate.length() != 10) 
	{
		message = "Error: bad input => ";
		message += strDate;
		if (noThrow == false)
			throw std::runtime_error(message);
		else
			std::cout << message << std::endl;
		return (false);

	}

	std::string	temp = strDate;

	tm.tm_year = splitDate(strDate);
	tm.tm_mon = splitDate(strDate);
	tm.tm_mday = splitDate(strDate);
	if (checkFormatDate(tm, temp, noThrow) == false)
		return (false);
	return (true);
}

static int	splitDate(std::string& strDate)
{
	size_t			pos;
	std::string		strTemp;
	int				ret = 0;

	pos = strDate.find("-");
	if (pos != std::string::npos)
	{
		strTemp = strDate.substr(0, pos);
		strDate.erase(0, pos + 1);
		ret = strConvert<int>(strTemp);
	}
	else
		ret = strConvert<int>(strDate);
	return (ret);
}

static int	checkLeapYear(int year);

static bool	checkFormatDate(struct tm tm, std::string& strDate, bool noThrow)
{
	std::string		message;
	int				feb = checkLeapYear(tm.tm_year);
	int				dayAccordingMonths[13] = {0, 31, feb, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (tm.tm_mday > dayAccordingMonths[tm.tm_mon] || tm.tm_mday < 1 || tm.tm_mon < 1 || tm.tm_mon > 12 || tm.tm_year > 2050 || tm.tm_year < 2009)
	{
		message = "Error: bad input => ";
		message += strDate;
		if (noThrow == false)
			throw std::runtime_error(message);
		else
			std::cout << message << std::endl;
		return (false);
	}
	return (true);
}

static int	checkLeapYear(int year)
{
	if (year % 400 == 0)
		return (29);
	else if (year % 100 == 0)
		return (28);
	else if (year % 4 == 0)
	{
		return (29);
	}
	return (28);
}

bool	BitcoinExchange::splitLine(std::string& str, std::string& strDate, std::string& strNumber, char c, bool noThrow)
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

		message = "Error: bad input => ";
		message = message + str;
		if (noThrow == false)
			throw std::runtime_error(message);
		else
			std::cout << message << std::endl;
		return (false);
	}
	return (true);
}

void	BitcoinExchange::checkHeader(std::string header, const char c, const std::string toCheck1, const std::string toCheck2, bool noThrow)
{
	std::string str1;
	std::string str2;

	this->splitLine(header, str1, str2, c, noThrow);
	if (str1 == toCheck1 && str2 == toCheck2)
		return ;
	throw std::runtime_error("Error: header format isn't correct");
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
