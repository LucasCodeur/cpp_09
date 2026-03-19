/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/19 16:57:38 by lud-adam         ###   ########.fr       */
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

class	PmergeMe
{
	public:
		std::vector<int>	mainVec;
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
		void		cleanDividedVec();
		void		divideAndComp(size_t size, size_t nbInsidePacket, size_t sizeDividedVec);
		void		fillDividedVec(int size, int nbInsidePacket, size_t* sizeDividedVec);
		void		fillMainVec(size_t sizeDividedVec);
		void		PushPacket(std::vector<int>* vect, int sizeDividedVec, int nbPacketToPush, size_t nbByPackets);
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
