#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paises.h"
#include "LinkedList.h"
#include "Controller.h"

//typedef struct{
//    int id;
//    char nombre[20];
//    int vac1dosis;
//    int vac2dosis;
//    int sinVacunar;
//}ePais;


ePais* paises_newParametros(char* idStr, char* nombreStr, char* vac1dosisStr, char* vac2dosisStr, char* sinVacunarStr){

    ePais* nuevo =  (ePais*) malloc(sizeof(ePais));

    if(nuevo != NULL && idStr != NULL &&
       nombreStr != NULL && vac1dosisStr != NULL &&
       vac2dosisStr != NULL && sinVacunarStr != NULL)
    {
        if(!(pais_setId(nuevo, atoi(idStr)) &&
           pais_setNombre(nuevo, nombreStr) &&
           pais_setvac1dosis(nuevo, atoi(vac1dosisStr)) &&
           pais_setvac2dosis(nuevo, atoi(vac2dosisStr)) &&
           pais_setsinVacunar(nuevo, atoi(sinVacunarStr))
           ))
        {
            pais_delete(nuevo);
            nuevo = NULL;
        }
    }
    return nuevo;
}

void pais_delete(ePais* this){
    free(this);
}

//////////////////////////////////////////////////////////// FUNCIONES SETTER ///////////////////////////////////////////



int pais_setId(ePais* this,int id){
    int todoOk = 0;
    if(this != NULL && id > 0)
    {
        this->id = id;
        todoOk = 1;
    }

    return todoOk;
}

int pais_setNombre(ePais* this,char* nombre){
    int todoOk = 0;
    if(this != NULL && nombre != NULL && strlen(nombre) < 30 && strlen(nombre) >= 2)
    {
        strcpy(this->nombre, nombre);
        todoOk = 1;
    }

    return todoOk;

}

int pais_setvac1dosis(ePais* this, int vac1dosis){
    int todoOk = 0;
    if(this != NULL && vac1dosis >= 0)
    {
        this->vac1dosis = vac1dosis;
        todoOk = 1;
    }
    return todoOk;
}

int pais_setvac2dosis(ePais* this, int vac2dosis){
    int todoOk = 0;
    if(this != NULL && vac2dosis >= 0)
    {
        this->vac2dosis= vac2dosis;
        todoOk = 1;
    }
    return todoOk;

}

int pais_setsinVacunar(ePais* this, int sinVacunar){
    int todoOk = 0;
    if(this != NULL && sinVacunar >= 0)
    {
        this->sinVacunar = sinVacunar;
        todoOk = 1;
    }

    return todoOk;
}

///////////////////////////////////////////////////////////// FUNCIONES GETTER ///////////////////////////////////////////


int pais_getId(ePais* this,int* id){
    int todoOk = 0;
    if(this != NULL && id != NULL)
    {
        *id = this->id;
        todoOk = 1;
    }
    return todoOk;
}

int pais_getNombre(ePais* this,char* nombre)
{
    int todoOk = 0;
    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        todoOk = 1;
    }
    return todoOk;
}

int pais_getvac1dosis(ePais* this, int* vac1dosis){
    int todoOk = 0;
    if(this != NULL && vac1dosis != NULL)
    {
        *vac1dosis = this->vac1dosis;
        todoOk = 1;
    }
    return todoOk;
}

int pais_getvac2dosis(ePais* this,int* vac2dosis){
    int todoOk = 0;
    if(this != NULL && vac2dosis != NULL)
    {
        *vac2dosis = this->vac2dosis;
        todoOk = 1;
    }
    return todoOk;
}

int pais_getsinVacunar(ePais* this,int* sinVacunar){
    int todoOk = 0;
    if(this != NULL && sinVacunar != NULL)
    {
        *sinVacunar = this->sinVacunar;
        todoOk = 1;
    }
    return todoOk;
}

void* asignarPaises(void* element){
    //srand(time(NULL));

    int unaDosis;
    int dosDosis;
    int sinVacunar;

    int minunaDosis = 1;
    int maxunaDosis = 60;
    int mindosDosis = 1;
    int maxdosDosis = 40;

    if(element != NULL){
        unaDosis = rand() % (maxunaDosis - minunaDosis + 1) + minunaDosis;
        dosDosis = rand() % (maxdosDosis - mindosDosis + 1) + mindosDosis;

        sinVacunar = 100 - unaDosis - dosDosis;

        ((ePais *)element)->vac1dosis = unaDosis;
        ((ePais *)element)->vac2dosis = dosDosis;
        ((ePais *)element)->sinVacunar = sinVacunar;
    }
}

int paisesExitosos(void* element){

    int agregar = 0;
    int porcentajeDosDosis = 30;

    if(element != NULL){

        if((((ePais *)element)->vac2dosis) > porcentajeDosDosis){
            agregar = 1;
        }

    }
    return agregar;
}

int paisesEnElHorno(void* element){

    int agregar = 0;
    int vacunados;
    int sinVacunar;

    if(element != NULL){
        sinVacunar = ((ePais *)element)->sinVacunar;
        vacunados = ((ePais *)element)->vac1dosis + ((ePais *)element)->vac2dosis;

        if(sinVacunar > vacunados){
            agregar = 1;
        }
    }
    return agregar;
}

int ordenarVacunacion(void* cantUno, void* cantDos)
{
	int ordenar = 0;
	ePais* emp1;
	ePais* emp2;

	if(cantUno != NULL && cantDos != NULL)
	{
		emp1 = (ePais*) cantUno;
		emp2 = (ePais*) cantDos;

		if(emp1->sinVacunar > emp2->sinVacunar)
		{
			ordenar = 1;
		}
		else
		{
			if(emp1->sinVacunar < emp2->sinVacunar)
			{
				ordenar = -1;
			}
		}
	}
	return ordenar;
}

int masCastigados(LinkedList* lista){

    int todoOk = 0;
	ePais* aux = NULL;
	ePais* auxDos = NULL;
	ePais* auxmayor = NULL;

	if(lista != NULL){
        ll_sort(lista, ordenarVacunacion, 0);
        auxmayor = (ePais*) ll_get(lista,0);

        printf("Pais/es con mayor cantidad sin vacunar: \n");
        printf("Pais: %s, cantidad sin vacunar: %d\n", auxmayor->nombre, auxmayor->sinVacunar);

        // en caso de que haya empate

        for (int i = 0; i < ll_len(lista); i++ )
        {
            auxDos = (ePais*) ll_get(lista,i);
            if(auxmayor->id != auxDos->id && auxmayor->sinVacunar == auxDos->sinVacunar)
            {
               printf("Pais: %s, cantidad sin vacunar: %d\n", auxDos->nombre, auxDos->sinVacunar);
            }
        }

	/*
	if(lista != NULL)
	{
		for(int i = 0; i < ll_len(lista) ; i++)
		{
			aux = (ePais*) ll_get(lista,i);
			if(i == 0 || (aux + i)->sinVacunar > auxmayor->sinVacunar)
			{
				auxmayor = aux;
			}
		}

		printf("Pais/es con mayor cantidad de sin vacunar: \n");
        printf("Pais: %s, cantidad sin vacunar: %d\n", auxmayor->nombre, auxmayor->sinVacunar);

        // en caso de que haya empate
		for (int i = 0; i < ll_len(lista); i++ )
        {
            auxDos = (ePais*) ll_get(lista,i);
            if(auxmayor->id != auxDos->id && auxmayor->sinVacunar == auxDos->sinVacunar)
            {
               printf("Pais: %s, cantidad sin vacunar: %d\n", auxDos->nombre, auxDos->sinVacunar);
            }
        }

        */
		todoOk = 1;
	}
	return todoOk;
}


