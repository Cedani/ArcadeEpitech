##
## EPITECH PROJECT, 2021
## B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
## File description:
## Makefile
##

SRC	=	src/main.cpp

CXXFLAGS    =    -W -Wall -Wextra -g3

CXX 		= g++ -std=c++14

NAME	=	arcade

CORE	=	arcade_core.a

all:	$(NAME)

core:
	make -C ./lib/core/Errors
	make -C ./lib/core

games:
	make -C ./lib/Game/menu
	make -C ./lib/Game/solarfox
	make -C ./lib/Game/PacMan
	make -C ./lib/Game/nibbler

graphicals:
	make -C ./lib/ncurses
	make -C ./lib/sdl2
	make -C ./lib/sfml


$(NAME):	core games graphicals
	$(CXX) -L$(shell pwd)/lib -o $(NAME) $(SRC) $(CXXFLAGS) ./lib/arcade_error.a -ldl

tests_run:
	$(CC) -o units $(SRC) $(UNIT) --coverage -lcriterion ./lib/my/libmy.a

clean:
		$(RM) $(OBJ)
		make -C ./lib/core clean
		make -C ./lib/ncurses clean
		make -C ./lib/sdl2 clean
		make -C ./lib/Game/menu clean
		make -C ./lib/Game/solarfox clean
		make -C ./lib/Game/PacMan clean
		make -C ./lib/Game/nibbler clean
		make -C ./lib/sfml clean
		make -C ./lib/Clock clean
		make -C ./lib/core/Errors clean

fclean: clean
		$(RM) $(NAME)
		make -C ./lib/core fclean
		make -C ./lib/ncurses fclean
		make -C ./lib/sdl2 fclean
		make -C ./lib/Game/menu fclean
		make -C ./lib/Game/solarfox fclean
		make -C ./lib/Game/PacMan fclean
		make -C ./lib/Game/nibbler fclean
		make -C ./lib/sfml fclean
		make -C ./lib/Clock fclean
		make -C ./lib/core/Errors fclean

re: 	fclean all

.PHONY:	all clean fclean re