PRGM = prog
FLAGS = -pthread -g -Wall -O0
OPTIONS =
ARCHV = $(PRGM)-$$(whoami)

HS = $(wildcard *.hpp)
CS = $(wildcard *.cpp)
OS = $(CS:.cpp=.o)

all: $(PRGM)
	@rm -Rf *.o
$(PRGM): $(OS)
	g++ $(FLAGS) $^ -o $@

%.o: %.cpp $(HS) makefile
	g++ $(FLAGS) -c $<

run: $(PRGM)
	./$(PRGM) $(OPTIONS)

dist:
	mkdir $(ARCHV)
	cp $(HS) $(CS) Makefile $(ARCHV)/
	tar zcf $(ARCHV).tar.gz $(ARCHV)
	rm -Rf $(ARCHV)

clean:
	@rm -Rf *.o $(PRGM) $(ARCHV) $(ARCHV).tar.gz
