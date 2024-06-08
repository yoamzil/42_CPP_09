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

void    PmergeMe::printSequence(std::string state, std::list<int> numbers)
{
    std::cout << state << ": ";
    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void    PmergeMe::merge(T leftArray, T rightArray, T &numbers)
{
    typename T::iterator it = numbers.begin();
    typename T::iterator leftIt = leftArray.begin();
    typename T::iterator rightIt = rightArray.begin();

//     int leftSize = leftArray.size();
//     int rightSize = rightArray.size();
//     int i = 0, leftIt = 0, rightIt = 0;

    while (leftIt != leftArray.end() && rightIt != rightArray.end())
    {
        if (*leftIt < *rightIt)
            *it++ = *leftIt++;
        else
            *it++ = *rightIt++;
    }
    while (leftIt != leftArray.end())
        *it++ = *leftIt++;
    while (rightIt != rightArray.end())
        *it++ = *rightIt++;
}

template <typename T>
void    PmergeMe::mergeSort(T &numbers)
{
    size_t  size = numbers.size();
    if (size <= 1)
        return ;


    typename T::iterator middle = numbers.begin();
    std::advance(middle, size / 2);

    T leftArray(numbers.begin(), middle);
    T rightArray(middle, numbers.end());

    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(leftArray, rightArray, numbers);
}

template <typename T>
void    PmergeMe::mergeAndPrintExecutionTime(const T& container, const std::string& containerName)
{
    T copy = container;
    clock_t start = clock();
    mergeSort(copy);
    clock_t end = clock();
    double executionTime = double(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "Time to process a range of " << container.size() << " elements with " << containerName << ": " << executionTime << "ms" << std::endl;
}

void    PmergeMe::run(int ac, char **av)
{
    try
    {
        std::vector<int> numbers = parseInput(ac, av);
        isValidInput(numbers);
        printSequence("Before", numbers);

        std::vector<int> numbersVectorCopy = numbers;
        mergeSort(numbersVectorCopy);
        printSequence("After", numbersVectorCopy);

        
        mergeAndPrintExecutionTime(numbers, "std::vector");

        std::list<int> numbersListCopy(numbers.begin(), numbers.end());
        mergeAndPrintExecutionTime(numbersListCopy, "std::list");
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}