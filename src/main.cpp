#include "engine.h"

int main() {
	engine* e = new engine();
	while (e->run) e->work();
	delete e;
	return 0;
}
