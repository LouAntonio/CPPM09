/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:50 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/12 10:38:36 by lantonio         ###   ########.fr       */
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
			original_vet.push_back(value);
			original_deq.push_back(value);
		} else
			throw std::runtime_error("invalid token => " + std::string(*av));
		av++;
	}
}

void PmergeMe::sortVet(std::vector<int> &vet) {
	int	_size = (int)vet.size();

	if (_size <= 1) {
		ordered_vet = vet;
		return;
	}

	bool	isOdd = false;
	int		stash;
	if (_size % 2 != 0) {
		isOdd = true;
		stash = vet.back();
		vet.pop_back();
	}

	int                 a, b;
	std::vector<int>	mainChain, pendings;
	mainChain.reserve(_size / 2);
	pendings.reserve(_size / 2);

	for (size_t i = 0; i < vet.size(); i += 2) {
		a = vet[i];
		b = vet[i+1];

		if (a < b)
			std::swap(a, b);
		mainChain.push_back(a);
		pendings.push_back(b);
	}
	sortVet(mainChain);

	int                 _pSize = (int)pendings.size();
	std::vector<int>    result = ordered_vet;

	if (_pSize > 0) {
		std::vector<int>    jac = jacobsthalVet(_pSize);
		std::vector<char>   used(_pSize, 0);
		std::vector<int>    insertion_order;
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

void PmergeMe::sortDeq(std::deque<int> &deq) {
	int	_size = (int)deq.size();

	if (_size <= 1) {
		ordered_deq = deq;
		return;
	}

	bool	isOdd = false;
	int		stash;
	if (_size %2 != 0) {
		isOdd = true;
		stash = deq.back();
		deq.pop_back();
	}

	int				a, b;
	std::deque<int>	mainChain, pendings;
	for (size_t i = 0; i < deq.size(); i += 2) {
		a = deq[i];
		b = deq[i + 1];

		if (a < b)
			std::swap(a, b);
		mainChain.push_back(a);
		pendings.push_back(b);
	}
	sortDeq(mainChain);

	int				_pSize = (int)pendings.size();
	std::deque<int>	result = ordered_deq;

	if (_pSize > 0) {
		std::deque<int>		jac = jacobsthalDeq(_pSize);
		std::deque<char>	used(_pSize, 0);
		std::deque<int>		insertion_order;

		for(int i = 1; i < (int)jac.size(); ++i) {
			int	jval = jac[i];
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
			std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), element);
			result.insert(pos, element);
		}

		for (int i = 0; i < _pSize; ++i) {
			if (used[i]) continue;
			int element = pendings[i];
			std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), element);
			result.insert(pos, element);
		}
	}

	if (isOdd) {
		std::deque<int>::iterator i = std::lower_bound(result.begin(), result.end(), stash);
		result.insert(i, stash);
	}
	ordered_deq = result;
}

std::vector<int> PmergeMe::jacobsthalVet(int n) {
	std::vector<int> sequence;
	sequence.reserve(n + 1);

	sequence.push_back(0);
	if (n >= 1) sequence.push_back(1);
	
	for (int i = 2; i <= n; ++i) {
		sequence.push_back(sequence[i - 1] + 2 * sequence[i - 2]);
	}
	
	return sequence;
}

std::deque<int> PmergeMe::jacobsthalDeq(int n) {
	std::deque<int> sequence;

	sequence.push_back(0);
	if (n >= 1) sequence.push_back(1);
	
	for (int i = 2; i <= n; ++i) {
		sequence.push_back(sequence[i - 1] + 2 * sequence[i - 2]);
	}
	
	return sequence;
}
