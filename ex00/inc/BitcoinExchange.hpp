/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/19 18:07:42 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP 
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>

//WARN Maybe handle space after date format
enum type { INT, FLOAT, DOUBLE, CHAR, NUL };
#define DATABASE "data.csv"

class	BitcoinExchange
{
	public:
		BitcoinExchange	(void);
		BitcoinExchange (const std::map<std::string, std::string>& database);
		BitcoinExchange	(const BitcoinExchange &);
		~BitcoinExchange (void);
		BitcoinExchange& operator= ( const BitcoinExchange &);

		void	buildDatabase(const char* inputFile);
		void	checkDateFormat(void);
		void	checkNumbers(void);
		void	checkNearestDate(void);
		void	rateConvert(void);

		void	printMap();
		const BitcoinExchange& getDatabase(void) const;
	private:
		std::map<std::string, std::string> _database;
};

# endif
