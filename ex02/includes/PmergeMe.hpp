/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:45:06 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/08 11:08:57 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <exception>
#include <string>
#include <algorithm>

class PmergeMe {
	public:
		PmergeMe() {};
		PmergeMe(const PmergeMe &src) {};
		PmergeMe &operator=(const PmergeMe &src) {
			if (this != &src)
				*this = src;
			return *this;
		}
		~PmergeMe();

		void	parseInput(std::string input);
};

#endif