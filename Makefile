TARGET = sistema
CFLAGS = -g -Wall
LIBS = -lm
CC = gcc
EXEC = bin/sistema

SRC = src/main.c src/io.c src/validacao.c src/clientes.c src/arvore_cliente.c src/arvore_medicos.c src/medicos.c src/tempo.c src/consultas.c src/arvore_consulta.c

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(EXEC)

clean: 
	-rm -f *.o
	-rm -f $(TARGET)


