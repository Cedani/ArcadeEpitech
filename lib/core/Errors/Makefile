##
## EPITECH PROJECT, 2021
## B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
## File description:
## Makefile
##

CXXFLAGS    +=    -W -Wall -Wextra -fPIC -g3

SRC		=		Error.cpp

CXX		= g++ -std=c++14

OBJ 	= $(SRC:.cpp=.o)

NAME	=		../../arcade_error.a

CP	=	cp

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re