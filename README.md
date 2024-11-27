## Práctica 1 ##

En nuestra aplicación debería haber una clase PAG::Renderer que se encargue de
encapsular todo lo relativo al dibujado de la escena 3D en el contexto gráfico OpenGL.
Esa clase debería tener un método llamado refrescarVentana() que debería llamarse
cada vez que la ventana deba redibujarse. El problema es que no podemos registrar
como callback para el evento window_refresh al método
PAG::Renderer::refrescarVentana(), ya que no podemos registrar como
callbacks métodos de clases, sino funciones sencillas de C.
¿Cómo solucionar este problema? ¿Cómo podemos llamar desde nuestras funciones
callback en C a los métodos de la clase PAG::Renderer que responden a los distintos
eventos? Todo ello habría de hacerse de la forma más encapsulada (es decir menos
acoplada) posible.

Pistas para plantear la solución:
  
-  ¿Cómo debería declararse el objeto de la clase PAG::Renderer que actúa como renderer de la aplicación?
-  ¿Qué módulo de la aplicación debería inicializarlo?
---
Para registrar la función PAG::Renderer::refrescarVentana() como callback deberiamos implementarla como un metodo de la propia clase a través del uso de la keyword "static", 
lo que a su vez implicaría, también por conveniencia, que la clase PAG::Renderer sería diseñada como un singleton, ya que solo necesitariamos una instancia de esta para nuestra aplicación.

La representación UML de la clase Renderer sería la siguiente:

<img src="./img/UML.png"> 

---
## Práctica 2 ##

Durante esta sesión de prácticas hemos incorporado dos nuevas clases, Renderer que se encargara
de dibujar todo los modelos en escena a traves de Opengl, y GUI que utilizara  la biblioteca ImGui, 
con la cual hemos logrado la implementación de una interfaz simple que nos permite capturar los 
mensajes que previamente se mostraba por consola, en una pequeña ventana, y elegir el color del 
fondo de nuestra aplicación.

Para ello  nuestra propia clase GUI, que encapsula todas las funcionalidades que necesitamos de 
dicha biblioteca, sera diseñada con el patrón de diseño singleton al igual que la clase Renderer,
y se encontrará en el espacio de nombres PAG. Esta clase como hemos indicado en el parrafo anterior
implementará dos ventanas a través de la función ImGui::Begin(), la primera funcionará como una consola, ya que mostrara
los mensajes de nuestra aplicación a través de la función ImGui::Text(), que permite mostrar texto en 
la ventana o contexto determinado. En la segunda ventana utilizaremos otro recurso diractemente implementado 
en la biblioteca, el cual es un selector de color, accesible a traves de la función ImGui::ColorPicker4(), el cual mostrara
los valores RGB, HSV y hexadecimal del color selecionado gracias a las etiquetas utilizadas en la función, que también
permiten no mostrar el valor de transparencia del color y seleccionar el formato con el que se muestra el selector de color.

---

Para cumplir ese proposito, la clase tiene todos los atributos y metodos necesarios, entre ellos:
#### atributos ####

- `std::deque<std::string> _messages;` &emsp; &emsp; todos los mensajes obtenidos para mostrar.
- `std::array<float, 4> _windowsPos;` &emsp; &emsp; &nbsp; las posiciones de las dos ventanas.
- `std::array<float, 4> _windowsSize;` &emsp; &emsp; el tamaño de las dos ventanas.
- `ImVec4 _colo;r` &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp;&emsp; el color seleccionado con el selector de color.

#### métodos ####
- `void init();` <br /> Inicializa todos los recursos necesarios para el funcionamiento de dear ImGui.
- `void newFrame();` <br /> Indica que se comienza un nuevo frame a dear ImGui para renderizar la interfaz.
- `void render();` <br /> Dibuja toda la interfaz previamente inicializada.
- `void addMessage(const std::string& newMessage);` <br /> Añade un nuevo mensaje a mostrar a la pila de mensajes.
- `void freeResources();` <br /> Libera los recursos de dear ImGui antés de que la aplicación finalice.
- `void setWindowsPos(float&& x1, float&& y1, float&& x2, float&& y2);` <br /> Define la posicion de las ventanas creadas.
- `void setWindowsSize(float&& w1, float&& h1, float&& w2, float&& h2);` <br /> Define el tamaño de las ventanas creadas.
- `void createWindows();` <br /> Crea las ventanas de la interfaz, siendo la primera de estas la salida de los mensajes de nuestra aplicación, y la segunda
el selector de color del fondo de la aplicación.

---

Ya que hemos cubrido la clase que cumple el papel de interfaz en nuestra aplicación, comenzaremos explicando brevemente la clase que
se encarga de dibujar los modelados a través de Opengl, la clase Renderer. La clase seguira el mísmo patrón de diseño que la clase anterior
y solo incluira la biblioteca GLAD.h para así mantener una estructura modular en el proyecto. 

---

Entre lo más destacado, la clase se ocupa de inicializar Opengl y del renderizado del color de fondo, 
que para ello requiere de los siguientes métodos y atributos:

#### atributos ####

- `glm::vec4 _clearColor;` &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; El color con el que pintar el fondo de la aplicación.

#### métodos ####
- `void init();` <br /> Inicializa todos los recursos necesarios para el funcionamiento de Opengl.
- `void refrescar();` <br /> Dibuja la escena a través de Opengl, en este caso el color de fondo.
- `void ratonRueda(double xoffset, double yoffset);` <br /> El callback que baja la tonalidad del color de fondo a traves de la rueda del ratón.
- `void tamanoViewport(int width, int height);` <br /> El callback que permite cambiar el tamaño del viewport cuando cambia el tamaño de la ventana de la aplicación.
- `std::string getInforme();` <br /> Interroga a Opengl para obtener un informe sobre la GPU del dispositivo.

---

Cabe destacar que para que las utilidades de ambas clase funcionen de forma correcta, es necesario que estas comuniquen entre si el color con el que 
se esta dibujando.

---

## Práctica 3 ##

En esta sesión de prácticas hemos conseguido dibujar un triángulo con un color distinto en cada vertice a través de las funciones otorgadas
por Opengl, para ello también hemos tenido que crear archivos glsl para la compilción de los shaders que son utilizados en el dibujado del modelado.

---

Las funciones que hemos creado en nuestra clase Renderer para desempeñar dichas acciones son las siguientes:

`void obtenerShaders(const std::string& path);` 

Función que lee los archivos pasados por parametro para obtener los shaders con los que se renderizará el modelo.

`void creaShaderProgram();`

Función que crea los dos shaders, el vertex shader y el fragment shader, compilandolos y enlazandolos en un programa para su posterior uso,
comprobando que no se ha producido ningún error en el proceso, y en el caso de que se produjese, informarlo a través de la ventana de mensajes.

`void creaTriangulo();`

Hace uso de los VAO (Vertex Array Object), VBO (Vertex Buffer Object), IBO (Index Buffer Object) de Opengl para la creación del triángulo.
Esta formado por un VBO entrelazado donde se encuentran las coordenadas y color de los vertices a dibujar, y un IBO donde se encuentra la topología 
del modelo, ambos buffers perteneciendo al mismo VAO.

---

### Ejercicio 5 ###

Responde a esta pregunta. Si redimensionas la ventana de la aplicación, verás que el triángulo
no permanece igual, sino que se deforma al mismo tiempo que la ventana. ¿A qué crees que se
debe este comportamiento?

- El efecto se debe a que cuando redimensionamos la ventana, estamos redimensionando exclusivamente el viewport de la escena, no
el tamaño de la vista de la cámara, para arreglar esto, tendriamos que manipular también la vista de la cámara de manera proporcional
a la de la ventana y viewport.

---

## Práctica 4 ##

En esta sesión de practicas hemos desacoplado la funcionalidad de shader de la clase Renderer, haciendo así nuestra
propia clase Shader, que por ahora se encargará de gestionar programas de shader muy simplificados, compuestos unicamente
por vertex shaders y fragment shaders.

A lo largo de que se desarrollen las practicas futuras, la clase Shader seguirá siendo cambiada para implementar las funciones más
complejas y, posiblemente, se implementará otra clase ShaderProgram que es la que se encargará de enlazar los shader, haciendo
la clase Shader más especializada en la gestión de los contenidos de los shaders como tal.

---

La clase Shader esta formada por los siguientes métodos y atributos:

#### atributos ####

- `GLuint _idVS;` &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; Identificador del vertexShader.
- `GLuint _idFS;` &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; Identificador del fragmentShader.
- `GLuint _idPS;` &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; Identificador del programa de shaders.
- `std::string _vsContent;`&emsp;&emsp;&emsp;Contenido del vertexShader.
- `std::string _fsContent;`&emsp;&emsp;&emsp;Contenido del fragmentShader.
- `bool _shaderFailure;`  &emsp;&emsp;&emsp;&emsp; Indica si ha habido algun error en la creción del programa de shaders.

#### métodos ####
- `void cargarShaders(const std::string& path);` <br /> Obtiene el codigo de los shaders dados en la variable path.
- `void compilarVertexShader();` <br /> Compila el vertexShader.
- `void compilarFragmentShader();` <br /> Compila el fragmentShader.
- `void crearShaderProgram();` <br /> Crea y enlaza el shaderProgram con los shaders.
- `GLuint getProgramID();` <br /> Devuelve el id del programa de shaders.
- `bool fail();` <br /> Indica si se ha producido algún error.

---

Con lo dicho anteriormente, se mostrará un esquema uml de como que la estructura de las clases creadas tras el desacoplamiento de
la clase Shader.

<img src="./img/UML_2.png">

---

## Práctica 5 ##

En esta sesión de prácticas hemos implementado una cámara con la capacidad de ser controlada a través de una interfaz creada
por nuestra clase GUI. También, a lo largo de esta sesión he creado una mejor implementacion de los shaders, formando dos clases:
ShaderProgram y Shader, para incrementar la flexibilidad de dicha implementación en nuestra aplicación.

Nuestra clase Camera tiene los atributos necesarios para el cálculo de la matríz de visión y las dos matrices de proyección, la matríz proyección
ortográfica y la matríz proyección perspectiva:

#### atributos ####

- `float _zNear;` <br /> Plano cercano de vision (si un modelo o parte de este se encuentra mas cerca de la camara que el este plano, el modelo a la parte no será renderizado).
- `float _zFar;` <br /> Plano lejano de vision (si un modelo o parte de este se encuentra mas lejos de la camara que el este plano, el modelo a la parte no será renderizado).
- `float _angle;` <br /> Ángulo de visión de la cámara (solo pertenece a la proyección perspectiva).
- `float _scope;` <br /> Aspecto de la visión de la cámara (proporción entre el ancho y largo del plano de visión de la cámara, solo pertenece a la proyección perspectiva).
- `float _left;` <br /> Plano izquierdo del prisma rectangular de visión de la cámara (solo pertenece a la proyección ortográfica).
- `float _right;` <br /> Plano derecho del prisma rectangular de visión de la cámara (solo pertenece a la proyección ortográfica).
- `float _top;` <br /> Plano superior del prisma rectangular de visión de la cámara (solo pertenece a la proyección ortográfica).
- `float _botton;` <br /> Plano inferior del prisma rectangular de visión de la cámara (solo pertenece a la proyección ortográfica).
- `glm::vec3 _position;` <br /> Posición de la cámara.
- `glm::vec3 _upVec;` <br /> Vector que indica la orientación de la cámara.
- `glm::vec3 _target;` <br /> Posición a la que apunta la cámara.

Entre sus métodos más importantes encontramos:

#### métodos ####

- `const glm::mat4 getOrthographicProjection() const;` <br /> Devuelve la matríz de proyección ortográfica.
- `const glm::mat4 getPerspectiveProjection() const;` <br /> Devuelve la matríz de proyección perspectiva.
- `const glm::mat4 getVision() const;` <br /> Devuelve la matríz de visión.
- `void tilt(float angle);` <br /> Gira la cámara según su vector derecha (dado por: _upVec x (_position - _target)).
- `void pan(float angle);` <br /> Gira la cámara según su vector arriba.
- `void dolly(float xMovement, float zMovement);` <br /> Mueve la cámara en el plano XZ del sistema de coordenadas de la escena.
- `void orbit(float xAngle, float yAngle);` <br /> Mueve la cámara orbitando el objetivo según su vector arriba y derecha.
- `void crane(float yMovement);` <br /> Mueve la cámara en el eje Y del sistema de coordenadas de la escena.
- `void zoom(float angle);` <br /> Incrementa o decrementa el zoom de la cámara.

---

Para la correcta implementación de la interfaz que permita seleccionar el movimiento de la cámara, ha sido necesario crear un enum indicando
el tipo de movimiento que se quiere que la cámara haga. Comunicando dicho movimiento seleccionado entre la clase Renderer y la clase GUI.

Con ese propósito también hemos tenido que implementar una nueva ventana en la clase GUI, con la que puedes indicar el movimiento y la proyección
que se deseé utilizar en la cámara.

---

### Controles de la cámara ###

Para utilizar la cámara en su totalidad lo primero es cargar los shaders con el nombre "pag05", los cuales son los archivos shader que calculan la posición
teniendo en cuenta las matrices de proyección y vista de la cámara.

#### Movimientos ####

Para utilizar los movimientos tienen que ser seleccionados en la ventada "camara" de la interfaz y mantener presionado el click izquierdo del ratón o utilizar los controles que otorga
la propia interfaz. 

- Tilt:
  - Mantener presionado el click izquierdo del ratón y mover arriba o abajo para girar la cámara en esas direcciones respectivamente.
  - Pulsar "UP" o "DOWN" para girar de la mísma mánera.
- Pan: 
  - Mantener presionado el click izquierdo del ratón y mover derecha o izquierda para girar la cámara en esas direcciones respectivamente.
  - Pulsar "LEFT" o "RIGHT" para girar de la mísma mánera.
- Dolly: 
  - Mantener presionado el click izquierdo del ratón y mover arriba, abajo, derecha o izquierda para mover la cámara hacia adelante, atras, derecha o izquierda respectivamente.
  - Pulsar "FORWARD", "BACKWARD", "RIGHT" o "LEFT" para mover de la mísma mánera.
- Crane: 
  - Mantener presionado el click izquierdo del ratón y mover arriba o abajo para mover la cámara hacía arriba o abajo.
  - Pulsar "UP" o "DOWN" para mover de la mísma mánera.
- Orbit: 
  - Mantener presionado el click izquierdo del ratón y mover arriba o abajo para cambiar la latitud de la cámara al orbitar el objetivo al que está apuntando, y derecha o izquierda para la longitud.
  - Pulsar "UP", "DOWN", "LEFT" o "RIGHT" para girar de la mísma mánera respecto al objetivo.
- Zoom: 
  - Mantener presionado el click izquierdo del ratón y mover derecha o izquierda para incrementar o decrementar el zoom de la cámara.
  - Utilizar la barra para manipular el ángulo de visión de la cámara.

---

El siguiente diagrama UML muestra la estructura de las clases creadas hasta ahora:

<img src="img/UML_3.png">

--- 

## Práctica 6 ##

En esta sesión de prácticas hemos implementado una clase modelo para desacoplarla de la clase Renderer, permitiendo al usuario de nuestra
aplicación importar modelos a través de ficheros de extension .obj, dando la posibilidad de transformalos con los controles que otorga la interfáz.

Nuestra clase modelo presenta los siguientes métodos y atributos para su correcto funcionamiento:

#### atributos ####

- `GLuint _idVAO;` Id del vertex array object creado con opengl.
- `GLuint _idIBO;` Id del index buffer object creado con opengl.
- `GLuint _idVBO;` Id del vertex buffer object creado con opengl.
- `std::vector<vertex> _vertexAtributtes;` Los atributos de vertices del modelo.
- `std::vector<unsigned int> _indexes;` Los indices de los vertices para formar el modelo.
- `glm::mat4 _transformMatrix;` Componente de transformacion del modelo.

Entre sus métodos más importantes encontramos:

#### métodos ####

- `void setVertexAttributtes(const std::vector<vertex>& vertexAtributtes);` Setter de los atributos de los vertices del modelo.
- `void setIndexes(const std::vector<unsigned int>& indexes);` Setter del vector de indices del modelo.
- `const glm::mat4& getModelMatrix() const;` Getter de la matríz de transformación del modelo.
- `void createModel();` Crea el IBO, VBO y VAO si se le han asignado de forma correcta los indices y vertices.
- `void destroyModel();` Destruye el modelo, liberando los ids de los IBO, VBO y VAO.
- `void render();` Dibuja el modelo.
- `void translateModel(const glm::vec3& translation);` Función de translación del modelo con la distancia dada.
- `void scaleModel(const glm::vec3& scale);` Función de escalado del modelo con las escalas dadas.
- `void rotateModel(float angle, const glm::vec3& axis);` Función de rotación del modelo con el ángulo y los ejes dados.

---

Una vez descrita la clase modelo, explicaremos los controles desarrollados para cargar nuevos modelos con el explorador de archivos, y como 
realizar transformaciones de modelado a los modelos ya creados.

---

### Importar Modelos ###

Para importar nuevos modelos en escena, hay que clicar "Create model with .obj file" en la ventana "File explorer", lo que abrira el explorador de archivos, 
ahora solo tenemos que seleccionar una archivo con extension .obj, cargando el modelo en la escena.

---

### Controles de Modelo ###

Para realizar transformaciones a los modelos, primero tendremos que cargar los shaders necesarios para su dibujado, en este caso los shaders "pag06", posteriormente debemos cargar un modelo
cualquiera o seleccionar el creado por defecto, esto no permitirá realizar cambios sobre él, entre ellos destruirlo con el botón "Destroy model" o realizar transformaciones de translación, rotación 
o escalado según la seleccionada.

#### Tranformaciones ####

Entre las transformaciones encontramos las siguientes, con sus controles:

- Translation:
  - UP: Mover el modelo una unidad en el eje y positivo.
  - DOWN: Mover el modelo una unidad en el eje y negativo.
  - LEFT: Mover el modelo una unidad en el eje x positibo.
  - RIGHT: Mover el modelo una unidad en el eje x negativo.
  - FORWARD: Mover el modelo una unidad en el eje z positivo.
  - BACKWARD: Mover el modelo una unidad en el eje z negativo.
- Rotation:
  - CLOCKWISE: Rotar el modelo según el sentido de las agujas del reloj con respecto al eje.
  - COUNTERCLOCKWISE: Rotar el modelo en el sentido contrario al de las agujas del reloj con respecto al eje.
- Scale:
  - INCREASE: Incrementar en un 5% el tamaño del modelo en ese eje.
  - DECREASE: Reducir en un 5% el tamaño del modelo en ese eje.

---

El siguiente diagrama UML muestra la estructura de las clases creadas hasta ahora:

<img src="img/UML_4.png">

---

## Práctica 7 ##

En esta sesión de prácticas hemos implementado un shader con subrutinas que permiten dibujar los modelos de dos formas distintas, para ello hemos necesitado desarrollar
la clase material, complementar la clase shaderProgram y crear una interfaz para el cambio de los materiales de los modelos.

Nuestra clase material presenta los siguientes métodos y atributos para su correcto funcionamiento:

#### atributos ####

- `glm::vec3 _diffuse;` Color de difusión del material.
- `glm::vec3 _ambient;` Color de ambientación del material.
- `glm::vec3 _specular;` Color especular del material.
- `float _phongExp;` Exponente de brillo del material.

Entre sus métodos más importantes encontramos:

#### métodos ####

- `void setDiffuse(const glm::vec3& diffuse);` Setter de color de difusión del material.
- `void setAmbient(const glm::vec3& ambient);` Setter de color de ambientación del material.
- `void setSpecular(const glm::vec3& specular);` Setter de color especular del material.
- `void setPhongExp(float phongExp);` Setter de exponente de brillo del material.

- `const glm::vec3& getDiffuse() const;` Getter de color de difusión del material.
- `const glm::vec3& getAmbient() const;` Getter de color de ambientación del material.
- `const glm::vec3& getSpecular() const;` Getter de color especular del material.
- `float getPhongExp() const;` Getter de exponente de brillo del material.

---

Para cumplir con el propósito de la práctica ha sido necesario la creación de una ventana nueva de la interfáz que te permita
cambiar el dibujado de la escena, alternando entre malla de triangulos o dibujado completo. También hemos modificado la ventada
de modelos para que permita cambiar las propiedades de su material.

---

El siguiente diagrama UML muestra la estructura de las clases creadas hasta ahora:

<img src="img/UML_5.png">

---

## Práctica 8 ##

En esta sesión de prácticas hemos implementado iluminación gracias a las clases desarrolladas tomanda el patrón de diseño estrategía, y las
subrutinas creadas en los shaders de esta práctica.

Describiremos las clases creadas relacionadas con la iluminación:

Clase Light:

Es la clase principal encargada de manifestar cualquiera de los tipos de luz según el aplicador utilizado, 
entre sus métodos y atributos se encuentran:

#### atributos ####

- `LightProperties _properties;` Las propiedades de la luz, entre ellas la posición, dirección, intensidad difusa, ambiental y especular, ángulo de foco y valor de atenuaciòn.
- `glm::mat4 _vision;` Matríz de visión de la cámara, para calcular la dirección y posición de la luz según la visión de esta.
- `LightApplicatorType _applicatorSelected;` Aplicador seleccionado, ya sea direccional, de punto, ambiental o de foco.
- `std::array<LightApplicator*, NUM_LIGHT_APPLICATORS> _applicators;` Todos los aplicadores posibles que se pueden manifestar.

Entre sus métodos más importantes encontramos:

#### métodos ####

- `void setLightApplicator(LightApplicatorType applicatorSelected);` Setter del aplicador de luz que se selecciona.
- `void setSubroutine(ShaderProgram& shaderProgram);` Setter de la subrutina que se utiliza para el calculo de la luz.
- `void applyLight(ShaderProgram& shaderProgram);` Función que aplica la luz escogida, definiendo las propiedades necesarias en el programa shader.

Clase LightApplicator:

Es una interfáz que cuenta con dos funciones puramente virtuales:

- `virtual void applySubroutine(ShaderProgram& shaderProgram) = 0;` Función puramente virtual para aplicar la subrutina dependiendo del tipo de aplicador que sea la luz.
- `virtual void applyLight(LightProperties& properties, const glm::mat4& vision, ShaderProgram& shaderProgram) = 0;` Función puramente virtual para aplicar la luz en escena dependiendo del tipo de aplicador.

El resto de clases a describir son las definiciones de la interfáz descrita.

Clase AmbientLightApplicator:

Es el aplicador de luz ambiental.

- Define el método "applySubroutine" de la interfáz para elegir la subrutina llamada "ambient" del programa de shaders.
- Define el método "applyLight" de la interfáz para aplicar la propiedad de intensidad ambiental en el programa de shaders.

Clase SpotLightApplicator:

Es el aplicador de luz focal.

- Define el método "applySubroutine" de la interfáz para elegir la subrutina llamada "spotLight" del programa de shaders.
- Define el método "applyLight" de la interfáz para aplicar la propiedad de intensidad difusa, especular, dirección y posición del foco, valor de atenuación
y ángulo en el programa de shaders.

Clase PointLightApplicator:

Es el aplicador de luz puntual.

- Define el método "applySubroutine" de la interfáz para elegir la subrutina llamada "point" del programa de shaders.
- Define el método "applyLight" de la interfáz para aplicar la propiedad de intensidad difusa, ambiental y posición del punto de luz en el programa de shaders.

Clase DirectionalLightApplicator:

Es el aplicador de luz direccional.

- Define el método "applySubroutine" de la interfáz para elegir la subrutina llamada "directional" del programa de shaders.
- Define el método "applyLight" de la interfáz para aplicar la propiedad de intensidad difusa, ambiental y la dirección de la luz en el programa de shaders.

---

Para cumplir con el propósito de la práctica ha sido necesario la creación de una ventana nueva de la interfáz que te permita cambiar las propiedades de la luz 
según que tipo sea esta. En la escena solo se posée de cuatro luces, cada una de su tipo, siendo respectivamente, luz focal, luz puntual, luz direccional 
y luz ambiental, estando posicionadas o dirigidas de mánera distinta con respecto al resto.

Esto conlleva también a la modificación de la clase Renderer, que es la clase que gestiona realmente las luces, creando los cuatro tipos de luces y dibujando los modelos con cada luz
para mezclar los resultados y obtener la imagen final.

---

El siguiente diagrama UML muestra la estructura de las clases creadas hasta ahora:

<img src="img/UML_6.png">

---