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
	int		sizeDividedVec = size / 2;

	this->dividedVec = new std::vector<int>[sizeDividedVec];
	divideAndComp(size, sizeDividedVec, 2, true);	
	PRINT("After Divide And Comp")
	this->printVec(mainVec);
	delete [] this->dividedVec;
}

void		PmergeMe::divideAndComp(int size, int sizeDividedVec, int endPacket, bool firstIteration)
{
	fillDividedVec(size, endPacket);
	PRINT("AFTER FILL DIVIDED VEC");
	for (int i = 0; i < sizeDividedVec; i++)
	{
		this->printVec(this->dividedVec[i]);
	}
	endPacket = this->dividedVec->size();
	swap(sizeDividedVec, endPacket, firstIteration);	
	PRINT("After Swap, SubdividedVec")
	for (int i = 0; i < sizeDividedVec; i++)
	{
		this->printVec(this->dividedVec[i]);
	}
	endPacket *= 2;
	fillMainVec(sizeDividedVec, this->dividedVec->size());
	if (endPacket >= size / 2)
		return ;
	PRINT("NEW ITERATION");
	PRINT("SizeDividedVec");
	PRINT(sizeDividedVec / 2);
	PRINT("Endpacket");
	PRINT(endPacket);
	divideAndComp(size, sizeDividedVec / 2, endPacket, false);
}

void		PmergeMe::fillDividedVec(int size, int endPacket)
{
	int	j = 0;
	int	handleOdd = (size % 2 == 0) ? 0 : 1;
	int	sizeDividedVec = size - handleOdd;

	for (int i = 0; i < size; i++)
	{
		this->dividedVec[j].push_back(this->mainVec[i]);
		if (i % endPacket == 0 && i != 0)
		{
			PRINT("ENDPACKET modulo i");
			PRINT("i")
			PRINT(i);
			PRINT(endPacket % i);
			j++;
		}
	}	
	mainVec.erase(mainVec.begin(), mainVec.end());
}

void	PmergeMe::swap(int sizeDividedVec, int endPacket, bool firstIteration)
{
	int temp = 0;

	if (firstIteration == false)
	{
		for (int i = 0; i < sizeDividedVec - 1; i++)
		{
			if (this->dividedVec[i][endPacket - 1] > this->dividedVec[i + 1][endPacket - 1])
				this->dividedVec[i].swap(this->dividedVec[i + 1]);
		}
	}
	else
	{
		for (int i = 0; i < sizeDividedVec; i++)
		{
			if (this->dividedVec[i][0] > this->dividedVec[i][1])
			{
				temp = this->dividedVec[i][0];
				this->dividedVec[i][0] = this->dividedVec[i][1];
				this->dividedVec[i][1] = temp;
			}
		}
	}
}

void		PmergeMe::fillMainVec(int sizeDividedVec, int step)
{
	int	temp = 0;
	int	i = 0;	
	int	j = 0;
	PRINT(step);
	while (j < sizeDividedVec)
	{
		temp = this->dividedVec[j][i];
		this->mainVec.push_back(temp);
		if (i == step - 1)
		{
			this->dividedVec[j].erase(this->dividedVec[j].begin(), this->dividedVec[j].end());
			j++;
			i = 0;
		}
		else
			i++;
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
