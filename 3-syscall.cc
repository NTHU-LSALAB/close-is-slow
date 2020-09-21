#include <chrono>
#include <cstdio>
#include <cassert>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	auto t0 = std::chrono::steady_clock::now();
	auto t = [&] (const char* msg) {
		auto t1 = std::chrono::steady_clock::now();
		fprintf(stderr, "%s %f\n", msg, std::chrono::duration<double>(t1-t0).count());
		t0 = t1;
	};
	int n = 0x7ffff000;
	char* data = new char[n];
	t("init");
	int fd = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	assert(fd != -1);
	t("open");
	assert(n == write(fd, data, n));
	t("write");
	assert(close(fd) == 0);
	t("close");
}
