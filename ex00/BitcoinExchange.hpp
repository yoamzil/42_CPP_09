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

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class   BitcoinExchange
{
	private:
		std::map<std::string, float>	database;

		void	loadFiles(const std::string &inputFile, const std::string &outputFile);
		bool    isValidFormat(const std::string &line);
		bool	isValidDate(const std::string &date);
		bool	isValidValue(const float &value);

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &original);
		BitcoinExchange  &operator=(BitcoinExchange const &original);

		void	exchange(const std::string &inputFile);
};

#endif