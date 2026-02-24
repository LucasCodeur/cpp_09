/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReversePolishNotation.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:16:20 by lud-adam          #+#    #+#             */
/*   Updated: 2026/02/22 19:15:03 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReversePolishNotation.hpp"
#include <cctype>
#include <stdexcept>

ReversePolishNotation::ReversePolishNotation (void)
{
	// std::cout << "ReversePolishNotation Default constructeur called\n";
}

ReversePolishNotation::ReversePolishNotation (const ReversePolishNotation &other)
{
	if (this != &other)
	{
		this->_sizeStr = other._sizeStr;
	}
	// std::cout << "ReversePolishNotation Copy constructeur called\n";
}

ReversePolishNotation::ReversePolishNotation (int _sizeStr) : _sizeStr(_sizeStr)
{
	// std::cout << "ReversePolishNotation Parameterized constructeur called\n";
}

ReversePolishNotation& ReversePolishNotation::operator= (const ReversePolishNotation &other)
{
	if (this != &other)
	{
		this->_sizeStr = other._sizeStr;
	}
	return (*this);
}

ReversePolishNotation::~ReversePolishNotation (void)
{
	// std::cout << "ReversePolishNotation Destructeur called\n";
}

static bool	detectOperators(char& op);

bool ReversePolishNotation::parsing(std::string polishExpression)
{
	int	operands = 0;
	int	operators = 0;
	std::string	errorMessage = "Error";

	if (polishExpression.empty() == true)
		throw std::runtime_error("Error");
	this->_sizeStr = polishExpression.length();
	for (int i = 0; i < this->_sizeStr; i++)
	{
		if (std::isspace(polishExpression[i]))
			continue ;
		else if (detectOperators(polishExpression[i]) == true)
			operators++;
		else if (!isdigit(polishExpression[i]))
			throw std::runtime_error(errorMessage);
		else
			operands++;
		if (operators >= operands)
			throw std::runtime_error(errorMessage);
	}
	if (operators < 1)
		throw::std::runtime_error(errorMessage);
	else if (std::abs(operands - operators) > 1) 
		throw::std::runtime_error(errorMessage);
	return (true);
}

static bool	detectOperators(char& op)
{
	if (op == '+' || op == '-' || op == '/' || op == '*')
		return (true);
	return (false);
}

static float	computeExpr(float operand_1, float operand_2, char& op);

bool ReversePolishNotation::rpn(std::string polishExpression)
{
	std::stack<float>	_stack;
	float				operand_1 = 0;
	float				operand_2 = 0;
	float				ret = 0;

	for (int i = 0; i < this->_sizeStr; i++)
	{
		if (std::isspace(polishExpression[i]))
			continue ;
		else if (detectOperators(polishExpression[i]) == true)
		{
			operand_1 = _stack.top();
			_stack.pop();
			operand_2 = _stack.top();
			_stack.pop();
			ret = computeExpr(operand_1, operand_2, polishExpression[i]);
			_stack.push(ret);
		}
		else
			_stack.push(strConvert<float>(polishExpression[i]));
	}
	std::cout << ret << std::endl;
	return (true);
}

static float	computeExpr(float operand_1, float operand_2, char& op)
{
	float		ret = 0;

	if (op == '+')
		ret = operand_2 + operand_1;
	else if (op == '-')
		ret = operand_2 - operand_1;
	else if (op == '*')
		ret = operand_2 * operand_1;
	else if (op == '/')
		ret = operand_2 / operand_1;
	return (ret);
}
