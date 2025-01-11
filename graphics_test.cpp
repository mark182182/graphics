#include "graphics_test.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <cassert>


using namespace std;

struct vec2 {
  int x, y;
};

struct vec3 {
  int x, y, z;
};

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
};

int main() {
  vec2 *v2 = new vec2{1, 2};
  vec3 *v3 = new vec3{3, 4, 5};

  assert(1 == 1);

  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  // after initializing glfw

  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(1024, 768, "Graphics test", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  while (!glfwWindowShouldClose(window)) {
    // render here

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  _CrtDumpMemoryLeaks();
  return 0;
}