#include <stdio.h>
#include <glad.h>
#include <GLFW/glfw3.h>

void error_callback(int, const char*);

int main() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    printf("could not initialize glfw\n");
    return -1;
  }

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Tictactoe", NULL, NULL);
  if (!window) {
    printf("could not create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));

  glClearColor(0.5, 0.5, 0.5, 1.0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void error_callback(int error, const char* description) {
  printf("GLFW Error (%x): %s\n", error, description);
}
