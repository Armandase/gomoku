MAKEFLAGS += -j

CXX       = c++
NAME      = Gomoku
TEST_NAME = run_test
SRC_MAIN  = main.cpp
TEST_MAIN = test_main.cpp
SRC       = Render.cpp utils.cpp \
            minMaxAlgorithm.cpp minMaxUtils.cpp \
            handleMouse.cpp gameChecker.cpp \
            Button.cpp startMenu.cpp \
            Heuristic.cpp Board.cpp

HEADER    = inc/gomoku.hpp inc/utils.hpp \
            inc/minMaxAlgorithm.hpp inc/Button.hpp \
            inc/Heuristic.hpp inc/Board.hpp \
            inc/Pattern.hpp inc/Render.hpp

OBJS      = $(addprefix obj/, $(SRC:.cpp=.o)) $(addprefix obj/, $(SRC_MAIN:.cpp=.o)) 
TEST_OBJS = $(addprefix obj/, $(SRC:.cpp=.o)) $(addprefix obj/, $(TEST_MAIN:.cpp=.o)) \
             obj/gtest-all.o

CXXFLAGS  = -Wall -Wextra --std=c++17 -Weffc++ -I${GTEST}/googletest/include -I${GTEST}/googletest -I$(SDL2_TTF) -I$(SDL2_IMAGE) -I/usr/include/SDL2 -Ofast -g
SDL2_TTF  = libs/SDL2_ttf
SDL2_IMAGE = libs/SDL2_image
GTEST     = libs/googletest
LDFLAGS   = -lSDL2 -L$(SDL2_TTF)/build -lSDL2_ttf -L$(SDL2_IMAGE)/build -lSDL2_image -Wl,-rpath,$(SDL2_TTF)/build -Wl,-rpath,$(SDL2_IMAGE)/build -Ofast -g

all       : ${NAME} 

lib       :
		cd ${SDL2_TTF} && \
		git checkout release-2.20.2 && \
		./configure && \
		cmake -S . -B build && \
		make -C build

		cd ${SDL2_IMAGE} && \
		git checkout release-2.8.0 && \
		./configure && \
		cmake -S . -B build && \
		make -C build

		cd ${GTEST} && \
		mkdir -p build && cd build && \
		cmake .. && make

lib_clean :
		rm -r ${SDL2_TTF}/build
		rm -r ${SDL2_IMAGE}/build
		rm -r ${GTEST}/googletest/build

${NAME} : ${OBJS} ${HEADER}
		${CXX} -o ${NAME} ${OBJS} ${LDFLAGS}

test: ${TEST_NAME}
	./${TEST_NAME}

${TEST_NAME}: ${TEST_OBJS}
		${CXX} -o ${TEST_NAME} ${TEST_OBJS} ${LDFLAGS} -pthread

obj/%.o: src/%.cpp $(HEADER)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

obj/test_main.o: test/${TEST_MAIN}
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

obj/gtest-all.o: ${GTEST}/googletest/src/gtest-all.cc
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

clean:
	rm -rf obj/

re: fclean
	@make all

.PHONY: all fclean clean re test lib lib_clean
