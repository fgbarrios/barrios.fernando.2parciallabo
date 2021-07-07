#include "LinkedList.h"
#ifndef PAISES_H_INCLUDED
#define PAISES_H_INCLUDED

typedef struct{
    int id;
    char nombre[20];
    int vac1dosis;
    int vac2dosis;
    int sinVacunar;
}ePais;


#endif // PAISES_H_INCLUDED

ePais* paises_newParametros(char* idStr, char* nombreStr, char* vac1dosisStr, char* vac2dosisStr, char* sinVacunarStr);
void pais_delete(ePais* this);

int pais_setId(ePais* this,int id);
int pais_setNombre(ePais* this,char* nombre);
int pais_setvac1dosis(ePais* this, int vac1dosis);
int pais_setvac2dosis(ePais* this, int vac2dosis);
int pais_setsinVacunar(ePais* this, int sinVacunar);

int pais_getId(ePais* this,int* id);
int pais_getNombre(ePais* this,char* nombre);
int pais_getvac1dosis(ePais* this, int* vac1dosis);
int pais_getvac2dosis(ePais* this,int* vac2dosis);
int pais_getsinVacunar(ePais* this,int* sinVacunar);

void* asignarPaises(void* element);
int paisesExitosos(void* element);
int paisesEnElHorno(void* element);
int ordenarVacunacion(void* cantUno, void* cantDos);
int masCastigados(LinkedList* lista);
