/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:50 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/09 11:17:28 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

void	PmergeMe::parseInput(char **av) {
	std::string	token;
	int			value;

	inputSize = 0;
	while (*av) {
		if (isNumeric(*av)) {
			value = std::atoi(*av);
			if (value < 0)
				throw std::runtime_error("negative number => " + std::string(*av));
			vet.push_back(value);
			deq.push_back(value);
			inputSize++;
		} else
			throw std::runtime_error("invalid token => " + std::string(*av));
		av++;
	}
}

void	PmergeMe::printVet(std::vector<int> vet) {
	 std::vector<int>::iterator	i = vet.begin();
	 while (i != vet.end())
	 	std::cout << " " << *i++;
	std::cout << std::endl;
}

void	PmergeMe::printDeq(std::deque<int> deq) {
	 std::deque<int>::iterator	i = deq.begin();
	 while (i != deq.end())
	 	std::cout << " " << *i++;
	std::cout << std::endl;
}

void	PmergeMe::pairedSortVet(void) {
	int	a, b;
	while (vet.size()) {
		a = vet.at(0);
		vet.erase(vet.begin());
		if (vet.size()) {
			b = vet.at(0);
			vet.erase(vet.begin());
			if (a < b)
				(shortest_vet.push_back(a), longest_vet.push_back(b));
			else
				(shortest_vet.push_back(b), longest_vet.push_back(a));
			std::cout << "Pair | A = " << a << " B = " << b << std::endl;
		} else
			(hasLast = 1 ,lastVet = a, std::cout << "A = " << a << std::endl);
	}
	hasLast ? std::cout << "LastVet = " << lastVet << std::endl : std::cout << std::endl ;
	std::sort(longest_vet.begin(), longest_vet.end());
}

void	PmergeMe::pairedSortDeq(void) {
	
}
