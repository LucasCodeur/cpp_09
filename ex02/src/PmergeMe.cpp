/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/26 11:45:53 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "debug.hpp"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iomanip>
#include <vector>

int PmergeMe::nbr_of_comps = 0;

PmergeMe::PmergeMe (void)
{
	// std::cout << "PmergeMe Default constructeur called\n";
}

// PmergeMe::PmergeMe (const PmergeMe)
// {
// 	// if (this != &other)
// 	// {
// 	// }
// 	// std::cout << "PmergeMe Copy constructeur called\n";
// }

PmergeMe::PmergeMe (int)
{
	// std::cout << "PmergeMe Parameterized constructeur called\n";
}

// PmergeMe& PmergeMe::operator= (const PmergeMe &other)
// {
// 	// if (this != &other)
// 	// {
// 	// }
// 	return (*this);
// }

PmergeMe::~PmergeMe (void)
{
	// std::cout << "PmergeMe Destructeur called\n";
}

void		PmergeMe::sortVec()
{
	size_t	sizeDividedVec;

	int	size = this->mainVec.size();

	if (size % 2 == 0)
		sizeDividedVec = size / 2;
	else
		sizeDividedVec = size / 2 + 1;

	this->originalSizeDividedVec = sizeDividedVec;
	std::vector<int>*	dividedVec = new std::vector<int>[sizeDividedVec];
	divideAndComp(dividedVec, size, 1, sizeDividedVec);

	std::vector<int> pend;
	fillmainVecAndPend(dividedVec, pend, sizeDividedVec, 1);

	std::vector<int> jacobsthalNbs;
	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);
	std::vector<int> copyMain = this->mainVec;
	while (this->countPend > 0)
	{
		this->mainIncrement = 0;
		binaryJacobsthalNbsInsert(pend, copyMain, jacobsthalNbs, 1);
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
	}
	printVec(this->mainVec);
	delete [] dividedVec;
}

void	PmergeMe::to_sort(int argc, char **argv)
{
	fillContainers(argc, argv);

	std::vector<int>	notSorted = this->mainVec;

	clock_t start_vec = clock();
	this->sortVec();
	clock_t end_vec = clock();

	double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;

	this->printInformation(notSorted, time_elapsed_vec, 0);
}
//
// void	PmergeMe::sortVec(std::vector<int>& vec)
// {
// 	int			size = vec.size();
// 	size_t			sizeDividedVec = (size % 2 == 0) ? size / 2 : size / 2 + 1;
// 	this->sizeDividedVec = sizeDividedVec;
// 	std::vector<int>*	dividedVec = new std::vector<int>[sizeDividedVec + 4];
// 	std::vector<int>	jacobsthalNbs;
// 	std::vector<int>	pend;
//
// 	dividedVec[0] = this->vec;
// 	divideAndComp(dividedVec, size, 1, sizeDividedVec);
//
// 	PRINT("Sort Vec: print array vec after divided and comp", RED, "\n");
// 	this->printArrayVecs(dividedVec, sizeDividedVec);
// 	fillMainAndPend(dividedVec, sizeDividedVec, 1);
//
// 	jacobsthalNbs.push_back(1);
// 	jacobsthalNbs.push_back(3);
// 	std::vector<int> copyMain = dividedVec[0];
// 	while (this->countPend > 0)
// 	{
// 		this->mainIncrement = 0;
// 		binaryJacobsthalNbsInsert(dividedVec, copyMain, jacobsthalNbs, 1);
// 		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
// 		jacobsthalNbs.erase(jacobsthalNbs.begin());
// 	}
// 	delete [] dividedVec;
// }

void		PmergeMe::divideAndComp(std::vector<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedVec)
{
	if (nbInsidePacket > 1)
	{
		this->cleanDividedVec(dividedVec);
		this->fillDividedVec(dividedVec, nbInsidePacket);
	}
	this->swap(dividedVec, sizeDividedVec, nbInsidePacket);
	this->fillMainVec(dividedVec, sizeDividedVec);
	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;
	divideAndComp(dividedVec, size, nbInsidePacket, sizeDividedVec);
	std::vector<int> pend;
	std::vector<int> jacobsthalNbs;
	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);
	this->cleanDividedVec(dividedVec);
	this->fillDividedVec(dividedVec, nbInsidePacket);
	fillmainVecAndPend(dividedVec, pend, sizeDividedVec, nbInsidePacket);
	std::vector<int> copyMain = this->mainVec;
	while (this->countPend > 0)
	{
		this->mainIncrement = 0;
		binaryJacobsthalNbsInsert(pend, copyMain, jacobsthalNbs, nbInsidePacket);
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
	}
	if (remaining.empty() == true)
		return ;
	for (size_t i = 0; i < this->remaining.size(); i++)
	{
		this->mainVec.push_back(remaining[i]);
	}
	remaining.clear();
}

int	PmergeMe::computeIncrement(std::vector<int>& pend, size_t nbInsidePacket, std::vector<int>& jacobsthalNumber, int j)
{
	size_t	increment = 0;

	this->mainIncrement = 0;

		increment = ((jacobsthalNumber[1]) * nbInsidePacket) - 1 - j;
		if (increment >= pend.size())
			increment = pend.size() - 1;
	this->mainIncrement = increment;
	return (increment);
}


void	PmergeMe::pushFirstPacket(std::vector<int> vec, int nbInsidePacket)
{
	for (int i = nbInsidePacket; i > 0; i--)
	{
		this->mainVec.insert(this->mainVec.begin(), vec[i - 1]);
		this->countPend--;
	}
}

std::vector<int>::iterator binarySearch(std::vector<int>& v, std::vector<int>::iterator it_bound, int target, int nbInsidePacket);

void	PmergeMe::binaryJacobsthalNbsInsert(std::vector<int>& pend, std::vector<int> copyMain, std::vector<int> jacobsthalNumber, int nbInsidePacket)
{
	size_t	sizePend = pend.size();
	mainVec.reserve(mainVec.size() + sizePend);
	if (sizePend == 0)
		return ;
	if (jacobsthalNumber[1] == 3)
		this->pushFirstPacket(pend, nbInsidePacket);
	int	count = jacobsthalNumber[1] - jacobsthalNumber[0];
	for (size_t j = 0; count > 0 && this->countPend > 0; j += nbInsidePacket)	
	{

		int increment = 0;
		if (this->mainIncrement == 0)
			increment = computeIncrement(pend, nbInsidePacket, jacobsthalNumber, j);
		if (increment < 0 || increment >= static_cast<int>(pend.size()))
			return ;
		int	temp = pend[this->mainIncrement];
		std::vector<int>::iterator it_bound;	
		if (static_cast<size_t>(this->mainIncrement) >= copyMain.size())
			it_bound = this->mainVec.end() - 1;
		else
			it_bound  = std::find(this->mainVec.begin(), this->mainVec.end(), copyMain[this->mainIncrement]);
		std::vector<int>::iterator it;
		it = binarySearch(this->mainVec, it_bound , pend[this->mainIncrement], nbInsidePacket);
		if (*it > temp)
		{
			for (int k = 0; k < nbInsidePacket; k++)
			{
					int temp = pend[this->mainIncrement - k];
					this->mainVec.insert(it - nbInsidePacket + 1, temp);
					this->countPend--;
			}
		}
		else
		{
			for (int k = 0; k < nbInsidePacket; k++)
			{
					int temp = pend[this->mainIncrement - k];
					this->mainVec.insert(it + 1, temp);
					this->countPend--;
			}

		}
		count--;
		this->mainIncrement -= nbInsidePacket;
	}
}

std::vector<int>::iterator PmergeMe::searchNumber(std::vector<int>::iterator it_bound, int value)
{
	std::vector<int>::iterator it;

	it = it_bound;
	for (std::vector<int>::iterator it = this->mainVec.begin(); it != it_bound; it++)
	{
		if (*it >= value)	
			return (it);
	}
	return (it);
}

std::vector<int> keepOnlyLastElements(std::vector<int>& v, int nbInsidePackets)
{
    std::vector<int> res;

    for (size_t i = nbInsidePackets - 1; i < v.size(); i++)
    {
       if ((i + 1) % (nbInsidePackets) == 0) 
            res.push_back(v[i]);
    }
    return (res);
}

std::vector<int>::iterator binarySearch(std::vector<int>& v, std::vector<int>::iterator it_bound, int target, int nbInsidePacket)
{	
	int high = 0;
	int	low = 0;
	std::vector<int> temp;
	if (nbInsidePacket != 1)
		 temp = keepOnlyLastElements(v, nbInsidePacket);
	else
		temp = v;

	std::vector<int>::iterator it_temp = temp.begin();
	while (it_temp != temp.end() && *it_temp != *it_bound)
	{
		it_temp++;
		high++;
	}
    while (low < high) {
      
        int mid = ((high - low) / 2) + low;
        if (temp[mid] <= target)
            low = mid + 1;
        else
			high = mid;
    }
  	
	std::vector<int>::iterator temp_it;
	if (static_cast<size_t>(low) < temp.size())
		temp_it = temp.begin() + low;
	else
		temp_it = temp.end();
	return(std::find(v.begin(), v.end(), *temp_it));
}

void	PmergeMe::fillmainVecAndPend(std::vector<int>*& dividedVec, std::vector<int>& pend, size_t sizeDividedVec, size_t nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		std::vector<int> temp;
		size_t		count; 

		if (this->mainVec.size() % 2 == 0)
			count = this->mainVec.size();
		else
			count = this->mainVec.size() - 1;
		for (size_t i = 0;  i < count; i++)
		{
			if (i % 2 == 0)
				pend.push_back(this->mainVec[i]);
			else
				temp.push_back(this->mainVec[i]);
		}
		this->mainVec.clear();
		this->mainVec = temp;
	}
	for (size_t j = 0; j < sizeDividedVec; j++)
	{
		if (j % 2 == 0)
		{
			if (dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					pend.push_back(dividedVec[j][k]);
			}
			else
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					this->remaining.push_back(dividedVec[j][k]);
			}
		}
		else
		{
			if (dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					this->mainVec.push_back(dividedVec[j][k]);
			}
			else
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					this->remaining.push_back(dividedVec[j][k]);
			}
		}
	}
	this->countPend = pend.size();
}

void		PmergeMe::fillDividedVec(std::vector<int>*& dividedVec, int nbInsidePacket)
{
	int	j = 0;
	int	nbAddInsidePacket = 0;

	for (size_t i = 0; i < this->mainVec.size(); i++)
	{
		dividedVec[j].push_back(this->mainVec[i]);
		nbAddInsidePacket++;
		if (nbAddInsidePacket == nbInsidePacket)
		{
			j++;
			nbAddInsidePacket = 0;
		}
	}
	mainVec.erase(mainVec.begin(), mainVec.end());
}

void	PmergeMe::cleanDividedVec(std::vector<int>*& dividedVec)
{
	for (int i = 0; i < this->originalSizeDividedVec; i++)
	{
		dividedVec[i].erase(dividedVec[i].begin(), dividedVec[i].end());
	}
}

void	PmergeMe::swap(std::vector<int>*& dividedVec, int sizeDividedVec, int nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		int			temp = 0;
		size_t		size = this->mainVec.size();

		for (size_t i = 0; i < size; i += 2)
		{
			if (i + 1 < size && this->mainVec[i] > this->mainVec[i + 1])
			{
				temp = this->mainVec[i];
				this->mainVec[i] = this->mainVec[i + 1];
				this->mainVec[i + 1] = temp;
			}
		}
	}
	else
	{
		for (int i = 0; i < sizeDividedVec - 1 && dividedVec[i + 1].size() == static_cast<size_t>(nbInsidePacket); i += 2)
		{
			if (dividedVec[i].back() > dividedVec[i + 1].back())
				dividedVec[i].swap(dividedVec[i + 1]);
		}
	}
}

void		PmergeMe::fillMainVec(std::vector<int>*& dividedVec, size_t sizeDividedVec)
{
	for (size_t j = 0; j < sizeDividedVec; j++)
	{
		for (size_t i = 0; i < dividedVec[j].size(); i++)
			this->mainVec.push_back(dividedVec[j][i]);
		dividedVec[j].erase(dividedVec[j].begin(), dividedVec[j].end());
	}
}

void		PmergeMe::printVec(std::vector<int> vec)
{
	if (vec.size() != 0)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << " ";
		}
	}
	std::cout << std::endl;
}

void	PmergeMe::printArrayVecs(int sizeDividedVec)
{
	for (int i = 0; i < sizeDividedVec; i++)
	{
		if (dividedVec[i].size() != 0)
			this->printVec(dividedVec[i]);
	}
}

void	PmergeMe::printInformation(std::vector<int> notSorted, double time_elapsed_vec, double time_elapsed_deq)
{

	std::cout << "\n";
	PRINT("Before: ", RED, "")
	printVec(notSorted);
	PRINT("After: ", GREEN, "")
	printVec(this->mainVec);
	std::cout << "Time to process a range of " << this->mainVec.size()
			  << " elements with std::vector: " << std::fixed << std::setprecision(6)
			  << time_elapsed_vec << "s\n";
	std::cout << "Time to process a range of " << this->mainVec.size()
			  << " elements with std::dequeu: " << std::fixed << std::setprecision(6)
			  << time_elapsed_deq << "s\n";
	std::cout << "Number of comparisons: " << this->nbr_of_comps << "\n";

}

static bool	checkDuplicates(std::vector<int>& vec, int nb);

bool		PmergeMe::fillContainers(int argc, char**argv)
{
	std::string	str;
	std::string	substr;
	size_t		pos = 0;
	int		number = 0;

	for (int i = 1; i < argc; i++)
	{
		str = argv[i];	
		if (str.empty() == true)
			continue ;
		while (1)
		{
			pos = str.find(" ");
			if (pos != std::string::npos)
			{
				substr = str.substr(0, pos);
				number = strConvert<int>(substr);
				if (checkDuplicates(this->mainVec, number) == false)
					return (false);
				this->mainVec.push_back(number);
				this->mainDeq.push_back(number);
				str.erase(0, pos + 1);
			}
			else
			{
				number = strConvert<int>(str);
				this->mainVec.push_back(number);
				this->mainDeq.push_back(number);
				break ;
			}
		}
	}
	return (true);
}

static bool	checkDuplicates(std::vector<int>& vec, int nb)
{
	int	size = vec.size();
	for (int i = 0; i < size; i++) 
	{
		if (nb == vec[i])
			return (false);

	}
	return (true);
}
