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

Lista Listadatos = NULL;
int ciudad1, ciudad2, ciudad3;

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
        printf("\nCiudad: %d, COORD X: %.2f, COORD Y: %.2f\n", aux->n_nodo, aux->x, aux->y);
        aux = aux->sig;
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
Lista Lista_INSERTA_FINAL(Lista L, int indice,float x,float y)
{
    Lista pNodo, aux;

    pNodo = CreaNodo(indice,x,y);
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

float DistanciaEuclidiana(float x1,float y1,float x2,float y2){
    float restax=x2-x1;
    float restay=y2-y1;
    float suma=pow(restax,2)+pow(restay,2);
    float distancia = sqrt(suma);
    return distancia;
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
                /*Iniciamos la lista ordenada con datos*/
                fscanf(archivo, "%d", &indice);
                fscanf(archivo, "%f", &coor_x);
                fscanf(archivo, "%f", &coor_y);
                Listadatos = CreaNodo(indice, coor_x, coor_y);
                /*Termina el proceso*/

                /*Insertamos las demas al final de la lista*/
                for(i=0;i<n_ciudades;i++){
                    fscanf(archivo, "%d", &indice);
                    fscanf(archivo, "%f", &coor_x);
                    fscanf(archivo, "%f", &coor_y);
                    Lista_INSERTA_FINAL(Listadatos,indice,coor_x,coor_y);
                }
                /*Termina el proceso*/
            fclose(archivo);
        }
        else
        {
            printf("No se encontr%c el archivo.\n\n", 162);
        }
    }while(i==0);
}

void TSP(void){
Lista Listasolucion = NULL;

}

int main()
{
    Lectura_archivo();
    return 0;
}
