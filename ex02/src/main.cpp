/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:44:44 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/08 10:59:06 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

int main(int ac, char **av) {
	if (ac > 2) {
		try {
			std::cout << "OK" << std::endl;
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cout << "./PmergeMe [args]" << std::endl;
	(void)av;
	return 0;
}
