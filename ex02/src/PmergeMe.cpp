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
#include <stdexcept>
#include <vector>

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

void debug_vec(const std::vector<int>& v);

static void		divideAndComp();

void		PmergeMe::fordJonhson()
{
	size_t	sizeDividedVec;
	int	size = this->mainVec.size();
	this->dividedVec = NULL;

	if (size % 2 == 0)
		sizeDividedVec = size / 2;
	else
		sizeDividedVec = size / 2 + 1;

	this->originalSizeDividedVec = sizeDividedVec;
	this->dividedVec = new std::vector<int>[sizeDividedVec];
	divideAndComp(size, 1, sizeDividedVec);

	PRINT("----------------------------------------------------------------------------------\n", RED);
	PRINT("LAST RECURSION", YELLOW);
	std::vector<int> pend;
	fillmainVecAndPend(pend, sizeDividedVec, 1);
	std::vector<int> jacobsthalNbs;
	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);
	while (this->countPend > 0)
	{
		binaryJacobsthalNbsInsert(pend, this->mainVec, jacobsthalNbs, 1);
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
		PRINT("DIVIDED AND COMP : count pend", YELLOW);
		PRINT(this->countPend, WHITE);
	}
	// if (remaining.empty() == true)
	// 	return ;
	// for (size_t i = 0; i < this->remaining.size(); i++)
	// {
	// 	this->mainVec.push_back(remaining[i]);
	// }
	// remaining.clear();

	delete [] this->dividedVec;
}

void		PmergeMe::divideAndComp(size_t size, size_t nbInsidePacket, size_t sizeDividedVec)
{
	// int	oldSizeDividedVec;
	if (nbInsidePacket > 1)
	{
		this->cleanDividedVec(sizeDividedVec);
		this->fillDividedVec(size, nbInsidePacket, &sizeDividedVec);
		// oldSizeDividedVec = sizeDividedVec;
		// PRINT("DIVIDE AND COMP: Divided Vec : after first divided vec", RED);
		// printArrayVecs(sizeDividedVec);
	}
	else
	{
		// PRINT("DIVIDE AND COMP: Main vec : before swap");
		// printVec(this->mainVec);
	}

	this->swap(sizeDividedVec, nbInsidePacket);
	this->fillMainVec(sizeDividedVec);

	if (nbInsidePacket > 1)
	{
		// PRINT("DIVIDE AND COMP: Divided Vec : after swap");
		// printArrayVecs(sizeDividedVec);
		// PRINT("DIVIDE AND COMP: Main Vec : after swap");
		// printVec(this->mainVec);
	}
	else
	{
		// PRINT("DIVIDE AND COMP: Main vec : after swap");
		// printVec(this->mainVec);
	}
	
	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;

	divideAndComp(size,  nbInsidePacket, sizeDividedVec);

	PRINT("\n", RESET);
	PRINT("\n", RESET);
	PRINT("SECOND PARTY OF THE ALGO", YELLOW);
	PRINT("\n", RESET);
	PRINT("\n", RESET);

	std::vector<int> pend;
	std::vector<int> jacobsthalNbs;
	jacobsthalNbs.push_back(1);
	jacobsthalNbs.push_back(3);

	// PRINT("DIVIDE AND COMP: MainVec before cleandivided and fillmainVecAndPend", RED);
	// this->printVec(this->mainVec);
	PRINT("\n", RESET);

	this->cleanDividedVec(sizeDividedVec);

	// PRINT("DIVIDED AND COMP: Just before fill divided vec", RED);
	// this->printArrayVecs(sizeDividedVec);

	this->fillDividedVec(size, nbInsidePacket, &sizeDividedVec);

	PRINT("DIVIDE AND COMP: DividedVec after creation pend and before push packet", RED);
	this->printArrayVecs(sizeDividedVec);
	PRINT("\n", RESET);

	// PRINT("DIVIDE AND COMP: Main vec : after pushPacket inside main", RED);
	// printVec(this->mainVec);

	fillmainVecAndPend(pend, sizeDividedVec, nbInsidePacket);

	while (this->countPend)
	{
		binaryJacobsthalNbsInsert(pend, this->mainVec, jacobsthalNbs, nbInsidePacket);
		jacobsthalNbs.push_back(jacobsthalNbs[0] + jacobsthalNbs[0] + jacobsthalNbs[1]);
		jacobsthalNbs.erase(jacobsthalNbs.begin());
		PRINT("FORD JHONSON: Count pend", YELLOW);
		PRINT(this->countPend, WHITE);
	}
	if (remaining.empty() == true)
		return ;
	for (size_t i = 0; i < this->remaining.size(); i++)
	{
		this->mainVec.push_back(remaining[i]);
	}
	remaining.clear();
}

int	PmergeMe::computeIncrement(std::vector<int>& pend, size_t nbInsidePacket, std::vector<int>& jacobsthalNumber, int j, int& count)
{
	size_t	increment = 0;

	this->mainIncrement = 0;

	// if (jacobsthalNumber[1] >= static_cast<int>(pend.size()))
	// {
	// 	PRINT("HERE", WHITE);
	// 	increment = pend.size() - 1;
	// }
	// else if (pend.size() == nbInsidePacket)
	// {
	// 	increment = nbInsidePacket - 1;
	// 	count = 1;
	// }
	// else
	// {
		increment = ((jacobsthalNumber[1]) * nbInsidePacket) - 1 - j;
		if (increment >= pend.size())
			increment = pend.size() - 1;
		// if (pend.size() > this->mainVec.size())
		// 	this->mainIncrement = ((jacobsthalNumber[1]) * nbInsidePacket) - 1 - j - nbInsidePacket;
		// else
		// 	this->mainIncrement = increment;
	// }
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

void	PmergeMe::binaryJacobsthalNbsInsert(std::vector<int>& pend, std::vector<int> copyMain, std::vector<int> jacobsthalNumber, int nbInsidePacket)
{
	PRINT("BINARY JACOBSTHAL", YELLOW);

	size_t	sizePend = pend.size();
	mainVec.reserve(mainVec.size() + sizePend);

	if (sizePend == 0)
		return ;


	if (jacobsthalNumber[1] == 3)
		this->pushFirstPacket(pend, nbInsidePacket);
	
	int	count = jacobsthalNumber[1] - jacobsthalNumber[0];
	for (size_t j = 0; count > 0 && this->countPend > 0; j += nbInsidePacket)	
	{
		PRINT("Jacob: Jacobsthal Number", GREEN);
		PRINT(jacobsthalNumber[1], WHITE);
		PRINT("\n", RESET);

		PRINT("Jacob: mainVec", GREEN);
		this->printVec(mainVec);
		PRINT("\n", RESET);

		PRINT("Jacob: CopyMainVec", GREEN);
		this->printVec(copyMain);
		PRINT("\n", RESET);

		PRINT("Jacob: pend", YELLOW);
		this->printVec(pend);
		PRINT("\n", RESET);

		PRINT("BinaryJacob: nbInsidePacket", RED);
		PRINT(nbInsidePacket, WHITE);
		PRINT("\n", RESET);

		int increment = computeIncrement(pend, nbInsidePacket, jacobsthalNumber, j, count);
		PRINT("Jacob: INCREMENT", YELLOW);
		PRINT(increment, WHITE);

		// PRINT("Jacob: Jacobsthal Number [1]", RED);
		// PRINT(jacobsthalNumber[1], WHITE);
		//
		// PRINT("Jacob: Jacobsthal Number [0]", RED);
		// PRINT(jacobsthalNumber[0], WHITE);
		//
		// PRINT("Jacob: nb Inside packet", RED);
		// PRINT(nbInsidePacket, WHITE);
		//
		// PRINT("Jacob: j", RED);
		// PRINT(j, WHITE);

		if (increment < 0 || increment >= static_cast<int>(pend.size()))
		{
			PRINT("Jacob: increment wrong", RED);
			return ;
		}

		PRINT("Jacob: count pend: ", BLUE);
		PRINT(this->countPend, WHITE);
		PRINT("\n", RESET);

		int	temp = pend[increment];
		PRINT("BinaryJacob: pend[increment]", GREEN);
		PRINT(temp, WHITE);

		PRINT("BinaryJacob: copyMain[increment]", GREEN);
		PRINT(copyMain[increment], WHITE);
		// PRINT("\n", RESET);
		//
		// PRINT("main vec: ", GREEN);
		// this->printVec(this->mainVec);
		// PRINT("\n", RESET);
		//
		// PRINT("main begin :", GREEN);
		// PRINT(*this->mainVec.begin(), WHITE);

		// PRINT("main end :", GREEN);
		// PRINT(*(this->mainVec.end() - 1), WHITE);
		//
		// PRINT("main size : ", GREEN);
		// PRINT(this->mainVec.size(), WHITE);
		//
		// PRINT("\n", RESET);
		// for (size_t i = 0; i < this->mainVec.size(); i++)
		// {
		// 	PRINT("Jacob: mainvec[i]: ", RED);
		// 	PRINT(this->mainVec[i], WHITE);
		// }

		// PRINT("Jacob: JacobsthalNumber", RED);
		// PRINT(jacobsthalNumber[1], WHITE);
		// PRINT("Jacob: nbInsidePacket", RED);
		// PRINT(nbInsidePacket, WHITE);
		// PRINT("Jacob: j", RED);
		// PRINT(j, WHITE);
		// PRINT("\n", RESET);

		// int born_end = (jacobsthalNumber[1]) * nbInsidePacket - 1 - j;
		//
		// PRINT("Jacob: born end: ", YELLOW);
		// PRINT(born_end, WHITE);

		// PRINT("Jacob: this->mainINcrement", GREEN);
		// PRINT(this->mainIncrement, WHITE);
		//
		// PRINT("Jacob: copyMain[increment]", YELLOW);
		// PRINT(copyMain[this->mainIncrement], WHITE);

		PRINT("Jacob: copyMain", YELLOW);
		this->printVec(copyMain);

		std::vector<int>::iterator it_bound;		
		if (static_cast<size_t>(increment) > copyMain.size())
		{
			PRINT("Jacob: Increment superior to copyMain", WHITE);
			it_bound = this->mainVec.end();
		}
		else
		{
			PRINT("Jacob: Increment inferior to copyMain", WHITE);
			it_bound  = std::find(this->mainVec.begin(), this->mainVec.end(), copyMain[increment]);
		}

		// std::vector<int>::iterator it = std::upper_bound(this->mainVec.begin(), it_bound, pend[increment]);		
		std::vector<int>::iterator it;
		// it = this->mainVec.end();
		it = searchNumber(it_bound, pend[increment]);

		PRINT("BinaryJacob: result it_bound", YELLOW);
		PRINT(*it_bound, WHITE);

		// PRINT("BinaryJacob: result it", YELLOW);
		// PRINT(*it, WHITE);

		PRINT("\n", RESET);

			PRINT("BinaryJacob: before for to add inside Vecmain: increment: ", GREEN);
			PRINT(increment, WHITE);
			PRINT("\n", RESET);

			if (*it > temp)
			{
				// FIXME: Have to change how to insert 
				PRINT("Jacob: first for", GREEN)
				for (int k = 0; k < nbInsidePacket; k++)
				{
						// int posInPend = increment - nbInsidePacket + 1;
						// PRINT("BinaryJacob: Inside for to add inside VecMain: posInPend: ", GREEN);
						// PRINT(posInPend, WHITE);
						// PRINT("\n", RESET);

						int temp = pend[increment - k];
						PRINT("BinaryJacob: Inside for to inside main : temp :", BLUE);
						PRINT(temp, WHITE);
						PRINT("\n", RESET);

						PRINT("Jacob: *it > temp:  just before insert", GREEN);
						PRINT(*it, WHITE);
					
						this->mainVec.insert(it - nbInsidePacket + 1, temp);
						this->countPend--;
				}
			}
			else
			{
				PRINT("Jacob: Second for", GREEN);
				for (int k = 0; k < nbInsidePacket; k++)
				{
						// int posInPend = increment - nbInsidePacket + 1;
						// PRINT("BinaryJacob: Inside for to add inside VecMain: posInPend: ", GREEN);
						// PRINT(posInPend, WHITE);
						// PRINT("\n", RESET);

						int temp = pend[increment - k];
						PRINT("BinaryJacob: Inside for to inside main : temp :", BLUE);
						PRINT(temp, WHITE);
						PRINT("\n", RESET);

						PRINT("Jacob: *it < temp: BEFORE INSERT: it", YELLOW);
						PRINT(*it, WHITE);

						this->mainVec.insert(it, temp);
						this->countPend--;
				}

			}
		PRINT("BinaryJaocb: pend", BLUE);
		PRINT("size: ", RED);
		PRINT(pend.size(), WHITE);
		printVec(pend);
		PRINT("\n", RESET);

		PRINT("BinaryJaocb: main", BLUE);
		printVec(this->mainVec);
		PRINT("\n", RESET);
		PRINT("----------------------------------------------------------------------------------\n", RED);
		count--;
	}
}

std::vector<int>::iterator PmergeMe::searchNumber(std::vector<int>::iterator it_bound, int value)
{
	std::vector<int>::iterator it;

	it = it_bound;
	if (this->countPend == 1)
	{
		PRINT("HERE", WHITE);
		for (std::vector<int>::iterator it = this->mainVec.end() - 1; it != it_bound; --it)
		{
			if (*it <= value)
				return (it);
		}
		return (it_bound);
	}
	else
	{
		for (std::vector<int>::iterator it = this->mainVec.begin(); it != it_bound; it++)
		{
			if (*it >= value)	
				return (it);
		}
	}
	return (it);
}

void	PmergeMe::fillmainVecAndPend(std::vector<int>& pend, size_t sizeDividedVec, size_t nbInsidePacket)
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
			PRINT("FILL MAIN VEC", RED);
			PRINT(this->mainVec[i], WHITE);
			if (i % 2 == 0)
			{
				pend.push_back(this->mainVec[i]);
			}
			else
			{
				temp.push_back(this->mainVec[i]);
			}
		}
		this->mainVec.clear();
		this->mainVec = temp;
	}
	for (size_t j = 0; j < sizeDividedVec; j++)
	{
		if (j % 2 == 0)
		{
			if (this->dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < this->dividedVec[j].size(); k++)
					pend.push_back(this->dividedVec[j][k]);
			}
			else
			{
				for (size_t k = 0; k < this->dividedVec[j].size(); k++)
					this->remaining.push_back(this->dividedVec[j][k]);
			}
		}
		else
		{
			if (this->dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < this->dividedVec[j].size(); k++)
					this->mainVec.push_back(this->dividedVec[j][k]);
			}
			else
			{
				for (size_t k = 0; k < this->dividedVec[j].size(); k++)
					this->remaining.push_back(this->dividedVec[j][k]);
			}
		}
	}

	PRINT("FILL MAIN VEC AND PEND: main", RED);
	this->printVec(this->mainVec);
	PRINT("\n", RESET);

	PRINT("FILL MAIN VEC AND PEND: pend", RED);
	this->printVec(pend);
	PRINT("\n", RESET);
	this->countPend = pend.size();
}

void		PmergeMe::fillDividedVec(int size, int nbInsidePacket, size_t* sizeDividedVec)
{
	int	j = 0;
	int	nbAddInsidePacket = 0;

	for (size_t i = 0; i < this->mainVec.size(); i++)
	{
		this->dividedVec[j].push_back(this->mainVec[i]);
		nbAddInsidePacket++;
		if (nbAddInsidePacket == nbInsidePacket)
		{
			j++;
			nbAddInsidePacket = 0;
		}
	}
	// *sizeDividedVec = ++j;
	mainVec.erase(mainVec.begin(), mainVec.end());
}

void	PmergeMe::cleanDividedVec(int sizeDividedVec)
{
	// PRINT("CLEAN DIVIDED VEC: SizeDividedVec");
	// PRINT(sizeDividedVec);

	for (int i = 0; i < this->originalSizeDividedVec; i++)
	{
		this->dividedVec[i].erase(dividedVec[i].begin(), dividedVec[i].end());
	}
}

void	PmergeMe::swap(int sizeDividedVec, int nbInsidePacket)
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
		for (int i = 0; i < sizeDividedVec - 1 && this->dividedVec[i + 1].size() == static_cast<size_t>(nbInsidePacket); i += 2)
		{
			if (this->dividedVec[i].back() > this->dividedVec[i + 1].back())
				this->dividedVec[i].swap(this->dividedVec[i + 1]);
		}
	}
}

void		PmergeMe::fillMainVec(size_t sizeDividedVec)
{
	// PRINT("FILL MAIN VEC");
	// PRINT(sizeDividedVec);
	for (size_t j = 0; j < sizeDividedVec; j++)
	{
		for (size_t i = 0; i < this->dividedVec[j].size(); i++)
			this->mainVec.push_back(this->dividedVec[j][i]);
		this->dividedVec[j].erase(this->dividedVec[j].begin(), this->dividedVec[j].end());
	}
}

void		PmergeMe::fillVec(int argc, char**argv)
{
	std::string str;
	std::string substr;
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
				this->mainVec.push_back(number);
				str.erase(0, pos + 1);
			}
			else
			{
				number = strConvert<int>(str);
				this->mainVec.push_back(number);
				break ;
			}
		}
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
	// else
	// 	std::cout << "Nothing inside bro";
	std::cout << std::endl;
}

void	PmergeMe::printArrayVecs(int sizeDividedVec)
{
	for (int i = 0; i < sizeDividedVec; i++)
	{
		// std::cout << "Step :" << i << std::endl;
		if (this->dividedVec[i].size() != 0)
			this->printVec(this->dividedVec[i]);
	}
}

void debug_vec(const std::vector<int>& v)
{
	PRINT("size: ", RED);
	PRINT(v.size(), WHITE)
	PRINT("capacity: ", RED);
	PRINT(v.capacity(), WHITE);
	PRINT("data ptr: ", RED);
	PRINT((void*)v.data(), WHITE);
	for (size_t i=0; i<v.capacity(); i++) 
	{
		PRINT("index ", RED);
		PRINT(i, WHITE);
		PRINT(": ", RED);
		PRINT(v[i], WHITE);
	}
}
