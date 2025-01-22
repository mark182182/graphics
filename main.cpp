#include "renderer.hpp"
#include <crtdbg.h>

int main() {
  Generator::render();
  _CrtDumpMemoryLeaks();
  return 0;
}
