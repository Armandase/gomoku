MAKEFLAGS += -j

CXX		=	c++
NAME 	= 	Gomoku
SRC 	=	main.cpp utils.cpp \
			minMaxAlgorithm.cpp minMaxUtils.cpp\
			handleMouse.cpp gameChecker.cpp \
			Button.cpp startMenu.cpp \
			Heuristic.cpp Board.cpp \
			Render.cpp

HEADER	=	inc/gomoku.hpp inc/utils.hpp \
			inc/minMaxAlgorithm.hpp inc/Button.hpp \
			inc/Heuristic.hpp inc/Board.hpp \
			inc/Pattern.hpp inc/Render.hpp
	
OBJS	=	$(addprefix obj/, $(SRC:.cpp=.o))
CXXFLAGS=	-Wall -Wextra --std=c++17 -Weffc++ -I$(SDL2_TTF) -I$(SDL2_IMAGE) -I/usr/include/SDL2 -Ofast -g
SDL2_TTF=	libs/SDL2_ttf
SDL2_IMAGE=	libs/SDL2_image
LDFLAGS = -lSDL2 -L$(SDL2_TTF)/build -lSDL2_ttf -L$(SDL2_IMAGE)/build -lSDL2_image -Wl,-rpath,$(SDL2_TTF)/build -Wl,-rpath,$(SDL2_IMAGE)/build -Ofast -g

all		:	${NAME} 

lib		:
			cd ${SDL2_TTF} && \
			./configure && \
			cmake -S . -B build && \
			make -C build

			cd ${SDL2_IMAGE} && \
			./configure && \
			cmake -S . -B build && \
			make -C build

lib_clean:
			rm -r ${SDL2_TTF}/build
			rm -r ${SDL2_IMAGE}/build

${NAME}	:	${OBJS} ${HEADER}
			${CXX} -o ${NAME} ${OBJS} ${LDFLAGS}

obj/%.o: src/%.cpp $(HEADER)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf obj/

re: fclean
	@make all

.PHONY: all fclean clean re
