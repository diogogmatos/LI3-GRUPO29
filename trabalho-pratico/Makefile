CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O3 -march=native -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
OBJS = $(patsubst %.c,%.o,$(wildcard src/*.c))            # Get all object files by replacing .c with .o
TARGET = programa-principal
RESULTS = Resultados/*.txt
OUTPUT = Resultados

INPUT = exemplos_de_queries/tests_2/input.txt
DATASET = Dataset_Fase1

INPUT_BIG = exemplos_de_queries/large-outputs/largedataset.txt
DATASET_BIG = data-large

# -fsanitize=leak

$(TARGET): $(OBJS)                                        # Compiling the program
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ ; echo "[COMPILED] $@"
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
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

run_big: $(TARGET)
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
	./programa-principal "$(DATASET_BIG)" "$(INPUT_BIG)"

clean:                                                    # Clean the output files
	@rm -f $(TARGET) $(OBJS) $(RESULTS) ; echo "[CLEANED]"
