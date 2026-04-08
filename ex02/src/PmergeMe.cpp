/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/04/06 13:49:49 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "debug.hpp"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iomanip>
#include <vector>

static void	printVec(std::vector<int> vec);
static void	printDeq(std::deque<int> deq);

PmergeMe::PmergeMe (void) {}

PmergeMe::PmergeMe (const PmergeMe& other) {(void)other;}

PmergeMe& PmergeMe::operator= (const PmergeMe &other) { (void)other; return (*this); }

PmergeMe::~PmergeMe (void) {}

static bool	isSorted(std::vector<int> vec);
static bool	fillContainers(int argc, char**argv, std::vector<int>& mainVec, std::deque<int>& mainDeq);

void	PmergeMe::to_sort(int argc, char **argv)
{
	if (fillContainers(argc, argv, this->mainVec, this->mainDeq) == false)
		return ;
	std::vector<int>	notSorted = this->mainVec;

	if (isSorted(this->mainVec) == false)
	{
		clock_t start_vec = clock();
		PRINT("To sort: mainvec", RED, "\n");
		printVec(this->mainVec);
		this->sortVec();
		clock_t end_vec = clock();
		clock_t start_deq = clock();
		PRINT("To sort: maindeq", RED, "\n");
		printDeq(this->mainDeq);
		this->sortDeq();
		clock_t end_deq = clock();

		double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;
		double time_elapsed_deq = static_cast<double>(end_deq - start_deq) / CLOCKS_PER_SEC;

		this->printInformation(notSorted, time_elapsed_vec, time_elapsed_deq);
	}
}

void		PmergeMe::sortVec()
{
	std::vector<int>*	dividedVec = NULL;
	std::vector<int>	pend;
	std::vector<int>	remaining;
	size_t				sizeDividedDeq;

	int	size = this->mainVec.size();

	if (size % 2 == 0)
		sizeDividedDeq = size / 2;
	else
		sizeDividedDeq = size / 2 + 1;

	dividedVec = new std::vector<int>[sizeDividedDeq];

	divideAndComp(dividedVec, size, 1, sizeDividedDeq);
	fillmainVecAndPend(dividedVec, pend, remaining, sizeDividedDeq, 1);
	binaryJacobsthalNbsInsert(pend, 1);

	PRINT("DividedAndComp: End Vec", YELLOW, "\n");
	printVec(this->mainVec);

	delete [] dividedVec;
}

static void	cleanDividedVec(std::vector<int>*& dividedVec, int sizeDividedDeq);
static void	swap(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int sizeDividedDeq, int nbInsidePacket);
static void	fillDividedVec(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int nbInsidePacket);
static void	fillMainVec(std::vector<int>*& dividedVec, std::vector<int>& mainVec, size_t sizeDividedDeq);

void		PmergeMe::divideAndComp(std::vector<int>*& dividedVec, size_t size, size_t nbInsidePacket, size_t sizeDividedDeq)
{
	if (nbInsidePacket > 1)
	{
		cleanDividedVec(dividedVec, sizeDividedDeq);
		fillDividedVec(dividedVec, mainVec, nbInsidePacket);
	}

	swap(dividedVec, this->mainVec, sizeDividedDeq, nbInsidePacket);

	if (nbInsidePacket > 1)
		fillMainVec(dividedVec, this->mainVec, sizeDividedDeq);

	printVec(this->mainVec);
	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;

	divideAndComp(dividedVec, size, nbInsidePacket, sizeDividedDeq);

	std::vector<int> pend;
	std::vector<int> remaining;

	cleanDividedVec(dividedVec, sizeDividedDeq);
	fillDividedVec(dividedVec, mainVec, nbInsidePacket);
	fillmainVecAndPend(dividedVec, pend, remaining, sizeDividedDeq, nbInsidePacket);
	binaryJacobsthalNbsInsert(pend, nbInsidePacket);	

	if (remaining.empty() == true)
		return ;

	for (size_t i = 0; i < remaining.size(); i++)
		this->mainVec.push_back(remaining[i]);

	remaining.clear();
	PRINT("DividedAndComp: End Vec", YELLOW, "\n");
	printVec(this->mainVec);
}

static void	cleanDividedVec(std::vector<int>*& dividedVec, int sizeDividedDeq)
{
	for (int i = 0; i < sizeDividedDeq; i++)
	{
		dividedVec[i].erase(dividedVec[i].begin(), dividedVec[i].end());
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

static void	swap(std::vector<int>*& dividedVec, std::vector<int>& mainVec, int sizeDividedDeq, int nbInsidePacket)
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
		for (int i = 0; i < sizeDividedDeq - 1 && dividedVec[i + 1].size() == static_cast<size_t>(nbInsidePacket); i += 2)
		{
			if (dividedVec[i].back() > dividedVec[i + 1].back())
				dividedVec[i].swap(dividedVec[i + 1]);
		}
	}
}

static std::vector<int>	handleBigNbInsidePacket(std::vector<int>*& dividedVec, std::vector<int>& mainVec, std::vector<int>& remaining, size_t sizeDividedDeq, size_t nbInsidePacket);

void	PmergeMe::fillmainVecAndPend(std::vector<int>*& dividedVec, std::vector<int>& pend, std::vector<int>& remaining, size_t sizeDividedDeq, size_t nbInsidePacket)
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
		pend = handleBigNbInsidePacket(dividedVec, mainVec, remaining, sizeDividedDeq, nbInsidePacket);
}

static std::vector<int>	handleBigNbInsidePacket(std::vector<int>*& dividedVec, std::vector<int>& mainVec, std::vector<int>& remaining, size_t sizeDividedDeq, size_t nbInsidePacket)
{
	std::vector<int> res;

	for (size_t j = 0; j < sizeDividedDeq; j++)
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
	size_t	countPend = pend.size();

	if (countPend == 0)
		return ;

	this->mainVec.reserve(mainVec.size() + countPend);

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

static void	fillMainVec(std::vector<int>*& dividedVec, std::vector<int>& mainVec, size_t sizeDividedDeq)
{
	for (size_t j = 0; j < sizeDividedDeq; j++)
	{
		for (size_t i = 0; i < dividedVec[j].size(); i++)
			mainVec.push_back(dividedVec[j][i]);
		dividedVec[j].erase(dividedVec[j].begin(), dividedVec[j].end());
	}
}

void		PmergeMe::sortDeq()
{
	std::deque<int>*	dividedDeq = NULL;
	std::deque<int>		pend;
	std::deque<int>		remaining;
	size_t				sizeDividedDeq;

	int	size = this->mainDeq.size();

	if (size % 2 == 0)
		sizeDividedDeq = size / 2;
	else
		sizeDividedDeq = size / 2 + 1;

	dividedDeq = new std::deque<int>[sizeDividedDeq];

	divideAndCompDeq(dividedDeq, size, 1, sizeDividedDeq);
	fillmainDeqAndPend(dividedDeq, pend, remaining, sizeDividedDeq, 1);
	binaryJacobsthalNbsInsertDeq(pend, 1);

	PRINT("DividedAndComp: End: Deq", YELLOW, "\n");
	printDeq(this->mainDeq);

	delete [] dividedDeq;
}

static void	cleanDividedDeq(std::deque<int>*& dividedDeq, int sizeDividedDeq);
static void	swap(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, int sizeDividedDeq, int nbInsidePacket);
static void	fillDividedDeq(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, int nbInsidePacket);
static void	fillMainDeq(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, size_t sizeDividedDeq);

void		PmergeMe::divideAndCompDeq(std::deque<int>*& dividedDeq, size_t size, size_t nbInsidePacket, size_t sizeDividedDeq)
{
	if (nbInsidePacket > 1)
	{
		cleanDividedDeq(dividedDeq, sizeDividedDeq);
		fillDividedDeq(dividedDeq, this->mainDeq, nbInsidePacket);
	}

	swap(dividedDeq, this->mainDeq, sizeDividedDeq, nbInsidePacket);
	if (nbInsidePacket > 1)
		fillMainDeq(dividedDeq, this->mainDeq, sizeDividedDeq);

	printDeq(this->mainDeq);
	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;

	divideAndCompDeq(dividedDeq, size, nbInsidePacket, sizeDividedDeq);

	std::deque<int> pend;
	std::deque<int> remaining;

	cleanDividedDeq(dividedDeq, sizeDividedDeq);
	fillDividedDeq(dividedDeq, this->mainDeq, nbInsidePacket);
	fillmainDeqAndPend(dividedDeq, pend, remaining, sizeDividedDeq, nbInsidePacket);
	binaryJacobsthalNbsInsertDeq(pend, nbInsidePacket);	

	if (remaining.empty() == true)
		return ;

	for (size_t i = 0; i < remaining.size(); i++)
		this->mainDeq.push_back(remaining[i]);

	remaining.clear();

	PRINT("DividedAndComp: End: Deq", YELLOW, "\n");
	printDeq(this->mainDeq);
}

static void	cleanDividedDeq(std::deque<int>*& dividedDeq, int sizeDividedDeq)
{
	for (int i = 0; i < sizeDividedDeq; i++)
		dividedDeq[i].erase(dividedDeq[i].begin(), dividedDeq[i].end());
}

static void		fillDividedDeq(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, int nbInsidePacket)
{
	int	j = 0;
	int	nbAddInsidePacket = 0;

	for (size_t i = 0; i < mainDeq.size(); i++)
	{
		dividedDeq[j].push_back(mainDeq[i]);
		nbAddInsidePacket++;
		if (nbAddInsidePacket == nbInsidePacket)
		{
			j++;
			nbAddInsidePacket = 0;
		}
	}
	mainDeq.erase(mainDeq.begin(), mainDeq.end());
}

static void	swap(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, int sizeDividedDeq, int nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		int			temp = 0;
		size_t		size = mainDeq.size();

		for (size_t i = 0; i < size; i += 2)
		{
			if (i + 1 < size && mainDeq[i] > mainDeq[i + 1])
			{
				temp = mainDeq[i];
				mainDeq[i] = mainDeq[i + 1];
				mainDeq[i + 1] = temp;
			}
		}
	}
	else
	{
		for (int i = 0; i < sizeDividedDeq - 1 && dividedDeq[i + 1].size() == static_cast<size_t>(nbInsidePacket); i += 2)
		{
			if (dividedDeq[i].back() > dividedDeq[i + 1].back())
				dividedDeq[i].swap(dividedDeq[i + 1]);
		}
	}
}

static std::deque<int>	handleBigNbInsidePacket(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, std::deque<int>& remaining, size_t sizeDividedDeq, size_t nbInsidePacket);

void	PmergeMe::fillmainDeqAndPend(std::deque<int>*& dividedDeq, std::deque<int>& pend, std::deque<int>& remaining, size_t sizeDividedDeq, size_t nbInsidePacket)
{
	if (nbInsidePacket == 1)
	{
		std::deque<int> temp;
		size_t			count; 

		count = this->mainDeq.size();
		for (size_t i = 0;  i < count; i++)
		{
			if (i % 2 == 0)
				pend.push_back(this->mainDeq[i]);
			else
				temp.push_back(this->mainDeq[i]);
		}
		this->mainDeq.clear();
		this->mainDeq = temp;
	}
	else
		pend = handleBigNbInsidePacket(dividedDeq, mainDeq, remaining, sizeDividedDeq, nbInsidePacket);
}

static std::deque<int>	handleBigNbInsidePacket(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, std::deque<int>& remaining, size_t sizeDividedDeq, size_t nbInsidePacket)
{
	std::deque<int> res;

	for (size_t j = 0; j < sizeDividedDeq; j++)
	{
		if (j % 2 == 0)
		{
			if (dividedDeq[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedDeq[j].size(); k++)
					res.push_back(dividedDeq[j][k]);
			}
			else
			{
				for (size_t k = 0; k < dividedDeq[j].size(); k++)
					remaining.push_back(dividedDeq[j][k]);
			}
		}
		else
		{
			if (dividedDeq[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < dividedDeq[j].size(); k++)
					mainDeq.push_back(dividedDeq[j][k]);
			}
			else
			{
				for (size_t k = 0; k < dividedDeq[j].size(); k++)
					remaining.push_back(dividedDeq[j][k]);
			}
		}
	}
	return (res);
}

static std::deque<int>::iterator	binarySearch(std::deque<int>& v, std::deque<int>::iterator it_bound, int target, int nbInsidePacket);
static void							insertion(std::deque<int>& mainDeq, std::deque<int>& pend, std::deque<int>& copyMain, int increment, int nbInsidePacket, size_t& countPend);
static void							pushFirstPacket(std::deque<int>& mainDeq, std::deque<int> vec, size_t& countPend,  int nbInsidePacket);
static int							computeIncrement(std::deque<int>& pend, size_t nbInsidePacket, std::deque<int>& jacobsthalNbs, int j);

void	PmergeMe::binaryJacobsthalNbsInsertDeq(std::deque<int>& pend, int nbInsidePacket)
{
	size_t	countPend = pend.size();

	if (countPend == 0)
		return ;

	std::deque<int> jacobsthalNbs;

	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);

	std::deque<int> copyMain = this->mainDeq;

	pushFirstPacket(this->mainDeq, pend, countPend, nbInsidePacket);

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

			insertion(this->mainDeq, pend, copyMain, increment, nbInsidePacket, countPend);

			count--;
			increment -= nbInsidePacket;
		}
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
	}
}

static void	insertion(std::deque<int>& mainDeq, std::deque<int>& pend, std::deque<int>& copyMain, int increment, int nbInsidePacket, size_t& countPend)
{
	int	temp = pend[increment];

	std::deque<int>::iterator it_bound;	

	if (static_cast<size_t>(increment) >= copyMain.size())
		it_bound = mainDeq.end() - 1;
	else
		it_bound  = std::find(mainDeq.begin(), mainDeq.end(), copyMain[increment]) - nbInsidePacket;

	std::deque<int>::iterator it;
	it = binarySearch(mainDeq, it_bound , pend[increment], nbInsidePacket);
	if (*it > temp)
	{
		for (int k = 0; k < nbInsidePacket; k++)
		{
				int temp = pend[increment - k];
				mainDeq.insert(it - nbInsidePacket + 1, temp);
				countPend--;
		}
	}
	else
	{
		for (int k = 0; k < nbInsidePacket; k++)
		{
				int temp = pend[increment - k];
				mainDeq.insert(it + 1, temp);
				countPend--;
		}

	}
}

static std::deque<int> keepOnlyLastElements(std::deque<int>& d, int nbInsidePackets);
static std::deque<int>::iterator binarySearch(std::deque<int>& d, std::deque<int>::iterator it_bound, int target, int nbInsidePacket)
{
	int high = 0;
	int	low = 0;
	std::deque<int> temp;

	if (nbInsidePacket != 1)
		temp = keepOnlyLastElements(d, nbInsidePacket);
	else
		temp = d;

	std::deque<int>::iterator it_temp = temp.begin();
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
  	
	std::deque<int>::iterator temp_it;
	if (static_cast<size_t>(low) < temp.size())
		temp_it = temp.begin() + low;
	else
		temp_it = temp.end();

	return(std::find(d.begin(), d.end(), *temp_it));
}

static std::deque<int> keepOnlyLastElements(std::deque<int>& d, int nbInsidePackets)
{
    std::deque<int> res;

    for (size_t i = nbInsidePackets - 1; i < d.size(); i++)
    {
       if ((i + 1) % (nbInsidePackets) == 0) 
            res.push_back(d[i]);
    }
    return (res);
}

static int	computeIncrement(std::deque<int>& pend, size_t nbInsidePacket, std::deque<int>& jacobsthalNbs, int j)
{
	size_t	increment = 0;
	size_t	pendSize = pend.size();

	increment = ((jacobsthalNbs[1]) * nbInsidePacket) - 1 - j;
	if (increment >= pendSize)
		increment = pendSize - 1;
	return (increment);
}


static void	pushFirstPacket(std::deque<int>& mainDeq, std::deque<int> deq, size_t& countPend,  int nbInsidePacket)
{
	for (int i = nbInsidePacket; i > 0; i--)
	{
		mainDeq.insert(mainDeq.begin(), deq[i - 1]);
		countPend--;
	}
}

static void	fillMainDeq(std::deque<int>*& dividedDeq, std::deque<int>& mainDeq, size_t sizeDividedDeq)
{
	for (size_t j = 0; j < sizeDividedDeq; j++)
	{
		for (size_t i = 0; i < dividedDeq[j].size(); i++)
			mainDeq.push_back(dividedDeq[j][i]);
		dividedDeq[j].erase(dividedDeq[j].begin(), dividedDeq[j].end());
	}
}

// PARSING

static bool	checkDuplicates(std::vector<int>& vec, int nb);
static bool	checkError(std::vector<int>& mainVec, int number);

static bool		fillContainers(int argc, char**argv, std::vector<int>& mainVec, std::deque<int>& mainDeq)
{
	std::string	str;
	std::string	substr;
	size_t		pos = 0;
	int			number = 0;

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
				if (checkError(mainVec, number) == false)
					return (false);
				mainVec.push_back(number);
				mainDeq.push_back(number);
				str.erase(0, pos + 1);
			}
			else
			{
				number = strConvert<int>(str);
				if (checkError(mainVec, number) == false)
					return (false);
				mainVec.push_back(number);
				mainDeq.push_back(number);
				break ;
			}
		}
	}
	return (true);
}

static bool	checkError(std::vector<int>& mainVec, int number)
{
	if (number < 0)
	{
		PRINT("Error: negative number", RED, "\n");
		return (false);
	}
	if (checkDuplicates(mainVec, number) == false)
	{
		PRINT("Error: Duplicate number", RED, "\n");
		return (false);
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

static void	printVec(std::vector<int> vec)
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

static void	printDeq(std::deque<int> deq)
{
	if (deq.size() != 0)
	{
		for (size_t i = 0; i < deq.size(); i++)
		{
			std::cout << deq[i] << " ";
		}
	}
	std::cout << std::endl;
}

void	PmergeMe::printInformation(std::vector<int> notSorted, double time_elapsed_vec, double time_elapsed_deq)
{

	std::cout << "\n";
	PRINT("Before: ", RED, "")
	printVec(notSorted);
	PRINT("After Vector: ", GREEN, "")
	printVec(this->mainVec);
	PRINT("After Deque: ", GREEN, "")
	printDeq(this->mainDeq);
	std::cout << "Time to process a range of " << this->mainVec.size()
			  << " elements with std::vector: " << std::fixed << std::setprecision(6)
			  << time_elapsed_vec << "s\n";
	std::cout << "Time to process a range of " << this->mainDeq.size()
			  << " elements with std::dequeu: " << std::fixed << std::setprecision(6)
			  << time_elapsed_deq << "s\n";
}
