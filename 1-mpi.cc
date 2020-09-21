#include <mpi.h>

#include <algorithm>
#include <chrono>
#include <cstdio>

int main(int argc, char** argv) {
	auto t0 = std::chrono::steady_clock::now();
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	auto t = [&] (const char* msg) {
		auto t1 = std::chrono::steady_clock::now();
		fprintf(stderr, "[%2d] %s %f\n", rank, msg, std::chrono::duration<double>(t1-t0).count());
		t0 = t1;
	};
	int n = 536870911; // around 2GB of ints
	int offset = (n / size) * rank + std::min(n % size, rank);
	int count = n / size + ((n % size) > rank);
	int* data = new int[count];
	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, "out", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	t("init+open");
	MPI_File_write_at(fh, offset * sizeof(int), data, count, MPI_INT, MPI_STATUS_IGNORE);
	t("MPI_File_write_at");
	MPI_File_close(&fh);
	t("MPI_File_close");
	MPI_Finalize();
	t("MPI_Finalize");
}
