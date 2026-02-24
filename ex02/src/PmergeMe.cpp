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

PmergeMe::PmergeMe (const PmergeMe &other)
{
	if (this != &other)
	{
		this->_sizeStr = other._sizeStr;
	}
	// std::cout << "PmergeMe Copy constructeur called\n";
}

PmergeMe::PmergeMe (int _sizeStr) : _sizeStr(_sizeStr)
{
	// std::cout << "PmergeMe Parameterized constructeur called\n";
}

PmergeMe& PmergeMe::operator= (const PmergeMe &other)
{
	if (this != &other)
	{
	}
	return (*this);
}

PmergeMe::~PmergeMe (void)
{
	// std::cout << "PmergeMe Destructeur called\n";
}
