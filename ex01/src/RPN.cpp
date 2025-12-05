/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:32:43 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/05 15:08:49 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

void	RNP::parseInput(std::string input)
{
	qtdOperators = 0;
	std::string			token;
	std::istringstream	iss(input);

	while (iss >> token)
	{
		if (isNumeric(token))
		{
			int value = std::atoi(token.c_str());
			if (value > 9)
				throw std::runtime_error("invalid number in input (greater then 9) => " + token);
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/")
			qtdOperators++;
		else
			throw std::runtime_error("invalid token in input => " + token);
	}
}

void RNP::operate(const std::string input)
{
    std::string token;
    std::stack<int> tmp;
    std::istringstream iss(input);

    while (iss >> token)
    {
        if (isNumeric(token))
        {
            int value = std::atoi(token.c_str());
            tmp.push(value);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (tmp.size() < 2)
                throw std::runtime_error("not enough operands for operator " + token);

            int b = tmp.top(); tmp.pop();
            int a = tmp.top(); tmp.pop();

            int res = makeOperation(a, b, token);
            tmp.push(res);
        }
        else
            throw std::runtime_error("invalid token in input => " + token);
    }

    if (tmp.size() != 1)
        throw std::runtime_error("invalid RPN expression");

    std::cout << tmp.top() << std::endl;
}

int		RNP::makeOperation(int a, int b, std::string _operator) {
	if (_operator == "+")
		return a + b;
	if (_operator == "-")
		return a - b;
	if (_operator == "*")
		return a * b;
	return a / b;
}
