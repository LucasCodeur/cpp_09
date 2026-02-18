/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/18 17:43:56 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP 
# define BITCOIN_EXCHANGE_HPP

#include <iostream>

class	BitcoinExchange
{
	public:
		BitcoinExchange	(void);
		BitcoinExchange	(int);
		BitcoinExchange	(const BitcoinExchange &);
		~BitcoinExchange (void);
		BitcoinExchange& operator= ( const BitcoinExchange &);

		void	fillMap(void);
		void	checkDateFormat(void);
		void	checkNumbers(void);
		void	checkNearestDate(void);
		void	rateConvert(void);
	private:
};

bool	openFile(char* inputFile);

# endif
