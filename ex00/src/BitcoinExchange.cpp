/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:35:00 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/03 10:16:52 by lantonio         ###   ########.fr       */
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
