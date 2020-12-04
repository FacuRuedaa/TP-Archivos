#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <conio.h>
#include <string.h>

#define ESC 27
#define AR_ALUMNOS "Alumnos.dat"
#define DIM 100

typedef struct {
int legajo;
char nombreYapellido [ 30 ];
int edad;
int anio;
} stAlumno;

void agregarElementoArchivo ();
stAlumno cargarUnAlumno ();
void mostrarUnAlumno();
void mostrarArchivo ();
int cuentaRegistros ();
void guardaUnAlumno (stAlumno a);
void cargaAlumnos ();
void pasarLegajoAPila (Pila *d);
int cuentaAlumnosMayoresAEdad (int edad);
void mostrarAlumnosRangoEdad (int edad, int edad2);
void mostrarAlumnosMayoresEdad (int edad);
int cargarArregloAlumnos (stAlumno a[], int dimension);
void copiaArregloToArchivo (stAlumno a[], int v);
void invierteElementosArchivo ();

int main()
{
    stAlumno aArreglo [50];
    Pila dada;
    inicpila(&dada);
    int cantidad=0;

   /// cargaAlumnos();
    mostrarArchivo();

    invierteElementosArchivo();
  /*  printf("\nLa cantidad de registros del archivo es de: %d\n", cuentaRegistros());

    pasarLegajoAPila(&dada);
    mostrar(&dada);

    printf("\nLa cantidad de alumnos mayores a 30 anios es de: %d\n", cuentaAlumnosMayoresAEdad(30));

    mostrarAlumnosRangoEdad(26, 29);

    mostrarAlumnosMayoresEdad(18);
    system("pause");
    system("cls");

    cantidad = cargarArregloAlumnos(aArreglo, 50);
    copiaArregloToArchivo(aArreglo, cantidad);
    mostrarArchivo();
*/
    return 0;
}

/// 1. acer una función que agregue un elemento al final de un archivo.

/*************************
 * \brief CARGAR UN ALUMNO
 * \return ALUMNO
 *************************/

stAlumno cargarUnAlumno ()
{
    stAlumno a;

    printf("\nIngrese el legajo del alumno................:");
    scanf("%d", &a.legajo);
    printf("\nIngrese el nombre y apellido del alumno.....:");
    fflush(stdin);
    gets(a.nombreYapellido);
    printf("\nIngrese la edad del alumno..................:");
    scanf("%d", &a.edad);
    printf("\nIngrese el anio..............................:");
    scanf("%d", &a.anio);

    return a;
}

/*********************************************
 * \brief AGREGAR UN ELEMENTO AL ARCHIVO
 * \return VOID
 *********************************************/

void agregarElementoArchivo ()
{
    FILE * pArchAlumnos = fopen(AR_ALUMNOS, "ab");
    stAlumno a;

    a = cargarUnAlumno();

    if (pArchAlumnos){
        fwrite(&a, sizeof(stAlumno), 1, pArchAlumnos);
        fclose(pArchAlumnos);
    }
}

/// 2. Hacer una función que muestre por pantalla el contenido de un archivo.

/*************************
 * \brief MOSTRAR UN ARCHIVO
 * \return VOID
 *************************/

void mostrarArchivo ()
{
    stAlumno a;
    FILE *pArchAlumnos = fopen(AR_ALUMNOS, "rb");

    if (pArchAlumnos){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumnos)>0){
            mostrarUnAlumno(a);
        }
        fclose(pArchAlumnos);
    }
}

/*************************
 * \brief MOSTRAR UN ALUMNO
 * \return VOID
 *************************/

void mostrarUnAlumno(stAlumno a)
{
    printf("--------------------------------------");
    printf("\nLegajo numero:........: %d", a.legajo);
    printf("\nNombre y Apellido.....: %s", a.nombreYapellido);
    printf("\nEdad..................: %d", a.edad);
    printf("\nAnio..................: %d", a.anio);
    printf("\n");
}

/// 3. Hacer una función que retorne la cantidad de registros que contiene un archivo.

/*************************
 * \brief CUENTA REGISTROS
 * \return CANTIDAD
 *************************/

 int cuentaRegistros ()
 {
     FILE *pArchAlumnos = fopen(AR_ALUMNOS, "rb");

     int i;
     if (pArchAlumnos){
        fseek(pArchAlumnos, 0, SEEK_END);
        i = ftell(pArchAlumnos) / sizeof(stAlumno);
        fclose(pArchAlumnos);
     }
     return i;
 }

/// 4. Crear una función que cargue un archivo de alumnos. Abrirlo de manera tal de verificar si el
/// archivo ya está creado previamente. Cargar el archivo con 5 datos. Cerrarlo dentro de l a
/// función.

/*************************
 * \brief GUARDAR UN ALUMNO
 * \return VOID
 *************************/

void guardaUnAlumno (stAlumno a)
{
    FILE * pArchAlumnos = fopen(AR_ALUMNOS, "ab");
    if (pArchAlumnos){
        fwrite(&a, sizeof(stAlumno), 1, pArchAlumnos);
        fclose(pArchAlumnos);
    }
}

/*************************
 * \brief CARGAR ALUMNOS
 * \return VOID
 *************************/

void cargaAlumnos ()
{
    char opcion;

    while (opcion!=ESC){
        printf("\nCargando archivo de alumnos\n");
        guardaUnAlumno(cargarUnAlumno());
        printf("\nPresione ESC para salir....");
        opcion = getch();
        system("cls");
    }
}

/// 7. Crear una función que pase a una pila l os números de l egajo de l os alumnos mayores de
/// edad.

/*****************************************************************
 * \brief PASAR A UNA PILA LOS LEGAJOS DE LOS MAYORES DE EDAD
 * \return VOID
 *****************************************************************/

 void pasarLegajoAPila (Pila *d)
 {
     FILE *pArchAlumnos = fopen(AR_ALUMNOS, "rb");
     stAlumno a;

     if (pArchAlumnos){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumnos)>0){
            if (a.edad >=18){
                apilar(d, a.legajo);
            }
        }
        fclose(pArchAlumnos);
     }
 }

/// 8. Dado un archivo de alumnos, hacer una función que cuente l a cantidad de alumnos
/// mayores a edad específica que se envía por parámetro.

/***************************************************
 * \brief CONTAR ALUMNOS MAYORES A EDAD ESPECIFICA
 * \return VOID
 ***************************************************/

 int cuentaAlumnosMayoresAEdad (int edad)
 {
     FILE *pArchAlumno = fopen(AR_ALUMNOS, "rb");
     stAlumno a;
     int i=0;
     if (pArchAlumno){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumno)>0){
            if (a.edad>=edad){
                i++;
            }
        }


        fclose(pArchAlumno);
     }
    return i;
 }


/// 9. Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un
/// rango de edades específico (por ejemplo, entre 17 y 25 años). Dicho rango debe recibirse
/// por parámetro. Modularizar

/***************************************************
 * \brief MOSTRAR ALUMNO SEGUN RANGO DE EDAD
 * \return VOID
 ***************************************************/

void mostrarAlumnosRangoEdad (int edad, int edad2)
{
    FILE *pArchAlumno = fopen(AR_ALUMNOS, "rb");
    stAlumno a;

    printf("\nEL nombre de los alumnos que estan dentro del rango de edad son: \n");

    if (pArchAlumno){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumno)>0){
            if (a.edad>=edad && a.edad<=edad2){
                printf("%s\n", a.nombreYapellido);
            }
        }
        fclose(pArchAlumno);
    }
}

/// 10. Dado un archivo de alumnos, mostrar el los datos del alumno de mayor edad. Modularizar.

/***************************************************
 * \brief MOSTRAR ALUMNOS MAYORES DE EDAD
 * \return VOID
 ***************************************************/

void mostrarAlumnosMayoresEdad (int edad)
{
    FILE *pArchAlumno = fopen(AR_ALUMNOS, "rb");
    stAlumno a;

    printf("\nLos alumnos mayores de edad son: \n");

    if (pArchAlumno){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumno)>0){
            if (a.edad>=edad){
                mostrarUnAlumno(a);
            }
        }
        fclose(pArchAlumno);
    }
}

/// 12. Crear una función que reciba como parámetro un arreglo de tipo alumno y l o copie en el
/// archivo.

/***************************************************
 * \brief CARGAR EL ARREGLO DE ALUMNOS
 * \param ARREGLO DE ALUMNOS
 * \param VALIDOS
 * \return VOID
 ***************************************************/

int cargarArregloAlumnos (stAlumno b[], int dimension)
{
    char opcion;
    int i=0;

    printf("\nCargando el arreglo de alumnnos\n");
    while (i<dimension && opcion!=ESC){
        b[i] = cargarUnAlumno();
        i++;

        printf("\nPresione ESC para salir...\n");
        opcion = getch();
        system("cls");
    }
    return i;
}

/***************************************************
 * \brief COPIAR ARREGLO AL ARCHIVO
 * \param ARREGLO DE ALUMNOS
 * \param VALIDOS
 * \return VOID
 ***************************************************/

void copiaArregloToArchivo (stAlumno b[], int v)
{
    FILE *pArchAlumno = fopen(AR_ALUMNOS, "ab");

    if (pArchAlumno){
        fwrite(b, sizeof(stAlumno), v, pArchAlumno);
        fclose(pArchAlumno);
    }
}

/// 15. Dado un archivo de alumnos, hacer una función que i nvierta l os elementos del mismo. No
/// se puede usar otro archivo auxiliar ni un arreglo auxiliar. Debe trabajar sobre el archivo.
/// Puede utilizar variables de tipo alumno auxiliares.

void invierteElementosArchivo ()
{
    FILE *pArchAlumnos = fopen(AR_ALUMNOS, "rb");
    stAlumno a;
    if (pArchAlumnos){
        fseek(pArchAlumnos, (-1)*sizeof(stAlumno), SEEK_END);
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumnos)>0){
            mostrarUnAlumno(a);
        }
        fclose(pArchAlumnos);
    }

}

