/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:45:06 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/08 12:29:05 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <exception>
#include <sstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <deque>
#include <vector>

bool	isNumeric(const std::string str);

class PmergeMe {
	public:
	std::vector<int>	vet;
	std::deque<int>		deq;
	std::vector<int>	ordered_vet;
	std::deque<int>		ordered_deq;
		PmergeMe() {};
		PmergeMe(const PmergeMe &src) { *this = src; };
		PmergeMe &operator=(const PmergeMe &src) {
			if (this != &src)
				(this->vet = src.vet, this->deq = src.deq);
			return *this;
		}
		~PmergeMe() {};

		void	parseInput(char **av);
		void	printVet(std::vector<int> vet);
		void	printDeq(std::deque<int> deq);
};

#endif
