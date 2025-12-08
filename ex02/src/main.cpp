/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:44 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/08 11:48:56 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

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
			PmergeMe	pmergeme;
			pmergeme.parseInput(av + 1);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cout << "./PmergeMe [args]" << std::endl;
	return 0;
}
