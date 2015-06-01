#------------------------------------------------------------------------------

SOURCE= graph.cpp algorithm.cpp main.cpp
MYPROGRAM= planning
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)


$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) 

clean:

	rm -f $(MYPROGRAM)
