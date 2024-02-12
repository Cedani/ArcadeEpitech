##
## EPITECH PROJECT, 2021
## B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
## File description:
## Makefile
##

CXXFLAGS    +=    -W -Wall -Wextra -fPIC -g3

SRC		=		solarfox.cpp

CXX		= g++ -std=c++14

OBJ 	= $(SRC:.cpp=.o)

NAME	=	../../arcade_solarfox.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
		$(RM) $(OBJ)

fclean: clean
		rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re