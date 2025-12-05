/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:32:46 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/05 14:34:22 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <exception>
#include <sstream>
#include <cstdlib>

bool		isNumeric(const std::string str);

class RNP : public std::stack<int> {
	private:
		int	qtdOperators;
	public:
		RNP() {}
		RNP (const RNP &src) : std::stack<int>(src) {}
		RNP &operator=(const RNP &src) {
			if (this != &src)
				std::stack<int>::operator=(src);
			return *this;
		}
		~RNP() {}

		void	parseInput(std::string input);
		void	operate(std::string input);
		int		makeOperation(int a, int b, std::string _operator);
};

#endif
