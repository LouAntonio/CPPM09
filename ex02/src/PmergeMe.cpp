/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:50 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/08 12:31:22 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

void	PmergeMe::parseInput(char **av) {
	std::string	token;
	int			value;

	while (*av) {
		if (isNumeric(*av)) {
			value = std::atoi(*av);
			if (value < 0)
				throw std::runtime_error("negative number => " + std::string(*av));
			vet.push_back(value);
			deq.push_back(value);
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
