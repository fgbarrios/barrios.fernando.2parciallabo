#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "extras.h"

/** \brief Menu de opciones principal
 *
 * \return int - opcion elegida
 *
 */
int menu()
{
    int opcion;

    system ("cls");
    printf("********** ESTADISTICAS PAISES CON COVID **********\n\n");
    printf("1. Cargar los datos de los paises desde el archivo data.csv (modo texto)\n");
    printf("2. Listar Paises\n");
    printf("3. Asignar estadisticas\n");
    printf("4. Filtrar por paises existosos\n");
    printf("5. Filtrar por paises en el horno\n");
    printf("6. Ordenar por nivel de vacunacion\n");
    printf("7. Mostrar pais mas castigado\n");
    printf("8. Salir\n\n");

    printf("Ingrese opcion (1-8): ");
    scanf("%d", &opcion);

    while(opcion < 0 || opcion > 8)
    {
        printf("ERROR. Ingrese opcion (1-8): ");
        scanf("%d", &opcion);
    }

    return opcion;
}

/** \brief Confirmacion de salida
 *
 * \return char - 's' para salir, 'n' para continuar
 *
 */
char confirmar()
{
    char respuesta;

    printf("Presione s para confirmar o n para cancelar: ");
    fflush(stdin);
    respuesta = getchar();

    while(respuesta != 's' && respuesta != 'n')
    {
        printf("Error. Presione s para confirmar o n para cancelar: ");
        fflush(stdin);
        respuesta = getchar();
    }

    return respuesta;
}

