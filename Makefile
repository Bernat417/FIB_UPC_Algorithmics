#------------------------------------------------------------------------------

SOURCE= graph main
MYPROGRAM= planning
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)


main: main.cpp
    $(CC) $(CFLAGS) main.cpp


graph: main.cpp
    $(CC) $(CFLAGS) graph.cpp


$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) 

clean:

	rm -f $(MYPROGRAM)

