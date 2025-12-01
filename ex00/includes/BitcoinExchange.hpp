/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:35:03 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/01 13:57:22 by lantonio         ###   ########.fr       */
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


class Btc {
	private:
		std::map <time_t, double> dates;
	public:
		Btc();
		Btc(const Btc &src);
		Btc &operator=(const Btc &src);
		~Btc();

		void	push(time_t date, double value);
		time_t	parseDate(const std::string &date);
		void	printmap(void);

		class badInput : public std::exception {
			virtual const char *what() const throw();
		};
		class outOfLimits : public std::exception {
			virtual const char *what() const throw();
		};
		class nonPositive : public std::exception {
			virtual const char *what() const throw();
		};
		
};

#endif
