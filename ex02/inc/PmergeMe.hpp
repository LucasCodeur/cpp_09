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
#include <stdexcept>
#include <stdlib.h>
#include <vector>

#define PRINT(x) std::cout << x << std::endl;

#define DATABASE "data.csv"

class	PmergeMe
{
	public:
		PmergeMe	(void);
		PmergeMe	(int _sizeStr);
		PmergeMe	(const PmergeMe &);
		~PmergeMe	(void);
		PmergeMe&	operator= ( const PmergeMe &);
		void		fordJonhson(void);
		void		parsing(int argc, char**argv);
		void				printVec(void);
	private:
		std::vector<int>	container;
		
};

template <typename T> T strConvert(std::string& number)
{
	T	number_convert = 0;
	
	char*	end = NULL;
	number_convert = std::strtod(number.c_str(), &end);
	// if (*end)
	// 	throw std::runtime_error("Error: problem inside argument");
	return (number_convert);
}

# endif
