/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:01:51 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/05 15:14:19 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

bool isNumeric(const std::string str)
{
	if (str.empty())
		return false;

	for (size_t i = 0; i < str.size(); ++i)
		if (!std::isdigit(str[i]))
			return false;
	return true;
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		RPN	rpn;
		try {
			rpn.operate(av[1]);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cerr << "./RPN \"args\"" << std::endl;
	return 0;
}
