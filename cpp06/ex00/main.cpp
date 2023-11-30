/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:52:10 by vvalet            #+#    #+#             */
/*   Updated: 2023/11/30 16:10:22 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(void)
{	
	ScalarConverter::convert("\'0\'");
	ScalarConverter::convert("0");
	ScalarConverter::convert("20");
	ScalarConverter::convert("33.32");
	ScalarConverter::convert("21456.32949494");
	ScalarConverter::convert("21456.32949494f");

	// converter.convert("2147483647");
	// converter.convert("-2147483648");
	// converter.convert("2147483648");
	// converter.convert("-2147483649");
	
}
