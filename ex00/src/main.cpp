/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:09:13 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/18 17:44:53 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "BitcoinExchange.hpp"

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Only one argument" << std::endl;
		return (1);
	}
	openFile(argv[1]);
	return (0);
}
