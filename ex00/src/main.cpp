/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:44:48 by lantonio          #+#    #+#             */
/*   Updated: 2025/11/27 12:46:14 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

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
		
		const std::string a = "2021-02-22";
		std::cout << bitcoin.parseDate(a) << std::endl;

	} else
		std::cout << "./btc [input file]" << std::endl;
	(void)av;
	return 0;
}
