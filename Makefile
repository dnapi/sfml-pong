NAME = game

SRC = main.cpp  Game.cpp Player.cpp Ball.cpp Ai.cpp #Animation.cpp
FLAGS = -Wall -Wextra -Werror -std=c++11 #17
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
INC = Game.hpp Player.hpp Ball.hpp Ai.cpp # Animation.hpp
OBJ = $(SRC:.cpp=.o)
CC = g++

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(FLAGS) $(SFMLFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp  $(INC)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re