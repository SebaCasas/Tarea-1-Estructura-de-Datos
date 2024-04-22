# Programa de gestion hospitalaria

## Descripción de la aplicación
Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital, clinica o consultorio. El usuarios pueden registrar nuevos pacientes, asignar prioridades a los pacientes, ver la lista de espera de los pacientes, y más. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

## Ejemplo de uso de la aplicación
### Ejecución
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar `repl.it` para una rápida configuración y ejecución. Sigue estos pasos para comenzar:
* Visita `repl.it`.
* Crea una nueva cuenta o inicia sesión si ya tienes una.
* Una vez en tu dashboard, selecciona `New Repl` y elige `Import from GitHub`.
* Pega la URL de este repositorio.
* repl.it clonará el repositorio y preparará un entorno de ejecución.
* Para ejecutar el main en `repl.it` primero debemos compilar (en la carpeta raíz):
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

* Y luego ejecutar:
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
* `Registrar paciente`: Ingresa los datos del paciente: nombre, edad y síntomas. Como en el ejemplo a continuación:
````
========================================
     Registrar nuevo paciente
========================================
     
Ingrese el nombre del nuevo paciente: Juan
     
Ingrese la edad de Juan: 30
     
Ingrese los sintomas de Juan: Tos
     
Paciente registrado exitosamente
````
* `Asignar prioridad a paciente`: Ingresa el nombre del paciente y el nuevo nivel de prioridad. Como en el ejemplo a continuación:
````
========================================
     Asignar prioridad a paciente
========================================

Pacientes en espera: 

   Nombre: Juan
   Edad: 30
   Síntomas: Tos
   Prioridad: Bajo
   Hora de llegada: 2:20:5

Ingrese el nombre del paciente para actualizar prioridad: Juan

Ingrese la nueva prioridad (Alto/Medio/Bajo): Medio

Prioridad asignada correctamente.
````
* `Mostrar lista de espera`: Muestra la lista de pacientes en espera. Como en el ejemplo a continuación:
````
========================================
     Mostrar lista de espera
========================================

Pacientes en espera: 

   Nombre: Juan
   Edad: 30
   Síntomas: Tos
   Prioridad: Medio
   Hora de llegada: 2:20:5
````
* `Atender al siguiente paciente`: Selecciona y atiende al siguiente paciente de la lista de espera. Como en el ejemplo a continuación:
````
========================================
     Atender al siguiente paciente
========================================

Atendiendo a Juan:
   Edad: 30
   Síntomas: Tos
   Prioridad: Medio
   Hora de llegada: 2:20:5
````
* `Mostrar pacientes por prioridad`: Ingresa un nivel de prioridad y muestra los pacientes correspondientes. Como en el ejemplo a continuación:
````
========================================
     Mostrar pacientes por prioridad
========================================

Ingrese la prioridad de pacientes a mostrar (Alto/Medio/Bajo): Medio

Lista de pacientes de prioridad Medio

   Nombre: Juan
   Edad: 30
   Síntomas: Tos
   Prioridad: Medio
   Hora de llegada: 2:20:5
````
* `Salir`: Terminar el programa.

## Especificaciones de la aplicacion
### Funcionalidades de la aplicación
* `registrar_paciente`: Permite al usuario ingresar los datos del paciente, incluyendo nombre, edad y síntomas. El paciente se registra con un nivel de prioridad "Bajo" automaticamente.
* `asignar_prioridad`: El usuario puede actualizar el nivel de prioridad de un paciente existente ingresando el nombre del paciente y la nueva priridad. Si el paciente y/o la nueva prioridad a actualizar no existe(n), se muestra un mensaje de aviso. Si no hay pacientes en espera, se muestra un aviso.
* `mostrar_lista_pacientes`: Muestra la lista de pacientes en espera, ordenados por nivel de prioridad (de "Alto" a "Bajo") y, dentro del mismo nivel, por orden de llegada (hora de registro). Se utiliza el metodo de bubbleSort, para que funcione copiamos toda la lista en un arreglo, bubbleSort llama una funcion que entrega si estan en orden 2 nodos de la lista(Esta funcion transforma en numeros las prioridades), una vez ordenado el arreglo se copia cada nodo a la lista original. Si no hay pacientes en espera, se muestra un aviso.
* `atender_paciente`: Selecciona al siguiente paciente a ser atendido según el orden de prioridad y lo elimina de la lista de espera. Muestra los datos del paciente atendido. Si no hay pacientes en espera, se muestra un aviso.
* `mostrar_prioridad_pacientes`: Permite al usuario ingresar un nivel de prioridad y muestra los pacientes que corresponden a ese nivel, ordenados por orden de llegada. Si no hay pacientes en espera o pacienets en la prioridad deseada, se muestra un aviso.

### Posibles errores en la aplicación
* El principal error podria ocurrir en la funcion `registrar_paciente`, ya que, si uno ingresa palabras/letras en la seccion de ingresar edad del paciente el programa no toma lo ingresado y se salta la seccion ingresar síntomas, volviendo al menu principal; Guarda al paciente con nombre, sin edad, pero tomando como las palabras/letras ingresadas como los síntomas.
* Otro error, que es muy poco probable que ocurra, sucede en la función `ordenar_pacientes_bubbleSort`, que si llega a ocurrir entrega un mensaje. Este error consiste en fallar al guardar memoria para el arreglo, ocacionando que no se genere el arreglo por lo que no se ordena la lista.
