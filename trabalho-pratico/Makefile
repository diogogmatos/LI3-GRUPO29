CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
OBJS = src/catalog.o src/driver.o src/io.o src/main.o src/parsing.o src/queries.o src/ride.o src/stats.o src/user.o src/utils.o
TARGET = programa_principal
RESULTS = Resultados/*.txt

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ ; echo "[COMPILED] $@"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@ ; echo "[LINKED] $@"

run: $(TARGET)
	@rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)"
	./programa_principal "Dataset_Fase1" "exemplos_de_queries/tests_2/input.txt"

clean:
	@rm -f $(TARGET) $(OBJS) $(RESULTS) ; echo "[CLEANED]"
