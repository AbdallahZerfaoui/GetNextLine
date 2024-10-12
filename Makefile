# Define variables
CC = gcc
VALGRIND = valgrind --leak-check=full
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 42
EXE = get_next_line.exe
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Compile with a specific BUFFER_SIZE

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(EXE)

$(EXE): $(OBJS)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) $(SRCS) -o $(EXE) 

basic: $(OBJS)
	@$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

basic_test: basic clean
	@./$(EXE) 

wflag_test: $(EXE) clean
	@./$(EXE) 

# Test with valgrind to check for memory leaks (if Valgrind is installed)
valgrind:
	@$(CC) $(CFLAGS) -g -o $(EXE) $(SRCS)
	@$(VALGRIND) ./$(EXE)

# Clean up object files
clean:
	$(RM) $(OBJS)

# Clean up object files and executable
fclean: clean
	$(RM) $(EXE)

# Recompile everything
re: fclean all

.PHONY: all basic clean fclean re valgrind basic basic_test wflag_test
