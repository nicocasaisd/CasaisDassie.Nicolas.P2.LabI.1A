#ifndef VIAJE_H_INCLUDED
#define VIAJE_H_INCLUDED

#include "fecha.h"
#include "micro.h"
#include "destino.h"

typedef struct{
    int id;
    int idMicro;
    int idDestino;
    eFecha fecha;
    int isEmpty;
}eViaje;

#endif // VIAJE_H_INCLUDED

int pedirAltaViaje(eViaje viajes[], int tamV, eMicro vec[], int tam, eDestino destinos[], int tamD, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int* nextId);
int buscarViajeLibre(eViaje vec[], int tam, int* pIndex);
int inicializarViajes(eViaje vec[], int tam);
int buscarViajePorIdMicro(eViaje vec[], int tam, int id, int* indice);
int buscarViajePorIdDestino(eViaje vec[], int tam, int id, int* indice);
int hardcodearEntradasViajes(eViaje vec[], int tam, int cant, int* nextId, int* pFlag);

// INFORMES
int menuInformesViajes();
int mostrarListaViajes(eViaje vec[], int tam, eDestino destinos[], int tamD);
int mostrarElementoViaje(eViaje e, char descripcionDestino[]);
int pedirInformesViajes(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, eViaje viajes[], int tamV, eDestino destinos[], int tamD);
int mostrarListaViajesPorMicro(eViaje vec[], int tam, int idMicro, eDestino destinos[], int tamD);
int mostrarListaViajesPorFecha(eViaje vec[], int tam, eFecha fecha, eDestino destinos[], int tamD);
int mostrarListaMicrosPorDestino(eViaje vec[], int tam, int idDestino, eDestino destinos[], int tamD);
