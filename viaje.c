#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viaje.h"
#include "destino.h"
#include "micro.h"
#include "my_lib.h"

int pedirAltaViaje(eViaje viajes[], int tamV, eMicro vec[], int tam, eDestino destinos[], int tamD, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int* nextId)
{
    int todoOk = 0;
    int indice;
    //int flagAuto = 0;
    eViaje nuevaStruct;
    eFecha fecha;

    if(vec != NULL && tam > 0 && nextId != NULL)
    {
        buscarViajeLibre(viajes, tamV, &indice);
        if(indice == - 1)
        {
            printf("No hay lugar en el sistema\n");
        }
        else
        {
            // aca caigo cuando haya lugar

            mostrarLista(vec, tam, empresas, tamE, tipos, tamT);
            printf("Ingrese id del micro: ");
            scanf_int("%d", &nuevaStruct.idMicro);
            while(!validarMicro(vec, tam, nuevaStruct.idMicro))
            {
                printf("\nId invalida. Reingrese id de empresa: ");
                scanf_int("%d", &nuevaStruct.idMicro);
            }

            listarDestinos(destinos, tamD);
            printf("\nIngrese id de destino: ");
            scanf_int("%d", &nuevaStruct.idDestino);
            while(!validarDestino(destinos, tam, nuevaStruct.idDestino))
            {
                printf("\nId invalida. Reingrese id de destino: ");
                scanf_int("%d", &nuevaStruct.idDestino);
            }

            printf("\nIngrese fecha (dd/mm/aaaa): ");
            if(scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio) == 0)
            {
                __fpurge(stdin);
                printf("Error. Valor no numerico\n");
            }
            while(!validarFecha(fecha))
            {
                printf("Fecha invalida. Reingrese fecha (dd/mm/aaaa): ");
                if(scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio) == 0)
                {
                    __fpurge(stdin);
                    printf("Error. Valor no numerico\n");
                }
            }
            nuevaStruct.fecha = fecha;


            nuevaStruct.isEmpty = 0;
            nuevaStruct.id = *nextId;
            *nextId += 1;

            viajes[indice] = nuevaStruct;
            todoOk = 1;
        }
    }
    return todoOk;
}


int buscarViajeLibre(eViaje vec[], int tam, int* pIndex)
{
    int todoOk = 0;
    if(vec != NULL && tam > 0 && pIndex != NULL)
    {
        *pIndex = -1;
        for(int i=0; i < tam; i++)
        {
            if( vec[i].isEmpty )
            {
                *pIndex = i;
                break;
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int inicializarViajes(eViaje vec[], int tam)
{
    int todoOk = 0;
    if(vec != NULL && tam > 0)
    {
        for(int i=0; i < tam; i++)
        {
            vec[i].isEmpty = 1;
        }
        todoOk = 1;
    }
    return todoOk;
}

int mostrarElementoViaje(eViaje e, char descripcionDestino[])
{
    int todoOk = 0;

    printf("%4d \t    %4d \t    %s \t %02d/%02d/%02d \n",
           e.id,
           e.idMicro,
           descripcionDestino,
           e.fecha.dia,
           e.fecha.mes,
           e.fecha.anio
           );
    todoOk = 1;

    return todoOk;
}


int mostrarListaViajes(eViaje vec[], int tam, eDestino destinos[], int tamD)
{
    int todoOk = 0;
    int flag = 0;
    char descripcionDestino[26];
    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t   Micro \t  Destino\t  Fecha\n");
        printf("------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty )
            {
                cargarDescripcionDestino(destinos, tamD, vec[i].idDestino, descripcionDestino);
                mostrarElementoViaje(vec[i], descripcionDestino);
                flag++;
            }
        }
        if(flag == 0)
        {
            printf("       No hay elementos que mostrar");
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarListaViajesPorMicro(eViaje vec[], int tam, int idMicro, eDestino destinos[], int tamD)
{
    int todoOk = 0;
    int flag = 0;
    char descripcionDestino[26];
    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t   Micro \t  Destino\t  Fecha\n");
        printf("------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty && vec[i].idMicro == idMicro)
            {
                cargarDescripcionDestino(destinos, tamD, vec[i].idDestino, descripcionDestino);
                mostrarElementoViaje(vec[i], descripcionDestino);
                flag++;
            }
        }
        if(flag == 0)
        {
            printf("       No hay elementos que mostrar");
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarListaViajesPorFecha(eViaje vec[], int tam, eFecha fecha, eDestino destinos[], int tamD)
{
    int todoOk = 0;
    int flag = 0;
    char descripcionDestino[26];
    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t   Micro \t  Destino\t  Fecha\n");
        printf("------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty && vec[i].fecha.anio == fecha.anio
                && vec[i].fecha.mes == fecha.mes && vec[i].fecha.dia == fecha.dia)
            {
                cargarDescripcionDestino(destinos, tamD, vec[i].idDestino, descripcionDestino);
                mostrarElementoViaje(vec[i], descripcionDestino);
                flag++;
            }
        }
        if(flag == 0)
        {
            printf("       No hay elementos que mostrar");
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarListaMicrosPorDestino(eViaje vec[], int tam, int idDestino, eDestino destinos[], int tamD)
{
    int todoOk = 0;
    int flag = 0;
    char descripcionDestino[26];
    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t   Micro \t  Destino\t  Fecha\n");
        printf("------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty && vec[i].idDestino == idDestino)
            {
                cargarDescripcionDestino(destinos, tamD, vec[i].idDestino, descripcionDestino);
                mostrarElementoViaje(vec[i], descripcionDestino);
                flag++;
            }
        }
        if(flag == 0)
        {
            printf("       No hay elementos que mostrar");
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int sumaCostosPorMicro(eViaje vec[], int tam, int idMicro, eDestino destinos[], int tamD)
{
    int todoOk = 0;
    int flag = 0;
    float acumuladorPrecio=0;
    int indiceDestino;

    if(vec != NULL && tam > 0)
    {
        for(int i=0; i < tam; i++)
        {
            if(vec[i].idMicro == idMicro)
            {
                buscarPorIdDestino(destinos, tamD, vec[i].idDestino, &indiceDestino);
                acumuladorPrecio += destinos[indiceDestino].precio;
                flag ++;
            }

        }
        if(flag == 0)
        {
            printf("       El micro no realizo ningun viaje.");
        }
        else
        {
            printf("Suma de los costos del micro %d: %.2f\n", idMicro, acumuladorPrecio);

        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}


int buscarViajePorIdDestino(eViaje vec[], int tam, int id, int* indice)
{
    int todoOk = 0;
    if(vec != NULL && tam > 0 && indice != NULL)
    {
        *indice = -1;
        for(int i=0; i < tam; i++)
        {
            if(vec[i].idDestino == id)
            {
                *indice = i;
                break;
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int buscarViajePorIdMicro(eViaje vec[], int tam, int id, int* indice)
{
    int todoOk = 0;
    if(vec != NULL && tam > 0 && indice != NULL)
    {
        *indice = -1;
        for(int i=0; i < tam; i++)
        {
            if(vec[i].idMicro == id)
            {
                *indice = i;
                break;
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int hardcodearEntradasViajes(eViaje vec[], int tam, int cant, int* nextId, int* pFlag)
{

    int todoOk = 0;
    eViaje impostores[] =
    {
        {0, 10000, 20003, {21, 12, 2018}, 0},
        {0, 10001, 20003, {20, 9, 2019}, 0},
        {0, 10002, 20002, {6, 4, 2019}, 0},
        {0, 10003, 20001, {2, 1, 2020}, 0},
        {0, 10003, 20001, {14, 12, 2019}, 0},
        {0, 10000, 20000, {7, 11, 2018}, 0},
        {0, 10000, 20000, {14, 12, 2019}, 0},
        {0, 10003, 20002, {30, 3, 2018}, 0},
        {0, 10001, 20001, {12, 6, 2020}, 0},
        {0, 10002, 20001, {1, 5, 2019}, 0},
    };

    if(vec != NULL && tam > 0 && nextId != NULL && cant > 0 && cant <= 10)
    {

        for(int i=0; i < cant; i++)
        {
            vec[i] = impostores[i];
            vec[i].id = *nextId;
            *nextId += 1;
            *pFlag += 1;
        }
        todoOk = 1;
    }
    return todoOk;

}

int menuInformesViajes()
{
    int opcion;
    printf("0- Informar todos los viajes\n");
    printf("7- Informe  viajes por micro\n");
    printf("8- Informe suma de los costos por micro\n");
    printf("9- Informe viajes por destino elegido\n");
    printf("10- Informe viajes por fecha elegida\n");
    printf("11- Salir\n");
    printf("Ingrese opcion: ");
    if(scanf("%d", &opcion) == 0)
    {
        __fpurge(stdin);
        printf("Error. Valor no numerico.\n");
    }
    while(!validarIntRango(opcion, 0, 11))
    {
        printf("Opcion invalida. Reingrese opcion: ");
        if(scanf("%d", &opcion) == 0)
        {
            __fpurge(stdin);
            printf("Error. Valor no numerico.\n");
        }
    }
    return opcion;
}

int pedirInformesViajes(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, eViaje viajes[], int tamV, eDestino destinos[], int tamD)
{
    int todoOk = 0;
    char salir = 'n';
    //int idEmpresa;
    //int idTipo;
    int idMicro;
    int idDestino;
    eFecha fecha;
    //char descEmpresa[21];
    //char descTipo[21];

    do
    {
        switch(menuInformesViajes())
        {
        case 0:
            system("clear");
            mostrarListaViajes(viajes, tamV, destinos, tamD);
            break;
        case 7:
            system("clear");
            mostrarLista(vec, tam, empresas, tamE, tipos, tamT);
            printf("Ingrese id micro: ");
            scanf_int("%d", &idMicro);
            while(!validarMicro(vec, tam, idMicro))
            {
                printf("Id invalida. Reingrese id de id micro: ");
                scanf_int("%d", &idMicro);
            }
            printf("\n\t\t*** Viajes por micro ***\n");
            mostrarListaViajesPorMicro(viajes, tamV, idMicro, destinos, tamD);
            break;
        case 8:
            system("clear");
            mostrarLista(vec, tam, empresas, tamE, tipos, tamT);
            printf("Ingrese id micro: ");
            scanf_int("%d", &idMicro);
            while(!validarMicro(vec, tam, idMicro))
            {
                printf("Id invalida. Reingrese id de id micro: ");
                scanf_int("%d", &idMicro);
            }
            printf("\n\t\t*** Viajes por micro ***\n");
            sumaCostosPorMicro(viajes, tamV, idMicro, destinos, tamD);
            break;
        case 9:
            system("clear");
            listarDestinos(destinos, tamD);
            printf("Ingrese id destino: ");
            scanf_int("%d", &idDestino);
            while(!validarDestino(destinos, tamD, idDestino))
            {
                printf("Id invalida. Reingrese id de destino: ");
                scanf_int("%d", &idDestino);
            }
            printf("\n\t\t*** Micros por Destino ***\n");
            mostrarListaMicrosPorDestino(viajes, tamV, idDestino, destinos, tamD);
            break;
        case 10:
            system("clear");
            mostrarListaViajes(viajes, tamV, destinos, tamD);
            printf("\nIngrese fecha (dd/mm/aaaa): ");
            if(scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio) == 0)
            {
                __fpurge(stdin);
                printf("Error. Valor no numerico\n");
            }
            while(!validarFecha(fecha))
            {
                printf("Fecha invalida. Reingrese fecha (dd/mm/aaaa): ");
                if(scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio) == 0)
                {
                    __fpurge(stdin);
                    printf("Error. Valor no numerico\n");
                }
            }
            printf("\n\t\t*** Viajes por Fecha ***\n");
            mostrarListaViajesPorFecha(viajes, tamV, fecha, destinos, tamD);
            break;
        case 11:
            salir = 's';
            break;
        }


    }
    while(salir != 's');

    todoOk = 1;
    return todoOk;
}
