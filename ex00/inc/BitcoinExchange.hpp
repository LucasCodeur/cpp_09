/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/21 19:21:21 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP 
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>

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
		void	parseInput(char* file);
		void	checkDateFormat(void);
		void	checkNumbers(void);
		void	checkNearestDate(void);
		void	rateConvert(void);
		void	printMap();

		const BitcoinExchange& getDatabase(void) const;

	private:
		std::map<std::string, double> _database;
};

# endif
