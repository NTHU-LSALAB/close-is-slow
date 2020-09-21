#include <chrono>
#include <cstdio>
#include <fstream>

int main() {
	auto t0 = std::chrono::steady_clock::now();
	auto t = [&] (const char* msg) {
		auto t1 = std::chrono::steady_clock::now();
		fprintf(stderr, "%s %f\n", msg, std::chrono::duration<double>(t1-t0).count());
		t0 = t1;
	};
	int n = 536870911;
	int* data = new int[n];
	std::ofstream outf("out");
	t("init");
	outf.write((char*)data, sizeof(int) * n);
	t("write");
	outf.close();
	t("close");
}
