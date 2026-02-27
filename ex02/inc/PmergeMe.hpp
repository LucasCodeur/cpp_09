/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/26 11:14:48 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP 
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
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
		void		fillVec(int argc, char**argv);
		void		printVec(std::vector<int> vec);
		void		divideAndComp(int size, int sizeDividedVec, int endPacket, bool firstIteration);
		void		fillDividedVec(int size, int endPacket);
		void		fillMainVec(int sizeMainVec, int step);
		void		swap(int sizeDividedVec, int endPacket, bool firstIteration);
		std::vector<int>	mainVec;
		std::vector<int>*	dividedVec;
	private:
};

template <typename T> T strConvert(std::string& number)
{
	T	number_convert = 0;
	std::stringstream ss(number);
	
	ss >> number_convert;
	if (ss.fail())
		throw std::runtime_error("Error: problem inside argument");
	return (number_convert);
}

# endif
