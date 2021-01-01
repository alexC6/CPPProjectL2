CC = g++
STD = -std=c++17
CPPFLAGS = -Wall -Wextra -pedantic-errors
EXEC = foot
RM = rm -fv

.PHONY: all clean

all: $(EXEC)

$(EXEC): main.cpp Joueur.o Equipe.o Match.o foot.o
	$(CC) $(STD) $(CPPFLAGS) $^ -o $@ -g

Joueur.o: Joueur.cpp
	$(CC) $(STD) $(CPPFLAGS) -c -o $@ $<

Equipe.o: Equipe.cpp
	$(CC) $(STD) $(CPPFLAGS) -c -o $@ $<

Match.o: Match.cpp
	$(CC) $(STD) $(CPPFLAGS) -c -o $@ $<

foot.o: foot.cpp
	$(CC) $(STD) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) *.o $(EXEC)