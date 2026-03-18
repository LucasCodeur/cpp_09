/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/18 18:11:06 by lud-adam         ###   ########.fr       */
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
	int	sizeDividedVec;
	int	size = this->mainVec.size();

	if (size % 2 == 0)
		sizeDividedVec = size / 2;
	else
		sizeDividedVec = size / 2 + 1;
	divideAndComp(size, 1, sizeDividedVec);
	delete [] this->dividedVec;
}

void		PmergeMe::divideAndComp(int size, int nbInsidePacket, size_t sizeDividedVec)
{
	if (nbInsidePacket > 1)
	{
		this->dividedVec = new std::vector<int>[sizeDividedVec];
		this->fillDividedVec(size, nbInsidePacket, &sizeDividedVec);
		PRINT("DIVIDE AND COMP: Divided Vec : after first divided vec");
		printArrayVecs(sizeDividedVec);
	}

	if (nbInsidePacket > 1)
	{
		PRINT("DIVIDE AND COMP: Divided Vec : before swap");
		printArrayVecs(sizeDividedVec);
	}
	else
	{
		PRINT("DIVIDE AND COMP: Main vec : before swap");
		printVec(this->mainVec);
	}

	swap(sizeDividedVec, nbInsidePacket);

	if (nbInsidePacket > 1)
	{
		PRINT("DIVIDE AND COMP: Divided Vec : after swap");
		printArrayVecs(sizeDividedVec);
		PRINT("DIVIDE AND COMP: Main Vec : after swap");
		printVec(this->mainVec);
	}
	else
	{
		PRINT("DIVIDE AND COMP: Main vec : after swap");
		printVec(this->mainVec);
	}
	
	nbInsidePacket *= 2;
	if (nbInsidePacket > size / 2)
		return ;
	delete [] this->dividedVec;
	divideAndComp(size,  nbInsidePacket, sizeDividedVec / 2);

	std::vector<int> pend;
	this->PushPacket(&this->mainVec, sizeDividedVec, 2);

	PRINT("DIVIDE AND COMP: Main vec : after pushPacket inside main");
	printVec(this->mainVec);


	fillPend(&pend, sizeDividedVec);
	PRINT("DIVIDE AND COMP: Main vec : after pushPacket inside pend");
	printVec(pend);
}

void	PmergeMe::fillPend(std::vector<int>* pend, size_t sizeDividedVec)
{
	PRINT("FILL PEND INSIDE");
	size_t	i = 0;

	while (this->dividedVec[i].size() == 0)
	{
		PRINT("FILL PEND : Increment");

		i++;
	}
	PRINT("FILL PEND: sizeDivided vec :");
	PRINT(sizeDividedVec);
	while (i < sizeDividedVec)
	{
		PRINT("FILL PEND : pushpacket");
		this->PushPacket(pend, sizeDividedVec, 1);
		i += 2;
	}
}

void		PmergeMe::fillDividedVec(int size, int nbInsidePacket, size_t* sizeDividedVec)
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
	*sizeDividedVec = j;
	mainVec.erase(mainVec.begin(), mainVec.end());
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
			if (this->dividedVec[i][nbInsidePacket - 1] > this->dividedVec[i + 1][nbInsidePacket - 1])
				this->dividedVec[i].swap(this->dividedVec[i + 1]);
		}
	}
}

void		PmergeMe::fillMainVec(size_t sizeDividedVec, int nbPacket)
{
	for (size_t j = 0; j <= sizeDividedVec; j++)
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
		if (this->dividedVec[j].size() == 0)
			continue ;
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
	if (vec.size() != 0)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << " ";
		}
	}
	else
		std::cout << "Nothing inside bro";
	std::cout << std::endl;
}

void	PmergeMe::printArrayVecs(int sizeDividedVec)
{
	for (int i = 0; i <= sizeDividedVec; i++)
	{
		// std::cout << "Step :" << i << std::endl;
		this->printVec(this->dividedVec[i]);
	}
}
