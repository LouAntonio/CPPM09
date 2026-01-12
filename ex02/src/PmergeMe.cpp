/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:50 by lantonio          #+#    #+#             */
/*   Updated: 2026/01/12 14:32:40 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() {};

PmergeMe::PmergeMe(const PmergeMe &src) { *this = src; };

PmergeMe& PmergeMe::operator=(const PmergeMe &src) {

	if (this != &src)
		(original_vet = src.original_vet, original_deq = src.original_deq, ordered_vet = src.ordered_vet, ordered_deq = src.ordered_deq);
	return *this;
}
PmergeMe::~PmergeMe() {};

void	PmergeMe::parseInput(char **av) {
	char		*end;
	long		tmpValue;
	std::string	token;
	int			value;
	std::string	splited;
	

	len = 0;
	while (*av) {
		std::istringstream split(*av);
		while (split >> token) {
			if (isNumeric(token)) {
				end = NULL;
				tmpValue = std::strtol(token.c_str(), &end, 10);
				if (*end != '\0')
					throw std::runtime_error("invalid token => " + token);
				if (tmpValue > INT_MAX || tmpValue < INT_MIN)
					throw std::runtime_error("value out of int limits => " + token);
				value = static_cast<int>(tmpValue);
				if (value < 0)
					throw std::runtime_error("negative number => " + std::string(token));
				original_vet.push_back(value);
				original_deq.push_back(value);
			} else
				throw std::runtime_error("invalid token => " + std::string(*av));
			len++;
		}
		av++;
	}
	if (len < 2)
		throw std::runtime_error("invalid number of arguments\n./PmergeMe [args]");
}

void	PmergeMe::printInput(char **av) {
	std::string	token;

	while (*av) {
		std::istringstream split(*av++);
		while (split >> token)
			std::cout << token << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sortVet(std::vector<int> &vet) {
	int n = (int)vet.size();

	if (n <= 1) {
		ordered_vet = vet;
		return;
	}

	bool	hasOdd = false;
	int		stash = 0;
	if (n % 2 != 0) {
		hasOdd = true;
		stash = vet.back();
		vet.pop_back();
		n--;
	}

	int					a, b;
	std::vector<int>	mainChain, pendings;
	mainChain.reserve(n / 2);
	pendings.reserve(n / 2);
	for (int i = 0; i < n; i += 2) {
		a = vet[i];
		b = vet[i + 1];

		if (a < b)
			std::swap(a, b);
		mainChain.push_back(a);
		pendings.push_back(b);
	}

	int	minPos = 0;
	for (int i = 1; i < (int)mainChain.size(); ++i) {
		if (mainChain[i] < mainChain[minPos])
			minPos = i;
	}

	int	firstPending = pendings[minPos];
	sortVet(mainChain);

	std::vector<int>	result = ordered_vet;
	result.insert(result.begin(), firstPending);

	int					pSize = (int)pendings.size();
	std::vector<char>	used(pSize, 0);
	used[minPos] = 1;

	std::vector<int>	jac = jacobsthalVet(pSize);
	for (int i = 1; i < (int)jac.size(); ++i) {
		int j = jac[i] - 1;
		if (j < 0 || j >= pSize) break;
		if (used[j]) continue;

		std::vector<int>::iterator	pos = std::lower_bound(result.begin(), result.end(), pendings[j]);
		result.insert(pos, pendings[j]);
		used[j] = 1;
	}

	for (int i = 0; i < pSize; ++i) {
		if (used[i]) continue;
		std::vector<int>::iterator	pos = std::lower_bound(result.begin(), result.end(), pendings[i]);
		result.insert(pos, pendings[i]);
	}

	if (hasOdd) {
		std::vector<int>::iterator	pos = std::lower_bound(result.begin(), result.end(), stash);
		result.insert(pos, stash);
	}

	ordered_vet = result;
}

void PmergeMe::sortDeq(std::deque<int> &deq) {
	int n = (int)deq.size();

	if (n <= 1) {
		ordered_deq = deq;
		return;
	}

	bool	hasOdd = false;
	int		stash = 0;
	if (n % 2 != 0) {
		hasOdd = true;
		stash = deq.back();
		deq.pop_back();
		n--;
	}

	int				a, b;
	std::deque<int> mainChain, pendings;
	for (int i = 0; i < n; i += 2) {
		a = deq[i];
		b = deq[i + 1];

		if (a < b)
			std::swap(a, b);
		mainChain.push_back(a);
		pendings.push_back(b);
	}

	int	minPos = 0;
	for (int i = 1; i < (int)mainChain.size(); ++i) {
		if (mainChain[i] < mainChain[minPos])
			minPos = i;
	}

	int	firstPending = pendings[minPos];
	sortDeq(mainChain);

	std::deque<int>	result = ordered_deq;
	result.push_front(firstPending);

	int					pSize = (int)pendings.size();
	std::deque<char>	used(pSize, 0);
	used[minPos] = 1;

	std::deque<int>	jac = jacobsthalDeq(pSize);
	for (int i = 1; i < (int)jac.size(); ++i) {
		int j = jac[i] - 1;
		if (j < 0 || j >= pSize) break;
		if (used[j]) continue;

		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendings[j]);
		result.insert(pos, pendings[j]);
		used[j] = 1;
	}

	for (int i = 0; i < pSize; ++i) {
		if (used[i]) continue;
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendings[i]);
		result.insert(pos, pendings[i]);
	}

	if (hasOdd) {
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), stash);
		result.insert(pos, stash);
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
