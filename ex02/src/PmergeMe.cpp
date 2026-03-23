/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/22 11:56:27 by lud-adam         ###   ########.fr       */
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
	int	sizeDividedVec;
	int	size = this->mainVec.size();
	this->dividedVec = NULL;

	if (size % 2 == 0)
		sizeDividedVec = size / 2;
	else
		sizeDividedVec = size / 2 + 1;

	this->originalSizeDividedVec = sizeDividedVec;
	this->dividedVec = new std::vector<int>[sizeDividedVec];
	divideAndComp(size, 1, sizeDividedVec);
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
		PRINT("DIVIDE AND COMP: Divided Vec : after first divided vec", RED);
		printArrayVecs(sizeDividedVec);
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

	PRINT("DIVIDE AND COMP: MainVec before cleandivided and fillmainVecAndPend", RED);
	this->printVec(this->mainVec);
	PRINT("\n", RESET);

	this->cleanDividedVec(sizeDividedVec);

	PRINT("DIVIDED AND COMP: Just before fill divided vec", RED);
	this->printArrayVecs(sizeDividedVec);

	this->fillDividedVec(size, nbInsidePacket, &sizeDividedVec);

	PRINT("DIVIDE AND COMP: DividedVec after creation pend and before push packet", RED);
	this->printArrayVecs(sizeDividedVec);
	PRINT("\n", RESET);

	PRINT("DIVIDE AND COMP: Main vec : after pushPacket inside main", RED);
	printVec(this->mainVec);

	fillmainVecAndPend(&pend, sizeDividedVec, nbInsidePacket);

	while (pend.size() != 0)
	{
		binaryJacobsthalNbsInsert(pend, jacobsthalNbs, nbInsidePacket);
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

void	PmergeMe::binaryJacobsthalNbsInsert(std::vector<int>& pend, std::vector<int> jacobsthalNumber, int nbInsidePacket)
{
	size_t	sizePend = pend.size();
	mainVec.reserve(mainVec.size() + sizePend + 10);

	if (sizePend == 0)
		return ;

	// int	count = jacobsthalNumber[1] - jacobsthalNumber[0];
	PRINT("BinaryJacob: nbInsidePacket", RED);
	PRINT(nbInsidePacket, WHITE);
	for (size_t j = 0; pend.size() > 0; j += nbInsidePacket)	
	{
		int	increment = ((jacobsthalNumber[1] - jacobsthalNumber[0]) * nbInsidePacket) - 1;

		if (increment < 0 || increment >= static_cast<int>(pend.size()))
		{
			PRINT("Jacob: increment wrong", RED);
			return ;
		}

		int	temp = pend[increment];
		PRINT("BinaryJacob: pend[increment]", GREEN);
		PRINT(temp, WHITE);
		PRINT("\n", RESET);

		PRINT("main vec: ", GREEN);
		this->printVec(this->mainVec);
		PRINT("\n", RESET);
		
		PRINT("main begin :", GREEN);
		PRINT(*this->mainVec.begin(), WHITE);

		PRINT("main end :", GREEN);
		PRINT(*(this->mainVec.end() - 1), WHITE);

		PRINT("main size : ", GREEN);
		PRINT(this->mainVec.size(), WHITE);

		PRINT("\n", RESET);
		// for (size_t i = 0; i < this->mainVec.size(); i++)
		// {
		// 	PRINT("Jacob: mainvec[i]: ", RED);
		// 	PRINT(this->mainVec[i], WHITE);
		// }

		int born_end = (jacobsthalNumber[1]) * nbInsidePacket - 1 - j;

		PRINT("Jacob: born end: ", YELLOW);
		PRINT(born_end, WHITE);
		std::vector<int>::iterator it = std::lower_bound(this->mainVec.begin(), this->mainVec.begin() + born_end, temp);

		PRINT("BinaryJacob: result lower bound", BLUE);
		PRINT(*it, WHITE);
		PRINT("\n", RESET);

			PRINT("BinaryJacob: before for to add inside Vecmain: increment: ", GREEN);
			PRINT(increment, WHITE);
			PRINT("\n", RESET);

			if (*it > temp)
			{
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

						this->mainVec.insert(it - nbInsidePacket + 1, temp);
						pend.erase(pend.begin() + increment - k);
				}
			}
			else
			{
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

						this->mainVec.insert(it + 1, temp);
						pend.erase(pend.begin() + increment - k);
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
	}
}

void	PmergeMe::fillmainVecAndPend(std::vector<int>* pend, size_t sizeDividedVec, size_t nbInsidePacket)
{
	size_t	i = 0;
	while (i < 2 && i < sizeDividedVec)
	{
		for (size_t j = 0; j < this->dividedVec[i].size(); j++)
			this->mainVec.push_back(this->dividedVec[i][j]);
		i++;
	}
	for (size_t j = i; j < sizeDividedVec; j++)
	{
		if (j % 2 == 0)
		{
			if (this->dividedVec[j].size() == nbInsidePacket)
			{
				for (size_t k = 0; k < this->dividedVec[j].size(); k++)
					pend->push_back(this->dividedVec[j][k]);
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
	this->printVec(*pend);
	PRINT("\n", RESET);
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
