/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:50 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/10 13:27:24 by lantonio         ###   ########.fr       */
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

void	PmergeMe::printContainer(std::vector<int> c) {
	std::vector<int>::iterator	i = c.begin();
	while (i != c.end())
	 	std::cout << *i++ << " ";
	std::cout << std::endl;
}

void PmergeMe::sortVets(std::vector<int> &c) {
	int		_size = (int)c.size();

	if (_size <= 1) return;

	bool	isOdd = false;
	int		stash = 0;
	if (_size % 2 != 0) {
		isOdd = true;
		stash = c.back();
		c.pop_back();
	}

	std::vector<int> mainChain;
	std::vector<int> pendings;    
	mainChain.reserve(_size / 2);
	pendings.reserve(_size / 2);

	for (size_t i = 0; i < c.size(); i += 2) {
		int a = c[i];
		int b = c[i+1];

		if (a < b) {
			pendings.push_back(a);
			mainChain.push_back(b);
		} else {
			pendings.push_back(b);
			mainChain.push_back(a);
		}
	}


	sortVets(mainChain);

	int _pSize = pendings.size();

	std::vector<int> result = mainChain;

	if (_pSize > 0) {
		std::vector<int> jac = jacobsthal(_pSize);
		std::vector<char> used(_pSize, 0); // char em C++98, usado como bool
		std::vector<int> insertion_order;
		insertion_order.reserve(_pSize);

		for (int i = 1; i < (int)jac.size(); ++i) {
			int jval = jac[i];
			if (jval <= 0) continue;
			if (jval > _pSize) break;
			int idx = jval - 1;
			if (idx >= 0 && idx < _pSize && !used[idx]) {
				used[idx] = 1;
				insertion_order.push_back(idx);
			}
		}

		for (int k = 0; k < (int)insertion_order.size(); ++k) {
			int idx = insertion_order[k];
			if (idx < 0 || idx >= _pSize) continue;
			int element = pendings[idx];
			std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), element);
			result.insert(pos, element);
		}

		for (int i = 0; i < _pSize; ++i) {
			if (used[i]) continue;
			int element = pendings[i];
			std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), element);
			result.insert(pos, element);
		}
	}

	if (isOdd) {
		std::vector<int>::iterator i = std::lower_bound(result.begin(), result.end(), stash);
		result.insert(i, stash);
	}
	ordered_vet = result;
}

std::vector<int> PmergeMe::jacobsthal(int n) {
	std::vector<int> sequence(n+1);
	sequence[0] = 0;
	sequence[1] = 1;
	for(int i = 2; i <= n; i++)
		sequence[i] = sequence[i-1] + 2*sequence[i-2];
	return sequence;
}
