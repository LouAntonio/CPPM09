/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:45:06 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/11 14:39:59 by lantonio         ###   ########.fr       */
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
		std::vector<int>	vet;
		std::vector<int>	ordered_vet;
		std::deque<int>		deq;
		std::deque<int>		ordered_deq;

		PmergeMe() {};
		PmergeMe(const PmergeMe &src) { *this = src; };
		PmergeMe &operator=(const PmergeMe &src) {
			if (this != &src)
				(this->vet = src.vet, this->deq = src.deq);
			return *this;
		}
		~PmergeMe() {};

		void				parseInput(char **av);
		std::vector<int>	jacobsthal(int n);

		template <typename Container>
		void				printContainer(Container c) {
			typename Container::iterator	i = c.begin();
			while (i != c.end())
				std::cout << *i++ << " ";
			std::cout << std::endl;
		}

		void				sortDeq(std::deque<int> &c);
		void				sortVet(std::vector<int> &c);
};

#endif
