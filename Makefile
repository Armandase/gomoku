CXX		=	c++
NAME 	= 	gomoku
SRC 	=	main.cpp utils.cpp drawCircle.cpp \
			minMaxAlgorithm.cpp handleMouse.cpp \
			Button.cpp startMenu.cpp \
			gameChecker.cpp
HEADER	=	inc/gomoku.hpp inc/utils.hpp \
			inc/minMaxAlgorithm.hpp inc/Button.hpp 
OBJS	=	$(addprefix obj/, $(SRC:.cpp=.o))
CXXFLAGS=	-Wall -Wextra --std=c++17 -g
LDFLAGS = 	-lSDL2

all		:	${NAME}

${NAME}	:	${OBJS} ${HEADER}
			${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS} ${LDFLAGS}

obj/%.o: src/%.cpp $(HEADER)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf obj/

re: fclean all

.PHONY: all fclean clean re
