#include <iostream>
#include <stdio.h>
#include <string.h> // Biblioteca para string
#include <stdlib.h> //Biblioteca parq system

using namespace std;

struct Nodo
{
 int digito;
 Nodo * sig;
};

void pop(Nodo *& Pila ,int& digito);
void push(Nodo *&Pila,int digito);
Nodo* sumarPila(Nodo*&,Nodo*&, Nodo*&, Nodo*&);
Nodo* sumarColaPila(Nodo*&Pila3,Nodo *&cFte,Nodo *&cFin);
void leerNumero(char linea[],Nodo * &Pila1);
void encolar(Nodo *&cFte,Nodo *&cFin,int);
void desencolar(Nodo *&cFte,Nodo *&cFin, int &);
void mostrarCola(Nodo *&cFte,Nodo *&cFin);

int main()
{
  Nodo* Pila1;
  Nodo* Pila2;
  Nodo* cFte;
  Nodo* cFin;
  Nodo* Pila3;
  Nodo* ptr;
  Nodo* ptrRes;
  FILE* archTXT;
  char linea[10];

  archTXT = fopen("num.txt","r");
  fgets(linea,10,archTXT);
  linea[strlen(linea)-1]='\0';//donde esta el \n pongo \0
  if (!feof(archTXT))
  {

    leerNumero(linea,Pila1);
    fgets(linea,10,archTXT);
    linea[strlen(linea)-1]='\0';
    if (!feof(archTXT))
    {
       leerNumero(linea,Pila2);
       ptr= sumarPila(Pila1,Pila2,cFte,cFin);
       fgets(linea,10,archTXT);

       while (!feof(archTXT))
       {
         linea[strlen(linea)-1]='\0';
         leerNumero(linea,Pila3);
         ptrRes= sumarColaPila(Pila3,cFte,cFin);
         fgets(linea,10,archTXT);
       }
       cout<<"\nla suma de todos los numeros del archivo es: "<<endl;
       mostrarCola(cFte,cFin);
    }
    else
    {
        cout<<"Error"<<endl;
    }
  }
  else
   {
        cout<<"Error"<<endl;
   }
   fclose(archTXT);
   return 0;
}

void leerNumero(char linea[],Nodo* &Pila)
{
 Pila= NULL;
 int i;
 int digito;

 i=0;
 while (linea[i]!='\0')
 {
  digito=(linea[i]-48);
  push(Pila,digito);
  i= i + 1;
 }
 return;
}

void push(Nodo *&Pila,int digito)
{
  Nodo * Nuevo = new Nodo();
  Nuevo->digito = digito;
  Nuevo->sig = Pila;
  Pila = Nuevo;
  return;
}

void pop(Nodo *&Pila,int &digito )
{
  Nodo *ptr;

  digito = Pila->digito;
  ptr = Pila;
  Pila= Pila->sig;
  delete ptr;
  return;
}


Nodo* sumarPila(Nodo *&Pila1,Nodo *&Pila2, Nodo *&cFte, Nodo *&cFin)
{
  cFte = NULL;
  cFin = NULL;
  int digito1;
  int digito2;
  int suma;

  while (Pila1 !=NULL && Pila2 != NULL)
  {
    pop(Pila1,digito1);
    pop(Pila2,digito2);
    suma = digito1+digito2;
    encolar(cFte,cFin,suma);
  }
  if (Pila1==NULL)
  {
   while (Pila2!= NULL)
   {
    pop(Pila2,digito2);
    encolar(cFte,cFin,digito2);
   }
  }
  else
  {
   while (Pila1!=NULL)
   {
    pop(Pila1,digito1);
    encolar(cFte,cFin,digito1);
   }
  }
  return cFte;
}

Nodo* sumarColaPila(Nodo *&Pila,Nodo *&cFte,Nodo *&cFin)
{
  Nodo* cFteRes = NULL;
  Nodo* cFinRes = NULL;
  int carry=0;
  int digito1;
  int digito2;
  int suma;

  while (Pila!= NULL && cFte!=NULL)
  {
   pop(Pila,digito1);
   desencolar(cFte,cFin,digito2);
   suma= digito1+digito2+carry;
   if (suma >=10)
   {
    carry= 1;
    suma= suma-10;
   }
   else
   {
    carry=0;
   }
   encolar(cFteRes,cFinRes,suma);
  }
  if (Pila==NULL && cFte==NULL)
  {
    encolar(cFteRes,cFinRes,carry);
  }
  else
  {
   while (cFte!=NULL)
   {
    desencolar(cFte,cFin,digito2);
    encolar(cFteRes,cFinRes,digito2+carry);
    carry= 0;
   }

   while (Pila!=NULL)
   {
    pop(Pila,digito1);
    encolar(cFteRes,cFinRes,digito1+carry);
    carry= 0;
   }
  }
  cFte= cFteRes;
  cFin= cFinRes;
  return cFte;
}

void encolar(Nodo *&cFte,Nodo *&cFin,int suma)
{
  Nodo * nuevo= new Nodo();
  nuevo->digito = suma;
  nuevo->sig = NULL;
  if (cFte== NULL)
  {
   cFte= nuevo;
  }
  else
  {
   cFin->sig= nuevo;
  }
  cFin= nuevo;
  return;
}

void desencolar(Nodo *&cFte,Nodo *&cFin, int &digito)
{
 digito= cFte->digito;
 Nodo * ptr = cFte;
 cFte= cFte->sig;
 delete ptr;
 if (cFte == NULL)
 {
  cFin= NULL;
 }
 return;
}

void mostrarCola(Nodo *&cFte,Nodo *&cFin)
{
  int digito;

  while (cFte!=NULL)
  {
   desencolar(cFte,cFin,digito);
   cout<<digito;
  }
  system("pause");
}
