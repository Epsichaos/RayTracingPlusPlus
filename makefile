PRGM = prog
FLAGS = -g -Wall -O3 -std=c++11
OPTIONS =
ARCHV = $(PRGM)-$$(whoami)

HS = $(wildcard *.hpp)
CS = $(wildcard *.cpp)
OS = $(CS:.cpp=.o)

all: $(PRGM)

$(PRGM): $(OS)
	clang++ $(FLAGS) $^ -o $@

%.o: %.cpp $(HS) makefile
	clang++ $(FLAGS) -c $<

run: $(PRGM)
	./$(PRGM) $(OPTIONS)

dist:
	mkdir $(ARCHV)
	cp $(HS) $(CS) Makefile $(ARCHV)/
	tar zcf $(ARCHV).tar.gz $(ARCHV)
	rm -Rf $(ARCHV)

clean:
	@rm -Rf *.o $(PRGM) $(ARCHV) $(ARCHV).tar.gz
