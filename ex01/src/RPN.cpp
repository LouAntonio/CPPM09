/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:32:43 by lantonio          #+#    #+#             */
/*   Updated: 2026/01/12 14:31:31 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

RPN::RPN() {}

RPN::RPN (const RPN &src) : std::stack<int>(src) {}

RPN& RPN::operator=(const RPN& src) {
	if (this != &src)
		std::stack<int>::operator=(src);
	return *this;
}

RPN::~RPN() {}

void RPN::operate(const std::string input)
{
	std::string			token;
	std::istringstream	split(input);
	int					a, b, value, res;

	while (split >> token)
	{
		if (isNumeric(token))
		{
			value = std::atoi(token.c_str());
			if (value > 9)
				throw std::runtime_error("invalid digit in input (greater then 9) => " + token);
			push(value);
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (size() < 2)
				throw std::runtime_error("not enough operands for operator " + token);

			b = top();
			pop();
			a = top();
			pop();

			res = makeOperation(a, b, token);
			push(res);
		}
		else
			throw std::runtime_error("invalid token in input => " + token);
	}

	if (size() != 1)
		throw std::runtime_error("invalid RPN expression");

	std::cout << top() << std::endl;
}

int		RPN::makeOperation(int a, int b, std::string _operator) {
	if (_operator == "+")
	{
		if (a <= (INT_MAX - b))
			throw std::runtime_error("result out of int limits!");
		return a + b;
	}
	if (_operator == "-")
	{
		if (b < 0 && a > INT_MAX + b)
			throw std::runtime_error("result out of int limits!");
		return a - b;
	}
	if (_operator == "*")
	{
		if (a > (INT_MAX / b))
			throw std::runtime_error("result out of int limits!");
		return a * b;
	}
	return a / b;
}
