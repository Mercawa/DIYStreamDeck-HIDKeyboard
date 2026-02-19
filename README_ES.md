# Stream Deck con Arduino (HID – F13 a F25)

---

## Descripción

Este proyecto comenzó reutilizando switches black que separé de un teclado Sentey roto que me regaló un amigo.  
Luego de medir cada switch con un multímetro, decidí reutilizarlos para construir un Stream Deck casero basado en Arduino.

Si bien existen muchos proyectos similares disponibles en internet, la mayoría depende de software de terceros.  
Este enfoque no me resultó óptimo, especialmente en Windows, donde instalar aplicaciones no verificadas suele ser molesto o problemático.

Por este motivo, aproveché la capacidad HID (Human Interface Device) del Arduino para que el dispositivo funcione como una extensión de teclado nativa.  
Utilizando las teclas F13 a F25, que Windows reconoce correctamente, el Stream Deck puede configurarse fácilmente en aplicaciones como Discord, OBS u otros programas que admitan atajos de teclado personalizados, sin necesidad de instalar software adicional.

---

## Case impreso en 3D

Imprimí únicamente el case del siguiente modelo (no es un diseño original mío):

https://www.printables.com/model/269757-stream-deck-macro-keyboard

Todos los archivos STL pertenecen a su creador original.  
Los créditos corresponden íntegramente al diseñador.

Las teclas y los switches fueron reutilizados del teclado original.

Al tratarse de un regalo para un streamer, el frente fue personalizado con su nombre artístico y un pequeño detalle “XD :V”.

---

## Armado del Hardware

1. Primero coloqué los switches en la plancha impresa para facilitar y mejorar el proceso de soldadura.
2. Realicé un puente común de GND entre todos los switches.
3. Cada salida de switch fue conectada individualmente a un pin digital del Arduino.
4. Se agregó una placa NeoPixel conectada al pin A1 y ubicada en la parte superior.
5. Los switches fueron fijados desde la parte trasera utilizando silicona caliente.
6. El Arduino se posicionó cuidadosamente para coincidir con la salida del puerto USB del case y se fijó con silicona caliente.

El procedimiento es relativamente sencillo, por lo que no se tomaron muchas fotos del proceso.


![Switches testing](images/wiring_2.jpeg)

---

## Software y Funcionalidad

El código es simple y fácil de entender.

### Funciones de Teclado

- Cada botón envía pulsaciones de teclas F13 a F25
- Compatible con:
  - Discord (muteo, silenciar, push-to-talk)
  - OBS (transiciones, acciones)
  - Cualquier aplicación que soporte atajos de teclado personalizados
- No requiere software externo

---

## Modos de Iluminación RGB

Los dos primeros botones se utilizan para controlar los modos de iluminación.

Modos disponibles:

1. Modo rainbow  
   El último botón permite cambiar entre tres velocidades diferentes.
2. Modo breathing RGB con cambio de colores
3. Modo breathing verde (color favorito de la persona que recibió el regalo)
4. Modo verde fijo
5. Modo reactivo, donde los LEDs se encienden y cambian de color al presionar un botón

![Switches testing](images/finished_4.jpeg)

---

## Tiempo de Construcción

El proyecto se completó en aproximadamente una semana.  
La parte que más tiempo requiere es la impresión del case, aunque no representa una gran dificultad.

---

## Posibles Mejoras y Observaciones

Luego de entregar el regalo, se identificaron algunas mejoras posibles:

1. El cableado interno tapa parcialmente el RGB, ya que la placa de LEDs se colocó después del cableado del Arduino.
2. El frente fue impreso en color verde; utilizar filamento blanco o transparente podría mejorar la difusión de la luz.
3. No se incluyó un modo sin iluminación, lo que puede resultar molesto dado que el Arduino permanece encendido mientras está conectado a la PC.
4. Los botones utilizados para cambiar los modos de iluminación siguen enviando las teclas F13, F14 y F25, lo que puede generar conflictos según la configuración de atajos.

Estos son los principales puntos a mejorar detectados hasta el momento.

[Demo en YouTube](https://www.youtube.com/watch?v=TU_LINK](https://www.youtube.com/shorts/s9-_362nHXg))

---

## Créditos e Inspiración

Este proyecto está inspirado en el siguiente tutorial:

https://www.instructables.com/HyperDeck-an-Arduino-Streamdeck/

Todos los créditos corresponden a los autores originales.
