#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int valor;
}Datos;

typedef struct nodo
{
  Datos info;
  int ID;
  
  struct nodo* hi;
  struct nodo* hd;
}Nodo;

Nodo* crearNodo();
void asignarValor( Nodo* , int );
void mostrarArbol( Nodo* );
int insertarNodo( Nodo**, Nodo* );
int borrarNodo( Nodo**, int );
