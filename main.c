#include <stdio.h>
#include <stdlib.h>
#include "my_lib.h"
#include "micro.h"
#include "fecha.h"
#include "empresa.h"
#include "tipo.h"
#include "destino.h"
#include "viaje.h"

#define TAMM 10
#define TAME 4
#define TAMT 4
#define TAMD 4
#define TAMV 10


int main()
{
    char salir = 'n';
    int nextId = 10000;
    int nextIdViaje = 100;
    int flagAlta = 0;
    int flagAltaViaje = 0;

    eMicro list[TAMM];
    eViaje viajes[TAMV];

    eEmpresa empresas[TAME] = {
        {1000, "Plusmar"},
        {1001, "Flecha Bus"},
        {1002, "Tas"},
        {1003, "El Rapido"}
    };

    eTipo tipos[TAMT] = {
        {5000, "Comun"},
        {5001, "CocheCama"},
        {5002, "Doble"},
        {5003, "Vip"}
    };

    eDestino destinos[TAMD] = {
        {20000, "Calafate", 22250},
        {20001, "Bariloche", 103000},
        {20002, "Iguazu", 84400},
        {20003, "Mendoza", 95600}
    };


    inicializar(list, TAMM);
    inicializarViajes(viajes, TAMV);
    hardcodearEntradas(list, TAMM, 8, &nextId, &flagAlta);
    hardcodearEntradasViajes(viajes, TAMV, 10, &nextIdViaje, &flagAltaViaje);

    do
    {
        system("clear");
        //printf("flag: %d\n", flagAlta);
        switch(menu())
        {
        case 1:
            system("clear");
            printf("\t\t *** Menu Alta Micro ***\n\n");
            if(pedirAlta(list, TAMM, empresas, TAME, tipos, TAMT, &nextId))
            {
                printf("Se agrego una entrada con exito!");
                flagAlta ++;
            }
            else
            {
                printf("Problema al realizar el alta.");
            }
            break;
        case 2:
            system("clear");
            if(flagAlta > 0)
            {
                printf("\t\t *** Menu Modificacion ***\n\n");
                pedirModificacion(list, TAMM, empresas, TAME, tipos, TAMT);
            }
            else
            {
                printf("Debe realizar al menos un alta antes de ingresar a este menu!");
            }
            break;
        case 3:
            system("clear");
            if(flagAlta > 0)
            {
                printf("\t\t *** Menu Baja ***\n\n");
                if(pedirBaja(list, TAMM, empresas, TAME, tipos, TAMT) == 1)
                {
                    flagAlta --;
                }
            }
            else
            {
                printf("Debe realizar al menos un alta antes de ingresar a este menu!");
            }
            break;
        case 4:
            system("clear");
            if(flagAlta > 0)
            {
                printf("\t\t *** Menu Informes ***\n\n");

                pedirInformes(list, TAMM, empresas, TAME, tipos, TAMT);
            }
            else
            {
                printf("Debe realizar al menos un alta antes de ingresar a este menu!");
            }
            break;
        case 5:
            system("clear");
            printf("\t\t *** Listar Empresas ***\n\n");
            listarEmpresas(empresas, TAME);
            break;
        case 6:
            system("clear");
            printf("\t\t *** Listar Tipos ***\n\n");
            listarTipos(tipos, TAMT);
            break;
        case 7:
            system("clear");
            printf("\t\t *** Listar Destinos ***\n\n");
            listarDestinos(destinos, TAMD);
            break;
        case 8:
            system("clear");
            printf("\t\t *** Menu Alta Viaje ***\n\n");
            if(pedirAltaViaje(viajes, TAMV, list, TAMM, destinos, TAMD, empresas, TAME, tipos, TAMT, &nextIdViaje))
            {
                printf("Se agrego una entrada con exito!");
            }
            else
            {
                printf("Problema al realizar el alta.");
            }
            break;
        case 9:
            system("clear");
            pedirInformesViajes(list, TAMM, empresas, TAME, tipos, TAMT, viajes, TAMV, destinos, TAMD);
            break;
        case 10:
            salir = 's';
            break;
        }
        pausar();

    }
    while(salir!='s');



    return 0;
}
