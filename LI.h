/* Funciones para Lista Invertida */
#ifndef LI_H_INCLUDED
#define LI_H_INCLUDED


void menu_LI(int *op)
{
    cant_LI = 0; // Inicializo la lista
    LI[0] = malloc(sizeof(Articulo));
    strcpy(LI[0]->codigo, "ZZZZZZ"); // +inf

    while (*op != 0)
    {
        encabezado();
        printf("\n\t       Lista Invertida        \n"
                 "\t       ---------------        \n"
               "\n[1] Nuevo articulo"
               "\n[2] Eliminar articulo"
               "\n[3] Consultar articulo"
               "\n[4] Mostrar articulos"
               "\n[5] Memorizacion previa"
               "\n\n[0] Volver\n"
               "\nElija una opcion: ");
        scanf("%d", op);

        switch (*op)
        {
        case 0: // Volver
            break;

        case 1: // Alta
            {
                encabezado();
                printf("\n\t        Lista Invertida        \n"
                         "\t        ---------------        \n"
                       "\n[1] Nuevo articulo");

                Articulo nuevo;
                int alta;

                printf("\n\n Codigo: \t");
                fflush(stdin);
                scanf("%s", nuevo.codigo);
                strupr(nuevo.codigo);
                printf(" Articulo:\t");
                fflush(stdin);
                fgets(nuevo.articulo, 52, stdin);
                printf(" Marca:\t\t");
                fflush(stdin);
                fgets(nuevo.marca, 62, stdin);
                printf(" Valor($):\t");
                fflush(stdin);
                scanf("%f", &nuevo.valor);
                printf(" Cantidad:\t");
                fflush(stdin);
                scanf("%i", &nuevo.cantidad);
                printf(" Club:\t\t");
                fflush(stdin);
                fgets(nuevo.club, 72, stdin);
                borrar_salto(&nuevo);
                alta = alta_LI(nuevo);
                if(alta == 0)
                    printf("\nEl articulo ya existe\n\n");
                else
                    printf("\nEl articulo fue agregado con exito\n\n");
                system("pause");
                break;
            }
        case 2: // Baja
            {
                encabezado();
                printf("\n\t        Lista Invertida        \n"
                         "\t        ---------------        \n"
                           "\n[2] Eliminar articulo");
                char cod[8];
                int baja;
                printf("\n\nCodigo: ");
                fflush(stdin);
                scanf("%s", cod);
                strupr(cod);
                baja = baja_LI(cod, 0);
                if(baja == 0)
                    printf("\nEl articulo %s no fue eliminado o no existe\n\n",cod);
                else
                    printf("\nEl articulo %s fue eliminado con exito\n\n",cod);
                system("pause");
                break;
            }
        case 3: // Consultar
            {
                encabezado();
                printf("\n\t       Lista Invertida        \n"
                         "\t       ---------------        \n"
                       "\n[3] Consultar articulo");
                char cod[8];
                printf("\n\nCodigo: ");
                fflush(stdin);
                scanf("%s", cod);
                strupr(cod);
                Articulo consulta = evocar_LI(cod);
                if(strcmp(consulta.codigo, "ZZZZZZ"))
                {
                    imprimirArt(consulta);
                    printf("\n");
                }
                else
                    printf("\n\t El articulo %s no existe\n\n",cod);
                system("pause");
                break;
            }
        case 4: // Mostrar
            {
                encabezado();
                printf("\n\t       Lista Invertida        \n"
                         "\t       ---------------        \n");
                mostrar_LI();
                system("pause");
                break;
            }
        case 5: // Memorizacion
            {
                encabezado();
                printf("\n\t       Lista Invertida        \n"
                         "\t       ---------------        \n");
                memorizacion_previa(2);
                system("pause");
                break;
            }
        }
    }
    *op = -1;

}

int localizar_LI(char codArt[], int *posicion, int conCosto) //-- DEVUELVE: 1.Exito 0.Fracaso
{
    //consultadas = 0;
    int li, ls, testigo;
    //int i;
    //int aux[DIM];
    //for(i = 0; i < DIM; i++)
    //    aux[i] = 0;
    if (cant_LI != 0)
    {
        li = 0;
        ls = cant_LI;
        while (li !=ls)
        {
            testigo = (li + ls - 1) / 2;
            //aux[testigo] = 1;
            //if(conCosto == 1) consultadas++;
            if(strcmp(codArt, LI[testigo]->codigo) > 0)
            {
                li = testigo + 1;
            }
            else
            {
                ls = testigo;
            }

        }
        *posicion = li;
        //if(aux[li] == 0 && conCosto == 1)
        //    consultadas++;
        if(strcmp(codArt, LI[li]->codigo) == 0)
        {
            return 1;
        }
        else
        {

            return 0;
        }
    }
    else
    {
        *posicion = 0;
        return 0;
    }
}

int alta_LI(Articulo nuevo) //-- DEVUELVE: 1.Exito 0.Fracaso.
{
    if (cant_LI < DIM)
    {
        //int corrimientos = 0;
        int loc;
        if (localizar_LI(nuevo.codigo, &loc, 0) == 0)
        {
            int i;
            for(i = cant_LI; i >= loc; i--)
            {
                LI[i + 1] = LI[i];
                //corrimientos++;
            }
            LI[loc] = malloc(sizeof(Articulo));
            *LI[loc] = nuevo;
            cant_LI++;
            //cant_altas_LSO++;
//            total_corrimientos_alta_LSO = total_corrimientos_alta_LSO + corrimientos;
//            if(maximo_alta_LSO < corrimientos)
//                maximo_alta_LSO = corrimientos;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
        return 0;
}

int baja_LI(char codArt[], int entrada) //-- DEVUELVE: 1.Exito 0.Fracaso
{
    if(cant_LI != 0)
    {
        //int corrimientos = 0;
        int loc;
        char c = 'S';
        if(localizar_LI(codArt, &loc, 0) == 1)
        {
            if(entrada == 0)
                c = confirmacion_baja(*LI[loc]);
            if(c == 'S' || c == 's' )
            {
                Articulo *aux = LI[loc];
                int i;
                for(i = loc; i < cant_LI; i++)
                {
                    LI[i] = LI[i + 1];
                    //corrimientos++;
                }
                free(aux);
                cant_LI--;
//                cant_bajas_LSO++;
//                total_corrimientos_baja_LSO = total_corrimientos_baja_LSO + corrimientos;
//                if(maximo_baja_LSO < corrimientos)
//                    maximo_baja_LSO = corrimientos;
                return 1;
            }
            else
                return 0;


        }
        else
            return 0;
    }
    else
        return 0;
}

Articulo evocar_LI(char codArt[])
{
    int loc;
    Articulo aux;
    strcpy(aux.codigo, "ZZZZZZ");
    if(localizar_LI(codArt, &loc, 1) == 1)
    {
        aux = *LI[loc];
//        if(maximo_evo_exito_LSO < consultadas)
//            maximo_evo_exito_LSO = consultadas;
//
//        total_consultadas_exito_LSO += consultadas;
//
//        cant_evocaciones_exito_LSO++;
        return aux;
    }
    else
    {
//        if(maximo_evo_fracaso_LSO < consultadas)
//            maximo_evo_fracaso_LSO = consultadas;
//
//        total_consultadas_fracaso_LSO += consultadas;
//
//        cant_evocaciones_fracaso_LSO++;
        return aux;
    }

}

void mostrar_LI()
{
    if(cant_LI == 0)
    {
        printf("\n\tLa lista esta vacia\n\n");
    }
    else
    {
        int i, j = 1;
        printf("\n\t----------LISTA DE ARTICULOS----------\n");
        for(i = 0; i < cant_LI; i++)
        {
            printf("\n Posicion: \t%d", i);
            imprimirArt(*LI[i]);
            if ((j % 5) == 0)
            {
                printf("\n");
                system("pause");
            }
            j++;
        }
        printf("\n\tTotal de articulos: %d \n\n", cant_LI);
    }
}

#endif // LI_H_INCLUDED
