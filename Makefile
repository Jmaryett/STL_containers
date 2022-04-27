NAME = ft_containers

FLAGS	= --std=c++98 -Wall -Wextra -Werror

SRCS = main.cpp

INCLUDES = vector/vector.hpp utils/utils.hpp \
			iterators/vector_iterator.hpp iterators/reverse_iterator.hpp

OBJ	= $(SRCS:.cpp=.o)

%.o: %.cpp $(INCLUDES)
	clang++ $(FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re all clean fclean