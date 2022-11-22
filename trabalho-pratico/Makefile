CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
OBJS = $(patsubst %.c,%.o,$(wildcard src/*.c))            # Get all object files by replacing .c with .o
TARGET = programa-principal
RESULTS = Resultados/*.txt
OUTPUT = Resultados

INPUT = exemplos_de_queries/tests_2/input.txt
DATASET = Dataset_Fase1

$(TARGET): $(OBJS)                                        # Compiling the program
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ ; echo "[COMPILED] $@"
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi

%.o: %.c                                                  #Linking object files
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@ ; echo "[LINKED] $@"

run: $(TARGET)                                            # Run the program
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET) ]; then\
		echo "[ERROR] $(DATASET)/ not found!";\
	fi
	@if [ ! -e $(INPUT) ]; then\
		echo "[ERROR] $(INPUT) not found!";\
	fi
	./programa-principal "$(DATASET)" "$(INPUT)"

clean:                                                    # Clean the output files
	@rm -f $(TARGET) $(OBJS) $(RESULTS) ; echo "[CLEANED]"
