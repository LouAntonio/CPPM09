/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:45:06 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/11 15:09:44 by lantonio         ###   ########.fr       */
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
		std::vector<int>	original_vet;
		std::vector<int>	ordered_vet;
		std::deque<int>		original_deq;
		std::deque<int>		ordered_deq;

		PmergeMe() {};
		PmergeMe(const PmergeMe &src) { *this = src; };
		PmergeMe &operator=(const PmergeMe &src) {
			if (this != &src)
				(original_vet = src.original_vet, original_deq = src.original_deq, ordered_vet = src.ordered_vet, ordered_deq = src.ordered_deq);
			return *this;
		}
		~PmergeMe() {};

		void				parseInput(char **av);
		std::vector<int>	jacobsthalVet(int n);
		std::deque<int>		jacobsthalDeq(int n);

		template <typename Container>
		void				printContainer(Container c) {
			typename Container::iterator	i = c.begin();
			while (i != c.end())
				std::cout << *i++ << " ";
			std::cout << std::endl;
		}

		void				sortDeq(std::deque<int> &vet);
		void				sortVet(std::vector<int> &deq);
};

#endif
