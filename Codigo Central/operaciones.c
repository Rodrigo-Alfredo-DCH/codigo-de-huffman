#include "cabecera.h"

Nodo* crearNodo()
{
  Nodo* p = NULL;

  p = (Nodo*)malloc(sizeof(Nodo));

  if( p != NULL )
  {
    p->hi = NULL;
    p->hd = NULL;
  } 

  return p;
}

void asignarValor( Nodo* p, int valor )
{
  p->info.valor = valor;
}

void mostrarArbol( Nodo* raiz )
{
  if( raiz == NULL )
  {
    return;
  }

  printf( "El id es: %d y el valor que tiene es: %d\n", raiz->ID, raiz->info.valor );
  mostrarArbol( raiz->hi );
  mostrarArbol( raiz->hd );
}

int insertarNodo( Nodo** raiz, Nodo* nuevo )
{
  if( (*raiz) != NULL && (*raiz)->ID == nuevo->ID  )
  {
    return -1;
  }

  if( *raiz == NULL )
  {
    *raiz = nuevo;
    return 1;
  }

  if( nuevo->ID < (*raiz)->ID )
  {
    insertarNodo( &((*raiz)->hi ), nuevo );
  }
  else
  {
    insertarNodo( &((*raiz)->hd ), nuevo );
  }
}


int borrarNodo( Nodo** raiz, int ID )
{
  /**Caso base 1. El ID del nodo a eliminar no existe*/
  if( *raiz == NULL )
  {
    return -1;
  }

  /**Caso base 2. Se encontro el ID del nodo que se quiere eliminar
     y se procede a eliminarlo, indicando que su hi tome su lugar
     como primera opcion*/
  if( (*raiz)->ID == ID )
  {
    Nodo* aux = *raiz;
    
    /**Caso 1. El nodo a borrar es una hoja*/
    if( (*raiz)->hi == NULL && (*raiz)->hd == NULL )
    {
      *raiz = NULL;
    }
    /**Caso 2. El nodo a eliminar tiene hi para que tome el lugar del padre*/
    else if( (*raiz)->hi != NULL  )
    {
      *raiz = (*raiz)->hi;
      /**Si el nuevo padre tiene hd, entonces el hd del nodo que se elimino
         se va a insertar como hd del nodo más a la derecha del nuevo arbol*/
      if( (*raiz)->hd != NULL )
      {
        insertarNodo( raiz, aux->hd );
      }
      /**Caso contrario, si el nuevo padre no tiene hd, entonces el hd del nodo
         que se elimino se inserta como hd del nuevo padre*/
      else
      {
        (*raiz)->hd = aux->hd;
      }
    }
    else
    {
      /**Caso 3. Si el nodo a eliminar no tiene hi entonces el hd toma el lugar
         del padre*/
      *raiz = (*raiz)->hd;
    }

    free(aux);
    return 1;
  }

  if( ID < (*raiz)->ID )
  {
    borrarNodo( &((*raiz)->hi), ID );
  }  
  else
  {
    borrarNodo( &((*raiz)->hd), ID );
  }
}
