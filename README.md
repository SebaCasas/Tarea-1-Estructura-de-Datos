# Programa de gestion hospitalaria

## Funcionalidades de la aplicación
* `registrar_paciente`: Permite al usuario ingresar los datos del paciente, incluyendo nombre, edad y síntomas. El paciente se registra con un nivel de prioridad "Bajo" automaticamente.
* `asignar_prioridad`: El usuario puede actualizar el nivel de prioridad de un paciente existente. Si el paciente y/o la nueva prioridad a actualizar no existe(n), se muestra un mensaje de aviso. Si no hay pacientes en espera, se muestra un aviso.
* `mostrar_lista_pacientes`: Muestra la lista de pacientes en espera, ordenados por nivel de prioridad (de "Alto" a "Bajo") y, dentro del mismo nivel, por orden de llegada (hora de registro). Si no hay pacientes en espera, se muestra un aviso.
* `atender_paciente`: Selecciona al siguiente paciente a ser atendido según el orden de prioridad y lo elimina de la lista de espera. Muestra los datos del paciente atendido. Si no hay pacientes en espera, se muestra un aviso.
* `mostrar_prioridad_pacientes`: Permite al usuario ingresar un nivel de prioridad y muestra los pacientes que corresponden a ese nivel, ordenados por orden de llegada. Si no hay pacientes en espera o pacienets en la prioridad deseada, se muestra un aviso.

## Posibles errores en la aplicación
* El principal error podria ocurrir en la funcion `registrar_paciente`, ya que, si uno ingresa palabras/letras en la seccion de ingresar edad del paciente el programa no toma lo ingresado y se salta la seccion ingresar síntomas, volviendo al menu principal; Guarda al paciente con nombre, sin edad, pero tomando como las palabras/letras ingresadas como los síntomas.
* Otro error, no tan grave pero error igual, es un mal uso de la memoria en la funcion `ordenar_pacientes_bubbleSort`, que si llega a ocurrir entrega un mensaje.

## Ejemplo de uso de la aplicación
### Ejecución
Para ejecutar el main en `replit` primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````
./main
````
### Uso de la aplicación
Al realizar la ejecución indicada se abrira el siguiente menu:
````
========================================
     Sistema de Gestión Hospitalaria
========================================
1) Registrar paciente
2) Asignar prioridad a paciente
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar pacientes por prioridad
6) Salir
Ingrese su opción:
````
Se debera ingresar el numero que acompaña a la accion en el menu para realizar la función deaseada.

A continuación lo que se puede realizar en cada una de las opciones:
* `Registrar paciente`: Ingresa los datos del paciente: nombre, edad y síntomas.
* `Asignar prioridad a paciente`: Ingresa el nombre del paciente y el nuevo nivel de prioridad.
* `Mostrar lista de espera`: Muestra la lista de pacientes en espera.
* `Atender al siguiente paciente`: Selecciona y atiende al siguiente paciente de la lista de espera.
* `Mostrar pacientes por prioridad`: Ingresa un nivel de prioridad y muestra los pacientes correspondientes.
* `Salir`: Termina el programa.
