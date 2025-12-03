/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:35:00 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/03 13:12:59 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"


Btc::Btc() {};

Btc::Btc(const Btc &src) { *this = src; };


Btc &Btc::operator=(const Btc &src) {
	if (this != &src)
		this->dates = src.dates;
	return *this;
};

Btc::~Btc() {};

int	Btc::size(void) {
	return static_cast<int>(this->dates.size());
}

void	Btc::push(time_t date, double value) {
	this->dates.insert(std::make_pair(date, value));
}

time_t	Btc::parseDate(const std::string &date) {
	int year, month, day;
	char dash1, dash2;

	std::istringstream iss(date);
	iss >> year >> dash1 >> month >> dash2 >> day;

	struct tm t;
	std::memset(&t, 0, sizeof(t));

	t.tm_year = year - 1900;
	t.tm_mon  = month - 1;
	t.tm_mday = day;

	t.tm_isdst = -1;

	return std::mktime(&t);
}

void Btc::printmap(void) {
	std::map<time_t, double>::iterator it = dates.begin();

	while (it != dates.end())
	{
		time_t raw = it->first;
		struct tm *t = localtime(&raw);

		char buffer[20];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);

		std::cout << buffer << " -> " << it->second << std::endl;

		++it;
	}
}

std::map<time_t, double>::iterator Btc::findMap(time_t key) {
	return this->dates.find(key);
}

void Btc::findClosest(time_t inputData, double value)
{
    std::map<time_t, double>::iterator it = this->dates.lower_bound(inputData);

    if (it != this->dates.end() && it->first == inputData) { // found the same data
		getCounterValue(inputData, value, it->second);
		return;
    }

    if (it == this->dates.end()) { // no data >= inputData, return the previous data
        --it;
		getCounterValue(inputData, value, it->second);
		return;
    }

    if (it == this->dates.begin()) { // no data is "before" inputData
        std::cout << "No data found!" << std::endl;
		return;
    }

	--it; // otherwise, use the previous data
	getCounterValue(inputData, value, it->second);
}

void Btc::validateDate(const std::string &date) {
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

	std::time_t now = std::time(NULL);
	std::tm *lt = std::localtime(&now);
	int currentYear = lt->tm_year + 1900;

	if (year < 2009 || year > currentYear)
		throw std::runtime_error("invalid year!");
	if (month < 1 || month > 12)
		throw std::runtime_error("invalid month!");

	int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap = false;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		leap = true;
	if (leap) daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		throw std::runtime_error("invalid day in date!");
}

double	Btc::convertToDouble(std::string value) {
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

void	Btc::parse_db(void) {
	int pos;
	std::string	date;
	double	exchange;
	std::string	lineFromDB;
	std::ifstream dbFile("data.csv");

	if (!dbFile.is_open())
		std::runtime_error("error while opening the file!");

	getline(dbFile, lineFromDB);
	if (lineFromDB != "date,exchange_rate")
		std::runtime_error("invalid database file!");

	while (getline(dbFile, lineFromDB)) {
		pos = ft_split(lineFromDB, ',');
		if (pos == -1)
			throw std::runtime_error("bad input!");
		date = trim(lineFromDB.substr(0, pos));
		validateDate(date);
		exchange = convertToDouble(trim(lineFromDB.substr(pos + 1)));
		push(parseDate(date), exchange);
	}
}

void	Btc::parse_input_comparing(char *inputPath) {
	int pos;
	std::string	date;
	double		value;
	std::string	lineFromInput;
	std::ifstream inputFile(inputPath);

	if (!inputFile.is_open())
		throw std::runtime_error("error while opening input file!");

	getline(inputFile, lineFromInput);
	if (lineFromInput != "date | value")
		throw std::runtime_error("invalid input file!");
	while (getline(inputFile, lineFromInput)) {
		try {
			pos = ft_split(lineFromInput, '|');
			if (pos == -1)
				throw std::runtime_error("invalid line!");
			date = trim(lineFromInput.substr(0, pos));
			validateDate(date);
			value = convertToDouble(lineFromInput.substr(pos + 1));
			findClosest(parseDate(date), value);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

void	Btc::getCounterValue(time_t date, double value, double exchange) {
	time_t raw = date;
	struct tm *t = localtime(&raw);

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);
	if (exchange == 0)
		std::cout << buffer << " => " << exchange << " = " << value << std::endl;
	else
		std::cout << buffer << " => " << exchange << " = " << value * exchange << std::endl;
}
