# by Sam Dunny

CC = g++  # use g++ compiler

FLAGS = -c
FLAGS += -std=c++17  # compile with C++ 17 standard
FLAGS += -Wall       # compile with all warnings
FLAGS += -I .        # compile with project directory on #include system path

LIBS = -lsfml-graphics
LIBS += -lsfml-window
LIBS += -lsfml-system
LIBS += -lsfml-audio

COMPILE = $(CC) $(FLAGS) -c

# $< loads first dependancy
# $^ loads all dependancies
# $@ loads target


sprite-app : bin/main.o
	$(CC) $^ -o $@ $(LIBS)

bin/main.o : src/main.cpp
	$(COMPILE) -o $@ $^



run-app : bin/run_app.o
	$(CC) $^ -o $@ $(LIBS)

bin/run_app.o : src/run_app.cpp
	$(COMPILE) -o $@ $^


# UTILITY: removes intermediary files and executables
clean:
	rm -f bin/* sprite-app run-app run_app.o main.o
