#include <stdio.h>
#include <glad.h>
#include <GLFW/glfw3.h>

void error_callback(int, const char*);
int createWindow(GLFWwindow** window, const char* title);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"

  "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\n";

const char* fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"

  "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n";

const char* fragmentShaderSource2 =
  "#version 330 core\n"
  "out vec4 FragColor;\n"

  "void main() {\n"
    "FragColor = vec4(0.3f, 0.3f, 0.9f, 1.0f);\n"
  "}\n";

int main() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    printf("could not initialize glfw\n");
    return -1;
  }

  GLFWwindow* window;
  if (!createWindow(&window, "Tic Tac Toe")) {
    printf("could not create window\n");
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int fragmentShader2;
  fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
  glCompileShader(fragmentShader2);

  unsigned int shaderProgram1;
  shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader);
  glLinkProgram(shaderProgram1);
  glDeleteShader(fragmentShader);

  unsigned int shaderProgram2;
  shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);
  glDeleteShader(fragmentShader2);

  glDeleteShader(vertexShader);

  // first triangle
  float triangle1[] = {
    -0.5f,  0.1f, 0.0f,
     0.5f,  0.1f, 0.0f,
     0.0f,  1.0f, 0.0f,
  };

  unsigned int triangle1VAO;
  glGenVertexArrays(1, &triangle1VAO);
  glBindVertexArray(triangle1VAO);
  unsigned int triangle1VBO;
  glGenBuffers(1, &triangle1VBO);
  glBindBuffer(GL_ARRAY_BUFFER, triangle1VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  float triangle2[] = {
    -0.5f,  0.0f, 0.0f,
     0.5f,  0.0f, 0.0f,
     0.0f, -0.6f, 0.0f,
  };

  unsigned int triangle2VAO;
  glGenVertexArrays(1, &triangle2VAO);
  glBindVertexArray(triangle2VAO);
  unsigned int triangle2VBO;
  glGenBuffers(1, &triangle2VBO);
  glBindBuffer(GL_ARRAY_BUFFER, triangle2VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  glClearColor(0.5, 0.5, 0.5, 1.0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram1);
    glBindVertexArray(triangle1VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(triangle2VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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

int createWindow(GLFWwindow** window, const char* title) {
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  *window = glfwCreateWindow(640, 480, title, NULL, NULL);
  if (!*window) {
    return 0;
  }  
  glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
  return 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
