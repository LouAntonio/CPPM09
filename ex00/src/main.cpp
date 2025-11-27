/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:44:48 by lantonio          #+#    #+#             */
/*   Updated: 2025/11/27 14:41:34 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

size_t	ft_split(std::string line, char c) {
	size_t	pos = line.find(c);
	return pos != std::string::npos ? pos : -1;
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::string	lineFromDB;
		Btc	bitcoin;

		std::ifstream db("data.csv");
		if (!db.is_open()) {
			std::cout << "Error while opening the file!" << std::endl;
			return 0;
		}
		getline(db, lineFromDB);
		if (lineFromDB != "date,exchange_rate")
		{
			std::cout << "Invalid input file!" << std::endl;
			return 1;
		}

		size_t pos;
		while (getline(db, lineFromDB)) {
			pos = ft_split(lineFromDB, ',');
			std::cout << lineFromDB.substr(0, pos) << " | " << lineFromDB.substr(pos + 1) << std::endl;
		}

	} else
		std::cout << "./btc [input file]" << std::endl;
	(void)av;
	return 0;
}
