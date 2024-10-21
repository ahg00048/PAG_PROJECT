#include <iostream>

// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include "Renderer/Renderer.h"
#include "GUI/GUI.h"
#include "Shader/Shader.h"

#include <chrono>
#include <GLFW/glfw3.h>

namespace chr = std::chrono;

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback(int errno, const char* desc) {
    std::string aux(desc);
    PAG::GUI::getGUI().addMessage("Error de GLFW número " + std::to_string(errno) + ": " + aux);
}

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.

void window_refresh_callback(GLFWwindow *window) {
    PAG::GUI::getGUI().newFrame();
    PAG::GUI::getGUI().createWindows();

    PAG::Renderer::getRenderer().setClearColor(PAG::GUI::getGUI().getColor().x, PAG::GUI::getGUI().getColor().y,
                                               PAG::GUI::getGUI().getColor().z, PAG::GUI::getGUI().getColor().w);

    PAG::Renderer::getRenderer().refrescar();
    PAG::GUI::getGUI().render();
// - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
// intercambia el buffer back (que se ha estado dibujando) por el
// que se mostraba hasta ahora front. Debe ser la última orden de
// este callback
    glfwSwapBuffers(window);
//    PAG::GUI::getGUI().addMessage("Refresh callback call");
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
//   del área de dibujo OpenGL.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    int _width, _height;
    glfwGetWindowSize(window, &_width, &_height);

    PAG::Renderer::getRenderer().tamanoViewport(width, height);

    PAG::GUI::getGUI().setColorPickerWindowPos(static_cast<float>(width) * 0.75f, 0.0f);
    PAG::GUI::getGUI().setMessagesWindowPos(0.0f, 0.0f);
//   PAG::GUI::getGUI().addMessage("Resize callback call");;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
//   dirigida al área de dibujo OpenGL.
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
//    PAG::GUI::getGUI().addMessage("Key callback called");
}

// - Esta función callback será llamada cada vez que se pulse algún botón
//   del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    ImGuiIO &io = ImGui::GetIO();

    if (!io.WantCaptureMouse) {
        PAG::Renderer::getRenderer().setCameraMove(PAG::GUI::getGUI().getCameraSelectedMove());
        if (action == GLFW_PRESS) {
            PAG::Renderer::getRenderer().setCameraMovementAllowed(true);
            PAG::GUI::getGUI().addMessage("Pulsado el boton: " + std::to_string(button));
        } else if (action == GLFW_RELEASE) {
            PAG::Renderer::getRenderer().setCameraMovementAllowed(false);
            PAG::GUI::getGUI().addMessage("Soltando el boton: " + std::to_string(button));
        }
    } else
        PAG::Renderer::getRenderer().setCameraMovementAllowed(false);
}
// - Esta función callback será llamada cada vez que se mueva la rueda
//   del ratón sobre el área de dibujo OpenGL.
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    PAG::Renderer::getRenderer().ratonRueda(xoffset, yoffset);
    //le comunicamos el cambio de color de la escena a la interfaz
    glm::vec4 color = PAG::Renderer::getRenderer().getClearColor();
    PAG::GUI::getGUI().setColor(color.r, color.g, color.b, color.a);
//    PAG::GUI::getGUI().addMessage("Movida la rueda del raton " + std::to_string(xoffset) + " Unidades en horizontal y " + std::to_string(yoffset) + " unidades en vertical");
}

void cursor_pos_callback(GLFWwindow *window, double xPos, double yPos) {
    static auto start = chr::high_resolution_clock::now();

    ImGuiIO& io = ImGui::GetIO();
    if(!io.WantCaptureMouse)
        PAG::Renderer::getRenderer().cursorPos(xPos, yPos, chr::duration<float>(chr::high_resolution_clock::now() - start).count());
    std::cout << "Time: " << chr::duration<float>(chr::high_resolution_clock::now() - start).count() << std::endl;

    start = chr::high_resolution_clock::now();
}

int main() {
// - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    glfwSetErrorCallback((GLFWerrorfun) error_callback);
    if(glfwInit () != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
// - Definimos las características que queremos que tenga el contexto gráfico
//   OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
//   modo Core Profile.
    glfwWindowHint(GLFW_SAMPLES, 4); // - Activa antialiasing con 4 muestras.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // - Esta y las 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // OpenGL Core Profile 4.1.
// - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
//   la creamos
    GLFWwindow *window;
// - Tamaño, título de la ventana, en ventana y no en pantalla completa,
//   sin compartir recursos con otras ventanas.
    window = glfwCreateWindow (1024, 576, "PAG Introduction", nullptr, nullptr);
// - Comprobamos si la creación de la ventana ha tenido éxito.
    if(window == nullptr) {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }
// - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
//   ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
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
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

// - Inicializamos imgui
    PAG::GUI::getGUI().init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

// - Establecemos un gris medio como color con el que se borrará el frame buffer.
//   No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    PAG::Renderer::getRenderer().setClearColor(0.6, 0.6, 0.6, 1.0);
    PAG::GUI::getGUI().setColor(0.6, 0.6, 0.6, 1.0);
// - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
//   No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    PAG::Renderer::getRenderer().init();
    PAG::Renderer::getRenderer().creaModelo();
    PAG::Renderer::getRenderer().getShaderProgram().addShader(std::move(PAG::Shader(PAG::vertexShader)));
    PAG::Renderer::getRenderer().getShaderProgram().addShader(std::move(PAG::Shader(PAG::fragmentShader)));
// - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
//   3D construido.
    PAG::GUI::getGUI().addMessage(PAG::Renderer::getRenderer().getInforme());
    PAG::GUI::getGUI().addMessage("");
// - Ciclo de eventos de la aplicación. La condición de parada es que la
//   ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
//   botón de cerrar la ventana (la X).

    int width, height;
    glfwGetWindowSize(window, &width, &height);
// - Definimos las posiciones de las ventanas
    PAG::GUI::getGUI().setColorPickerWindowPos(static_cast<float>(width) * 0.75f, 0.0f);
    PAG::GUI::getGUI().setMessagesWindowPos(0.0f, 0.0f);
    PAG::GUI::getGUI().setShaderLoaderWindowPos(static_cast<float>(width) * 0.25f, 0.0f);
    PAG::GUI::getGUI().setCameraWindowPos(static_cast<float>(width) * 0.50f, 0.0f);

    while(!glfwWindowShouldClose(window)){
    // - nuevo frame para renderizar la interfaz
        PAG::GUI::getGUI().newFrame();
        PAG::GUI::getGUI().createWindows();

        PAG::Renderer::getRenderer().setClearColor(PAG::GUI::getGUI().getColor().x, PAG::GUI::getGUI().getColor().y,PAG::GUI::getGUI().getColor().z, PAG::GUI::getGUI().getColor().w);
        PAG::Renderer::getRenderer().setCameraPerspProjection(PAG::GUI::getGUI().getCameraPerspProjection());

        if(PAG::GUI::getGUI().getShaderButtonState()) {
            // - Cargamos el shader
            try {
                std::vector<PAG::Shader*> shaders = PAG::Renderer::getRenderer().getShaderProgram().getShaders();
                for(auto shader : shaders)
                    shader->setContentFromFile("../shaders/" + PAG::GUI::getGUI().getShaderName() + "-" + ((shader->getType() == PAG::ShaderType::fragmentShader) ? "fs.glsl" : "vs.glsl"));
                PAG::Renderer::getRenderer().getShaderProgram().createShaderProgram();
            } catch (std::exception &e) {
                PAG::GUI::getGUI().addMessage(e.what());
                PAG::GUI::getGUI().addMessage("\n");
                PAG::Renderer::getRenderer().getShaderProgram().deleteShaderProgram();
            }
            PAG::GUI::getGUI().setShaderButtonState(false);
        }

    // - Borra los buffers (color y profundidad) y se dibuja
    // - se dibuja la escena con opengl
        PAG::Renderer::getRenderer().refrescar();
    // - se dibuja la interfaz con imgui
        PAG::GUI::getGUI().render();
    // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden intercambia el buffer back (en el que se ha estado dibujando) por el que se mostraba hasta ahora (front).
        glfwSwapBuffers(window);
    // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de teclas o de ratón, etc. Siempre al final de cada iteración del ciclo de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents();
    }

    PAG::GUI::getGUI().freeResources();
    glfwDestroyWindow(window); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
}