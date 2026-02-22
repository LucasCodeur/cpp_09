/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 11:09:42 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP 
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>
#include <stdlib.h>

#define PRINT(x) std::cout << "Value is: " << x << std::endl

#define DATABASE "data.csv"

class	BitcoinExchange
{
	public:
		BitcoinExchange	(void);
		BitcoinExchange (const std::map<std::string, double>& database);
		BitcoinExchange	(const BitcoinExchange &);
		~BitcoinExchange (void);
		BitcoinExchange& operator= ( const BitcoinExchange &);

		void	buildDatabase(const char* inputFile);
		void	parseInput(const char* inputFile);
		void	checkDateFormat(void);
		void	checkNumbers(void);
		void	checkNearestDate(void);
		void	convert(const char* inputFile);
		void	printMap();

		void	splitLine(std::string& str, std::string& strDate, std::string& strNumber, char c);
		bool	detectMultipleCharacters(const std::string& str, const char c);
		void	parsing(std::string& strDate, std::string& strNumber);
		void	checkHeader(std::string header, const char c, const std::string toCheck1, const std::string toCheck2);

	private:
		std::map<std::string, double> _database;
};

template <typename T> T strConvert(std::string& number)
{
	T	number_convert = 0;
	
	char*	end = NULL;
	number_convert = std::strtod(number.c_str(), &end);
	return (number_convert);
}

# endif
