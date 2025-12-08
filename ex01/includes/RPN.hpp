/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:32:46 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/05 15:14:08 by lantonio         ###   ########.fr       */
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

class RPN : public std::stack<int> {
	public:
		RPN() {}
		RPN (const RPN &src) : std::stack<int>(src) {}
		RPN &operator=(const RPN &src) {
			if (this != &src)
				std::stack<int>::operator=(src);
			return *this;
		}
		~RPN() {}

		void	operate(std::string input);
		int		makeOperation(int a, int b, std::string _operator);
};

#endif
