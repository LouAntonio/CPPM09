/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:32:46 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/05 11:59:42 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <exception>

class RNP : public std::stack<int> {
	public:
		RNP() {}
		RNP (const RNP &src) : std::stack<int>(src) {}
		RNP &operator=(const RNP &src) {
			if (this != &src)
				std::stack<int>::operator=(src);
			return *this;
		}
		~RNP() {}

		void	build(char *str);
};

#endif