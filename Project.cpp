#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <iomanip>
using namespace std;

struct registro{
    int  NR;       // Numero de registro
    char dato[12]; // Nombre herramienta
    double  precio;   // Precio
    int  cantidad;  // Cantidad
    int  PD;
    int  PI;
    int  ARE;
}r, a;

struct encabezado{
    int NRS;    // numero de registros
    int RAIZ;
    int URE;
}e;

FILE *fd;
int lr, le;   // longitud de registro y encabezado

/*                Funcion Escribir Archivo
---------------------------------------------------------*/
void escribir()
{
    int x, pos;
    char rpt, lado;

    if( (fd=fopen("arbol_binario.txt", "w+"))==NULL )
    {
        cout << " No se creo el archivo arbol_binario.txt"<< endl;
        return;
    }
    // Inicializando variables
    e.NRS  = 0;
    e.RAIZ = -1;
    e.URE  = -1;
    fwrite(&e, le, 1, fd);

    do{
        r.NR = ++e.NRS;
        fflush(stdin);
        cout << " Nombre : "; gets(r.dato);
        cout << " Stock  : "; cin >> r.cantidad;
        cout << " Precio : "; cin >> r.precio;
        r.PI = -1;
        r.PD = -1;
        r.ARE = 0;
        fseek(fd, 0, 2);  // al final
        fwrite(&r, lr, 1, fd);
        cout <<"1."<<endl;
        if(e.RAIZ == -1)
        {
            e.RAIZ = r.NR;
            cout << " * Raiz" << endl;
        }
        else
        {
            x = e.RAIZ;

            while( x != -1 )
            {
                cout <<"2."<<endl;
                pos = (x-1)*lr + le;
                fseek(fd, pos, SEEK_SET);
                fread(&a, lr, 1, fd);

                if( strcmp(r.dato, a.dato)>0 ){
                    x = a.PD;
                    lado = 'D';
                    continue;
                }
                if( strcmp(r.dato, a.dato)<0 ){
                    x = a.PI;
                    lado = 'I';
                    continue;
                }

            }
            if(lado=='D')
            {
                a.PD = r.NR;
                cout << " * Lado der. de "<< a.dato << endl;
            }
            if(lado=='I')
            {
                a.PI = r.NR;
                cout << " * Lado izq. de "<< a.dato << endl;
            }
            cout <<"3."<<endl;
            fseek(fd, pos, SEEK_SET);
            fwrite(&a, lr, 1, fd);
            cout <<"4."<<endl;
        }

        cout << " Mas registros [s/n]: "; cin >> rpt;
        cout << endl;
    }while(rpt!='n');

    fseek(fd, 0, SEEK_SET);
    fwrite(&e, le, 1, fd);
    fclose(fd);
}

/*                Funcion Mostrar Archivo
---------------------------------------------------------*/
void mostrar()
{
    if( (fd=fopen("arbol_binario.txt", "r"))==NULL )
    {
        cout << " No se pudo abrir el archivo"<< endl;
        return;
    }

    fread(&e, le, 1, fd);

    cout << " -----------------------------------"   << endl;
    cout << " |  NRS: " << e.NRS << "    RAIZ: " ;
    cout << e.RAIZ << "    URE: " << e.URE << "   |" << endl;
    cout << " -----------------------------------"   << endl<<endl;

    cout << setw(3) << "NR" << setw(10) << "NOMBRE" << setw(10 ) << " STOCK " << " CANTIDAD " <<setw(10 );
    cout << "PI" << setw(5) << "PD" << setw(6) << "ARE" << endl << endl;


    while(fread(&r, lr, 1, fd)!=NULL)
    {
        cout << " " << r.NR << "\t" << r.dato;
        cout << "\t" << r.cantidad << "\t" << r.precio;
        cout << "\t\t" << r.PI << "\t" << r.PD;
        cout << "\t" << r.ARE << endl;
    }
/*
    fread(&r, lr, 1, fd);
    while( !feof(fd) )
    {
        cout << setw(3) << r.NR << setw(10) << r.dato;
        cout << setw(5) << r.PI << setw(5) << r.PD;
        cout << setw(5) << r.ARE << endl;
        fread(&r, lr, 1, fd);
    }
*/
    fclose(fd);
}

/*                   Funcion Leer
---------------------------------------------------------*/
void leer()
{
    int x, pos;
    bool band;
    char v_dato[12];

    if( (fd=fopen("arbol_binario.txt", "r"))==NULL )
    {
        cout << " No se pudo abrir ela archivo"<< endl;
        return;
    }

    fflush(stdin);
    cout << " Nombre : "; gets(v_dato);
    fread(&e, le, 1, fd);
    x = e.RAIZ;
    band = false;

    while( x != -1 )
    {
        pos = (x-1)*lr + le;
        fseek(fd, pos, SEEK_SET);
        fread(&r, lr, 1, fd);

        if( strcmp(v_dato, r.dato)>0 ) {
            x = r.PD;
            continue;
        }
        if( strcmp(v_dato, r.dato)<0 ) {
            x = r.PI;
            continue;
        }

        band = true;
        cout << "\n >> Dato " << r.dato << " encotrado..!" << endl;
        break;
    }

    if(band==false)
        cout << "\n\n >> No existe..!" << endl;

    fclose(fd);
}

/*                  Funcion Insertar
---------------------------------------------------------*/
void insertar()
{
    int x, pos;
    char rpt, lado;

    if( (fd=fopen("arbol_binario.txt", "r+"))==NULL )
    {
        cout << "Error al abrir archivo"<< endl;
        return;
    }

    fread(&e, le, 1, fd);

    do{
        r.NR = ++e.NRS;
        fflush(stdin);
        cout << " Nombre : "; gets(r.dato);

        r.PI = -1;
        r.PD = -1;
        r.ARE = 0;
        fseek(fd, 0, SEEK_END);  // al final
        fwrite(&r, lr, 1, fd);

        if(e.RAIZ == -1)
        {
            e.RAIZ = r.NR;
            cout << " * Raiz" << endl;
        }
        else
        {
            x = e.RAIZ;

            while( x != -1 )
            {
                pos = (x-1)*lr + le;
                fseek(fd, pos, SEEK_SET);
                fread(&a, lr, 1, fd);

                if( strcmp(r.dato, a.dato)>0 ){
                    x = a.PD;
                    lado = 'D';
                    continue;
                }
                if( strcmp(r.dato, a.dato)<0 ){
                    x = a.PI;
                    lado = 'I';
                    continue;
                }
            }
            if(lado=='D')
            {
                a.PD = r.NR;
                cout << " * Lado der. de "<< a.dato << endl;
            }
            if(lado=='I')
            {
                a.PI = r.NR;
                cout << " * Lado izq. de "<< a.dato << endl;
            }

            fseek(fd, pos, SEEK_SET);
            fwrite(&a, lr, 1, fd);
        }

        cout << " Insertar mas registros [s/n]: "; cin >> rpt;
        cout << endl;
    }while(rpt!='n');

    fseek(fd, 0, SEEK_SET);
    fwrite(&e, le, 1, fd);
    fclose(fd);
}

/*                 Funcion Eliminar
---------------------------------------------------------*/
void eliminar_registro()
{
    cout << "\n\n Implementando..!" << endl;
}

/*                 Funcion Eliminar Archivo
---------------------------------------------------------*/
void eliminar_archivo()
{
    remove("arbol_binario.txt");
    cout << " >> Archivo arbol_binario.txt eliminado..!" << endl;
}

/*                 Menu de Opcion
---------------------------------------------------------*/
void menu()
{
    cout << "\t\t ARBOLES BINARIOS DE BUSQUEDA EN ARCHIVOS \n\n";
    cout << "\t 1. Escribir              \n";
    cout << "\t 2. Mostrar               \n";
    cout << "\t 3. Leer                  \n";
    cout << "\t 4. Insertar              \n";
    cout << "\t 5. Eliminar Registro     \n";
    cout << "\t 6. Eliminar Archivo      \n";
    cout << "\t 7. Salir                 \n";
    cout << "\t >> Ingrese opcion:  ";
}

/*                 Funcion Principal
---------------------------------------------------------*/
int main()
{
    int op;  // opcion
    lr = sizeof(struct registro);
    le = sizeof(struct encabezado);

    do
    {
        menu(); cin >> op; cout << "\n\n";

        switch(op)
        {
            case 1:
                escribir(); break;
            case 2:
                mostrar(); break;
            case 3:
                leer(); break;
            case 4:
                insertar(); break;
            case 5:
                eliminar_registro(); break;
            case 6:
                eliminar_archivo(); break;
            case 7:
                exit(0);
        }
        cout <<"\n\n ";
        system("pause"); system("cls");

    }while(op>0);

    return 0;
}
