TARGETS = 1-mpi 2-fstream 3-syscall

1-mpi: CXX = mpicxx

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -f $(TARGETS)
