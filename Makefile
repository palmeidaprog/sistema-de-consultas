TARGET = sistema
CFLAGS = -g -Wall
LIBS = -lm
CC = gcc
EXEC = bin/sistema

SRC = src/main.c src/io.c src/clientesconstantes.c src/clientes.c src/medicos.c src/consultas.c 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(EXEC)

clean: 
	-rm -f *.o
	-rm -f $(TARGET)


