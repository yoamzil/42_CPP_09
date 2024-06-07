/* ************************************************************************************** */
/*																						  */
/*                                                						d8b		888       */
/*                                                  					Y8P		888       */
/*                                                      						888       */
/*		888  888	  .d88b.   	8888b.  	88888b.d88b.	88888888	888 	888       */
/*		888  888 	d88""88b     	"88b 	888 "888 "88b    	d88P 	888 	888       */
/*		888  888 	888  888 	.d888888 	888  888  888		d88P   	888 	888       */
/*		Y88b 888 	Y88..88P 	888  888 	888  888  888	  d88P    	888 	888       */
/*		"Y88888  	"Y88P"  	"Y888888 	888  888  888	88888888 	888 	888       */
/*	  		 888																          */
/*		Y8b d88P																          */
/*		"Y88P"									By: yoamzil <yoamzil@student.1337.ma>     */
/*																						  */
/* ************************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	// std::cout << "PmergeMe constructor called" << std::endl;
}

PmergeMe::~PmergeMe()
{
	// std::cout << "PmergeMe destructor called" << std::endl;
}

PmergeMe::PmergeMe(PmergeMe const &original)
{
	// std::cout << "PmergeMe copy constructor called" << std::endl;
	*this = original;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &original)
{
	if (this != &original)
	{
		// std::cout << "PmergeMe assignation operator called" << std::endl;
		// database = original.database;
	}
	return (*this);
}

std::vector<int>    PmergeMe::parseInput(int ac, char **av)
{
    if (ac < 2)
    {
        throw std::invalid_argument("Not enough arguments provided.");
    }
    std::vector<int> numbers;
    for (int i = 1; i < ac; i++)
    {
        std::istringstream iss(av[i]);
        int number;
        if (!(iss >> number))
        {
            throw std::invalid_argument("Invalid argument provided.");
        }
        numbers.push_back(number);
    }
    return (numbers);
}

void    PmergeMe::isValidInput(std::vector<int> numbers)
{
    if (numbers.size() < 2)
    {
        std::cerr << "Error: Not enough numbers provided." << std::endl;
        return ;
    }
    for (unsigned long i = 0; i <= numbers.size(); i++)
    {
        if (numbers[i] < 0)
        {
            std::cerr << "Error: Negative numbers are not allowed." << std::endl;
            return ;
        }
    }
}

void    PmergeMe::run(int ac, char **av)
{
    try
    {
        std::vector<int> numbers = parseInput(ac, av);
        isValidInput(numbers);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}