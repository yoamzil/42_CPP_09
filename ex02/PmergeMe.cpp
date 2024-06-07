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
    for (unsigned long i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] < 0)
        {
            throw std::invalid_argument("Negative numbers are not allowed.");
        }
    }
}

void    PmergeMe::printSequence(std::string state, std::vector<int> numbers)
{
    std::cout << state << ": ";
    for (unsigned long i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}

void    PmergeMe::merge(std::vector<int> leftArray, std::vector<int> rightArray, std::vector<int> &numbers)
{
    int leftSize = leftArray.size();
    int rightSize = rightArray.size();
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize)
    {
        if (leftArray[l] < rightArray[r])
            numbers[i++] = leftArray[l++];
        else
            numbers[i++] = rightArray[r++];
    }
    while (l < leftSize)
        numbers[i++] = leftArray[l++];
    while (r < rightSize)
        numbers[i++] = rightArray[r++];
}

void    PmergeMe::mergeSort(std::vector<int> &numbers)
{
    int     size = numbers.size();

    if (size <= 1)
        return ;

    int                 middle = size / 2;
    std::vector<int>    leftArray = std::vector<int>(numbers.begin(), numbers.begin() + middle);
    std::vector<int>    rightArray = std::vector<int>(numbers.begin() + middle, numbers.end());

    int i = 0, j = 0;
    for (; i < size; i++)
    {
        if (i < middle)
            leftArray[i] = numbers[i];
        else
            rightArray[j++] = numbers[i];
    }
    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(leftArray, rightArray, numbers);
}

void    PmergeMe::run(int ac, char **av)
{
    try
    {
        std::vector<int> numbers = parseInput(ac, av);
        isValidInput(numbers);
        printSequence("Before", numbers);
        mergeSort(numbers);
        printSequence("After", numbers);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}