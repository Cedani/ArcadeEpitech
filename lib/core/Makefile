##
## EPITECH PROJECT, 2021
## B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
## File description:
## Makefile
##

CXXFLAGS    +=    -W -Wall -Wextra -fPIC -g3

SRC		=		Errors/Error.cpp	\
				Core.cpp

CXX		= g++ -std=c++14

OBJ 	= $(SRC:.cpp=.o)

NAME	=		../arcade_core.so

ERROR	=	../arcade_error.a

CP	=	cp

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS) $(ERROR)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re