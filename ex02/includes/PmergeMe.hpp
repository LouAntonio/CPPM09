/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:45:06 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/11 11:33:48 by lantonio         ###   ########.fr       */
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

extern int lastVet;
extern int lastDeq;

bool						isNumeric(const std::string str);

class PmergeMe {
	public:
		int					inputSize;

		std::vector<int>	vet;
		std::vector<int>	ordered_vet;
		std::deque<int>		deq;

		PmergeMe() {};
		PmergeMe(const PmergeMe &src) { *this = src; };
		PmergeMe &operator=(const PmergeMe &src) {
			if (this != &src)
				(this->vet = src.vet, this->deq = src.deq);
			return *this;
		}
		~PmergeMe() {};

		void				parseInput(char **av);

		void				printContainer(std::vector<int> c);

		void				sortVets(std::vector<int> &vet);

		std::vector<int>	jacobsthal(int n);
};

#endif
