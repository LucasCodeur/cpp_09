/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:09:13 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/26 10:49:12 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>

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

	static int nbr_of_comps = 0;
	try 
	{
		clock_t start_vec = clock();
		PmergeMe	test;

		// std::cout << "\n";
		test.fillVec(argc, argv);
		// std::cout << "\033[31mBefore\033[00m: ";
		// test.printVec(test.vec);
		test.sortVec();
		clock_t end_vec = clock();
		double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;
		std::cout << "After:  ";
		test.printVec(test.vec);
		// std::cout << "\n";
		std::cout << "Time to process a range of " << test.vec.size()
				  << " elements with std::vector: " << std::fixed << std::setprecision(6)
				  << time_elapsed_vec << "s\n";
		std::cout << "Time to process a range of " << test.vec.size()
				  << " elements with std::dequeu: " << std::fixed << std::setprecision(6)
				  << time_elapsed_vec << "s\n";
		std::cout << "Number of comparisons: " << nbr_of_comps << '\n';
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
