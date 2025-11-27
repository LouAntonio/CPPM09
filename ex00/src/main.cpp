/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:44:48 by lantonio          #+#    #+#             */
/*   Updated: 2025/11/27 11:04:34 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::string	db = "data.csv";
		std::string	lineToComp;

		std::ifstream toComp(av[1]);
		if (!toComp.is_open()) {
			std::cout << "Error while opening the file!" << std::endl;
			return 0;
		}
		getline(toComp, lineToComp);
		if (lineToComp != "date,exchange_rate")
		{
			std::cout << "Invalid input file!" << std::endl;
			return 1;
		}
	} else
		std::cout << "./btc [input file]" << std::endl;
	(void)av;
	return 0;
}
