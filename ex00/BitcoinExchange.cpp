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

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    // std::cout << "BitcoinExchange constructor called" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    // std::cout << "BitcoinExchange destructor called" << std::endl;
}


BitcoinExchange::BitcoinExchange(BitcoinExchange const &original)
{
    // std::cout << "BitcoinExchange copy constructor called" << std::endl;
    *this = original;
}

BitcoinExchange  &BitcoinExchange::operator=(BitcoinExchange const &original)
{
    if (this != &original)
    {
        // std::cout << "BitcoinExchange assignation operator called" << std::endl;
    }
    return (*this);
}

BitcoinExchange::BitcoinExchange(const std::string &inputFile)
{
    // std::cout << "BitcoinExchange constructor called" << std::endl;
    loadFile(inputFile);
}

void    BitcoinExchange::loadFile(const std::string &inputFile)
{
    std::ifstream   file(inputFile);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        return ;
    }
    std::string     line;
    while (std::getline(file, line))
    {
        std::istringstream   ss(line);
        std::string         date;
        std::string rateStr;
        float               rate;
        if (std::getline(ss, date, '|') && std::getline(ss, rateStr))
        {
            try
            {
                rate = std::stof(rateStr);
                database[date] = rate;
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "Error: Could not parse rate for line: " << line << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Could not parse line: " << line << std::endl;
        }
    }
}

void BitcoinExchange::printDatabase() const {
    for (std::map<std::string, float>::const_iterator it = database.begin(); it != database.end(); ++it) {
        std::cout << "Date: " << it->first << ", Rate: " << it->second << '\n';
    }
}