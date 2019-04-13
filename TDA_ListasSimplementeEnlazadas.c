#include <stdio.h>
#include <stdlib.h>

//Definición de Constantes para el manejo de Booleanos
#define VERDADERO 1
#define FALSO 0

//Tipo "tNodo" que será la estructura de un nodo de la lista
struct Nodo{
    int info;
    struct Nodo *sig;
};
typedef struct Nodo tNodo;

//Tipo "Lista" que será un puntero a un nodo de la lista
typedef tNodo *Lista;

//Abstraccion para el manejo de booleanos
typedef int BOOL;

//Funciones definidas en este programa:
/*Operaciones Constructoras*/
Lista Lista_INICIALIZA(void);
Lista Lista_CREA_NODO(int valor);
/*Operaciones Modificadoras*/
Lista Lista_INSERTA_PRINCIPIO(Lista L, int x);
Lista Lista_INSERTA_FINAL(Lista L, int x);
Lista Lista_INSERTA_EN_POSICION(Lista L, int x, int pos);
Lista Lista_INSERTA_ORDENADO(Lista L, int x);
Lista Lista_ELIMINA(Lista L, int p);
/*Operaciones Analizadoras*/
void Lista_IMPRIME(Lista L);
int Lista_LARGO(Lista L);
BOOL Lista_VACIA(Lista L);
int Lista_POSICION_ELEMENTO(Lista L, int x);
/*Operaciones Destructoras*/
void Lista_DESTRUYE(Lista L);
/*Funciones Complementarias*/
int LeeInfo(void);
int LeePosicion(void);
void MensajePausa(void);
/*Funciones de Menú*/
int ImprimeMenu(void);
Lista ProcesaOpciones(int opcion, Lista L);
void Menu(Lista L);
/*---------------------------------------------------------------------------------------------------*/
/*-------------------------------- INICIO OPERACIONES TDA LISTA -------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/

/*-------------------------------- INICIO OPERACIONES CONSTRUCTORAS -------------------------------------*/
Lista Lista_INICIALIZA(void)
{
    return NULL;
}
Lista Lista_CREA_NODO(int valor)
{
    Lista aux;

    aux = (Lista)malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->info = valor;
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
/*-------------------------------- FIN OPERACIONES CONSTRUCTORAS -------------------------------------*/

/*-------------------------------- INICIO OPERACIONES MODIFICADORAS -------------------------------------*/
Lista Lista_INSERTA_PRINCIPIO(Lista L, int x)
{
    Lista pNodo;

    pNodo = Lista_CREA_NODO(x);
    pNodo->sig = L;
    L = pNodo;
    pNodo = NULL;
    return L;
}
Lista Lista_INSERTA_FINAL(Lista L, int x)
{
    Lista pNodo, aux;

    pNodo = Lista_CREA_NODO(x);
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
Lista Lista_INSERTA_EN_POSICION(Lista L, int x, int pos)
{
    Lista pNodo, aux;
    int i, largo;

    largo = Lista_LARGO(L);
    pNodo = Lista_CREA_NODO(x);
    if (pos <= largo+1) //Si p es válido para el largo de la lista.
    {
        if (pos == 1)	//Inserta en la primera posición.
            L = Lista_INSERTA_PRINCIPIO(L, x);
        else
        {
            if (pos == largo+1)           //Inserta en la última posición.
                L = Lista_INSERTA_FINAL(L, x);
            else
            {
                aux = L;
                i = 1;
                while (i < pos-1)
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
Lista Lista_INSERTA_ORDENADO(Lista L, int x)
{
    Lista pNodo, aux1, aux2;

    pNodo = Lista_CREA_NODO(x);
    if (L == NULL)
        L = pNodo;
    else
    {
        if (x < L->info) //Inserta al principio de L.
        {
            pNodo->sig = L;
            L = pNodo;
        }
        else
        {		//2 ó más Nodos, o inserción al final.
            aux1 = L;
            while ((aux1 != NULL) && (aux1->info < x))
            {
                aux1 = aux1->sig;
            }
            aux2 = L;
            while (aux2->sig != aux1)
                aux2 = aux2->sig;
            aux2->sig = pNodo;
            pNodo->sig = aux1;
            aux1 = NULL;
            aux2 = NULL;
        }
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
/*-------------------------------- FIN OPERACIONES MODIFICADORAS -------------------------------------*/

/*-------------------------------- INICIO OPERACIONES ANALIZADORAS -------------------------------------*/
void Lista_IMPRIME(Lista L)
{
    Lista aux;

    aux = L;
    printf("\n\n\tL -> ");
    while(aux != NULL)
    {
        printf("%d -> ", aux->info);
        aux = aux->sig;
    }
    printf("NULL");

}
int Lista_LARGO(Lista L)
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
BOOL Lista_VACIA(Lista L)
{
    if (L == NULL)
        return VERDADERO;
    return FALSO;
}
int Lista_POSICION_ELEMENTO(Lista L, int x)
{
    Lista aux;
    int pos=0;

    aux = L;
    while (aux != NULL)
    {
        pos++;
        if (aux->info == x)
            return pos;
        aux = aux->sig;
    }
    return 0;
}
int Lista_POSICION_ELEMENTO_REC(Lista L, int x, int i)
{
    if (L == NULL)
        return 0;
    if (L->info == x)
        return i;
    else
        return Lista_POSICION_ELEMENTO_REC(L->sig, x, i+1);
}
/*-------------------------------- FIN OPERACIONES ANALIZADORAS -------------------------------------*/

/*-------------------------------- INICIO OPERACIONES DESTRUCTORAS -------------------------------------*/
void Lista_DESTRUYE(Lista L)
{
    Lista aux;
    do
    {
        aux = L;
        L = L->sig;
        aux->sig = NULL;
        free(aux);
    } while (L != NULL);
}
/*-------------------------------- FIN OPERACIONES DESTRUCTORAS -------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-------------------------------- FIN OPERACIONES TDA LISTA -------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*-------------------------------- INICIO FUNCIONES COMPLEMENTARIAS -------------------------------------*/
int LeeInfo(void)
{
    int valor;
    printf("\n\tIngrese un entero: ");
    scanf("%d",&valor);

    return valor;
}
int LeePosicion(void)
{
    int posicion;
    printf("\n\tIngrese una posicion: ");
    scanf("%d",&posicion);

    return posicion;
}
void MensajePausa(void)
{
    printf("\n\n\t");
    system("PAUSE");
}
/*-------------------------------- FIN FUNCIONES COMPLEMENTARIAS -------------------------------------*/

/*-------------------------------- INICIO FUNCIONES DE MENU -------------------------------------*/
int ImprimeMenu(void)
{
    int opcion;

    system("cls");
    printf("\n\t\t\tMENU");
    printf("\n\t\t\t====\n");
    printf("\n\t\t1. Ingresar Nodo.");
    printf("\n\t\t2. Ingresar Ordenado.");
    printf("\n\t\t3. Eliminar Nodo.");
    printf("\n\t\t4. Largo Lista.");
    printf("\n\t\t5. Imprimir Lista.");
    printf("\n\t\t6. Localizar Elemento.");
    printf("\n\t\t20. Salir.");
    printf("\n\n\t\tIngrese una opci%cn: ", 162);
    scanf("%d", &opcion);
    return opcion;
}
Lista ProcesaOpciones(int opcion, Lista L)
{
    int valor, pos;

    switch(opcion)
    {
        case 1:
            valor = LeeInfo();
            pos = LeePosicion();
            if (pos <= Lista_LARGO(L)+1)
                L = Lista_INSERTA_EN_POSICION(L, valor, pos);
            else
            {
                printf("\n\tERROR: Posici%cn Inv%clida.", 162, 160);
                MensajePausa();
            }
            break;
        case 2:
            valor = LeeInfo();
            L = Lista_INSERTA_ORDENADO(L, valor);
            break;
        case 3:
            if (!Lista_VACIA(L))
            {
                pos = LeePosicion();
                if ((0 < pos) && (pos <= Lista_LARGO(L)))
                    L = Lista_ELIMINA(L, pos);
                else
                {
                    printf("\n\tERROR: Posici%cn Inv%clida.", 162, 160);
                    MensajePausa();
                }
            }
            else
            {
                printf("\n\tERROR: No existen elementos en la Lista.");
                MensajePausa();
            }
            break;
        case 4:
            printf("\n\tLa lista tiene %d elementos.", Lista_LARGO(L));
            MensajePausa();
            break;
        case 5:
            Lista_IMPRIME(L);
            MensajePausa();
            break;
        case 6:
            if (!Lista_VACIA(L))
            {
                valor = LeeInfo();
                pos = Lista_POSICION_ELEMENTO(L, valor);
                if (pos == 0)
                    printf("\n\tEl elemento %d, no est%c en la lista.", valor, 160);
                 else
                    printf("\n\tEl elemento %d, est%c en la posici%cn %d de la lista.", valor, 160, 162, pos);
            }
            else
                printf("\n\tERROR: No existen elementos en la Lista.");
            MensajePausa();
            break;
        case 20:
            if (!Lista_VACIA(L))
                Lista_DESTRUYE(L);
            printf("\n\tLa aplicaci%cn se cerrar%c.", 162, 160);
            MensajePausa();
            break;
        default:
            printf("\n\tERROR: Ingrese una opci%cn v%clida.", 162, 160);
            MensajePausa();
    }
    return L;
}
void Menu(Lista L)
{
    int opcion = 0;

    while (opcion != 20)
    {
        opcion = ImprimeMenu();
        L = ProcesaOpciones(opcion, L);
    }
}
/*-------------------------------- FIN FUNCIONES DE MENU -------------------------------------*/
int main()
{
    Lista L;

    L = Lista_INICIALIZA();
    Menu(L);

    return 0;
}








