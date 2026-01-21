# Makefile for Vowel Counter

CC = gcc
CFLAGS = -O0

.PHONY: all clean test original optimized parallel

all: original optimized parallel

original: main.c vowel_counting_original.c
	$(CC) $(CFLAGS) main.c vowel_counting_original.c -o original.out -lm

optimized: main.c vowel_counting.c
	$(CC) $(CFLAGS) main.c vowel_counting.c -o optimized.out -lm

# Parallel version using fork with the optimized vowel counting
parallel: main.c vowel_counting_optimized.c
	$(CC) $(CFLAGS) main.c vowel_counting_optimized.c -o parallel.out -lm

# Run tests
test: all test_medium
	./run_stats.sh input_medium.txt

clean:
	rm -f *.out input_*.txt temp_*.txt
