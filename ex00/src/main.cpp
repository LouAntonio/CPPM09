/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:44:48 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/03 10:32:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int	ft_split(std::string line, char c) {
	return static_cast<int>(line.find(c));
}

std::string trim(const std::string str) {
	std::string result = str;

	std::string::iterator it = result.begin();
	while (it != result.end() && std::isspace(*it))
		++it;
	result.erase(result.begin(), it);

	if (result.empty())
		return result;

	std::string::iterator rit = result.end() - 1;
	while (rit != result.begin() && std::isspace(*rit))
		--rit;

	if (std::isspace(*rit))
		result.erase(rit, result.end());
	else
		result.erase(rit + 1, result.end());

	return result;
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		Btc	db;
		try {
			db.parse_db();
			db.parse_input_comparing(av[1]);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cout << "./btc [input file]" << std::endl;
	(void)av;
	return 0;
}
