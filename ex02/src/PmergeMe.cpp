/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/03/19 16:57:36 by lud-adam         ###   ########.fr       */
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
	int	oldSizeDividedVec;
	if (nbInsidePacket > 1)
	{
		this->cleanDividedVec();
		this->fillDividedVec(size, nbInsidePacket, &sizeDividedVec);
		oldSizeDividedVec = sizeDividedVec;
		// PRINT("DIVIDE AND COMP: Divided Vec : after first divided vec");
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

	PRINT("\n");
	PRINT("\n");
	PRINT("SECOND PARTY OF THE ALGO");
	PRINT("\n");
	PRINT("\n");

	std::vector<int> pend;

	this->cleanDividedVec();

	// PRINT("DIVIDED AND COMP: Just before fill divided vec");
	// this->printArrayVecs(sizeDividedVec);

	this->fillDividedVec(size, nbInsidePacket, &sizeDividedVec);

	PRINT("DIVIDE AND COMP: after creation pend and before push packet");
	this->printArrayVecs(sizeDividedVec);
	PRINT("\n");

	this->PushPacket(&this->mainVec, sizeDividedVec, 2, nbInsidePacket);

	// PRINT("DIVIDE AND COMP: Main vec : after pushPacket inside main");
	// printVec(this->mainVec);


	size_t	i = 0;

	while (this->dividedVec[i].size() == 0)
	{
		// PRINT("FILL PEND : Increment");

		i++;
	}
	// PRINT("FILL PEND: sizeDivided vec :");
	// PRINT(sizeDividedVec);
	while (i < sizeDividedVec && this->dividedVec[i].size() == nbInsidePacket)
	{
		// PRINT("FILL PEND : pushpacket");
		this->PushPacket(&pend, sizeDividedVec, 1, nbInsidePacket);
		i += 2;
	}
	PRINT("DIVIDE AND COMP: Main vec : after pushPacket inside pend");
	printVec(pend);
}

void	PmergeMe::fillPend(std::vector<int>* pend, size_t sizeDividedVec, size_t nbInsidePacket)
{
	// PRINT("FILL PEND INSIDE");
	size_t	i = 0;

	while (this->dividedVec[i].size() == 0)
	{
		// PRINT("FILL PEND : Increment");

		i++;
	}
	// PRINT("FILL PEND: sizeDivided vec :");
	// PRINT(sizeDividedVec);
	while (i < sizeDividedVec)
	{
		// PRINT("FILL PEND : pushpacket");
		this->PushPacket(pend, sizeDividedVec, 1, nbInsidePacket);
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
	*sizeDividedVec = ++j;
	mainVec.erase(mainVec.begin(), mainVec.end());
}

void	PmergeMe::cleanDividedVec()
{
	int	sizeDividedVec;
	int	size = this->mainVec.size();

	sizeDividedVec =  size / 2 + 1;

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
			if (this->dividedVec[i][nbInsidePacket - 1] > this->dividedVec[i + 1][nbInsidePacket - 1])
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

void		PmergeMe::PushPacket(std::vector<int>* vect, int sizeDividedVec, int nbPacket, size_t nbByPackets)
{
	int	nbPacketPush = 0;

	// PRINT("PUSHPACKET out of the for");
	int	i = 0;
	while (i < sizeDividedVec && this->dividedVec[i].size() == 0)
		i++;

	for (int j = i; j < sizeDividedVec; j++)
	{
		// PRINT("PUSHPACKET Content of divided vec");
		// this->printVec(this->dividedVec[j]);
		// PRINT("PUSHPACKET: inside the for");
		// PRINT("PUSHPACKET");
		// PRINT("This packet dividedvec[j]");
		// PRINT(this->dividedVec[j].size());
		// PRINT("NB BY PACKETS");
		// PRINT(nbByPackets);
		if ((nbPacket != 0 && nbPacketPush == nbPacket) || this->dividedVec[j].size() != nbByPackets)
		{
			// PRINT("PUSHPACKET: inside the return");
			return ;
		}
		if (this->dividedVec[j].size() == 0)
			continue ;
		// PRINT("PUSHPACKET: just before push inside vect");
		for (size_t i = 0; i < this->dividedVec[j].size(); i++)
		{

			// PRINT("PUSHPACKET: Inside for to push inside vect");
			vect->push_back(this->dividedVec[j][i]);
		}
		nbPacketPush++;
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
