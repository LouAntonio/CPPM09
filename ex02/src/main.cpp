/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:44 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/12 10:54:33 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

int lastVet;
int lastDeq;

bool isNumeric(const std::string str)
{
	size_t	i = 0;
	if (str.empty())
		return false;
	if (str[i] == '-' || str[i] == '+') i = 1;
	if (str[i] == '\0') return false;
	for (; i < str.size(); ++i)
		if (!std::isdigit(str[i]))
			return false;
	return true;
}

int main(int ac, char **av) {
	if (ac > 2) {
		try {
			PmergeMe		pmergeme;
			struct timeval	start, end;
			long			seconds, usec;
			double			total;

			pmergeme.parseInput(av + 1);

			gettimeofday(&start, NULL);
			pmergeme.sortVet(pmergeme.original_vet);
			gettimeofday(&end, NULL);
			seconds = end.tv_sec  - start.tv_sec;
			usec = end.tv_usec - start.tv_usec;
			total = seconds * 1000000 + usec;
			std::cout << "Before: ";
			pmergeme.printInput(av + 1);
			std::cout << "After:  ";
			pmergeme.printContainer(pmergeme.ordered_vet);
			std::cout << "Time to process a range of " << pmergeme.len << " elements " << total << " ms" << std::endl;
			
			std::cout << "---" << std::endl;
			gettimeofday(&start, NULL);
			pmergeme.sortDeq(pmergeme.original_deq);
			gettimeofday(&end, NULL);
			seconds = end.tv_sec  - start.tv_sec;
			usec = end.tv_usec - start.tv_usec;
			total = seconds * 1000000 + usec;
			std::cout << "Before: ";
			pmergeme.printInput(av + 1);
			std::cout << "After:  ";
			pmergeme.printContainer(pmergeme.ordered_deq);
			std::cout << "Time to process a range of " << pmergeme.len << " elements " << total << " ms" << std::endl;
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cout << "./PmergeMe [args]" << std::endl;
	return 0;
}
