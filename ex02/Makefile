CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
NAME		=	PmergeMe
SRCS		=	main.cpp PmergeMe.cpp
OBJS		=	$(SRCS:.cpp=.o)
HFS			=	PmergeMe.hpp

%.o			:	%.cpp $(HFS)
				$(CXX) $(CXXFLAGS) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HFS)
				$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	clean fclean all re