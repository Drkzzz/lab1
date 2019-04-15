#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//Estructura
typedef struct Nodo
{
    int nodos;
    int id;
    double x, y;
    struct Nodo *sig;
}tNodo;
typedef tNodo *Lista;

Lista Ls = NULL;
Lista Ln = NULL;

double DistEuc(double x1,double y1,double x2, double y2)
{
    double resta_x,resta_y;
    resta_x = (x2-x1);
    resta_y = (y2-y1);
    double d = sqrt(pow(resta_x,2) + pow(resta_y,2));
    return d;
}
double DistanciaAcumulada(Lista L)
{
    Lista aux;
    double dist_acum, dist, x1, y1, x2, y2;
    aux = L;
    while(aux->sig != NULL)
    {
        x1 = aux->x;
        y1 = aux->y;
        x2 = aux->sig->x;
        y2 = aux->sig->y;
        dist = DistEuc(x1,y1,x2,y2);
        dist_acum += dist;
        aux = aux->sig;
    }
    x1 = aux->x;
    y1 = aux->y;
    x2 = L->x;
    y2 = L->y;
    dist = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    dist_acum += dist;

    return dist_acum;
}
int LargoLista(Lista L)
{
    Lista aux= L;
    int i = 0;

    while (aux != NULL)
    {
        aux = aux->sig;
        i++;
    }
    return i;
}
Lista CreaNodo(int id, double x, double y)
{
    Lista aux;
    aux = (Lista)malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->id = id;
        aux->x = x;
        aux->y = y;
        aux->sig = NULL;
    }
    else
    {
        system("cls");
        printf("\n----------------------------------------------");
        printf("\n\tERROR: No Hay espacio suficiente.");
        printf("\n\tEste programa se cerrar%c.", 160);
        printf("\n----------------------------------------------");
        exit(1);
    }
    return aux;
}
Lista InsertarInicio(Lista L, int id, double x, double y)
{
    Lista pNodo;

    pNodo = CreaNodo(id,x,y);
    pNodo->sig = L;
    L = pNodo;
    pNodo = NULL;

    return L;
}
Lista InsertarFinal(Lista L,int id, double x, double y)
{
    Lista pNodo, aux;
    pNodo = CreaNodo(id,x,y);
    if (L == NULL)
    {
        L = pNodo;
    }
    else
    {
        aux = L;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = pNodo;
        aux = NULL;
    }
    pNodo = NULL;
    return L;
}
Lista InsertarPosicion(Lista L, int id, double x ,double y, int p)
{
    Lista pNodo, aux;
    int i, largo;

    largo = LargoLista(L);
    pNodo = CreaNodo(id,x,y);
    if (p <= largo+1)
    {
        if (p == 1)
            L = InsertarInicio(L,id,x,y);
        else
        {
            if (p == largo+1)
                L = InsertarFinal(L,id,x,y);
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
Lista EliminaLista(Lista L, int id) 
{
   Lista aux1, aux2;
   
   if (L->id == id)
   {
      aux1 = L;
      L = L->sig;
      aux1->sig = NULL;
      free(aux1);
   }
   else
   {
      aux1 = L;
      while(aux1->id != id)
    {
         aux1 = aux1->sig;
    }
      aux2 = L;
      while (aux2->sig = aux1)
    {
         aux2 = aux2->sig;
    }
      aux2->sig = aux1->sig;
      aux1->sig = NULL;
      free(aux1);
      aux2 = NULL;
   }
   return L; 
}
Lista EliminaListaPosicion(Lista L, int p) 
{ 
    Lista aux, auxNodo;
    int i;
    aux = L;

    if(p == 1)
    {
        L = L->sig;
        aux->sig = NULL;
        free(aux);   
    }
    else
    {
        i = 1;
        while(i < p-1)
        {
            aux = aux->sig; 
            i++;
        }
        auxNodo = aux->sig;
        aux->sig  = auxNodo->sig;
        auxNodo->sig = NULL;
        free(auxNodo);
    }
    return L;
}
void MostrarLista(Lista L,double dist_acum)
{
   Lista aux = L;
   printf("Costo: %.2lf\n",dist_acum);
   printf("L ->");
   if (L != NULL)
    {
       while(aux != NULL)
       {
        printf(" %d",aux->id);
        aux = aux->sig;
       }
       printf("\n****************************************************************************\n\n");
       
       //printf("-> (%d,%.2lf,%.2lf).\n",L->id,L->x,L->y);

    }
    else 
    {
        printf("-> NULL\n");
    }
}
bool BuscarElemento(Lista L, int id)
{
    Lista aux;

    aux = L;
    while(aux != NULL)
    {
        if (aux->id == id)
        {
            return true;
        }
        else
        {
            aux = aux->sig;
        }
    }
    return false;
}
int LocalizarPosicion(Lista L, int id)
{
    Lista aux;
    int i;

    if (BuscarElemento(L,id))
    {
        aux = L;
        i = 1;
        while (aux->id != id)
        {
            aux = aux->sig;
            i++;
        }
        return i;
    }
    else
    {
      return -1;
    }
}
Lista ActualizaLista(Lista L, int p, int id, double x, double y)
{
    Lista aux, auxNodo;
    int largo, i;

    largo = LargoLista(L);

    if ((p <= largo) || (L != NULL))
    {
        i = 1;
        aux = L;
        while (i < p)
        {
            aux = aux->sig;
            i++;
        }
        aux->id  = id;
        aux->x  = x;
        aux->y  = y;
        aux = NULL;
    }
    return L;
}
void LecturaArchivo(char n_arch[50])
{
    FILE *arch;
    int nodos, id, c1, c2, c3, i;
    double x, y;
    Lista C1= NULL, C2=NULL, C3=NULL;

    arch = fopen(n_arch, "r");
    if (arch != NULL)
    {

        fscanf(arch, "%d", &nodos);
        printf("\nLa cantidad de ciudades es: %d", nodos);
        fscanf(arch, "%d", &c1);
        fscanf(arch, "%d", &c2);
        fscanf(arch, "%d", &c3);
        printf("\nCiudades de inicio: %d, %d, %d \n", c1, c2, c3);
        for (i = 0; i < nodos; i++)
        {
            printf("--------------------------------------------------\n");
            fscanf(arch, "%d", &id);
            fscanf(arch, "%lf", &x);
            fscanf(arch, "%lf", &y);
            printf("Nodo %d, tiene las coordenadas X: %.2lf , Y: %.2lf\n", id, x, y);
            if(id == c1)
            {
                C1 = CreaNodo(id,x,y);
            }
            else if(id == c2)
            {
                C2 = CreaNodo(id,x,y);
            }
            else if(id == c3)
            {
                C3 = CreaNodo(id,x,y);
            }
            if((id != c1) && (id != c2) && (id != c3))
            {
                Ln = InsertarFinal(Ln,id,x,y);
            }

        }
        fclose(arch);
        printf("--------------------------------------------------\n\n");
        Ls = InsertarFinal(Ls,C1->id,C1->x,C1->y);
        Ls = InsertarFinal(Ls,C2->id,C2->x,C2->y);
        Ls = InsertarFinal(Ls,C3->id,C3->x,C3->y);
    }
    else
    {
        printf("\nEl archivo no se ha podido leer");
        printf("\nEjecute el programa ingresando la instancia.");
        printf("\nEj: ./Tsp burma14.tsp\n");
    }
}
Lista OrdenarLs(Lista L)
{
    Lista aux,aux2;
    aux = L->sig;
    aux2 = aux->sig;
    if (DistEuc(L->x,L->y,aux->x,aux->y) < DistEuc(L->x,L->y,aux2->x,aux2->y))
    {
        return L;
    }
    else
    {
        L = InsertarPosicion(L,aux2->id,aux2->x,aux2->y,2);
        L = EliminaListaPosicion(L,4);
    }
    return L;
}
Lista VecinoMasCercano(Lista Ls,Lista Ln)
{
    Lista auxs,auxn,L;
    auxs = Ls->sig;
    auxn = Ln;
    double d1,menor;

    while(auxs != NULL)
    {
        auxs = auxs->sig;
        L = Ln;
        menor = DistEuc(auxs->x,auxs->y,auxn->x,auxn->y);
        while(auxn != NULL)
        {
            d1 = DistEuc(auxs->x,auxs->y,auxn->x,auxn->y);
            if (menor > d1)
            {
                menor = d1;
                L = auxn;
            }
            auxn = auxn->sig;
        }
        Ls = InsertarFinal(Ls,L->id,L->x,L->y);
    }
    return Ls;
}
void TravelmanSaleProblem()
{
    Lista auxN = Ln;
    Lista auxS = Ls;
    double d_total;
    int nodos_restantes = LargoLista(Ln);

    printf("\n\n");
    while(nodos_restantes > 0)
    {
        int p, i, largo_auxS;
        double menor, dist;

        menor = 0;
        dist = 0;
        p = 0;
        largo_auxS = 0;
        largo_auxS = LargoLista(auxS);

        for(i=2; i<=largo_auxS+1; i++)
        {
            auxS = InsertarPosicion(auxS, auxN->id, auxN->x, auxN->y, i);
            dist = DistanciaAcumulada(auxS);
            auxS = EliminaLista(auxS,i);

            if(i == 2)
            {
                p = 2;
                menor = dist;
            }
            if (dist < menor)
            {
                p = i;
                menor = dist;
            }
        }
        auxS = InsertarPosicion(auxS, auxN->id, auxN->x, auxN->y, p);
        auxN = EliminaLista(auxN, 1);
        nodos_restantes = LargoLista(auxN);
    }
    printf("\t<Lista Solucion>\n\n");
    MostrarLista(auxS,DistanciaAcumulada(auxS));
}

//Main
int main(int argc , char* argv[])
{
	LecturaArchivo(argv[1]);

    printf("\t<Lista Solucion Inicial>\n\n");
    MostrarLista(Ls,DistanciaAcumulada(Ls));
    printf("\t<Lista Ciudades Restantes>\n\n");
    MostrarLista(Ln,DistanciaAcumulada(Ln));
    printf("\t<Lista Solucion>\n\n");
    Ls = OrdenarLs(Ls);
    MostrarLista(Ls,DistanciaAcumulada(Ls));
    TravelmanSaleProblem();
    

    return 0;
}