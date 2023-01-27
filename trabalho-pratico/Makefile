CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O3 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
OBJS = $(patsubst %.c,%.o,$(wildcard principal/src/*.c))            # Get all object files by replacing .c with .o
OBJS_TESTES = $(patsubst %.c,%.o,$(wildcard testes/src/*.c))
TARGET = programa-principal
TARGET_TESTES = programa-testes
RESULTS = Resultados/*.txt
OUTPUT = Resultados

TESTS = queries/tests-regular-2
TESTS_ERRORS = queries/tests-regular-errors
TESTS_BIG = queries/tests-large
TESTS_BIG_ERRORS = queries/tests-large-errors

INPUT = queries/tests-regular-2/input.txt
DATASET = data/data-regular

INPUT_ERRORS = queries/tests-regular-errors/input.txt
DATASET_ERRORS = data/data-regular-errors

INPUT_BIG = queries/tests-large/input.txt
DATASET_BIG = data/data-large

INPUT_BIG_ERRORS = queries/tests-large-errors/input.txt
DATASET_BIG_ERRORS = data/data-large-errors

# -fsanitize=leak

all: $(TARGET) $(TARGET_TESTES)

programa-principal: $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ ; echo "[COMPILED] $@"
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	fi

programa-testes: $(OBJS_TESTES)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ ; echo "[COMPILED] $@"
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	fi

%.o: %.c                                                  #Linking object files
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@ ; echo "[LINKED] $@"

run: $(TARGET)
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

run-errors: $(TARGET)
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET_ERRORS) ]; then\
		echo "[ERROR] $(DATASET_ERRORS)/ not found!";\
	fi
	@if [ ! -e $(INPUT_ERRORS) ]; then\
		echo "[ERROR] $(INPUT_ERRORS) not found!";\
	fi
	./programa-principal "$(DATASET_ERRORS)" "$(INPUT_ERRORS)"

run-big: $(TARGET)
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET_BIG) ]; then\
		echo "[ERROR] $(DATASET_BIG)/ not found!";\
	fi
	@if [ ! -e $(INPUT_BIG) ]; then\
		echo "[ERROR] $(INPUT_BIG) not found!";\
	fi
	./programa-principal "$(DATASET_BIG)" "$(INPUT_BIG)"

run-big-errors: $(TARGET)
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET_BIG_ERRORS) ]; then\
		echo "[ERROR] $(DATASET_BIG_ERRORS)/ not found!";\
	fi
	@if [ ! -e $(INPUT_BIG_ERRORS) ]; then\
		echo "[ERROR] $(INPUT_BIG_ERRORS) not found!";\
	fi
	./programa-principal "$(DATASET_BIG_ERRORS)" "$(INPUT_BIG_ERRORS)"

run-testes: $(TARGET_TESTES)
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
	make run
	./programa-testes "$(DATASET)" "$(INPUT)" "$(TESTS)"

run-testes-errors: $(TARGET_TESTES)
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET_ERRORS) ]; then\
		echo "[ERROR] $(DATASET_ERRORS)/ not found!";\
	fi
	@if [ ! -e $(INPUT_ERRORS) ]; then\
		echo "[ERROR] $(INPUT_ERRORS) not found!";\
	fi
	make run-errors
	./programa-testes "$(DATASET_ERRORS)" "$(INPUT_ERRORS)" "$(TESTS_ERRORS)"

run-testes-big: $(TARGET_TESTES)
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET_BIG) ]; then\
		echo "[ERROR] $(DATASET_BIG)/ not found!";\
	fi
	@if [ ! -e $(INPUT_BIG) ]; then\
		echo "[ERROR] $(INPUT_BIG) not found!";\
	fi
	make run-big
	./programa-testes "$(DATASET_BIG)" "$(INPUT_BIG)" "$(TESTS_BIG)"

run-testes-big-errors: $(TARGET_TESTES)
	@if [ ! -e $(OUTPUT) ]; then\
		mkdir -p $(OUTPUT) ; echo "[CREATED] $(OUTPUT)/";\
	else\
		rm -f $(RESULTS) ; echo "[CLEANED] $(RESULTS)";\
	fi
	@if [ ! -e $(DATASET_BIG_ERRORS) ]; then\
		echo "[ERROR] $(DATASET_BIG_ERRORS)/ not found!";\
	fi
	@if [ ! -e $(INPUT_BIG_ERRORS) ]; then\
		echo "[ERROR] $(INPUT_BIG_ERRORS) not found!";\
	fi
	make run-big-errors
	./programa-testes "$(DATASET_BIG_ERRORS)" "$(INPUT_BIG_ERRORS)" "$(TESTS_BIG_ERRORS)"	

clean: # Clean the output files
	@rm -f $(TARGET) $(TARGET_TESTES) $(OBJS) $(OBJS_TESTES) $(RESULTS) ; echo "[CLEANED]"
