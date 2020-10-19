#------------------------------------------------------------------------------
# Tia Bhattacharya 
# rubhatta
# CSE101
# Dec 5, 2019
# Compiles files for pa5
# Makefile
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
SUBMIT	       = submit cse101-pt.f19 pa5
FILES	       = List.c List.h Graph.c Graph.h GraphTest.c FindComponents.c Makefile README 

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents GraphClient FindComponents.o GraphClient.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in3 junk3

checkClient : GraphClient
	$(MEMCHECK) GraphClient

submit: ${FILES}
	${SUBMIT} ${FILES}

checksubmit: 
	ls /afs/cats.ucsc.edu/class/cse101-pt.f19/pa5/rubhatta