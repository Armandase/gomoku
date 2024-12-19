# MAKEFLAGS += -j

CXX		=	g++
NAME 	= 	Gomoku
SRC 	=	utils.cpp \
			handleMouse.cpp \
			algorithmUtils.cpp \
			Button.cpp \
			Render.cpp \
			IBoard.cpp \
			DiagBoard.cpp \
			AntiDiagBoard.cpp \
			TransposedBoard.cpp \
			ClassicBoard.cpp \
			Game.cpp \
			pvs.cpp

HEADER	=	inc/gomoku.hpp \
			inc/algorithm.hpp \
			inc/Render.hpp \
			inc/IBoard.hpp \
			inc/Button.hpp \
			inc/DiagBoard.hpp \
			inc/AntiDiagBoard.hpp \
			inc/TransposedBoard.hpp \
			inc/ClassicBoard.hpp \
			inc/Game.hpp
			
TEST_NAME = run_test
SRC_MAIN  = main.cpp
TEST_FILES = main_test.cpp board.cpp extract_pattern.cpp game_rules.cpp algo.cpp

OBJS      = $(addprefix obj/, $(SRC:.cpp=.o)) $(addprefix obj/, $(SRC_MAIN:.cpp=.o)) 
TEST_OBJS = $(addprefix obj/, $(SRC:.cpp=.o)) $(addprefix obj/, $(TEST_FILES:.cpp=.o)) \
             obj/gtest-all.o

CXXFLAGS  = -Wall -Wextra --std=c++17 -I${GTEST}/googletest/include -I${GTEST}/googletest -I$(SDL2_TTF) -I$(SDL2_IMAGE)/include -I/usr/include/SDL2 -Ofast
SDL2_TTF  = libs/SDL2_ttf
SDL2_IMAGE = libs/SDL2_image
GTEST     = libs/gtest
LDFLAGS   = -lSDL2 -L$(SDL2_TTF)/build -lSDL2_ttf -L$(SDL2_IMAGE)/build -lSDL2_image \
            -Wl,-rpath,$(SDL2_TTF)/build -Wl,-rpath,$(SDL2_IMAGE)/build \
            -Ofast


all: lib ${NAME}

lib:
	@if [ ! -d "$(SDL2_TTF)/build" ]; then \
		echo "Building SDL2_ttf..."; \
		git submodule update --init && \
		cd ${SDL2_TTF} && \
		git checkout release-2.20.2 && \
		./configure && \
		cmake -S . -B build && \
		make -C build; \
	fi

	@if [ ! -d "$(SDL2_IMAGE)/build" ]; then \
		echo "Building SDL2_image..."; \
		git submodule update --init && \
		cd ${SDL2_IMAGE} && \
		git checkout release-2.8.0 && \
		./configure && \
		cmake -S . -B build && \
		make -C build; \
	fi

	@if [ ! -d "$(GTEST)/build" ]; then \
		echo "Building googletest..."; \
		git submodule update --init && \
		cd ${GTEST} && \
		mkdir -p build && cd build && \
		cmake .. && make; \
	fi

	@cd ${SDL2_TTF} && git checkout release-2.20.2 > /dev/null 2>&1
	@cd ${SDL2_IMAGE} && git checkout release-2.8.0 > /dev/null 2>&1

lib_clean :
		rm -rf ${SDL2_TTF}/build
		rm -rf ${SDL2_IMAGE}/build
		rm -rf ${GTEST}/googletest/build

${NAME} : ${OBJS} ${HEADER}
		${CXX} -o ${NAME} ${OBJS} ${LDFLAGS}

test: ${TEST_NAME}
	 ./${TEST_NAME} --gtest_filter=BoardRules.doubleThree

${TEST_NAME}: ${TEST_OBJS}
		make lib
		${CXX} -o ${TEST_NAME} ${TEST_OBJS} ${LDFLAGS} -pthread

obj/%.o: src/%.cpp $(HEADER)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

obj/%.o: test/%.cpp
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

obj/gtest-all.o: ${GTEST}/googletest/src/gtest-all.cc
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

push: fclean
	git add .
	git commit -m "${arg}"
	git push

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

clean:
	rm -rf obj/

re: fclean
	@make all

.PHONY: all fclean clean push re test lib lib_clean
