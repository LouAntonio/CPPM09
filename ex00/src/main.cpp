/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:44:48 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/03 10:16:41 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

double findClosest(const std::map<time_t, double>& bd, time_t inputTime)
{
    // Primeiro elemento >= inputTime
    auto it = bd.lower_bound(inputTime);

    // Caso 1: encontrou exatamente a data
    if (it != bd.end() && it->first == inputTime) {
        return it->second;
    }

    // Caso 2: nenhuma data >= inputTime → todas são menores
    // Retornar a última (a mais próxima e anterior)
    if (it == bd.end()) {
        --it;
        return it->second;
    }

    // Caso 3: inputTime é menor que a menor data do mapa
    // Não existe data anterior → não "aconteceu" nada ainda
    if (it == bd.begin()) {
        // não há datas passadas → depende do que você quer
        // mas normalmente retorna vazio ou lança erro
        return "";  
    }

    // Caso 4: existe uma anterior → essa é a data válida
    --it;  // agora it aponta para a data imediatamente anterior
    return it->second;
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

void validateDate(const std::string &date) {
	if (date.size() != 10)
		throw std::runtime_error("invalid date lenth!");

	if (date[4] != '-' || date[7] != '-')
		throw std::runtime_error("invalid date format!");

	for (size_t i = 0; i < date.size(); ++i) {
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			throw std::runtime_error("invalid char in date!");
	}

	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (year < 0001 || year > 2025 || month < 1 || month > 12)
		throw std::runtime_error("invalid year!");

	int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap = false;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		leap = true;
	if (leap) daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		throw std::runtime_error("invalid day in date!");
}

double	convertToDouble(std::string value) {
	errno = 0;
	char		*end_ptr;
	double		toDouble = std::strtod(value.c_str(), &end_ptr);
	if (errno == ERANGE)
		throw std::runtime_error("value out of limits!");
	else if (end_ptr == value.c_str() || *value.c_str() == '\0' || *end_ptr != '\0')
		throw std::runtime_error("invalid value!");
	else if (toDouble < 0)
		throw std::runtime_error("not a positive number!");
	return toDouble;
}

int	ft_split(std::string line, char c) {
	return static_cast<int>(line.find(c));
}

void	parse_db(Btc *db) {
	int pos;
	std::string	date;
	double	exchange;
	std::string	lineFromDB;
	std::ifstream dbFile("data.csv");

	if (!dbFile.is_open())
		std::runtime_error("error while opening the file!");

	getline(dbFile, lineFromDB);
	if (lineFromDB != "date,exchange_rate")
		std::runtime_error("invalid input file!");

	while (getline(dbFile, lineFromDB)) {
		pos = ft_split(lineFromDB, ',');
		if (pos == -1)
			throw std::runtime_error("bad input!");
		date = trim(lineFromDB.substr(0, pos));
		validateDate(date);
		exchange = convertToDouble(trim(lineFromDB.substr(pos + 1)));
		db->push(db->parseDate(date), exchange);
	}
}



void	parse_input_comparing(char *inputPath, Btc db) {
	int pos;
	std::string	date;
	double		value;
	std::string	lineFromInput;
	std::ifstream inputFile(inputPath);

	if (!inputFile.is_open())
	{
		std::cerr << "Error while opening input file!" << std::endl;
		return ;
	}
	getline(inputFile, lineFromInput);
	if (lineFromInput != "date | value") {
		std::cerr << "Invalid input file!" << std::endl;
		return ;
	}
	while (getline(inputFile, lineFromInput)) {
		try {
			pos = ft_split(lineFromInput, '|');
			if (pos == -1)
				throw std::runtime_error("invalid line!");
			date = trim(lineFromInput.substr(0, pos));
			validateDate(date);
			value = convertToDouble(lineFromInput.substr(pos + 1));
			std::cout << value << " | " << db.findMap(db.parseDate(date))->second << std::endl;
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		Btc	db;
		try {
			parse_db(&db);
			parse_input_comparing(av[1], db);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cout << "./btc [input file]" << std::endl;
	(void)av;
	return 0;
}
