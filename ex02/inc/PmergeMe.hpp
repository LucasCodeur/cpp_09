/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/24 11:15:53 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP 
# define PMERGEME_HPP

#include <iostream>
#include <stdlib.h>

#define PRINT(x) std::cout << x << std::endl;

#define DATABASE "data.csv"

class	PmergeMe
{
	public:
		PmergeMe	(void);
		PmergeMe (int _sizeStr);
		PmergeMe	(const PmergeMe &);
		~PmergeMe	(void);
		PmergeMe& operator= ( const PmergeMe &);

	private:
};

template <typename T> T strConvert(const char number)
{
	T	number_convert = 0;
	
	char*	end = NULL;
	number_convert = std::strtod(&number, &end);
	return (number_convert);
}

# endif
