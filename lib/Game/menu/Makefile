##
## EPITECH PROJECT, 2021
## B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
## File description:
## Makefile
##

CXXFLAGS    +=    -W -Wall -Wextra -fPIC -g3

SRC		=		Menu.cpp

CXX		= g++ -std=c++14

OBJ 	= $(SRC:.cpp=.o)

CL	=	../../arcade_clock.a

NAME	=	../../arcade_menu.so

all:	$(NAME)

clock:
	make -C ../../Clock

$(NAME):	clock $(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CL) $(CXXFLAGS)

clean:
		$(RM) $(OBJ)

fclean: clean
		rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re