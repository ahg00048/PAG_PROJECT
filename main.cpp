#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include "Renderer/Renderer.h"
#include "GUI/GUI.h"

#include <GLFW/glfw3.h>

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback(int errno, const char* desc) {
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.

void window_refresh_callback(GLFWwindow *window) {
    PAG::Renderer::getRenderer().refrescar();

// - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
// intercambia el buffer back (que se ha estado dibujando) por el
// que se mostraba hasta ahora front. Debe ser la última orden de
// este callback
    glfwSwapBuffers(window);
    std::cout << "Refresh callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    PAG::Renderer::getRenderer().tamanoViewport(width, height);
    std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    PAG::GUI::getGUI().setMessage("Key callback called");
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if(action == GLFW_PRESS)
        std::cout << "Pulsado el boton: " << button << std::endl;
    else if(action == GLFW_RELEASE)
        std::cout << "Soltado el boton: " << button << std::endl;
}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    PAG::Renderer::getRenderer().ratonRueda(xoffset, yoffset);
}

int main() {
// - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    glfwSetErrorCallback((GLFWerrorfun) error_callback);
    if(glfwInit () != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
// - Definimos las características que queremos que tenga el contexto gráfico
// OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
// modo Core Profile.
    glfwWindowHint(GLFW_SAMPLES, 4); // - Activa antialiasing con 4 muestras.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // - Esta y las 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // OpenGL Core Profile 4.1.
// - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
// la creamos
    GLFWwindow *window;
// - Tamaño, título de la ventana, en ventana y no en pantalla completa,
// sin compartir recursos con otras ventanas.
    window = glfwCreateWindow (1024, 576, "PAG Introduction", nullptr, nullptr);
// - Comprobamos si la creación de la ventana ha tenido éxito.
    if(window == nullptr) {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }
// - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
// ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent(window);
// - Ahora inicializamos GLAD.
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow(window); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

// - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback (window, window_refresh_callback);
    glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);
    glfwSetKeyCallback (window, key_callback);
    glfwSetMouseButtonCallback (window, mouse_button_callback);
    glfwSetScrollCallback (window, scroll_callback);

// - Inicializamos imgui
    PAG::GUI::getGUI().init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

// - Establecemos un gris medio como color con el que se borrará el frame buffer.
// No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    PAG::Renderer::getRenderer().setClearColor(0.6, 0.6, 0.6, 1.0);
// - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
// No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    PAG::Renderer::getRenderer().init();

// - Ciclo de eventos de la aplicación. La condición de parada es que la
// ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
// botón de cerrar la ventana (la X).
    while(!glfwWindowShouldClose(window)){
        PAG::Renderer::getRenderer().refrescar();
        PAG::GUI::getGUI().newFrame();

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        PAG::GUI::getGUI().setWindowsPos(0.0f, 0.0f, static_cast<float>(width) * 0.75f, 0.0f, ImGuiCond_Appearing, ImGuiCond_Always);
        PAG::GUI::getGUI().createWindows();
    // - Borra los buffers (color y profundidad)
        PAG::Renderer::getRenderer().refrescar();

        // - se dibuja la interfaz con imgui
        PAG::GUI::getGUI().render();
    // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
    // intercambia el buffer back (en el que se ha estado dibujando) por el
    // que se mostraba hasta ahora (front).
        glfwSwapBuffers(window);
    // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
    // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
    // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents();
    }

    PAG::GUI::getGUI().freeResources();
    glfwDestroyWindow(window); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
}