#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_lib.h"
#include "micro.h"
#include "fecha.h"
#include "my_lib.h"
#include "viaje.h"


int menu()
{
    int opcion;

    printf(" *** Menu de opciones ***\n\n");
    printf("1- Alta \n");
    printf("2- Modificacion \n");
    printf("3- Baja \n");
    printf("4- Informes micros (punto 1 al 6) \n");
    printf("5- Listar Empresas \n");
    printf("6- Listar Tipos \n");
    printf("7- Listar Destinos \n");
    printf("8- Alta Viaje \n");
    printf("9- Informes Viajes (punto 7 en adelante) \n");
    printf("10- Salir \n\n");
    printf("Ingrese opcion: ");
    if(scanf("%d", &opcion) == 0)
    {
        __fpurge(stdin);
        printf("Error. Valor no numerico.\n");
    }
    while(opcion < 1 || opcion > 10)
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

int menuModificar()
{
    int opcion;
    printf("     *** Campos a modificar ***\n");
    printf("1- Tipo\n");
    printf("2- Capacidad\n");
    printf("3- Salir\n");
    printf("Ingrese opcion: ");
    if(scanf("%d", &opcion) == 0)
    {
        __fpurge(stdin);
        printf("Error. Valor no numerico.\n");
    }
    while(opcion < 1 || opcion > 3)
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

int menuInformes()
{
    int opcion;
    printf("0- Informar todos los micros\n");
    printf("1- Informe  micros por empresa\n");
    printf("2- Informe micros por tipo\n");
    printf("3- Informe promedio de micros VIP sobre total por empresa\n");
    printf("4- Informe todos los micros separados por empresa\n");
    printf("5- Informe empresa con mayor capacidad de transporte\n");
    printf("6- Informe empresa con menor cantidad de micros\n");
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

int hardcodearEntradas(eMicro vec[], int tam, int cant, int* nextId, int* pFlag)
{

    int todoOk = 0;
    eMicro impostores[] =
    {
        {0, 1000, 5003, 23, 0},
        {0, 1001, 5003, 45, 0},
        {0, 1002, 5002, 10, 0},
        {0, 1003, 5001, 25, 0},
        {0, 1003, 5001, 50, 0},
        {0, 1000, 5000, 45, 0},
        {0, 1000, 5000, 34, 0},
        {0, 1003, 5002, 36, 0},
        {0, 1001, 5001, 25, 0},
        {0, 1002, 5001, 49, 0},
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

int inicializar(eMicro vec[], int tam)
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

int buscarLibre(eMicro vec[], int tam, int* pIndex)
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


int pedirAlta(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int* nextId)
{
    int todoOk = 0;
    int indice;
    eMicro nuevaStruct;

    if(vec != NULL && tam > 0 && nextId != NULL)
    {
        buscarLibre(vec, tam, &indice);
        if(indice == - 1)
        {
            printf("No hay lugar en el sistema\n");
        }
        else
        {
            // aca caigo cuando haya lugar
            listarEmpresas(empresas, tamE);
            printf("\nIngrese id de empresa: ");
            scanf_int("%d", &nuevaStruct.idEmpresa);
            while(!validarEmpresa(empresas, tamE, nuevaStruct.idEmpresa))
            {
                printf("\nId invalida. Reingrese id de empresa: ");
                scanf_int("%d", &nuevaStruct.idEmpresa);
            }

            listarTipos(tipos, tamT);
            printf("\nIngrese id de tipo: ");
            scanf_int("%d", &nuevaStruct.idTipo);
            while(!validarTipo(tipos, tamT, nuevaStruct.idTipo))
            {
                printf("\nId invalida. Reingrese id de tipo: ");
                scanf_int("%d", &nuevaStruct.idTipo);
            }

            printf("Ingrese capacidad del micro: ");
            __fpurge(stdin);
            scanf_int("%d", &nuevaStruct.capacidad);
            while(!validarCapacidad(nuevaStruct.capacidad))
            {
                printf("\nCapacidad invalida. Reingrese capacidad: ");
                scanf_int("%d", &nuevaStruct.capacidad);
            }

            nuevaStruct.isEmpty = 0;
            nuevaStruct.id = *nextId;
            *nextId += 1;

            vec[indice] = nuevaStruct;
            todoOk = 1;
        }
    }
    return todoOk;
}

int mostrarElemento(eMicro e, char descEmpresa[], char descTipo[])
{
    int todoOk = 0;

    printf("%4d  \t   %10s \t   %10s \t     %4d \n",
           e.id,
           descEmpresa,
           descTipo,
           e.capacidad
          );
    todoOk = 1;

    return todoOk;
}


int mostrarLista(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT)
{
    int todoOk = 0;
    char descEmpresa[21];
    char descTipo[21];

    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t    Empresa \t        Tipo \t  Capacidad\n");
        printf("-----------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty )
            {
                cargarDescripcionEmpresa(empresas, tamE, vec[i].idEmpresa, descEmpresa);
                cargarDescripcionTipo(tipos, tamT, vec[i].idTipo, descTipo);
                mostrarElemento(vec[i], descEmpresa, descTipo);
            }
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarListaXEmpresa(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int idEmpresa)
{
    int todoOk = 0;
    char descEmpresa[21];
    char descTipo[21];

    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t    Empresa \t        Tipo \t  Capacidad\n");
        printf("-----------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty && vec[i].idEmpresa == idEmpresa)
            {
                cargarDescripcionEmpresa(empresas, tamE, vec[i].idEmpresa, descEmpresa);
                cargarDescripcionTipo(tipos, tamT, vec[i].idTipo, descTipo);
                mostrarElemento(vec[i], descEmpresa, descTipo);
            }
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarListaEmpresas(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT)
{
    int todoOk = 0;

    if(vec != NULL && tam > 0)
    {
        for(int i= 0; i < tamE; i++)
        {
                mostrarListaXEmpresa(vec, tam, empresas, tamE, tipos, tamT, empresas[i].id);
                //printf("\n\n");
        }

        todoOk = 1;
    }
    return todoOk;
}

int mostrarListaXTipo(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT, int idTipo)
{
    int todoOk = 0;
    char descEmpresa[21];
    char descTipo[21];

    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        printf(" Id  \t    Empresa \t        Tipo \t  Capacidad\n");
        printf("-----------------------------------------------------\n");
        for(int i=0; i < tam; i++)
        {
            if( !vec[i].isEmpty && vec[i].idTipo == idTipo)
            {
                cargarDescripcionEmpresa(empresas, tamE, vec[i].idEmpresa, descEmpresa);
                cargarDescripcionTipo(tipos, tamT, vec[i].idTipo, descTipo);
                mostrarElemento(vec[i], descEmpresa, descTipo);
            }
        }
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarEmpresaMayorCapacidad(eMicro vec[], int tam, eEmpresa empresas[], int tamE)
{
    int todoOk = 0;
    char descEmpresa[21];
    int idEmpresaMax;
    int capacidadMax;
    int acumulador;

    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        for(int e=0; e<tamE; e++)
        {
            acumulador = 0;

            for(int m=0; m < tam; m++)
            {
                if(vec[m].idEmpresa == empresas[e].id)
                {
                    acumulador += vec[m].capacidad;
                }
            }
            if(e==0 || acumulador > capacidadMax)
            {
                idEmpresaMax = empresas[e].id;
                capacidadMax = acumulador;
            }
        }
        cargarDescripcionEmpresa(empresas, tamE, idEmpresaMax, descEmpresa);
        printf("Empresa con mayor capacidad acumulada: %s\n", descEmpresa);
        printf("Capacidad: %d\n", capacidadMax);
        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int mostrarEmpresaMenorCantidadMicros(eMicro vec[], int tam, eEmpresa empresas[], int tamE)
{
    int todoOk = 0;
    char descEmpresa[21];
    int minimoCantidad;
    int contador;

    if(vec != NULL && tam > 0)
    {
        //system("clear");
        //printf("          *** Lista ***\n\n");
        for(int e=0; e<tamE; e++)
        {
            contador = 0;

            for(int m=0; m < tam; m++)
            {
                if(vec[m].idEmpresa == empresas[e].id)
                {
                    contador ++;
                }
            }
            if(e==0 || contador < minimoCantidad)
            {
                minimoCantidad = contador;
            }
        }

        for(int e=0; e<tamE; e++)
        {
            contador = 0;

            for(int m=0; m < tam; m++)
            {
                if(vec[m].idEmpresa == empresas[e].id)
                {
                    contador ++;
                }
            }
            if(contador == minimoCantidad)
            {
                cargarDescripcionEmpresa(empresas, tamE, empresas[e].id, descEmpresa);
                printf("Empresa con menor cantidad de micros: %s\n", descEmpresa);

            }
        }
        printf("Cantidad: %d\n", minimoCantidad);

        printf("\n\n");

        todoOk = 1;
    }
    return todoOk;
}

int contarMicrosXEmpresaYTipo(eMicro vec[], int tam, int idTipo, int idEmpresa)
{
    int todoOk = 0;
    int cantidad=0;

    if(vec != NULL && tam > 0)
    {
        for(int i=0; i<tam; i++)
        {
            if(vec[i].idEmpresa == idEmpresa && vec[i].idTipo == idTipo)
            {
                cantidad ++;
            }
        }
        printf("Cantidad de micros: %d\n", cantidad);

        todoOk = 1;
    }
    return todoOk;
}

float promedioMicrosXEmpresaYTipo(eMicro vec[], int tam, int idTipo, int idEmpresa)
{
    float promedio = 0;
    int cantidadEmpresa=0;
    int cantidadVip=0;

    if(vec != NULL && tam > 0)
    {
        for(int i=0; i<tam; i++)
        {
            if(vec[i].idEmpresa == idEmpresa)
            {
                cantidadEmpresa ++;
                if(vec[i].idTipo == idTipo)
                {
                    cantidadVip ++;
                }
            }
        }

    }
    if(cantidadEmpresa != 0)
    {
        promedio = (float)cantidadVip / cantidadEmpresa;
    }
    return promedio;
}

int promedioMicrosVip(eMicro vec[], int tam, eEmpresa empresas[], int tamE)
{
    int todoOk = 0;
    float promedio;
    char descEmpresa[21];

    if(vec != NULL && tam > 0)
    {
        for(int i=0; i<tamE; i++)
        {
            promedio = promedioMicrosXEmpresaYTipo(vec, tam, 5003, empresas[i].id);
            cargarDescripcionEmpresa(empresas, tamE, empresas[i].id, descEmpresa);
            printf("Promedio de micros Vip de la empresa %s: %.2f\n", descEmpresa, promedio);
        }
        todoOk = 1;
    }
    return todoOk;
}


int buscarPorId(eMicro vec[], int tam, int id, int* indice)
{
    int todoOk = 0;
    if(vec != NULL && tam > 0 && indice != NULL)
    {
        *indice = -1;
        for(int i=0; i < tam; i++)
        {
            if(!vec[i].isEmpty && vec[i].id == id)
            {
                *indice = i;
                break;
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int pedirBaja(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT)
{
    int todoOk = 0;
    int indice;
    int id;
    char confirma;
    char descEmpresa[21];
    char descTipo[21];
    if(vec != NULL && tam > 0)
    {
        mostrarLista(vec, tam, empresas, tamE, tipos, tamT);
        printf("Ingrese id: ");
        scanf_int("%d", &id);
        buscarPorId(vec, tam, id, &indice);

        if(indice == -1)
        {
            printf("No hay un elemento con id %d\n", id);
        }
        else
        {
            cargarDescripcionEmpresa(empresas, tamE, vec[indice].idEmpresa, descEmpresa);
            cargarDescripcionTipo(tipos, tamT, vec[indice].idTipo, descTipo);
            mostrarElemento(vec[indice], descEmpresa, descTipo);
            printf("Confirma baja? (S/s): ");
            __fpurge(stdin);
            scanf("%c", &confirma);
            if(confirma != 'S' && confirma != 's')
            {
                printf("Baja cancelada por el usuario\n");
            }
            else
            {
                vec[indice].isEmpty = 1;
                printf("Baja realizada con exito!!!\n");
                todoOk = 1;
            }
        }
    }
    return todoOk;
}

int pedirModificacion(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT)
{
    int todoOk = 0;
    int indice;
    int id;
    char descEmpresa[21];
    char descTipo[21];
    char salir = 'n';
    if(vec != NULL && tam > 0)
    {
        mostrarLista(vec, tam, empresas, tamE, tipos, tamT);
        printf("Ingrese id: ");
        scanf_int("%d", &id);
        if( buscarPorId(vec, tam, id, &indice))
        {
            if(indice == -1)
            {
                printf("No hay un micro con id %d\n", id);
            }
            else
            {
                cargarDescripcionEmpresa(empresas, tamE, vec[indice].idEmpresa, descEmpresa);
                cargarDescripcionTipo(tipos, tamT, vec[indice].idTipo, descTipo);
                mostrarElemento(vec[indice], descEmpresa, descTipo);
                do
                {
                    switch(menuModificar())
                    {

                    case 1:
                        listarTipos(tipos, tamT);
                        printf("Ingrese nuevo tipo: ");
                        scanf_int("%d", &vec[indice].idTipo);
                        while(!validarTipo(tipos, tamT, vec[indice].idTipo))
                        {
                            printf("Id invalida. Reingrese id de tipo: ");
                            scanf_int("%d", &vec[indice].idTipo);
                        }
                        printf("Se ha modificado el tipo\n");
                        break;
                    case 2:
                        printf("Ingrese nueva capacidad: ");
                        scanf_int("%d", &vec[indice].capacidad);
                        while(!validarCapacidad(vec[indice].capacidad))
                        {
                            printf("Capacidad invalida. Reingrese capacidad: ");
                            scanf_int("%d", &vec[indice].capacidad);
                        }
                        printf("Se ha modificado la capacidad\n");
                        break;
                    case 3:
                        salir = 's';
                        break;
                    }
                }
                while(salir != 's');
            }
        }
        else
        {
            printf("Ocurrio un problema al buscar el micro\n");
        }

        todoOk = 1;
    }
    return todoOk;
}

int pedirInformes(eMicro vec[], int tam, eEmpresa empresas[], int tamE, eTipo tipos[], int tamT)
{
    int todoOk = 0;
    char salir = 'n';
    int idEmpresa;
    int idTipo;
    //char descEmpresa[21];
    //char descTipo[21];

    do
    {
        switch(menuInformes())
        {
        case 0:
            system("clear");
            ordenarElementosEmpresaXCapacidad(vec, tam);
            mostrarLista(vec, tam, empresas, tamE, tipos, tamT);
            break;
        case 1:
            system("clear");
            listarEmpresas(empresas, tamE);
            printf("Ingrese empresa: ");
            scanf_int("%d", &idEmpresa);
            while(!validarEmpresa(empresas, tamE, idEmpresa))
            {
                printf("Id invalida. Reingrese id de empresa: ");
                scanf_int("%d", &idEmpresa);
            }
            printf("\n\t\t*** Micros por Empresa ***\n");
            mostrarListaXEmpresa(vec, tam, empresas, tamE, tipos, tamT, idEmpresa);

            break;
        case 2:
            system("clear");
            listarTipos(tipos, tamT);
            printf("Ingrese tipo: ");
            scanf_int("%d", &idTipo);
            while(!validarTipo(tipos, tamT, idTipo))
            {
                printf("Id invalida. Reingrese id de tipo: ");
                scanf_int("%d", &idTipo);
            }
            printf("\n\t\t*** Micros por Tipo ***\n");
            mostrarListaXTipo(vec, tam, empresas, tamE, tipos, tamT, idTipo);
            break;
        case 3:
            system("clear");
            printf("\t\t*** Promedio de micros VIP sobre total de micros de la empresa ***\n");
            promedioMicrosVip(vec, tam, empresas, tamE);
            break;
        case 4:
            system("clear");
            printf("\t\t*** Micros separados por Empresa ***\n");
            mostrarListaEmpresas(vec, tam, empresas, tamE, tipos, tamT);
            break;
        case 5:
            system("clear");
            printf("\t\t*** Empresa con mayor capacidad de transporte ***\n");
            mostrarEmpresaMayorCapacidad(vec, tam, empresas, tamE);
            break;
        case 6:
            system("clear");
            printf("\t\t*** Empresa(s) con menor cantidad de micros ***\n");
            mostrarEmpresaMenorCantidadMicros(vec, tam, empresas, tamE);
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

int ordenarElementosEmpresaXCapacidad(eMicro vec[], int tam)
{
    int todoOk = 0;
    eMicro auxStruct;
    if(vec != NULL && tam >0)
    {
        for(int i=0; i<tam-1; i++)
        {
            for(int j=i+1; j<tam; j++)
            {
                // condicion ascendente
                if( (
                            // si son del mismo empresa, ordeno por capacidad
                            (vec[i].idEmpresa == vec[j].idEmpresa &&
                             (vec[i].capacidad > vec[j].capacidad))
                            || // si son de distinto empresa, ordeno por empresa
                            (vec[i].idEmpresa != vec[j].idEmpresa &&
                             vec[i].idEmpresa > vec[j].idEmpresa)
                        )      // condicion descendente
                  )
                {
                    //swapeo
                    auxStruct = vec[i];
                    vec[i] = vec[j];
                    vec[j] = auxStruct;
                }
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int validarCapacidad(int cap)
{
    int esValido = 0;
    if(cap <= 50 && cap > 0)
    {
        esValido = 1;
    }
    return esValido;
}

int validarMicro(eMicro vec[], int tam, int id)
{
    int esValido;
    int indice;
    buscarPorId(vec, tam, id, &indice);
    if(indice == -1)
    {
        esValido = 0;
    }
    else
    {
        esValido = 1;
    }
    return esValido;
}
