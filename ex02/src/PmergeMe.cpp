/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/06 13:33:16 by lud-adam         ###   ########.fr       */
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

void		printVec(std::vector<int> vec);

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
	std::vector<int>*	dividedVec = NULL;
	std::vector<int>	pend;
	std::vector<int>	remaining;
	size_t				sizeDividedVec;

	int	size = this->mainVec.size();

	if (size % 2 == 0)
		sizeDividedVec = size / 2;
	else
		sizeDividedVec = size / 2 + 1;
	dividedVec= new std::vector<int>[sizeDividedVec];
	divideAndComp(dividedVec, size, 1, sizeDividedVec);
	fillmainVecAndPend(dividedVec, pend, remaining, sizeDividedVec, 1);
	binaryJacobsthalNbsInsert(pend, 1);
	delete [] dividedVec;
}

static bool	isSorted(std::vector<int> vec);

void	PmergeMe::to_sort(int argc, char **argv)
{
	if (fillContainers(argc, argv) == false)
	{
		PRINT("Error: Duplicate number", RED, "\n");
		return ;
	}
	std::vector<int>	notSorted = this->mainVec;

	clock_t start_vec = clock();
	if (isSorted(this->mainVec) == false)
		this->sortVec();
	clock_t end_vec = clock();

	double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;

	this->printInformation(notSorted, time_elapsed_vec, 0);
}

static void	cleanDividedVec(std::vector<int>*& dividedVec, int sizeDividedVec);
static void	swap(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int sizeDividedVec, int nbInsidePacket);
static void	fillDividedVec(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int nbInsidePacket);

void		PmergeMe::divideAndComp(std::vector<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedVec)
{
	std::vector<int> remaining;

	if (nbInsidePacket > 1)
	{
		cleanDividedVec(dividedVec, sizeDividedVec);
		fillDividedVec(dividedVec, mainVec, nbInsidePacket);
	}
	swap(dividedVec, this->mainVec, sizeDividedVec, nbInsidePacket);
	this->fillMainVec(dividedVec, sizeDividedVec);
	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;
	divideAndComp(dividedVec, size, nbInsidePacket, sizeDividedVec);
	std::vector<int> pend;
	cleanDividedVec(dividedVec, sizeDividedVec);
	fillDividedVec(dividedVec, mainVec, nbInsidePacket);
	fillmainVecAndPend(dividedVec, pend, remaining, sizeDividedVec, nbInsidePacket);
	binaryJacobsthalNbsInsert(pend, nbInsidePacket);	
	if (remaining.empty() == true)
		return ;
	for (size_t i = 0; i < remaining.size(); i++)
		this->mainVec.push_back(remaining[i]);
	remaining.clear();
}

static void	swap(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int sizeDividedVec, int nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		int			temp = 0;
		size_t		size = mainVec.size();

		for (size_t i = 0; i < size; i += 2)
		{
			if (i + 1 < size && mainVec[i] > mainVec[i + 1])
			{
				temp = mainVec[i];
				mainVec[i] = mainVec[i + 1];
				mainVec[i + 1] = temp;
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

static std::vector<int>	handleBigNbInsidePacket(std::vector<int>*& dividedVec, std::vector<int>& mainVec, std::vector<int>& remaining, size_t sizeDividedVec, size_t nbInsidePacket);

void	PmergeMe::fillmainVecAndPend(std::vector<int>*& dividedVec, std::vector<int>& pend, std::vector<int>& remaining, size_t sizeDividedVec, size_t nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		std::vector<int> temp;
		size_t			count; 

		count = this->mainVec.size();
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
	else
		pend = handleBigNbInsidePacket(dividedVec, mainVec, remaining, sizeDividedVec, nbInsidePacket);
}

static std::vector<int>	handleBigNbInsidePacket(std::vector<int>*& dividedVec, std::vector<int>& mainVec, std::vector<int>& remaining, size_t sizeDividedVec, size_t nbInsidePacket)
{
	std::vector<int> res;

	for (size_t j = 0; j < sizeDividedVec; j++)
	{
		if (j % 2 == 0)
		{
			if (dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedVec[j].size(); k++)
					res.push_back(dividedVec[j][k]);
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
	return (res);
}

static std::vector<int>::iterator	binarySearch(std::vector<int>& v, std::vector<int>::iterator it_bound, int target, int nbInsidePacket);
static void							insertion(std::vector<int>& mainVec, std::vector<int>& pend, std::vector<int>& copyMain, int increment, int nbInsidePacket, size_t& countPend);
static void							pushFirstPacket(std::vector<int>& mainVec, std::vector<int> vec, size_t& countPend,  int nbInsidePacket);
static int							computeIncrement(std::vector<int>& pend, size_t nbInsidePacket, std::vector<int>& jacobsthalNbs, int j);

void	PmergeMe::binaryJacobsthalNbsInsert(std::vector<int>& pend, int nbInsidePacket)
{
	size_t				countPend = pend.size();
	if (countPend == 0)
		return ;

	mainVec.reserve(mainVec.size() + countPend);

	std::vector<int> jacobsthalNbs;
	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);

	std::vector<int> copyMain = this->mainVec;

	pushFirstPacket(this->mainVec, pend, countPend, nbInsidePacket);

	while (countPend > 0)
	{
		int increment = 0;
		int	count = jacobsthalNbs[1] - jacobsthalNbs[0];

		for (size_t j = 0; count > 0 && countPend > 0; j += nbInsidePacket)	
		{
			if (increment == 0)
				increment = computeIncrement(pend, nbInsidePacket, jacobsthalNbs, j);
			if (increment < 0 || increment >= static_cast<int>(pend.size()))
				return ;
			insertion(this->mainVec, pend, copyMain, increment, nbInsidePacket, countPend);
			count--;
			increment -= nbInsidePacket;
		}
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
	}
}

static void	insertion(std::vector<int>& mainVec, std::vector<int>& pend, std::vector<int>& copyMain, int increment, int nbInsidePacket, size_t& countPend)
{
	int	temp = pend[increment];

	std::vector<int>::iterator it_bound;	

	if (static_cast<size_t>(increment) >= copyMain.size())
		it_bound = mainVec.end() - 1;
	else
		it_bound  = std::find(mainVec.begin(), mainVec.end(), copyMain[increment]) - nbInsidePacket;

	std::vector<int>::iterator it;
	it = binarySearch(mainVec, it_bound , pend[increment], nbInsidePacket);
	if (*it > temp)
	{
		for (int k = 0; k < nbInsidePacket; k++)
		{
				int temp = pend[increment - k];
				mainVec.insert(it - nbInsidePacket + 1, temp);
				countPend--;
		}
	}
	else
	{
		for (int k = 0; k < nbInsidePacket; k++)
		{
				int temp = pend[increment - k];
				mainVec.insert(it + 1, temp);
				countPend--;
		}

	}
}

static std::vector<int> keepOnlyLastElements(std::vector<int>& v, int nbInsidePackets);

static std::vector<int>::iterator binarySearch(std::vector<int>& v, std::vector<int>::iterator it_bound, int target, int nbInsidePacket)
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
		PmergeMe::nbr_of_comps++;
    }
  	
	std::vector<int>::iterator temp_it;
	if (static_cast<size_t>(low) < temp.size())
		temp_it = temp.begin() + low;
	else
		temp_it = temp.end();
	return(std::find(v.begin(), v.end(), *temp_it));
}

static std::vector<int> keepOnlyLastElements(std::vector<int>& v, int nbInsidePackets)
{
    std::vector<int> res;

    for (size_t i = nbInsidePackets - 1; i < v.size(); i++)
    {
       if ((i + 1) % (nbInsidePackets) == 0) 
            res.push_back(v[i]);
    }
    return (res);
}

static int	computeIncrement(std::vector<int>& pend, size_t nbInsidePacket, std::vector<int>& jacobsthalNbs, int j)
{
	size_t	increment = 0;
	size_t	pendSize = pend.size();

	increment = 0;
	increment = ((jacobsthalNbs[1]) * nbInsidePacket) - 1 - j;
	if (increment >= pendSize)
		increment = pendSize - 1;
	return (increment);
}


static void	pushFirstPacket(std::vector<int>& mainVec, std::vector<int> vec, size_t& countPend,  int nbInsidePacket)
{
	for (int i = nbInsidePacket; i > 0; i--)
	{
		mainVec.insert(mainVec.begin(), vec[i - 1]);
		countPend--;
	}
}

static void		fillDividedVec(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int nbInsidePacket)
{
	int	j = 0;
	int	nbAddInsidePacket = 0;

	for (size_t i = 0; i < mainVec.size(); i++)
	{
		dividedVec[j].push_back(mainVec[i]);
		nbAddInsidePacket++;
		if (nbAddInsidePacket == nbInsidePacket)
		{
			j++;
			nbAddInsidePacket = 0;
		}
	}
	mainVec.erase(mainVec.begin(), mainVec.end());
}

static void	cleanDividedVec(std::vector<int>*& dividedVec, int sizeDividedVec)
{
	for (int i = 0; i < sizeDividedVec; i++)
	{
		dividedVec[i].erase(dividedVec[i].begin(), dividedVec[i].end());
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
				if (checkDuplicates(this->mainVec, number) == false)
					return (false);
				this->mainVec.push_back(number);
				this->mainDeq.push_back(number);
				str.erase(0, pos + 1);
			}
			else
			{
				number = strConvert<int>(str);
				if (checkDuplicates(this->mainVec, number) == false)
					return (false);
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

static bool	isSorted(std::vector<int> vec)
{
	int size = vec.size();

	for (int i = 1; i < size; i++)
	{
		if (vec[i - 1] > vec[i])
			return (false);
	}
	return (true);
}

// PRINT

void	printVec(std::vector<int> vec)
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


void	printArrayVecs(std::vector<int>*& dividedVec, int sizeDividedVec)
{
	for (int i = 0; i < sizeDividedVec; i++)
	{
		if (dividedVec[i].size() != 0)
			printVec(dividedVec[i]);
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
