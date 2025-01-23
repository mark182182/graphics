#include "renderer.hpp"
#include <crtdbg.h>

int main() {
  Renderer::render();
  _CrtDumpMemoryLeaks();
  return 0;
}
