/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/26 11:00:28 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP 
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <vector>
#include <deque>

class	PmergeMe
{
	public:
		static int nbr_of_comps;
		std::deque<int>		mainDeq;
		std::vector<int>	mainVec;
		std::vector<int>	remaining;
		std::vector<int>*	dividedVec;
		int					originalSizeDividedVec;
		int					mainIncrement;
		int					countPend;

		PmergeMe	(void);
		PmergeMe	(int _sizeStr);
		PmergeMe	(const PmergeMe &);
		~PmergeMe	(void);
		PmergeMe&	operator= ( const PmergeMe &);
		void		fordJonhson(void);
		void		printVec(std::vector<int> vec);
		void		cleanDividedVec(void);
		void		divideAndComp(size_t size, size_t nbInsidePacket, size_t sizeDividedVec);
		void		fillDividedVec(int nbInsidePacket);
		void		fillMainVec(size_t sizeDividedVec);
		void		fillmainVecAndPend(std::vector<int>& pend, size_t sizeDividedVec, size_t nbInsidePacket);
		int			computeIncrement(std::vector<int>& pend, size_t nbInsidePacket, std::vector<int>& jacobsthalNumber, int j);
		void		binaryJacobsthalNbsInsert(std::vector<int>& pend, std::vector<int> copyMain, std::vector<int> jacobsthalNumber, int nbInsidePacket);
		void		pushFirstPacket(std::vector<int> vec, int nbInsidePacket);
		void		swap(int sizeDividedVec, int nbInsidePacket);
		void		fillPend(std::vector<int>* pend, size_t sizeDividedVec, size_t nbInsidePacket);
		void		resizeDividedArrayVec();
		void		printArrayVecs(int sizeDividedVec);
		void		to_sort(int argc, char **argv);
		void		sortVec();
		std::vector<int>::iterator searchNumber(std::vector<int>::iterator it_bound, int value);
		void	printInformation(std::vector<int> notSorted, double time_elapsed_vec, double time_elapsed_deq);

		bool		fillContainers(int argc, char**argv);
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

// class	PmergeMe
// {
// 	public:
// 		std::vector<int>	remaining;
// 		int			sizeDividedVec;
// 		int			mainIncrement;
// 		int			countPend;
//
// 		PmergeMe	(void);
// 		PmergeMe	(int _sizeStr);
// 		PmergeMe	(const PmergeMe &);
// 		~PmergeMe	(void);
// 		PmergeMe&	operator= ( const PmergeMe &);
// 		void		fordJonhson(void);
// 		void		fillVec(int argc, char**argv);
// 		void		printVec(std::vector<int> vec);
// 		void		cleanDividedVec(std::vector<int>*& dividedVec, int sizeDividedVec);
// 		void		divideAndComp(std::vector<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedVec);
// 		void		fillDividedVec(std::vector<int>*& dividedVec, int nbInsidePacket);
// 		void		fillMainVec(std::vector<int>*& dividedVec, size_t sizeDividedVec);
// 		void		fillMainAndPend(std::vector<int>*& dividedVec, size_t sizeDividedVec, size_t nbInsidePacket);
// 		int			computeIncrement(std::vector<int>& pend, size_t nbInsidePacket, std::vector<int>& jacobsthalNumber, int j);
// 		void		pushFirstPacket(std::vector<int>*& DividedVec, std::vector<int> vec, int nbInsidePacket);
//
// 		void		binaryJacobsthalNbsInsert(std::vector<int>*& DividedVec, std::vector<int> copyMain, std::vector<int> jacobsthalNumber, int nbInsidePacket);
// 		void		swap(std::vector<int>*& dividedVec, int sizeDividedVec, int nbInsidePacket);
// 		void		fillPend(std::vector<int>* pend, size_t sizeDividedVec, size_t nbInsidePacket);
// 		void		resizeDividedArrayVec();
// 		void		printArrayVecs(std::vector<int>*& dividedVec, int sizeDividedVec);
// 		std::vector<int>::iterator searchNumber(std::vector<int>::iterator it_bound, int value);
// 		void	printInformation(std::vector<int> notSorted, double time_elapsed_vec, double time_elapsed_deq);
// 		void	to_sort(int argc, char **argv);
// 		void	sortVec(std::vector<int>& vec);
// 		void	sortDeque();
//
// 		bool	fillContainers(int argc, char**argv);
// 	private:
// };
