/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 19:15:09 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP 
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>
#include <stdlib.h>

#define PRINT(x) std::cout << x << std::endl;

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
		bool	checkDate(std::string strDate, bool noThrow);
		void	checkNumbers(void);
		void	checkNearestDate(void);
		void	convert(const char* inputFile);
		void	printMap();

		bool	splitLine(std::string& str, std::string& strDate, std::string& strNumber, char c, bool noThrow);
		bool	detectMultipleCharacters(const std::string& str, const char c);
		bool	parsing(std::string& strDate, std::string& strNumber, bool noThrow);
		void	checkHeader(std::string header, const char c, const std::string toCheck1, const std::string toCheck2, bool noThrow);

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
