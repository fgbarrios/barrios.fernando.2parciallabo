#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LinkedList.h"
#include "Controller.h"
#include "parser.h"
#include "paises.h"
#include "extras.h"


int main()
{

    srand(time(NULL));
    char salir = 'n';
    int flag = 0;
    int flagEstadisticas = 0;
    char path[20];

    LinkedList* lista = ll_newLinkedList();
    LinkedList* exitosos = ll_newLinkedList();
    LinkedList* paisesHorno = ll_newLinkedList();

    if(lista == NULL){
        printf("Error.No se pudo crear la lista.\n");
        exit(1);
    }

    do{
        switch(menu())
        {
            case 1:
                system("cls");
                printf("Ingrese PATH (vacunas.csv): ");
                fflush(stdin);
                gets(path);
                while(strcmp(path, "vacunas.csv")){
                    printf("Error. Ingrese PATH correcto(vacunas.csv): ");
                    gets(path);
                }
                controller_loadFromText(path,lista);
                flag = 1;

            break;

            case 2: //Listar paises
                system("cls");
                if(flag == 1){
                    controller_ListPaises(lista);
                }else{
                    printf("Primero debes cargar los paises desde el texto (opcion 1).\n");
                }

            break;

            case 3: //Asignar estadisticas
                system("cls");
                if(flag == 1){

                    ll_map(lista, asignarPaises);
                    flagEstadisticas = 1;

                }else{
                    printf("Primero debes cargar los paises desde el texto (opcion 1).\n");
                }
            break;

            case 4: //Filtrar EXITOSOS
                system("cls");
                if(flag == 1 && flagEstadisticas == 1){
                    exitosos = ll_filter(lista, paisesExitosos);
                    printf("Lista de paises Exitosos (paises con personas vacunadas con dos dosis en un porcentaje mayor al 30%).\n\n");
                    if(exitosos != NULL && ll_len(exitosos) > 0){
                        controller_ListPaises(exitosos);
                        printf("\n");
                        controller_saveAsText("exitosos.csv", exitosos);
                    }else{
                        printf("No hay paises exitosos.\n");
                    }
                }else{
                    printf("Primero debes cargar los paises desde el texto (opcion 1) y cargar las estadisticas (opcion 3).\n");
                }
            break;

            case 5: //Filtrar PAISES EN EL HORNO
                system("cls");
                if(flag == 1 && flagEstadisticas == 1){
                    paisesHorno = ll_filter(lista, paisesEnElHorno);
                    printf("Lista de paises En El Horno (paises donde la cantidad de no vacunados es mayor a la de vacunados).\n\n");
                    if(paisesHorno != NULL && ll_len(paisesHorno) > 0){
                        controller_ListPaises(paisesHorno);
                        printf("\n");
                        controller_saveAsText("paiseshorno.csv", paisesHorno);
                    }else{
                        printf("No hay paises en el horno.\n");
                    }
                }else{
                    printf("Primero debes cargar los paises desde el texto (opcion 1) y cargar las estadisticas (opcion 3).\n");
                }
            break;

            case 6: //ORDENAR POR NIVEL DE VACUNACION
                system("cls");

                if(flag == 1 && flagEstadisticas == 1){
                        printf("Lista de paises ordenados por nivel de vacunacion.\n\n");
                        ll_sort(lista, ordenarVacunacion, 1);
                        controller_ListPaises(lista);
                }else{
                    printf("Primero debes cargar los paises desde el texto (opcion 1) y cargar las estadisticas (opcion 3).\n");
                }
            break;

            case 7: //MAS CASTIGADO
                system("cls");
                if(flag == 1 && flagEstadisticas == 1){
                   printf("Lista de paises mas castigados.\n\n");
                   masCastigados(lista);
                }else{
                    printf("Primero debes cargar los paises desde el texto (opcion 1) y cargar las estadisticas (opcion 3).\n");
                }
            break;

            case 8: // Salir
            salir = confirmar();
            if(salir == 's'){
                ll_deleteLinkedList(lista);
                ll_deleteLinkedList(exitosos);
                ll_deleteLinkedList(paisesHorno);
            }
            break;

        default:
            printf("Opcion invalida!\n");
            break;
        }

        system("pause");
    }while(salir == 'n');
    return 0;
}
