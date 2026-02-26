/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:09:13 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/26 10:50:53 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "PmergeMe.hpp"

static void	t_strtod_error(std::string test);
static void	t_parsing(int argc, char** argv);
static void	t_fordjohnson(int argc, char **argv);

int	main(int argc, char** argv)
{
	// t_strtod_error("2a4");
	// t_parsing(argc, argv);
	t_fordjohnson(argc, argv);
	
}

static void	t_fordjohnson(int argc, char **argv)
{
	try 
	{
		PmergeMe	test;

		test.fillVec(argc, argv);
		PRINT("MAIN VEC")
		test.printVec(test.mainVec);
		test.fordJonhson();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
}

static void	t_parsing(int argc, char** argv)
{
	try 
	{
		PmergeMe	test;

		test.fillVec(argc, argv);
		test.printVec(test.mainVec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

static void	t_strtod_error(std::string test)
{
	try 
	{
		int number = strConvert<int>(test);
		std::cout << number << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
