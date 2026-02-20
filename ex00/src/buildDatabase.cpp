/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildDatabase.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:23:54 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/19 18:07:09 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <fstream>
#include <stdexcept>

static void	parsing(const std::string& strDate, const std::string& strNumber);
static void	splitLine(std::string& str, std::string* strDate, std::string* strNumber);

void BitcoinExchange::buildDatabase(const char* inputFile)
{
	std::ifstream	file(inputFile);
	std::string		str;
	std::string		strDate;
	std::string		strNumber;	

	file.exceptions(std::ifstream::badbit);
	while (std::getline(file, str))
	{
		splitLine(str, &strDate, &strNumber);
		if (strDate == "date" && strNumber == "exchange_rate")
			continue ;
		parsing(strDate, strNumber);
		this->_database.insert( std::pair<std::string, std::string>(strDate, strNumber));
	}
}

static void	splitLine(std::string& str, std::string* strDate, std::string* strNumber)
{
	size_t			i = 0;

	i = str.find(",");
	if (i != std::string::npos)
	{
		*strDate = str.substr(0, i);
		*strNumber = str.substr(i + 1, str.length());
	}
	else
		throw std::runtime_error("Error Database, not find : ','");

}

static bool	detectMultipleDots(const std::string& str);
static bool isGoodFormatNumber(const std::string& s);

static void	parsing(const std::string& strDate, const std::string& strNumber)
{
	struct tm		tm;
	
	if (!strptime(strDate.c_str(), "%Y-%m-%d", &tm) || strDate.length() != 10) 
		throw std::runtime_error("Date format isn't correct");
	else if (detectMultipleDots(strNumber) == true)
		throw std::runtime_error("Multiple dots");
	else if (strNumber[0] == '-')
		throw std::runtime_error("Number is negative");
	else if (isGoodFormatNumber(strNumber) == false)
		throw std::runtime_error("Number format isn't correct");
}

static bool	detectMultipleDots(const std::string& str)
{
	short int nb_dots= 0;

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '.')	
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
