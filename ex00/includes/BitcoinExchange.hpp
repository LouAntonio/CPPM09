/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:35:03 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/03 10:32:25 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <ctime>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cstdlib>

int			ft_split(std::string line, char c);
std::string	trim(const std::string str);


class Btc {
	private:
		std::map <time_t, double> dates;
	public:
		Btc();
		Btc(const Btc &src);
		Btc &operator=(const Btc &src);
		~Btc();

		void								push(time_t date, double value);
		time_t								parseDate(const std::string &date);
		void								printmap(void);
		std::map<time_t, double>::iterator	findMap(time_t key);
		double								findClosest(time_t inputTime);
		void								validateDate(const std::string &date);
		double								convertToDouble(std::string value);
		void								parse_db(void);
		void								parse_input_comparing(char *inputPath);
		
};

#endif
