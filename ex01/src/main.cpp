/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:01:51 by lantonio          #+#    #+#             */
/*   Updated: 2025/12/05 12:02:29 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		RNP	rnp;
		try {
			rnp.build(av[1]);
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	} else
		std::cerr << "./RNP \"args\"" << std::endl;
	return 0;
}
