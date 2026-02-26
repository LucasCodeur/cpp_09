/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/24 11:16:06 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <cctype>
#include <stdexcept>

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

static void		divideAndComp(int step, int size,int start, int handleEnd);

void		PmergeMe::fordJonhson()
{
	int	size = this->container.size();
	if (size < 2)
		throw std::runtime_error("Error: not enough elements");
	int	step = 2;
	int	start = 1;
	int	handleEnd = (size % step == 0) ? 0 : 1;
	divideAndComp(step, size, handleEnd);
}

static void		divideAndComp(int step, int size,int start, int handleEnd)
{
	for (size_t i = start; i < this->container.size() - handleEnd; i += step)
	{
		if (this->container[i - 1] > this->container[i])
		{
			int	temp = this->container[i - 1];
			this->container[i - 1] = this->container[i];
			this->container[i] = temp;
		}
	}
	this->printVec();
	step *= 2;
	if (step == size)
		return ;
	handleEnd = (size % step == 0) ? 0 : 1;
	start = step - 1;
	divideAndComp(step, size, start, handleEnd);
}

static void swap(int pos, int range)
{
	std::vector<int> temp;


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
				this->container.push_back(number);
				str.erase(0, pos + 1);
			}
			else
			{
				number = strConvert<int>(str);
				this->container.push_back(number);
				break ;
			}
		}
	}
}

void		PmergeMe::printVec()
{
	for (size_t i = 0; i < this->container.size(); i++)
	{
		std::cout << this->container[i] << " ";
	}
	std::cout << std::endl;
}
