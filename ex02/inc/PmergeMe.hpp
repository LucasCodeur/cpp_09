/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/22 10:15:33 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP 
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

class	PmergeMe
{
	public:
		std::vector<int>	mainVec;
		std::vector<int>	remaining;
		std::vector<int>*	dividedVec;
		int					originalSizeDividedVec;

		PmergeMe	(void);
		PmergeMe	(int _sizeStr);
		PmergeMe	(const PmergeMe &);
		~PmergeMe	(void);
		PmergeMe&	operator= ( const PmergeMe &);
		void		fordJonhson(void);
		void		fillVec(int argc, char**argv);
		void		printVec(std::vector<int> vec);
		void		cleanDividedVec(int sizeDividedVec);
		void		divideAndComp(size_t size, size_t nbInsidePacket, size_t sizeDividedVec);
		void		fillDividedVec(int size, int nbInsidePacket, size_t* sizeDividedVec);
		void		fillMainVec(size_t sizeDividedVec);
		void		fillmainVecAndPend(std::vector<int>* pend, size_t sizeDividedVec, size_t nbInsidePacket);
		void		binaryJacobsthalNbsInsert(std::vector<int>& pend, int jacobsthalNumber, int nbInsidePacket);
		void		swap(int sizeDividedVec, int nbInsidePacket);
		void		fillPend(std::vector<int>* pend, size_t sizeDividedVec, size_t nbInsidePacket);
		void		resizeDividedArrayVec();
		void		printArrayVecs(int sizeDividedVec);
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
