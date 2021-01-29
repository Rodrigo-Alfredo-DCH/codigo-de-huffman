#include "cabecera.h"

int main()
{
  Nodo* arbol = NULL, *nuevo = NULL;
  int ID;
  
  nuevo = crearNodo();
  if( nuevo != NULL )
  {
    nuevo->ID = 8;
    asignarValor( nuevo, 30 );
    if( insertarNodo( &arbol, nuevo ) != -1 )
    {
      printf( "Insercion exitosa...\n" );
    }
    else
    {
      printf( "No se pudo insertar el nodo con ID: %d\n", nuevo->ID );
    }
    mostrarArbol( arbol );
  }

  nuevo = crearNodo();
  if( nuevo != NULL )
  {
    nuevo->ID = 5;
    asignarValor( nuevo, 60 );
    if( insertarNodo( &arbol, nuevo ) != -1 )
    {
      printf( "Insercion exitosa...\n" );
    }
    else
    {
      printf( "No se pudo insertar el nodo con ID: %d\n", nuevo->ID );
    }
    mostrarArbol( arbol );
  }

  nuevo = crearNodo();
  if( nuevo != NULL )
  {
    nuevo->ID = 10;
    asignarValor( nuevo, -34 );
    if( insertarNodo( &arbol, nuevo ) != -1 )
    {
      printf( "Insercion exitosa...\n" );
    }
    else
    {
      printf( "No se pudo insertar el nodo con ID: %d\n", nuevo->ID );
    }
    mostrarArbol( arbol );
  }

  nuevo = crearNodo();
  if( nuevo != NULL )
  {
    nuevo->ID = 25;
    asignarValor( nuevo, 100 );
    if( insertarNodo( &arbol, nuevo ) != -1 )
    {
      printf( "Insercion exitosa...\n" );
    }
    else
    {
      printf( "No se pudo insertar el nodo con ID: %d\n", nuevo->ID );
    }
    mostrarArbol( arbol );
  }

  nuevo = crearNodo();
  if( nuevo != NULL )
  {
    nuevo->ID = 20;
    asignarValor( nuevo, -200 );
    if( insertarNodo( &arbol, nuevo ) != -1 )
    {
      printf( "Insercion exitosa...\n" );
    }
    else
    {
      printf( "No se pudo insertar el nodo con ID: %d\n", nuevo->ID );
    }
    mostrarArbol( arbol );
  }

  nuevo = crearNodo();
  if( nuevo != NULL )
  {
    nuevo->ID = 2;
    asignarValor( nuevo, 11 );
    if( insertarNodo( &arbol, nuevo ) != -1 )
    {
      printf( "Insercion exitosa...\n" );
    }
    else
    {
      printf( "No se pudo insertar el nodo con ID: %d\n", nuevo->ID );
    }
    mostrarArbol( arbol );
  }

  ID = 8;
  if( borrarNodo( &arbol, ID ) != -1 )
  {
    printf( "Eliminación exitosa...\n" );
  }
  else
  {
    printf( "No se pudo eliminar el nodo con ID: %d\n", ID );
  }
  mostrarArbol( arbol );

  return 1;
}
