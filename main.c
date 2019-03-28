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

Lista CreaNodo(int ind, float val1, float val2)
{
    Lista aux;

    aux = (Lista)malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->n_nodo = ind;
        aux->x = val1;
        aux->y = val2;
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

void Lectura_archivo ()
{
    FILE *archivo;
    int i=0, n_ciudades, indice, ciudad1, ciudad2, ciudad3;
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

            for(i; i<n_ciudades; i++)
            {
                fscanf(archivo, "%d", &indice);
                fscanf(archivo, "%f", &coor_x);
                fscanf(archivo, "%f", &coor_y);
                CreaNodo(indice, coor_x, coor_y);
            }
            fclose(archivo);
        }
        else
        {
            printf("No se encontr%c el archivo.\n\n", 162);
        }
    }while(i==0);
}

int main()
{
    Lectura_archivo();

    return 0;
}
