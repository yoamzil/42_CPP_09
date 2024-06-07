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

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

class   PmergeMe
{
	private:
        static std::vector<int>     parseInput(int ac, char **av);
        static void                 isValidInput(std::vector<int> numbers);
        static void                 printSequence(std::string state, std::vector<int> numbers);
        static void                 mergeSort(std::vector<int> numbers);
        static void                 merge(std::vector<int> leftArray, std::vector<int> rightArray, std::vector<int> &numbers);

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe  &operator=(PmergeMe const &original);

        static void                 run(int ac, char **av);
};

#endif