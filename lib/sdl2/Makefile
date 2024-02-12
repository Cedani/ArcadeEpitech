##
## EPITECH PROJECT, 2021
## B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
## File description:
## Makefile
##

CXXFLAGS    +=  -W -Wall -Wextra -fPIC -g3 -lSDL2 -lSDL2_ttf -lSDL2_image

SRC		=		Windows.cpp

CXX		= g++ -std=c++14

OBJ 	= $(SRC:.cpp=.o)

NAME	=		../arcade_sdl2.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re