#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "heap.h"
#include "treemap.h"


// Tarea
typedef struct {
    char nombre[100];
    int prioridad;
    char tareasPrecedentes[100];
    int completada;
} Tarea;


int compararPrioridades(void* key1, void* key2) {
    int prioridad1 = *(int*)key1;
    int prioridad2 = *(int*)key2;
    return prioridad1 - prioridad2;
}


Tarea* buscarTarea(Map* mapa, const char* nombre) {
    Tarea* tarea = NULL;
    void* data = searchMap(mapa, (void*)nombre);
    if (data != NULL) {
        tarea = (Tarea*)data;
    }
    return tarea;
}


void imprimirTareasPorHacer(Map* mapa) {
    Heap* heap = createHeap();
    setSortFunction(heap, compararPrioridades);

    // se insertan en el heap
    void* data = firstMap(mapa);
    while (data != NULL) {
        Tarea* tarea = (Tarea*)data;
        if (!tarea->completada) {
            heap_push(heap, tarea, tarea->prioridad);
        }
        data = nextMap(mapa);
    }

    // se imprimen por prioridad
    int contador = 1;
    while (heap->size > 0) {
        Tarea* tarea = (Tarea*)heap_top(heap);
        printf("%d. %s (Prioridad: %d)", contador, tarea->nombre, tarea->prioridad);
        if (strlen(tarea->tareasPrecedentes) > 0) {
            printf(" - Precedente: %s", tarea->tareasPrecedentes);
        }
        printf("\n");
        heap_pop(heap);
        contador++;
    }

  
    free(heap);
}


void marcarTareaComoCompletada(Map* mapa) {
    char nombre[100];
    printf("Ingrese el nombre de la tarea a marcar como completada: ");
    scanf("%s", nombre);

    Tarea* tarea = buscarTarea(mapa, nombre);

    if (tarea == NULL) {
        printf("La tarea no existe.\n");
    } else {
        if (strlen(tarea->tareasPrecedentes) > 0) {
            printf("Advertencia: Esta tarea tiene precedentes. ¿Estás seguro de que deseas marcarla como completada? (s/n): ");
            char respuesta;
            scanf(" %c", &respuesta);
            if (respuesta != 's' && respuesta != 'S') {
                printf("Operación cancelada.\n");
                return;
            }
        }

        tarea->completada = 1;
        eraseMap(mapa, (void*)nombre);
        printf("Tarea marcada como completada y eliminada de la lista de tareas por hacer.\n");
    }
}

int main() {
    // Crear mapa de tareas
    Map* mapaTareas = createMap(compararPrioridades);

    int opcion = 0;
    while (opcion != 5) {
       printf("\n\n\n");
        printf("┃━━━━━━━━━━━━━━━━━━Menú━━━━━━━━━━━━━━━━━━━┃\n");
        printf("┃ 1. Agregar tarea                        ┃\n");
        printf("┃ 2. Establecer precedente entre tareas   ┃\n");
        printf("┃ 3. Mostrar tareas por hacer             ┃\n");
        printf("┃ 4. Marcar tarea como completada         ┃\n");
        printf("┃ 5. Salir y liberar memoria              ┃\n");
        
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            // Agregar tarea
            char nombre[100];
            int prioridad;
            printf("┃ Ingrese el nombre de la tarea: ");
            scanf("%s", nombre);
            printf("┃ Ingrese la prioridad de la tarea: ");
            scanf("%d", &prioridad);

            Tarea* tarea = buscarTarea(mapaTareas, nombre);
            if (tarea == NULL) {
                tarea = (Tarea*)malloc(sizeof(Tarea));
                strcpy(tarea->nombre, nombre);
                tarea->prioridad = prioridad;
                tarea->completada = 0;
                strcpy(tarea->tareasPrecedentes, "");
                insertMap(mapaTareas, (void*)nombre, (void*)tarea);
               
              printf("┃ Tarea Agregada !                        ┃\n");
            } else {
            
              printf("┃ E: Nombre de la tarea ya existe         ┃\n");
            
            }
        } else if (opcion == 2) {
            // precedentes 
            char tareaActual[100];
            char tareaPrecedente[100];
            printf("Ingrese el nombre de t1: ");
            scanf("%s", tareaActual);
            printf("Ingrese el nombre de t2: ");
            scanf("%s", tareaPrecedente);

            Tarea* tareaActualObj = buscarTarea(mapaTareas, tareaActual);
            Tarea* tareaPrecedenteObj = buscarTarea(mapaTareas, tareaPrecedente);

            if (tareaActualObj == NULL || tareaPrecedenteObj == NULL) {
              printf("┃ Error, t1 o t2 no existen                ┃\n");
            } else {
                strcpy(tareaActualObj->tareasPrecedentes, tareaPrecedente);

                printf("┃ Precedente establecido,                 ┃\n");

            }
        } else if (opcion == 3) {
            // mostrar
            imprimirTareasPorHacer(mapaTareas);
        } else if (opcion == 4) {
            // marcar
            marcarTareaComoCompletada(mapaTareas);
        } else if (opcion == 5) {
            // cahao
            printf("...Cerrando programa y liberando memoria. bye!...\n");
        } else {
            printf("ingrese una opcion valida.\n");
        }
    }

    // end
    void* data = firstMap(mapaTareas);
    while (data != NULL) {
        Tarea* tarea = (Tarea*)data;
        free(tarea);
        data = nextMap(mapaTareas);
    }
    

    return 0;
}
