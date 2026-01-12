/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:45:06 by lantonio          #+#    #+#             */
/*   Updated: 2026/01/12 14:33:17 by lantonio         ###   ########.fr       */
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
#include <climits>
#include <sys/time.h>

extern int lastVet;
extern int lastDeq;

bool						isNumeric(const std::string str);

class PmergeMe {
	public:
		int					len;
		std::vector<int>	original_vet;
		std::vector<int>	ordered_vet;
		std::deque<int>		original_deq;
		std::deque<int>		ordered_deq;

		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);
		~PmergeMe();

		void				parseInput(char **av);
		void				printInput(char **av);
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
