#include <cstdint>
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "OpenGlCore/VertexArray.h"
#include "OpenGlCore/VertexBuffer.h"

static const char *vert_shader =
    "#version 450 core\n"
    "layout (location = 0) in vec3 a_Position;\n"
    "layout (location = 1) in vec4 a_Color;\n"
    "out vec4 o_Color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(a_Position.xyz, 1.0);\n"
    "    o_Color = a_Color;\n"
    "}\n";

static const char *frag_shader = "#version 450 core\n"
                                 "out vec4 d_Color;\n"
                                 "in vec4 o_Color;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    d_Color = o_Color;\n"
                                 "}\n";

static void error_callback(int error, const char *description) {
  std::cout << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void) {
  GLFWwindow *window;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(1);

  // Generate Vertex buffer
  float vertices[] = {0.5f,  0.5f,  0.0f, 0.8f, 0.2f, 0.3f, 1.0f,
                      0.5f,  -0.5f, 0.0f, 0.3f, 0.8f, 0.2f, 1.0f,
                      -0.5f, 0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                      -0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f};
  uint32_t indices[] = {0, 1, 2, 2, 3, 1};

  OpenGLCore::VertexArray vertexArray;
  OpenGLCore::VertexBuffer vertexBuffer(vertices, sizeof(vertices));
  vertexBuffer.SetLayout({{OpenGLCore::ShaderDataType::Float3, "a_Position"},
                          {OpenGLCore::ShaderDataType::Float4, "a_Color"}});
  vertexArray.AddVertexBuffer(vertexBuffer);
  OpenGLCore::IndexBuffer indexBuffer(indices,
                                      sizeof(indices) / sizeof(uint32_t));
  vertexArray.SetIndexBuffer(indexBuffer);

  // Generate Shader
  GLuint vertex_shader, fragment_shader, program;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vert_shader, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &frag_shader, NULL);
  glCompileShader(fragment_shader);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  glUseProgram(program);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glUseProgram(program);
    vertexArray.Bind();
    glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer().GetCount(),
                   GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
