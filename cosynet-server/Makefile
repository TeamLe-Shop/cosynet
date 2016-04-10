CC=clang
SRC=src/*.c
OBJ=$(SRC:src/%.c=%.o)
EXECUTABLE=cosyserver

all : $(EXECUTABLE)

$(EXECUTABLE) : $(SRC)
	$(CC) -c -g $(SRC)
	$(CC) $(OBJ) -o $(EXECUTABLE)

clean :
	rm *.o

