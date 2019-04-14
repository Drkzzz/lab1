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

int ciudad1, ciudad2, ciudad3;
Lista ListaDatos = NULL;
Lista ListaSolucion = NULL;

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

Lista Lista_INSERTA_PRINCIPIO(Lista L, int indice, float x, float y)
{
    Lista pNodo;

    pNodo = CreaNodo(indice, x, y);
    pNodo->sig = L;
    L = pNodo;
    pNodo = NULL;

    return L;
}

Lista Lista_INSERTA_FINAL(Lista L, int indice, float x, float y)
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

Lista Lista_ELIMINA(Lista L, int p)
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

Lista InsertarPosicion(Lista L, int id, float x ,float y, int p)
{
    Lista pNodo, aux;
    int i, largo;

    largo = LargoLista(L);
    pNodo = CreaNodo(id,x,y);
    if (p <= largo+1)
    {
        if (p == 1)
            L = Lista_INSERTA_PRINCIPIO(L, id, x, y);
        else
        {
            if (p == largo+1)
                L = Lista_INSERTA_FINAL(L, id, x, y);
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
    }
    pNodo = NULL;
    return L;
}

int Lista_POSICION_ELEMENTO(Lista L, int x)
{
    Lista aux;
    int pos=0;

    aux = ListaSolucion;
    while (aux != NULL)
    {
        pos++;
        if (aux->n_nodo == x)
            return pos;
        aux = aux->sig;
    }
    return 0;
}


void Lista_IMPRIME(Lista L)
{
    Lista aux;

    aux = L;
    printf("\n\n\tL -> ");
    while(aux != NULL)
    {
        printf("%d , %.2f, %.2f -> ", aux->n_nodo, aux->x, aux->y);
        aux = aux->sig;
    }
    printf("NULL");
}

float DistanciaEuclidiana(float x1,float y1,float x2,float y2){
    float restax=x2-x1;
    float restay=y2-y1;
    float suma=pow(restax,2)+pow(restay,2);
    float distancia = sqrt(suma);
    return distancia;
}

float DistanciaAcumulada(void){
    float distanciaAcum,distancia;
    float cx1,cx2,cy1,cy2;
    Lista aux;
    aux = ListaSolucion;
    while(aux->sig != NULL){
        cx1 = aux->x;
        cy1 = aux->y;
        cx2 = aux->sig->x;
        cy2 = aux->sig->y;
        distanciaAcum=DistanciaEuclidiana(cx1,cy1,cx2,cy2);
        aux=aux->sig;
    }
    cx1 = aux->x;
    cy1 = aux->y;
    cx2 = ListaDatos->x;
    cy2 = ListaDatos->y;
    distancia = DistanciaEuclidiana(cx1,cy1,cx2,cy2);
    distanciaAcum = distanciaAcum + distancia;

    return distanciaAcum;
}


void Lectura_archivo (void)
{
    FILE *archivo;
    int i=1, n_ciudades, indice;
    float coor_x, coor_y;
    char n_archivo[20];

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
                /*Insertamos todos los datos a una lista*/
                for(i=0;i<n_ciudades;i++){
                    fscanf(archivo, "%d", &indice);
                    fscanf(archivo, "%f", &coor_x);
                    fscanf(archivo, "%f", &coor_y);
                    /*Se insertan las primeras 3 ciudades a una lista*/
                    if(indice==ciudad1)
                    {
                        ListaSolucion = Lista_INSERTA_PRINCIPIO(ListaSolucion, indice, coor_x, coor_y);
                    }
                    else if (indice == ciudad2|| indice == ciudad3)
                    {
                        ListaSolucion = Lista_INSERTA_FINAL(ListaSolucion, indice, coor_x, coor_y);
                    }
                    if(i==0)
                    {
                        if((indice!=ciudad1)&&(indice!=ciudad2)&&(indice!=ciudad3))
                            ListaDatos = Lista_INSERTA_PRINCIPIO(ListaDatos, indice, coor_x, coor_y);
                    }
                    else
                    {
                        if((indice!=ciudad1)&&(indice!=ciudad2)&&(indice!=ciudad3))
                            ListaDatos = Lista_INSERTA_FINAL(ListaDatos, indice, coor_x, coor_y);
                    }
                }
                /*Termina el proceso*/
                if(i==n_ciudades)
                {
                    printf("\nLista solucion:\n");
                    Lista_IMPRIME(ListaSolucion);
                    printf("\n\nLista Datos:\n");
                    Lista_IMPRIME(ListaDatos);
                }
                fclose(archivo);
        }
        else
        {
            printf("No se encontr%c el archivo.\n\n", 162);
        }
    }while(i==0);
}

void TSP(void){

}

int main()
{
    Lectura_archivo();
    return 0;
}
