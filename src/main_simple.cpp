 #include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

     // Set your background color (RGBA) — e.g., cornflower blue
    float red = 0.39f;
    float green = 0.58f;
    float blue = 0.93f;
    float alpha = 1.0f;

    while (!glfwWindowShouldClose(window)) 
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
