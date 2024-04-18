#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
//agregado
#include <string.h>

typedef struct{
  char nombre[100];
  int edad;
  char sintomas[100];
} Paciente;

typedef struct {
  int numLlegada;
  char prioridad[6];
  Paciente *paciente;
} Atencion;

int numeroAtencionGlobal = 1;

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

void registrar_paciente(List *pacientes) {
  //INGRESO DATOS PACIENTE
  printf("\nRegistrar nuevo paciente\n");
  Atencion *nuevoP = malloc(sizeof(Atencion));
  if(nuevoP == NULL)printf("A sucedido un error al registrar");
  nuevoP->paciente = malloc(sizeof(Paciente));
  printf("Ingrese el nombre del nuevo paciente: ");
  scanf("%s", nuevoP->paciente->nombre);
  printf("\nIngrese la edad de %s: ", nuevoP->paciente->nombre);
  scanf("%d", &nuevoP->paciente->edad);
  printf("\nIngrese los sintomas de %s: ", nuevoP->paciente->nombre);
  scanf("%s", nuevoP->paciente->sintomas);
  nuevoP->numLlegada = numeroAtencionGlobal++;
  strcpy(nuevoP->prioridad,"BAJA");
  list_pushBack(pacientes,nuevoP);
  // Aquí implementarías la lógica para registrar un nuevo paciente
}

void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("\nPacientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  for (void *current = list_first(pacientes); current != NULL; current = list_next(pacientes)) {
    Atencion *atencion = current;
    printf("   Número de llegada: %d\n", atencion->numLlegada);
    printf("   Nombre: %s\n", atencion->paciente->nombre);
    printf("   Edad: %d\n", atencion->paciente->edad);
    printf("   Síntomas: %s\n", atencion->paciente->sintomas);
    printf("   Prioridad: %s\n\n", atencion->prioridad);
  }
}

void asignar_prioridad(List *pacientes) {
  char nombre[100];
  char nueva_prioridad[6];

  mostrar_lista_pacientes(pacientes);
  printf("Ingrese el nombre del paciente para actualizar prioridad: ");
  scanf("%s", nombre);
  printf("\nIngrese la nueva prioridad (Alto/Medio/Bajo): ");
  scanf("%s", nueva_prioridad);

  int encontrado = 0;
  for (void *current = list_first(pacientes); current != NULL; current = list_next(pacientes)) {
    Atencion *atencion = current;
    if (strcmp(atencion->paciente->nombre, nombre) == 0) {
      strcpy(atencion->prioridad, nueva_prioridad);
      encontrado = 1;
      printf("Prioridad asignada correctamente.\n");
      break; 
    }
  }

  if (!encontrado) {
    printf("El paciente con nombre %s no ha sido encontrado en la lista de espera.\n", nombre);
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
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
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
