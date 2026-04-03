/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/03 16:12:10 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "debug.hpp"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iomanip>

#include <vector>
#include <deque>

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

#include <cmath>

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

void	PmergeMe::to_sort(int argc, char **argv)
{
	fillContainers(argc, argv);

	std::vector<int>	notSorted = this->vec;
	
	clock_t start_vec = clock();
	this->sortVec(vec);
	clock_t end_vec = clock();

	double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;

	this->printInformation(notSorted, time_elapsed_vec, 0);
}

void	PmergeMe::sortVec(std::vector<int>& vec)
{
	int			size = vec.size();
	size_t			sizeDividedVec = (size % 2 == 0) ? size / 2 : size / 2 + 1;
	this->sizeDividedVec = sizeDividedVec;
	std::vector<int>*	dividedVec = new std::vector<int>[sizeDividedVec + 3];
	std::vector<int>	jacobsthalNbs;
	std::vector<int>	pend;

	dividedVec[0] = this->vec;
	PRINT("Sort vec: dividedvec[0]", RED, "\n");
	this->printVec(dividedVec[0]);
	divideAndComp(dividedVec, size, 1, sizeDividedVec);
	this->printArrayVecs(dividedVec, sizeDividedVec);
	fillMainAndPend(dividedVec, sizeDividedVec, 1);

	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);
	std::vector<int> copyMain = dividedVec[0];
	while (this->countPend > 0)
	{
		this->mainIncrement = 0;
		binaryJacobsthalNbsInsert(dividedVec, copyMain, jacobsthalNbs, 1);
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
	}
	delete [] dividedVec;
}

void		PmergeMe::divideAndComp(std::vector<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedVec)
{
	if (nbInsidePacket > 1)
	{
		this->cleanDividedVec(dividedVec, sizeDividedVec);
		PRINT("Dividedandcomp: dividedvec : inside if nbInsidePacket > 1: after clean divided vec", BLUE, "\n");
		this->printArrayVecs(dividedVec, sizeDividedVec);

		this->fillDividedVec(dividedVec, nbInsidePacket);

		PRINT("Dividedandcomp: dividedvec : inside if nbInsidePacket > 1 : after fill divided vec", GREEN, "\n");
		this->printArrayVecs(dividedVec, sizeDividedVec);
	}

	PRINT("Dividedandcomp: dividedvec", RED, "\n");
	this->printArrayVecs(dividedVec, sizeDividedVec);

	this->swap(dividedVec, sizeDividedVec, nbInsidePacket);

	PRINT("Dividedandcomp: dividedvec: after swap", RED, "\n");
	this->printArrayVecs(dividedVec, sizeDividedVec);

	this->fillMainVec(dividedVec, sizeDividedVec);

	PRINT("Dividedandcomp: dividedvec: after fillmain", RED, "\n");
	this->printArrayVecs(dividedVec, sizeDividedVec);

	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;

	divideAndComp(dividedVec, size,  nbInsidePacket, sizeDividedVec);

	std::vector<int> pend;
	std::vector<int> jacobsthalNbs;

	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);

	//FIXME: Take off maybe
	this->cleanDividedVec(dividedVec, sizeDividedVec);
	this->fillDividedVec(dividedVec, nbInsidePacket);
	this->fillMainAndPend(dividedVec, sizeDividedVec, nbInsidePacket);

	std::vector<int> copyMain = dividedVec[0];

	//WARN: Takeoff
	while (this->countPend > 0)
	{
		this->sizeDividedVec = sizeDividedVec;
		this->mainIncrement = 0;
		binaryJacobsthalNbsInsert(dividedVec, copyMain, jacobsthalNbs, nbInsidePacket);
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
	}
	std::vector<int>& mainVec = dividedVec[0];
	std::vector<int>& remainingVec = dividedVec[2];
	if (remainingVec.empty() == true)
		return ;
	for (size_t i = 0; i < remainingVec.size(); i++)
		mainVec.push_back(remainingVec[i]);
	remainingVec.clear();
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


void	PmergeMe::pushFirstPacket(std::vector<int>*& DividedVec, std::vector<int> pend, int nbInsidePacket)
{
	for (int i = nbInsidePacket; i > 0; i--)
	{
		DividedVec[0].insert(DividedVec[0].begin(), pend[i - 1]);
		this->countPend--;
	}
}

std::vector<int>::iterator binarySearch(std::vector<int>& v, std::vector<int>::iterator it_bound, int target, int nbInsidePacket);

void	PmergeMe::binaryJacobsthalNbsInsert(std::vector<int>*& dividedVec, std::vector<int> copyMain, std::vector<int> jacobsthalNumber, int nbInsidePacket)
{
	std::vector<int>& pendVec = dividedVec[1];
	std::vector<int>& mainVec = dividedVec[0];


	//FIXME: Maybe take off
	size_t	sizePendVec = pendVec.size();
	if (sizePendVec == 0)
		return ;

	if (jacobsthalNumber[1] == 3)
		this->pushFirstPacket(dividedVec, pendVec, nbInsidePacket);

	mainVec.reserve(mainVec.size() + sizePendVec);
	// PRINT("binaryJacobsthalNbsInsert: dividedvec: after pushFirstPacket", YELLOW, "\n");
	// this->printArrayVecs(dividedVec, this->sizeDividedVec);

	int	count = jacobsthalNumber[1] - jacobsthalNumber[0];

	for (size_t j = 0; count > 0 && this->countPend > 0; j += nbInsidePacket)	
	{
		if (this->mainIncrement == 0)
			computeIncrement(pendVec, nbInsidePacket, jacobsthalNumber, j);

		if (this->mainIncrement < 0 || this->mainIncrement >= static_cast<int>(pendVec.size()))
		{
			PRINT("Jacob: increment wrong", RED, "\n");
			return ;
		}

		int	temp = pendVec[this->mainIncrement];
		std::vector<int>::iterator it_bound;

		if (static_cast<size_t>(this->mainIncrement) >= copyMain.size())
			it_bound = mainVec.end() - 1;
		else
			it_bound  = std::find(mainVec.begin(), mainVec.end(), copyMain[this->mainIncrement]);

		std::vector<int>::iterator it;
		it = binarySearch(mainVec, it_bound , pendVec[this->mainIncrement], nbInsidePacket);

		if (*it > temp)
		{
			for (int k = 0; k < nbInsidePacket; k++)
			{
					int temp = pendVec[this->mainIncrement - k];
					mainVec.insert(it - nbInsidePacket + 1, temp);
					this->countPend--;
			}
		}
		else
		{
			for (int k = 0; k < nbInsidePacket; k++)
			{
					int temp = pendVec[this->mainIncrement - k];
					mainVec.insert(it + 1, temp);
					this->countPend--;
			}
		}
		count--;
		this->mainIncrement -= nbInsidePacket;
	}
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

std::vector<int>::iterator binarySearch(
    std::vector<int>& v,
    std::vector<int>::iterator it_bound,
    int target,
    int nbInsidePacket)
{
	int low = 0;
	int high = 0;
	std::vector<int> temp;

	if (nbInsidePacket != 1)
		temp = keepOnlyLastElements(v, nbInsidePacket);
	else
		temp = v;

	int boundIndex = (it_bound - v.begin()) / nbInsidePacket;

	high = boundIndex + 1;

	while (low < high)
	{
		int mid = low + (high - low) / 2;

		if (temp[mid] <= target)
		    low = mid + 1;
		else
		    high = mid;
		PmergeMe::nbr_of_comps++;
	}

	if (low >= (int)temp.size())
		return (v.end() - 1);

	int realIndex;

	if (nbInsidePacket == 1)
		realIndex = low;
	else
		realIndex = (low + 1) * nbInsidePacket - 1;

	return (v.begin() + realIndex);
}

void	PmergeMe::fillMainAndPend(std::vector<int>*& dividedVec, size_t sizeDividedVec, size_t nbInsidePacket)
{
	std::vector<int>& mainVec = dividedVec[0];
	std::vector<int>& pendVec = dividedVec[1];
	std::vector<int>& remainingVec = dividedVec[2];

	if (nbInsidePacket == 1)
	{
		std::vector<int> temp;
		size_t		count; 

		if (mainVec.size() % 2 == 0)
			count = mainVec.size();
		else
			count = mainVec.size() - 1;
		for (size_t i = 0;  i < count; i++)
		{
			if (i % 2 == 0)
				pendVec.push_back(mainVec[i]);
			else
				temp.push_back(mainVec[i]);
		}
		mainVec.clear();
		mainVec = temp;
	}
	for (size_t j = 3; j < sizeDividedVec + 3; j++)
	{
		if (j % 2 == 0)
		{
			if (dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					pendVec.push_back(dividedVec[j][k]);
			}
			else
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					remaining.push_back(dividedVec[j][k]);
			}
		}
		else
		{
			if (dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					mainVec.push_back(dividedVec[j][k]);
			}
			else
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					remaining.push_back(dividedVec[j][k]);
			}
		}
	}
	this->countPend = pendVec.size();
}

void		PmergeMe::fillDividedVec(std::vector<int>*& dividedVec, int nbInsidePacket)
{
	int	j = 2;
	int	nbAddInsidePacket = 0;

	for (size_t i = 0; i < dividedVec[0].size(); i++)
	{
		dividedVec[j].push_back(dividedVec[0][i]);
		nbAddInsidePacket++;
		if (nbAddInsidePacket == nbInsidePacket)
		{
			j++;
			nbAddInsidePacket = 0;
		}
	}
	dividedVec[0].erase(dividedVec[0].begin(), dividedVec[0].end());
}

void	PmergeMe::cleanDividedVec(std::vector<int>*& dividedVec, int sizeDividedVec)
{
	for (int i = 3; i < sizeDividedVec + 3; i++)
	{
		dividedVec[i].erase(dividedVec[i].begin(), dividedVec[i].end());
	}
}

void	PmergeMe::swap(std::vector<int>*& dividedVec, int sizeDividedVec, int nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		int	temp = 0;
		size_t	size = dividedVec[0].size();

		for (size_t i = 0; i < size; i += 2)
		{
			if (i + 1 < size && dividedVec[0][i] > dividedVec[0][i + 1])
			{
				temp = dividedVec[0][i];
				dividedVec[0][i] = dividedVec[0][i + 1];
				dividedVec[0][i + 1] = temp;
			}
			PmergeMe::nbr_of_comps++;
		}
	}
	else
	{
		for (int i = 3; i < sizeDividedVec + 2 && dividedVec[i + 1].size() == static_cast<size_t>(nbInsidePacket); i += 2)
		{
			if (dividedVec[i].back() > dividedVec[i + 1].back())
				dividedVec[i].swap(dividedVec[i + 1]);
			PmergeMe::nbr_of_comps++;
		}
	}
}

void		PmergeMe::fillMainVec(std::vector<int>*& dividedVec, size_t sizeDividedVec)
{
	for (size_t j = 3; j < sizeDividedVec + 3; j++)
	{
		for (size_t i = 0; i < dividedVec[j].size(); i++)
			dividedVec->push_back(dividedVec[j][i]);
		dividedVec[j].erase(dividedVec[j].begin(), dividedVec[j].end());
	}
}

// PARSING

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
				if (checkDuplicates(this->vec, number) == false)
					return (false);
				this->vec.push_back(number);
				this->deq.push_back(number);
				str.erase(0, pos + 1);
			}
			else
			{
				number = strConvert<int>(str);
				this->vec.push_back(number);
				this->deq.push_back(number);
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

void	PmergeMe::printVec(std::vector<int> vec)
{
	if (vec.size() != 0)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i];
			if (i != vec.size() - 1)
				std::cout << ", "; 
		}
	}
	std::cout << std::endl;
}

void	PmergeMe::printArrayVecs(std::vector<int>*& dividedVec, int sizeDividedVec)
{
	for (int i = 0; i < sizeDividedVec + 3; i++)
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
	printVec(this->vec);
	std::cout << "Time to process a range of " << vec.size()
			  << " elements with std::vector: " << std::fixed << std::setprecision(6)
			  << time_elapsed_vec << "s\n";
	std::cout << "Time to process a range of " << vec.size()
			  << " elements with std::dequeu: " << std::fixed << std::setprecision(6)
			  << time_elapsed_deq << "s\n";
	std::cout << "Number of comparisons: " << this->nbr_of_comps << "\n";

}
