#include <Application.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
	void *array[50];
	size_t size;
	// get void*'s for all entries on the stack
	size = backtrace(array, 50);
	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char *argv[]) {
//	signal(SIGSEGV, handler);
//	signal(SIGABRT, handler);
	return gumyns::sh::Application::create()->run(argc, argv);
}