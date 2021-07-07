#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "paises.h"

/** \brief Parsea los datos los datos de los paises desde el archivo vacunas.csv (modo texto).
 *
 * \param path char* - path del archivo
 * \param LinkedList* pArrayList - Linkedlist donde se cargarian los datos
 * \return int
 *
 */
int parser_PaisesFromText(FILE* pFile , LinkedList* pArrayList)
{
    int cant;
    char buffer[5][20];
    int flag = 0;
    ePais* aux = NULL;

    if(pFile != NULL && pArrayList != NULL){

        // lectura fantasma para el encabezado del archivo
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

        while(!feof(pFile))
            {
                cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
                if(cant == 5){
                    // si la lectura fue exitosa creo un empleado con el constructor


                    aux = paises_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

                    if(aux != NULL)
                    {
                        ll_add(pArrayList, aux); // agrego el nuevo empleado al array Lista
                        aux = NULL; // desactivo el auxiliar
                    }else{
                        flag = 1; // 1 problema al cargar empleado
                        break;
                        }
                }else{
                    flag = 2; // 2 error en la lectura del renglon (cant != 4)
                    break;
                }
            }// fin del while
        }

    switch(flag)
    {
        case 0:
            printf("Paises cargados correctamente (desde texto).\n");
        break;
        case 1:
            printf("No se pudo crear los paises.\n");
        break;
        case 2:
            printf("Error en la lectura del archivo de texto.\n");
        break;
    }
    return 1;
}


