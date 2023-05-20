# Gestor de Tareas

instrucciones https://docs.google.com/document/d/1dSpZc_DFGfb63PwFMRAS7E7FCF8_VJiZDiyTHPad6nw/edit

## Funcionalidad

Esta tare presenta las siguientes funciones en su menú:

- Agregar tarea: Permite agregar una tarea especificando su nombre y prioridad.

- **Establecer precedencia entre tareas: Permite establecer una tarea precedente para otra tarea.** (Leer Problema conocido)

- Mostrar tareas por hacer: Muestra la lista de tareas por hacer ordenadas por prioridad.

- Marcar tarea como completada: Permite marcar una tarea como completada y eliminarla de la lista de tareas por hacer.

## Problema conocido

Actualmente, la función de agregar precedencia entre tareas no funciona correctamente. Existe un problema que impide establecer correctamente la tarea precedente. Esto puede deberse a la forma en que se realiza la asignación de la tarea precedente en la estructura de la tarea.

## Posibles soluciones

Se sugieren las siguientes posibles soluciones para solucionar el problema de la función de agregar precedencia:

1. Revisar la lógica de asignación de la tarea precedente en la función `establecerPrecedenciaEntreTareas`. Asegurarse de que se está asignando correctamente el nombre de la tarea precedente a la tarea actual.

2. Verificar el funcionamiento de la función `buscarTarea` para asegurarse de que está devolviendo la tarea correcta al buscarla en el mapa de tareas.

3. Utilizar un enfoque alternativo para almacenar la relación de precedencia entre tareas, como un enlace directo entre las tareas en lugar de almacenar el nombre de la tarea precedente en la estructura de la tarea.

## Compilación y ejecución

Para compilar y ejecutar el proyecto en Replit, sigue los siguientes pasos:

1. Copia el repositorio en tu cuenta de Replit.

2. Haz clic en el botón "Run" para compilar y ejecutar el programa.


