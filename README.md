### Práctica 1

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
### Práctica 2

Durante esta sesión de practicas hemos incorporado la biblioteca ImGUI, con la cual hemos
logrado la implementación de una interfaz simple que nos permite capturar los mensages
que previamente se mostraba por consola, en una pequeña ventana, y elegir el color del fondo
de nuestra aplicación.

Para ello hemos creado nuestra propia clase GUI que encapsulara todas las funcionalidades de 
dicha biblioteca, la clase se diseñara con el patrón de diseño singleton al igual que la clase Renderer,
y se encontrará en el espacio de nombres PAG. Esta clase como hemos indicado en el parrafo anterior
implementará dos ventanas a través de la función ImGui::Begin, la primera funcionará como una consola, ya que mostrara
los mensages de nuestra aplicación a través de la función ImGui::Text, que permite mostrar texto en 
la ventana o contexto determinado. En la segunda ventana utilizaremos otro recurso diractemente implementado 
en la biblioteca, el cual es un selector de color, accesible a traves de la función ImGui::ColorPicker4, el cual mostrara
los valores RGB, HSV y hexadecimal del color selecionado gracias a las etiquetas utilizadas en la función, que también
permiten no mostrar el valor de transparencia del color y seleccionar el formato con el que se muestra el selector de color.

Para que la implementación de las utilidades que aportan nuestra clase GUI funcionen correctamente con el resto del 
programa, ha sido necesario que la clase Renderer comunique el color con el que dibuja el fondo de la aplicación a la clase
GUI y viceversa.

La clase Renderer al igual que la clase GUI se ha diseñado como un singleton y también pertenece al espacio de nombres PAG,
esta solo incluye bibliotecas de Opengl para mantaner una estructura modular en el proyecto. Esta clase se encarga del dibujado y 
la inicialización de Opengl en la aplicación.

### Práctica 3