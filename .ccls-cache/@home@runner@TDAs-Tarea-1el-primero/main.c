#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
// Inlcudes agregados
#include <string.h>
#include <time.h>
// Se define un maximo global para la cantidad de caracteres de el nombre y sintomas de cada paciente
#define MAX 150
// Estructuras a utilizar en el programa
typedef struct{
  char nombre[MAX];
  int edad;
  char sintomas[MAX];
} Paciente;

typedef struct {
  time_t hora;
  int numLlegada;
  char prioridad[6];
  Paciente *datosPaciente;
} Atencion;
// Variables globales para saber la cantidad de pacientes en la lista
int numeroAtencionGlobal = 1;
int numerosAtendidos = 0;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}
// Función para registrar pacientes
void registrar_paciente(List *pacientes) {
  limpiarPantalla(); // Se limpia la pantalla
  // Se muestra el encabezado
  puts("========================================");
  puts("     Registrar nuevo paciente");
  puts("========================================");
  puts("");
  // Se crea un nuevo nodo y se entrega la memoria necesaria
  Atencion *nuevoP = malloc(sizeof(Atencion));
  if(nuevoP == NULL)printf("A sucedido un error al registrar");
  nuevoP->datosPaciente = malloc(sizeof(Paciente));
  // Se ingresan los datos del paciente
  printf("Ingrese el nombre del nuevo paciente: ");
  scanf(" %[^\n]", nuevoP->datosPaciente->nombre);
  printf("\nIngrese la edad de %s: ", nuevoP->datosPaciente->nombre);
  scanf("%d", &nuevoP->datosPaciente->edad);
  getchar();
  printf("\nIngrese los sintomas de %s: ", nuevoP->datosPaciente->nombre);
  scanf(" %[^\n]", nuevoP->datosPaciente->sintomas);
  nuevoP->numLlegada = numeroAtencionGlobal++;
  time(&nuevoP->hora);
  strcpy(nuevoP->prioridad,"Bajo");// Todo nuevo paciente se inicializa con prioridad "Bajo"
  list_pushBack(pacientes,nuevoP);
  puts("\nPaciente registrado exitosamente");// Mensaje de realización exitosa
  puts("");
}
// Función para comparar orden de prioridades
int comparar_pacientes_prioridad( void *a, void *b) {
  // Inicialización de variables
  const Atencion *atencion1 = *(const Atencion **)a;
  const Atencion *atencion2 = *(const Atencion **)b;

  // Se asignan valores numéricos a las prioridades
  int prioridad1, prioridad2;
  if (strcmp(atencion1->prioridad, "Alto") == 0) {
      prioridad1 = 3;
  } else if (strcmp(atencion1->prioridad, "Medio") == 0) {
      prioridad1 = 2;
  } else {
      prioridad1 = 1;
  }
  if (strcmp(atencion2->prioridad, "Alto") == 0) {
      prioridad2 = 3;
  } else if (strcmp(atencion2->prioridad, "Medio") == 0) {
      prioridad2 = 2;
  } else {
      prioridad2 = 1;
  }

  // Se comparan las prioridades numéricas
  if (prioridad1 > prioridad2) {
      return -1;
  } else if (prioridad1 < prioridad2) {
      return 1;
  } else {
      // Si las prioridades son iguales, se comparan los números de llegada
      if (atencion1->numLlegada < atencion2->numLlegada) {
          return -1;
      } else if (atencion1->numLlegada > atencion2->numLlegada) {
          return 1;
      } else {
          return 0;
      }
  }
}
// Función para ordenar pacientes
void ordenar_pacientes_bubbleSort(List *pacientes) {
  // Creamos un arreglo dinámico para almacenar los elementos de la lista
  int size = numeroAtencionGlobal - numerosAtendidos; // Se entrega un tamaño para el arreglo
  Atencion **array = (Atencion **)malloc(size * sizeof(Atencion *));
  if (array == NULL) {
      printf("Error: No se pudo asignar memoria para el arreglo.\n");
      return;
  }

  // Llenar el arreglo con los elementos de la lista
  int index = 0;
  void *current;
  for (current = list_first(pacientes); current != NULL; current = list_next(pacientes)) {
      array[index++] = (Atencion *)current;
      if (index >= size) {
          size *= 2; // Duplicar el tamaño del arreglo si se llena
          array = (Atencion **)realloc(array, size * sizeof(Atencion *));
          if (array == NULL) {
              printf("Error: No se pudo asignar memoria para el arreglo.\n");
              return;
          }
      }
  }

  // Se ordena el arreglo utilizando el método de ordenación de burbuja
  for (int i = 0; i < index - 1; i++) {
      for (int j = 0; j < index - i - 1; j++) {
          if (comparar_pacientes_prioridad(&array[j], &array[j + 1]) > 0) {
              // Intercambiar los elementos si están en el orden incorrecto
              Atencion *temp = array[j];
              array[j] = array[j + 1];
              array[j + 1] = temp;
          }
      }
  }

  // Limpiar la lista para insertar los elementos ordenados
  list_clean(pacientes);

  // Insertar los elementos ordenados de vuelta en la lista
  for (int i = 0; i < index; i++) {
        list_pushBack(pacientes, array[i]);
  }

  // Liberar memoria del arreglo
  free(array);
}
// Función para mostrar pacientes
void mostrar_lista_pacientes(List *pacientes) {
  limpiarPantalla();// Se limpia la pantalla

  // Ordenar la lista antes de mostrarla
  ordenar_pacientes_bubbleSort(pacientes);
  // Se muestra encabezado
  puts("========================================");
  puts("     Mostrar lista de espera");
  puts("========================================");
  puts("");
  // Preguntamos si hay pacientes en espera
  void *current = list_first(pacientes);
  if (current == NULL)
    puts("No hay pacientes en espera\n");
  else {
    // Mostrar pacientes en la lista de espera
    printf("Pacientes en espera: \n\n");
    while (current != NULL) {
      Atencion *atencion = current;
      struct tm *local = localtime(&atencion->hora);
      printf("   Nombre: %s\n", atencion->datosPaciente->nombre);
      printf("   Edad: %d\n", atencion->datosPaciente->edad);
      printf("   Síntomas: %s\n", atencion->datosPaciente->sintomas);
      printf("   Prioridad: %s\n", atencion->prioridad);
      printf("   Hora de llegada: %d:%d:%d\n", local->tm_hour, local->tm_min, local->tm_sec);
      puts("");
      current = list_next(pacientes);
    }
  }
}
// Función para asignar una nueva prioridad a un pacientes
void asignar_prioridad(List *pacientes) {
  limpiarPantalla();// Se limpia la pantalla
  // Se inician variables locales
  char nombre[MAX];
  char nueva_prioridad[6];
  // Se muestra encabezado
  puts("========================================");
  puts("     Asignar prioridad a paciente");
  puts("========================================");
  puts("");

  ordenar_pacientes_bubbleSort(pacientes);// Ordenamos la lista
  // Se pregunta si la lista esta vacia
  void *currentLista = list_first(pacientes);
  if(currentLista == NULL)printf("No hay pacientes en espera\n");
  else{
    // Mostramos los pacientes en la lista para que el usuario sepa a quien cambiar su prioridad
    printf("Pacientes en espera: \n\n");
    while (currentLista != NULL) {
      Atencion *atencion = currentLista;
      struct tm *local = localtime(&atencion->hora);
      printf("   Nombre: %s\n", atencion->datosPaciente->nombre);
      printf("   Edad: %d\n", atencion->datosPaciente->edad);
      printf("   Síntomas: %s\n", atencion->datosPaciente->sintomas);
      printf("   Prioridad: %s\n", atencion->prioridad);
      printf("   Hora de llegada: %d:%d:%d\n", local->tm_hour, local->tm_min, local->tm_sec);
      puts("");
      currentLista = list_next(pacientes);
    }
    // Se ingresan los datos del paciente en cuestión
    printf("Ingrese el nombre del paciente para actualizar prioridad: ");
    scanf(" %[^\n]", nombre);
    printf("\nIngrese la nueva prioridad (Alto/Medio/Bajo): ");
    scanf("%s", nueva_prioridad);
  
    if(strcmp(nueva_prioridad,"Alto") != 0 && strcmp(nueva_prioridad,"Medio") != 0 && strcmp(nueva_prioridad,"Bajo") != 0)
      printf("No existe la prioridad %s",nueva_prioridad);// Si se ingresa de manera erronea se muestra un mensaje
    else{
      int encontrado = 0;
      for (void *current = list_first(pacientes); current != NULL; current = list_next(pacientes)) {
        Atencion *atencion = current;
        if (strcmp(atencion->datosPaciente->nombre, nombre) == 0) {
          strcpy(atencion->prioridad, nueva_prioridad);
          encontrado = 1;
          puts("");
          printf("Prioridad asignada correctamente.\n");// Se muestra la realización exitosa
          break; 
        }
      }
      // En caso de no existir el paciente se entrega un mensaje
      if (!encontrado) {
        printf("El paciente con nombre %s no ha sido encontrado en la lista de espera.\n", nombre);
      }
    }
  }
  puts("");
}
// Se atiende al primer paciente de la lista
void atender_paciente(List *pacientes){
  limpiarPantalla();// Se limpia la pantalla
  ordenar_pacientes_bubbleSort(pacientes);// Se ordenan los pacientes
  // Se muestra el encabezado
  puts("========================================");
  puts("     Atender al siguiente paciente");
  puts("========================================");
  puts("");
  
  Atencion *atencion = list_popFront(pacientes);// Retiramos al paciente de l alista
  if(atencion == NULL)
    printf("No hay pacientes en espera\n");// Si no hay pacientes se muestra un mensaje
  else{
    numerosAtendidos++;// Contador para saber cuantos pacienets se han atendido
    // Se muestran los datos del paciente atendido
    printf("Atendiendo a %s:\n", atencion->datosPaciente->nombre);
    struct tm *local = localtime(&atencion->hora);
    printf("   Edad: %d\n", atencion->datosPaciente->edad);
    printf("   Síntomas: %s\n", atencion->datosPaciente->sintomas);
    printf("   Prioridad: %s\n", atencion->prioridad);
    printf("   Hora de llegada: %d:%d:%d\n", local->tm_hour, local->tm_min,local->tm_sec);
  }
  puts("");
}
// Función mostrar solo pacientes con prioridad especifica
void mostrar_prioridad_pacientes(List *pacientes){
  limpiarPantalla();// Se limpia la pantalla
  // Se muestra el encabezado
  puts("========================================");
  puts("     Mostrar pacientes por prioridad");
  puts("========================================");
  puts("");

  if(list_first(pacientes) == NULL){
    puts("No hay pacientes en espera");// Si no hay pacientes se muestra un mensaje
    puts("");}
  else{
    char prioridad[6];
    int cont = 0;
    printf("Ingrese la prioridad de pacientes a mostrar (Alto/Medio/Bajo): ");// Usuario ingresa prioridad a mostrar
    scanf( "%s", prioridad);
    puts("");
    if(strcmp(prioridad,"Alto") != 0 && strcmp(prioridad,"Medio") != 0 && strcmp(prioridad,"Bajo") != 0)
      printf("No existe la prioridad %s\n",prioridad);// En caso de ingresar alguna prioridad inexistente se muestra un mensaje
    else{
      // Se recorre la lista solo mostrando los pacientes con la prioridad solicitada
      for (void *current = list_first(pacientes); current != NULL; current = list_next(pacientes)) {
        Atencion *atencion = current;
        if(strcmp(prioridad,atencion->prioridad) == 0){
          cont++;
          if(cont==1) printf("Lista de pacientes de prioridad %s\n\n", prioridad);
          struct tm *local = localtime(&atencion->hora);
          printf("   Nombre: %s\n", atencion->datosPaciente->nombre);
          printf("   Edad: %d\n", atencion->datosPaciente->edad);
          printf("   Síntomas: %s\n", atencion->datosPaciente->sintomas);
          printf("   Prioridad: %s\n", atencion->prioridad);
          printf("   Hora de llegada: %d:%d:%d\n", local->tm_hour, local->tm_min,local->tm_sec);
          puts("");
        }
      }
    }
    if(cont == 0)
      printf("No hay pacientes con prioridad %s\n\n", prioridad);// Si la prioridad ingresada no tiene pacientes se muestra un mensaje
  }
}

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      atender_paciente(pacientes);
      break;
    case '5':
      mostrar_prioridad_pacientes(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}
