#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "paises.h"
#include <time.h>


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this != NULL){
       this->pFirstNode = NULL;
       this->size = 0;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL){
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNodoRetorno = NULL;
    int tam = ll_len(this);
    if(this != NULL && nodeIndex >= 0 && nodeIndex < tam){
        pNodoRetorno = this->pFirstNode; // direccion del primer vagon

        // si nodeIndex es mayor a 0, recorro el resto
        while(nodeIndex > 0){
            pNodoRetorno = pNodoRetorno->pNextNode;
            nodeIndex--;
        }
    }
    return pNodoRetorno;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNuevoNodo = NULL;
    Node* pPrevNodo = NULL;
    // no validamos pElement para que sea distinto de NULL para poder cargar un nuevo vagon vacio en caso de que se quiera
    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this)){
        pNuevoNodo = (Node*) malloc(sizeof(Node));
        if(pNuevoNodo != NULL){
            pNuevoNodo->pElement = pElement;

            if(nodeIndex == ll_len(this)){
                // si quiere agregar el nodo en el ultimo vagon
                pNuevoNodo->pNextNode = NULL;
            }else{
                // si NO quiere agregar el nodo en el ultimo vagon
                pNuevoNodo->pNextNode = getNode(this, nodeIndex);
            }

            if(nodeIndex == 0){
                this->pFirstNode = pNuevoNodo;
            }else{
                pPrevNodo = getNode(this, nodeIndex -  1);
                pPrevNodo->pNextNode = pNuevoNodo;
            }
            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL){
        if(!addNode(this, ll_len(this), pElement))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Devuelve el elemento guardado en la lista en el indice especificado
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* aux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this)){

        aux = getNode(this, index);
        if(aux != NULL){
            returnAux = aux->pElement;
            aux = NULL;
        }
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* aux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this)){
        aux = getNode(this, index);
        if(aux != NULL){
            aux->pElement = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pAuxNode = NULL;
    Node* pNodoAnt = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this)){
        pAuxNode = getNode(this, index);
        if(index == 0){

            this->pFirstNode = pAuxNode->pNextNode;

        }else{
            pNodoAnt = getNode(this, index - 1);
            pNodoAnt->pNextNode = pAuxNode->pNextNode;
        }
        free(pAuxNode);
        this->size--;
        returnAux = 0;

    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int flag = 1;
    if(this != NULL){
            // recorremos el array de atras para adelante
        for (int i = ll_len(this) -1; i >= 0; i-- ){
           if(ll_remove(this, i) == -1){
            flag = 0;
            break;
           }
        }
        if(flag){
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL){
        if(!ll_clear(this)){
            free(this);
        }
    returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int tam = ll_len(this);
    if(this != NULL){
        for (int i = 0; i < tam; i++ ){
            if(ll_get(this, i) == pElement)
            returnAux = i;
            break;
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL){
        if(ll_len(this)){
            returnAux = 0;
        }else{
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= ll_len(this)){
        if(addNode(this,index, pElement) == 0){
            returnAux = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this)){
        returnAux = ll_get(this, index);
        ll_remove(this, index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL){
        returnAux = 0;
        if(ll_indexOf(this, pElement) == -1){
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int tam;

    if(this != NULL && this2 != NULL){
        tam = ll_len(this2);
        returnAux = 1;
        for (int i = 0; i < tam ;i++ ){
            if(!ll_contains(this, ll_get(this2, i))){
               returnAux = 0;
               break;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int tam = ll_len(this);

    if(this != NULL && from >= 0 && from < tam && to > from && to <= tam ){
        cloneArray = ll_newLinkedList();
        if(cloneArray != NULL){
            for (int i = from; i < to ; i++ ){
                ll_add(cloneArray, ll_get(this, i));
            }
        }

    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL){
        cloneArray = ll_subList(this, 0, ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int tam;
    void* auxI = NULL;
    void* auxJ = NULL;
    void* aux = NULL;

    if(this != NULL && pFunc != NULL && order >= 0 && order <= 1){
        tam = ll_len(this);
       for (int i = 0; i< tam -1 ; i++ ){
            for (int j = i+1; j < tam ;j++ ){
                auxI = ll_get(this, i);
                auxJ = ll_get(this, j);
                if((pFunc(auxI, auxJ) > 0 && order ) ||
                   (pFunc(auxI, auxJ) < 0 && !order)){
                aux = auxI;
                ll_set(this, i, auxJ);
                ll_set(this, j, aux);
                }
            }
            returnAux = 0;
        }
    }

    return returnAux;

}

/** \brief mapeado de los elementos de una lista
 *
 * \param *pFunc - funcion encargada de hacer el mapeo
 * \return LinkedList* this - linkedlist mapeado
 *
 */
LinkedList* ll_map (LinkedList* this, void*(*pFunc) (void* element)){

    LinkedList* resultado = NULL;
    Node* auxNode = NULL;

    if(this != NULL && pFunc != NULL){
        resultado = ll_newLinkedList();
        for (int i = 0; i< ll_len(this) ;i++ ){
            auxNode = pFunc((ePais*) ll_get(this, i));
            ll_add(resultado, auxNode);
        }
    }
    if(resultado != NULL){
        printf("Paises mapeados con exito.\n");
    }else{
        printf("Hubo un error al hacer el mapeo.\n");
    }
    return resultado;
}

/** \brief Filtrado de linkedlist a traves de una funcion que pasamos por parametro
 *
 * \param this LinkedList* - linkedlist a filtrar
 * \param (*pFunc int - funcion para hacer el filtrado
 * \return LinkedList* - nueva linkedlist filtrada
 *
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc) (void* element)){

    LinkedList* resultado = NULL;
    int aux;

    if(this != NULL && pFunc != NULL){
        resultado = ll_newLinkedList();
        for (int i = 0; i< ll_len(this) ;i++ ){
            aux = pFunc((ePais*) ll_get(this, i));
            if(aux == 1){
                ll_add(resultado,(ePais*) ll_get(this, i));
            }
        }
    }
    if(resultado != NULL){
        printf("Paises filtrados con exito.\n");
    }else{
        printf("Hubo un error al filtrar.\n");
    }
    return resultado;

}


