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

	while (std::getline(file, s))
		std::cout << s << std::endl;
	file.close();
	return (true);
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
