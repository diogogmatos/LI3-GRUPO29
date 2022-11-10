CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
OBJS = driver.o main.o parsing.o ride.o user.o io.o queries.o catalog.o
TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./main

clean:
	@rm -f $(TARGET) $(OBJS)
