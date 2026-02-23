/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReversePolishNotation.hpp                                :+:      :+:    :+:   */
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
#include <stack>
#include <stdlib.h>

#define PRINT(x) std::cout << x << std::endl;

#define DATABASE "data.csv"

class	ReversePolishNotation
{
	public:
		ReversePolishNotation	(void);
		ReversePolishNotation (int _sizeStr);
		ReversePolishNotation	(const ReversePolishNotation &);
		~ReversePolishNotation	(void);
		ReversePolishNotation& operator= ( const ReversePolishNotation &);

		bool parsing(std::string polishExpression);
		bool rpn(std::string polishExpression);

	private:
		int	_sizeStr;
};

template <typename T> T strConvert(const char& number)
{
	T	number_convert = 0;
	
	char*	end = NULL;
	number_convert = std::strtod(&number, &end);
	return (number_convert);
}

# endif
