/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/26 13:38:59 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <cctype>
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

static void		divideAndComp();

void		PmergeMe::fordJonhson()
{
	int		size = this->mainVec.size();
	int		sizeDividedVec = (size / 2) + 1;
	this->sizeDividedVec = sizeDividedVec;
	int		temp = 0;

	this->dividedVec = new std::vector<int>[sizeDividedVec];
	this->fillDividedVec(size, 2);
	// PRINT("DIVIDED VEC");
	// for (int i = 0; i < sizeDividedVec; i++)
	// {
	// 	this->printVec(this->dividedVec[i]);
	// }
	for (int i = 0; i < sizeDividedVec - 1; i++)
	{
		if (this->dividedVec[i][0] > this->dividedVec[i][1])
		{
			temp = this->dividedVec[i][0];
			this->dividedVec[i][0] = this->dividedVec[i][1];
			this->dividedVec[i][1] = temp;
		}
	}
	// PRINT("AFTER SWAP");
	// for (int i = 0; i < sizeDividedVec; i++)
	// {
	// 	this->printVec(this->dividedVec[i]);
	// }
	mainVec.erase(mainVec.begin(), mainVec.end());
	divideAndComp(size, sizeDividedVec, 2, true);
	PRINT("MAIN VEC");
	this->printVec(this->mainVec);
	delete [] this->dividedVec;
}

void		PmergeMe::divideAndComp(int size, int sizeDividedVec, int nbInsidePacket, bool firstIteration)
{
	PRINT("DIVIDED VEC");
	for (int i = 0; i <= this->sizeDividedVec; i++)
	{
		this->printVec(this->dividedVec[i]);
	}
	PRINT("\n");
	swap(this->sizeDividedVec, nbInsidePacket);
	// std::vector<int>	pend;
	// this->PushPacket(&this->mainVec, sizeDividedVec, 2);
	// sizeDividedVec -= 2;
	// for (int i = 0; i < sizeDividedVec; i++)
	// {
	// 	if (this->dividedVec[0].size() != static_cast<size_t>(nbInsidePacket))
	// 		this->PushPacket(&pend, sizeDividedVec, 1);
	// 	else
	// 		break ;
	// 	sizeDividedVec--;
	// 	if (sizeDividedVec < 0)
	// 		break;
	// 	if (this->dividedVec[0].size() != static_cast<size_t>(nbInsidePacket))
	// 		this->PushPacket(&this->mainVec, sizeDividedVec, 1);
	// 	else
	// 		break ;
	// 	sizeDividedVec--;
	// }
	// PRINT("PEND");
	// this->printVec(pend);
	PRINT("AFTER SWAP");
	for (int i = 0; i <= this->sizeDividedVec; i++)
	{
		this->printVec(this->dividedVec[i]);
	}
	fillMainVec(sizeDividedVec, this->dividedVec->size());
	PRINT("MAIN VEC");
	this->printVec(this->mainVec);
	nbInsidePacket *= 2;
	if (nbInsidePacket >= (size / 2) + 1)
		return ;
	this->fillDividedVec(size, nbInsidePacket);
	divideAndComp(size, sizeDividedVec / 2, nbInsidePacket, false);
}

void		PmergeMe::fillDividedVec(int size, int nbInsidePacket)
{
	int	j = 0;
	int	nbAddInsidePacket = 0;

	for (int i = 0; i < size; i++)
	{
		this->dividedVec[j].push_back(this->mainVec[i]);
		nbAddInsidePacket++;
		if (nbAddInsidePacket == nbInsidePacket)
		{
			j++;
			nbAddInsidePacket = 0;
		}
	}
	this->sizeDividedVec = j;
	mainVec.erase(mainVec.begin(), mainVec.end());
}

void	PmergeMe::swap(int sizeDividedVec, int nbInsidePacket)
{
	for (int i = 0; i < sizeDividedVec - 1 && this->dividedVec[i + 1].size() == static_cast<size_t>(nbInsidePacket); i += 2)
	{
		if (this->dividedVec[i][nbInsidePacket - 1] > this->dividedVec[i + 1][nbInsidePacket - 1])
			this->dividedVec[i].swap(this->dividedVec[i + 1]);
	}
}

void		PmergeMe::fillMainVec(int sizeDividedVec, int nbPacket)
{
	for (int j = 0; j <= this->sizeDividedVec; j++)
	{
		for (size_t i = 0; i < this->dividedVec[j].size(); i++)
			this->mainVec.push_back(this->dividedVec[j][i]);
		this->dividedVec[j].erase(this->dividedVec[j].begin(), this->dividedVec[j].end());
	}
}

void		PmergeMe::PushPacket(std::vector<int>* vect, int sizeDividedVec, int nbPacket)
{
	for (int j = 0; j < sizeDividedVec; j++)
	{
		if (nbPacket != 0 && j == nbPacket)
			return ;
		for (size_t i = 0; i < this->dividedVec[j].size(); i++)
			vect->push_back(this->dividedVec[j][i]);
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
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}
