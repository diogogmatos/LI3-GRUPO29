CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
OBJS = catalog.o driver.o io.o main.o parsing.o queries.o ride.o stats.o user.o utils.o
TARGET = programa_principal
RESULTS = ../Resultados/*.txt

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ ; echo "[COMPILED] $@"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@ ; echo "[LINKED] $@"

run: $(TARGET)
	@rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)"
	./programa_principal "../Dataset_Fase1" "../exemplos_de_queries/tests_2/input.txt"

clean:
	@rm -f $(TARGET) $(OBJS) $(RESULTS) ; echo "[CLEANED]"
