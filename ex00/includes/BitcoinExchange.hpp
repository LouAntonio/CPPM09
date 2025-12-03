/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:35:03 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/03 11:58:54 by lantonio         ###   ########.fr       */
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

std::string									trim(const std::string str);
int											ft_split(std::string line, char c);


class Btc {
	private:
		std::map <time_t, double> dates;
	public:
		Btc();
		Btc(const Btc &src);
		Btc &operator=(const Btc &src);
		~Btc();

		void								parse_db(void);
		void								printmap(void);
		std::map<time_t, double>::iterator	findMap(time_t key);
		double								findClosest(time_t inputData);
		void								push(time_t date, double value);
		double								convertToDouble(std::string value);
		time_t								parseDate(const std::string &date);
		void								validateDate(const std::string &date);
		void								parse_input_comparing(char *inputPath);
		
};

#endif
