#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Nodo{
    int n_nodo;
    float x;
    float y;
    struct Nodo *sig;
};

typedef struct Nodo tNodo;
typedef tNodo *Lista;

/*Variables Globales*/
int ciudad1, ciudad2, ciudad3;
Lista ListaDatos = NULL;
Lista ListaSolucion = NULL;
/*Variables Globales*/

/*Funcion crea nodo*/
Lista CreaNodo(int indice, float x, float y)
{
    Lista aux;

    aux = (Lista)malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->n_nodo = indice;
        aux->x = x;
        aux->y = y;
        aux->sig = NULL;
    }
    else
    {
        system("cls");
        printf("\n\tERROR: No hay memoria suficiente para generar un nuevo Nodo.");
        printf("\n\tEste programa se cerrar%c.", 160);
        exit(1);
    }
    return aux;
}
/*Funcion crea nodo*/


/*Funcion para saber el largo de la lista*/
int LargoLista(Lista L)
{
    Lista aux;
    int cont = 0;

    aux = L;
    while(aux != NULL)
    {
        aux = aux->sig;
        cont++;
    }
    return cont;
}
/*Funcion para saber el largo de la lista*/


Lista Lista_InsertaFinal(Lista L, int indice, float x, float y)
{
    Lista pNodo, aux;

    pNodo = CreaNodo(indice, x, y);

    if (L == NULL)
        L = pNodo;
    else
    {
        aux = L;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = pNodo;
        aux = NULL;
    }
    pNodo = NULL;
    return L;
}

Lista Lista_Elimina(Lista L, int p)
{
    int cont = 1;
    Lista aux, aux2;

    aux = L;
    if (p == 1)
    {
        L = L->sig;
        aux->sig = NULL;
        free(aux);
    }
    else
    {
        while (cont < p-1)
        {
            aux = aux->sig;
            cont++;
        }
        aux2 = aux->sig;
        aux->sig = aux2->sig;
        aux2->sig = NULL;
        free(aux2);
    }
    return L;
}

Lista InsertarPosicion(Lista L, int id, float x, float y, int p)
{
    Lista pNodo, aux;
    int i, largo;

    largo = LargoLista(L);
    pNodo = CreaNodo(id,x,y);
    if (p <= largo+1)
    {
        if (p == largo+1)
        {
            L = Lista_InsertaFinal(L, id, x, y);
        }
        else
        {
            aux = L;
            i = 1;
            while (i < p-1)
            {
                aux = aux->sig;
                i = i+1;
            }
            pNodo->sig = aux->sig;
            aux->sig = pNodo;
            aux = NULL;
        }
    }
    pNodo = NULL;
    return L;
}

int Lista_PosicionElemento(Lista L, int x)
{
    Lista aux;
    int pos=0;

    aux = ListaDatos;
    while (aux != NULL)
    {
        pos++;
        if (aux->n_nodo == x)
            return pos;
        aux = aux->sig;
    }
    return 0;
}

void Lista_Imprime(Lista L)
{
    Lista aux;

    aux = L;
    printf("\n\n\tL -> ");
    while(aux != NULL)
    {
        printf("%d -> ", aux->n_nodo);
        aux = aux->sig;
    }
    printf("NULL");
}

float DistanciaAcumulada(Lista L)
{
    Lista aux;
    float dist_acum, dist, x1, y1, x2, y2;
    aux = L;
    dist_acum=0;
    while(aux->sig != NULL)
    {
        x1 = aux->x;
        y1 = aux->y;
        x2 = aux->sig->x;
        y2 = aux->sig->y;
        dist = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
        dist_acum = dist_acum + dist;
        aux = aux->sig;
    }
    x1 = aux->x;
    y1 = aux->y;
    x2 = L->x;
    y2 = L->y;
    dist = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    dist_acum = dist_acum + dist;

    return dist_acum;
}

void Lectura_archivo ()
{
    FILE *archivo;
    int i=0, n_ciudades, indice;
    float coor_x, coor_y;
    char n_archivo[20];
    Lista C1= NULL, C2=NULL, C3=NULL;

    do
    {
        printf("Ingrese nombre del archivo: ");
        scanf("%s", n_archivo);

        archivo=fopen(n_archivo, "r");
        if(archivo!=NULL)
        {
            fscanf(archivo, "%d", &n_ciudades);
            printf("\nEl numero de ciudades es: %d", n_ciudades);
            fscanf(archivo, "%d", &ciudad1);
            fscanf(archivo, "%d", &ciudad2);
            fscanf(archivo, "%d", &ciudad3);
            printf("\nCiudades de inicio: %d, %d, %d", ciudad1, ciudad2, ciudad3);
            printf("\n");

            for(i=0;i<n_ciudades;i++)
            {
                fscanf(archivo, "%d", &indice);
                fscanf(archivo, "%f", &coor_x);
                fscanf(archivo, "%f", &coor_y);
                if(indice==ciudad1)
                    C1 = CreaNodo(indice, coor_x, coor_y);
                else if(indice==ciudad2)
                    C2 =CreaNodo(indice, coor_x, coor_y);
                else if(indice==ciudad3)
                    C3 = CreaNodo(indice, coor_x, coor_y);
                if((indice!=ciudad1)&&(indice!=ciudad2)&&(indice!=ciudad3))
                    ListaDatos = Lista_InsertaFinal(ListaDatos, indice, coor_x, coor_y);
            }

            fclose(archivo);

            ListaSolucion=CreaNodo(C1->n_nodo,C1->x,C1->y);
            ListaSolucion=Lista_InsertaFinal(ListaSolucion,C2->n_nodo,C2->x,C2->y);
            ListaSolucion=Lista_InsertaFinal(ListaSolucion,C3->n_nodo,C3->x,C3->y);

        }
        else
            printf("No se encontr%c el archivo.\n\n", 162);
    }while(i==0);
}

void TSP(){

Lista auxDatos = ListaDatos;
Lista auxSolucion = ListaSolucion;

printf("\n\n");
printf("\n\n");

float disTotal;
int numciudadRestantes=LargoLista(auxDatos);

    while(numciudadRestantes>0)
    {
        int mejorPosicion,i,largoauxSolucion;
        float menDistancia,distancia;

            menDistancia=0;
            distancia=0;
            mejorPosicion=0;
            largoauxSolucion=0;
            largoauxSolucion = LargoLista(auxSolucion);


        for(i=2;i<=largoauxSolucion+1;i++)
        {
            auxSolucion=InsertarPosicion(auxSolucion, auxDatos->n_nodo , auxDatos->x , auxDatos->y,i);
            distancia=DistanciaAcumulada(auxSolucion);
            auxSolucion=Lista_Elimina(auxSolucion,i);

            //El mejor caso es que lo agregue en la posicion 2//
            if(i==2)
            {
                mejorPosicion=2;
                menDistancia=distancia;
            }
            //En cualquier otro caso, lo insertar� en la posici�n m�s conveniente//
            if (distancia<menDistancia)
            {
                mejorPosicion=i;
                menDistancia=distancia;
            }

        }
        auxSolucion=InsertarPosicion(auxSolucion, auxDatos->n_nodo , auxDatos->x , auxDatos->y,mejorPosicion);
        auxDatos=Lista_Elimina(auxDatos,1);
        numciudadRestantes=LargoLista(auxDatos);
    }
    printf("\nEl ciclo hamiltoniano es: ");
    Lista_Imprime(auxSolucion);
    disTotal=DistanciaAcumulada(auxSolucion);
    printf("\n\nLa Distancia del ciclo total es: %.2f\n",disTotal);
}
int main()
{
    Lectura_archivo();
    TSP();
    return 0;
}
