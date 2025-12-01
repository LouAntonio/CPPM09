/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:44:48 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/01 14:06:54 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int validateDate(const std::string &date) {
    if (date.size() != 10)
        return 0;

    if (date[4] != '-' || date[7] != '-')
        return 0;

    for (size_t i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return 0;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (year < 0001 || year > 2025 || month < 1 || month > 12)
        return 0;

    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = false;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        leap = true;
    if (leap) daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return 0;
    return 1;
}

int	validateValue(std::string value) {
	errno = 0;
	char		*end_ptr;
	double		toDouble = std::strtod(value.c_str(), &end_ptr);
	if (errno == ERANGE)
		throw std::runtime_error("value out of limits!");
	else if (end_ptr == value.c_str() || *value.c_str() == '\0' || *end_ptr != '\0')
		throw std::runtime_error("invalid value!");
	else if (toDouble < 0)
		throw std::runtime_error("not a positive number!");
	
	return 1;
}

double	convertToDouble(std::string str) {
	char		*end_ptr;
	return std::strtod(str.c_str(), &end_ptr);
}

int	ft_split(std::string line, char c) {
	return static_cast<int>(line.find(c));
}

void	parse_db(Btc *db) {
	std::string	date;
	std::string	exchange;
	std::string	lineFromDB;
	std::ifstream dbFile("data.csv");

	if (!dbFile.is_open())
		std::runtime_error("error while opening the file!");

	getline(dbFile, lineFromDB);
	if (lineFromDB != "date,exchange_rate")
		std::runtime_error("invalid input file!");

	int pos;
	while (getline(dbFile, lineFromDB)) {
		pos = ft_split(lineFromDB, ',');
		if (pos == -1)
			throw Btc::badInput();
		date = lineFromDB.substr(0, pos);
		exchange = lineFromDB.substr(pos + 1);
		if (!validateDate(date))
			throw std::runtime_error("invalid date format!");
		if (!validateValue(exchange))
			throw std::runtime_error("invalid date format!");
		db->push(db->parseDate(date), convertToDouble(exchange));
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		Btc	db;
		try {
			parse_db(&db);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cout << "./btc [input file]" << std::endl;
	(void)av;
	return 0;
}
