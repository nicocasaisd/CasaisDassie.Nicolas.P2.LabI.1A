#ifndef MICRO_H_INCLUDED
#define MICRO_H_INCLUDED


#include "fecha.h"
#include "empresa.h"
#include "tipo.h"




typedef struct{
    int id;
    int idEmpresa;
    int idTipo;
    int capacidad;
    int isEmpty;
}eMicro;

#endif // MICRO_H_INCLUDED


// MENUS

int menu();
int menuModificar();
int menuInformes();

// ABM

int hardcodearEntradas(eMicro vec[], int tam, int cant, int* nextId, int* pFlag);
int inicializar(eMicro vec[], int tam);
int pedirAlta(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int* nextId);
int pedirBaja(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT);
int pedirModificacion(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT);
int buscarLibre(eMicro vec[], int tam, int* pIndex);
int buscarPorId(eMicro vec[], int tam, int id, int* indice);

// INFORMES

int pedirInformes(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT);
int mostrarElemento(eMicro e, char descEmpresa[], char descTipo[]);
int mostrarLista(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT);
int mostrarListaXEmpresa(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int idEmpresa);
int mostrarListaXTipo(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int idTipo);
int mostrarEmpresaMayorCapacidad(eMicro vec[], int tam, eEmpresa empresas[], int tamE);
int contarMicrosXEmpresaYTipo(eMicro vec[], int tam, int idTipo, int idEmpresa);
float promedioMicrosXEmpresaYTipo(eMicro vec[], int tam, int idTipo, int idEmpresa);
int promedioMicrosVip(eMicro vec[], int tam, eEmpresa empresas[], int tamE);
int mostrarEmpresaMenorCantidadMicros(eMicro vec[], int tam, eEmpresa empresas[], int tamE);

// ORDENAR
int ordenarElementosEmpresaXCapacidad(eMicro vec[], int tam);

// VALIDAR
int validarCapacidad(int cap);
int validarMicro(eMicro vec[], int tam, int id);



