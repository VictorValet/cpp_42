/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:49:02 by vvalet            #+#    #+#             */
/*   Updated: 2023/12/20 15:49:17 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::PmergeMe(char **argv)
{
	timeval		vector_beginning;
	timeval		vector_end;
	long long	vector_chrono;
	timeval		list_beginning;
	timeval		list_end;
	long long	list_chrono;

	this->verify_arguments(argv);
	
	for (unsigned int i = 0; argv[i]; i++)
	{
		std::cout << argv[i];
		if (argv[i] + 1 != 0)
			std::cout << " ";
	}
	std::cout << '\n';

	gettimeofday(&vector_beginning, NULL);
	this->fill_container(argv, this->_vector);
	this->recursive_sort(1, this->_vector);
	gettimeofday(&vector_end, NULL);
	vector_chrono = (vector_end.tv_sec - vector_beginning.tv_sec) * 1000000 + (vector_end.tv_usec - vector_beginning.tv_usec);

	gettimeofday(&list_beginning, NULL);
	this->fill_container(argv, this->_list);
	this->recursive_sort(1, this->_list);
	gettimeofday(&list_end, NULL);
	list_chrono = (list_end.tv_sec - list_beginning.tv_sec) * 1000000 + (list_end.tv_usec - list_beginning.tv_usec);

	for (unsigned int i = 0; i < this->_vector.size(); i++)
	{
		std::cout << this->_vector[i];
		if (i < this->_vector.size() - 1)
			std::cout << " ";
	}
	std::cout << '\n';

	std::cout << "Time to process a range of " <<  this->_vector.size() << " elements with std::vector : " 
		<< vector_chrono << '\n';//attention aux changements de seconde
	std::cout << "Time to process a range of " <<  this->_vector.size() << " elements with std::list : " 
		<< list_chrono << '\n';//attention aux changements de seconde
	return ;
}

PmergeMe::PmergeMe(const PmergeMe &original)
{
	*this = original;
	return ;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &original)
{
	(void) original;
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

void	PmergeMe::verify_arguments(char **argv)
{
	while (*argv)
	{
		int 		i = 0;
		while ((*argv)[i])
		{
			if (isdigit((*argv)[i]) == false)
				throw (ArgumentsException());
			i++;
		}
		std::string	check(*argv);
		if (check.size() > 10 || (check.size() == 10 && check > "2147483647"))
			throw (ArgumentsException());
		argv++;
	}
}

template<typename T>
void	PmergeMe::fill_container(char **argv, T &cont)
{
	while (*argv)
	{
		int n = atoi(*argv);
		cont.push_back(n);
		argv++;
	}
}

template<typename T>
T	PmergeMe::move(T it, long long n)
{
	while (n > 0)
	{
		it++;
		n--;
	}	
	while (n < 0)
	{
		it--;
		n++;
	}	
	return (it);
}

template<typename T>
void	PmergeMe::sort_range(unsigned int range, T &cont)
{
	long long				limit = cont.size() / (range * 2);
	typename T::iterator	left = this->move(cont.begin(), range - 1);
	typename T::iterator	right = this->move(left, range);
	for (int i = 0; i < limit; i++)
	{
		if (*left > *right)
		{
			std::swap_ranges(this->move(right, 1 - static_cast<long long>(range)),
			this->move(right, 1), this->move(left, 1 - static_cast<long long>(range)));
		}
		right = this->move(right, range);
		left = right;
		right = this->move(right, range);
	}
}

template<typename T>
void	PmergeMe::insert_range(unsigned int range, T &cont)
{
	long long				limit = cont.size() - range;
	typename T::iterator	left;
	typename T::iterator	right;
	for (int i = 0; i <= limit; i += (2 * range))
	{
		left = this->move(cont.begin(), range - 1);
		right = this->move(left, i);
		while (left != right)
		{
			if (*left > *right)
			{
				T copy(this->move(right, 1 - static_cast<long long>(range)), this->move(right, 1));
				cont.erase(this->move(right, 1 - static_cast<long long>(range)), this->move(right, 1));
				cont.insert(this->move(left, 1 - static_cast<long long>(range)), copy.begin(), copy.end());
				break ;
			}
			left = this->move(left, range);
		}
	}
}

template<typename T>
void	PmergeMe::recursive_sort(unsigned int range, T &cont)
{
	if (range > cont.size() / 2)
		return ;
	this->sort_range(range, cont);
	this->recursive_sort(range * 2, cont);
	this->insert_range(range, cont);
}

const char *PmergeMe::ArgumentsException::what(void) const throw()
{
	return ("Error: wrong argument");
}
