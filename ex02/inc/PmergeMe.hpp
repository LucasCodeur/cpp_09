/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:47:29 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/06 13:48:36 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP 
# define PMERGEME_HPP

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

		PmergeMe	(void);
		PmergeMe	(const PmergeMe &other);
		~PmergeMe	(void);
		PmergeMe&	operator= (const PmergeMe &other);

		void		to_sort(int argc, char **argv);

		void		sortVec();
		void		divideAndComp(std::vector<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedVec);
		void		fillmainVecAndPend(std::vector<int>*& dividedVec, std::vector<int>& pend, std::vector<int>& remaining,  size_t sizeDividedVec, size_t nbInsidePacket);
		void		binaryJacobsthalNbsInsert(std::vector<int>& pend, int nbInsidePacket);

		void		sortDeq();
		void		divideAndCompDeq(std::deque<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedVec);
		void		fillmainDeqAndPend(std::deque<int>*& dividedDeq, std::deque<int>& pend, std::deque<int>& remaining,  size_t sizeDividedDeq, size_t nbInsidePacket);
		void		binaryJacobsthalNbsInsertDeq(std::deque<int>& pend, int nbInsidePacket);

		void		printInformation(std::vector<int> notSorted, double time_elapsed_vec, double time_elapsed_deq);

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
