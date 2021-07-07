#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "Controller.h"
#include "extras.h"
#include "paises.h"


/** \brief Carga los datos de los paises desde el archivo vacunas.csv (modo texto).
 *
 * \param path char* - path del archivo a cargar
 * \param pArrayListEmployee LinkedList* - linkedlist en donde se guardaria la info
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    if(path != NULL && pArrayListEmployee != NULL){

    // Abre el archivo y llama a parser. Carga los datos y luego cierra el archivo.
        FILE* f = fopen(path, "r");
        if(f == NULL)
        {
            printf("No se pudo abrir el archivo de texto.\n");
            exit(1);
        }else{
            parser_PaisesFromText(f, pArrayListEmployee);
        }
        fclose(f);

    }
    return 1;
}

/** \brief Lista 1 pais
 *
 * \param ePais pPais* - pais a listar
 * \return int - 1 Todo ok - 0 error
 *
 */

int controller_ListPais(ePais* pPais)
{
    int todoOk = 0;
    int id;
    char nombre[128];
    int vac1dosis;
    int vac2dosis;
    int sinVacunar;

    if(pPais != NULL &&
       pais_getId(pPais , &id) &&
       pais_getNombre(pPais , nombre) &&
       pais_getvac1dosis(pPais , &vac1dosis) &&
       pais_getvac2dosis(pPais , &vac2dosis) &&
       pais_getsinVacunar(pPais , &sinVacunar)
       )
    {
            printf("%4d    %20s        %4d        %4d        %4d\n\n",
               id,
               nombre,
               vac1dosis,
               vac2dosis,
               sinVacunar);
        todoOk = 1;
    }
    return todoOk;
}

/** \brief Listar paises
 *
 * \param pArrayList ePais* - paises a listar
 * \return int - 1 todo ok - 0 error
 *
 */
int controller_ListPaises(ePais* pArrayList)
{
    int todoOk = 0;
    ePais* aux = NULL;

    if(pArrayList != NULL){
        printf("  ID               Pais            Vac1Dosis    Vac2Dosis    SinVacunar\n");

        for (int i = 0; i < ll_len(pArrayList) ;i++ ){
            aux = (ePais*) ll_get(pArrayList, i);
            controller_ListPais(aux);
        }
        todoOk = 1;
    }
    return todoOk;
}

/** \brief Guarda los datos de los paises en un archivo (modo texto).
 *
 * \param path char* - path del archivo a guardar
 * \param LinkedList* pArrayList - lista a cargar
 * \return int - 1 todo ok - 0 error
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayList)
{
    int todoOk = 0;
	char confirma = 's';

	FILE* f = NULL;
	ePais* aux = NULL;

	if(path != NULL && pArrayList != NULL)
	{
		f = fopen(path,"r");
		if(f != NULL)
		{
			printf("Cuidado el archivo existe y se va a sobrescribir. Desea confirmar? s/n :\n ");
			fflush(stdin);
			scanf("%c", &confirma);
		}
		fclose(f);

		if(confirma == 's')
		{
			f = fopen(path,"w");
			if(f == NULL)
			{
				printf("\n   No se pudo abrir el archivo\n\n");
			}
			else
			{
				fprintf(f,"id,nombre,vac1dosis,vac2dosis,sinVacunar\n");
				for(int i = 0; i < ll_len(pArrayList); i++)
				{
					aux = (ePais*) ll_get(pArrayList,i);
					if(aux != NULL)
					{
						fprintf(f,"%d,%s,%d,%d,%d\n",
								aux->id,
								aux->nombre,
								aux->vac1dosis,
								aux->vac2dosis,
								aux->sinVacunar);
					}
					aux = NULL;
				}
				todoOk = 1;
				printf("Archivo nuevo generado con exito.\n");
			}
			fclose(f);
		}
	}

	return todoOk;
}


