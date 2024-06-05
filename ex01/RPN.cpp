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

#include "RPN.hpp"

RPN::RPN()
{
	// std::cout << "RPN constructor called" << std::endl;
}

RPN::~RPN()
{
	// std::cout << "RPN destructor called" << std::endl;
}

RPN::RPN(RPN const &original)
{
	// std::cout << "RPN copy constructor called" << std::endl;
	*this = original;
}

RPN &RPN::operator=(RPN const &original)
{
	if (this != &original)
	{
		// std::cout << "RPN assignation operator called" << std::endl;
		// database = original.database;
	}
	return (*this);
}

int     RPN::evaluate(std::string str)
{
    std::istringstream iss(str);
    std::string token;
    int a, b;

    while (iss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error: Invalid expression");
            b = stack.top();
            stack.pop();
            a = stack.top();
            stack.pop();
            if (token == "+")
                stack.push(a + b);
            else if (token == "-")
                stack.push(a - b);
            else if (token == "*")
                stack.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error("Error: Division by zero");
                stack.push(a / b);
            }
        }
        else
        {
            try
            {
                stack.push(std::stoi(token));
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Error: Invalid expression");
            }
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error: Invalid expression");
    return (stack.top());
}