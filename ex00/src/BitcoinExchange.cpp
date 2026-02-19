/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/18 17:46:33 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <bits/stdc++.h>

static bool isNumber(const std::string& s);
static type	detectType(std::string& number);

bool	openFile(char* inputFile)
{
	std::ifstream file(inputFile);

	// file.exceptions(std::ifstream::badbit);
	if (file.fail() == true)
	{
		std::cout << "Error: cannot open input file\n";
		return (false);
	}

	std::string s;
	std::map<std::string, std::string> dataBase;

	while (std::getline(file, s))
	{
		int i = s.find(",");
		std::string	strDate = s.substr(0, i);
		std::string	strNumber = s.substr(i + 1, s.length());
		std::cout << strDate << std::endl;
		std::cout << strNumber << std::endl;

		if (strDate == "date" && strNumber == "exchange_rate")
			continue ;
		struct tm tm;
		if (!strptime(strDate.c_str(), "%Y-%m-%d", &tm)) 
		{
			std::cout << "Database is corrupted\n";
			return (false);
		}
		type ret = detectType(strNumber);
		if (ret == CHAR || ret == NUL)
			return (false);

	}
	file.close();
	return (true);
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

static type	detectType(std::string& number)
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

// class	BitcoinExchange
// {
// 	public:
// 		BitcoinExchange	(void);
// 		BitcoinExchange	(int);
// 		BitcoinExchange	(const BitcoinExchange &);
// 		~BitcoinExchange (void);
// 		BitcoinExchange& operator= ( const BitcoinExchange &);
//
// 		void	fillMap(void);
// 		void	checkDateFormat(void);
// 		void	checkNumbers(void);
// 		void	checkNearestDate(void);
// 		void	rateConvert(void);
//
// 	private:
// };
