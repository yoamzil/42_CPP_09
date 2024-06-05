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

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &original)
{
	if (this != &original)
	{
		// std::cout << "BitcoinExchange assignation operator called" << std::endl;
		database = original.database;
	}
	return (*this);
}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		return (false);
	}
	int year, month, day;
	try
	{
		year = std::stoi(date.substr(0, 4));
		month = std::stoi(date.substr(5, 2));
		day = std::stoi(date.substr(8, 2));
	}
	catch (const std::invalid_argument &)
	{
		return (false);
	}
	if (day < 1 || day > 31 || month < 1 || month > 12)
	{
		return (false);
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
	{
		return (false);
	}
	if (month == 2)
	{
		bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > 29 || (day > 28 && !leapYear))
			return (false);
	}
	return (true);
}

bool	BitcoinExchange::isValidValue(const float &value)
{
	if (value < 0 || value > 1000)
		return (false);
	return (true);
}

bool	BitcoinExchange::isValidFormat(const std::string &line)
{
	if (line != "date | value" && (line.length() != 14 || line[11] != '|'))
		return (false);
	return (true);
}

void	BitcoinExchange::loadFiles(const std::string &inputFile, const std::string &outputFile)
{
	// store the data from the database to the map
	std::ifstream dbFile(outputFile);
	if (!dbFile.is_open())
	{
		std::cerr << "Error: Could not open dbFile." << std::endl;
		return;
	}
	std::string dbLine;
	while (std::getline(dbFile, dbLine))
	{
		std::istringstream ss(dbLine);
		std::string dbDate;
		std::getline(ss, dbDate, ',');

		std::string rateStr;
		std::getline(ss, rateStr);

		float rate = std::atof(rateStr.c_str());
		database[dbDate] = rate;
	}

	// load the data from the input file
	std::ifstream file(inputFile);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file." << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date;
		std::string valueStr;
		float value;
		if (std::getline(ss, date, ' ') && std::getline(ss, valueStr))
		{
			std::istringstream ss2(valueStr);
			std::getline(ss2, valueStr, ' ') && std::getline(ss2, valueStr);
			if (!isValidFormat(line))
			{
				std::cerr << line << std::endl;
				std::cerr << "Error: Date | Value format isn't respected." << std::endl;
				return;
			}
			try
			{
				value = std::stof(valueStr);
				if (isValidDate(date) && isValidValue(value))
				{
					std::map<std::string, float>::iterator it = database.find(date);
					if (it != database.end())
					{
						std::cout << date << " => " << value << " = " << value * it->second << std::endl;
					}
					else
					{
						std::map<std::string, float>::iterator it = database.lower_bound(date);
						if (it == database.begin())
						{
							std::cerr << "Error: no data" << std::endl;
						}
						else
						{
							--it;
							std::cout << date << " => " << value << " = " << value * it->second << std::endl;
						}
					}
				}
				else if (value < 0)
					std::cerr << "Error: not a positive number." << std::endl;
				else if (value > 1000)
					std::cerr << "Error: too large a number." << std::endl;
				else if (!isValidDate(date))
				{
					std::cerr << "Error: bad input => " << date << std::endl;
				}
			}
			catch (const std::invalid_argument &)
			{
				std::cerr << "Error: Could not parse this line: " << line << std::endl;
			}
		}
		else
			std::cerr << "Error: Could not parse this line: " << line << std::endl;
	}
}

void	BitcoinExchange::exchange(const std::string &inputFile)
{
	loadFiles(inputFile, "data.csv");
}
