#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<Windows.h>
using namespace std;

void gotoxy(int x,int y){
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}


struct Peliculas{
	string codPeli;
	string nomPeli;
	string descriccionP;
	string protragonistas;

	Peliculas *sgtePeli;
	Peliculas *antePeli;
};

struct Sesiones{
	string codSes;
	string nomSes;
	string horaSes;
	string calificacion;
	Peliculas *pCabPeli=NULL;
	Peliculas *pFinPeli=NULL;

	Sesiones *sgteSes;
	Sesiones *anteSes;
};

struct Salas{
	string codSala;
	string nomSala;
	string diaSala;
	string categoriaSala; // si es en 3D o normal
	Sesiones *pCabSes=NULL;
	Sesiones *pFinSes=NULL;

	Salas *sgteSala;
	Salas *anteSala;
};

struct Cine{
	string codCine;
	string nomCine;
	string direccionCine;
	Salas *pCabSalas=NULL;
	Salas *pFinSalas=NULL;

	Cine *sgteCine;
	Cine *anteCine;
};

int menu();
void operaciones(int op,Cine *&pCabCine,Cine *&pFinCine);
int menuRegistro();
void registroCine(Cine *&pCabCine,Cine *&pFinCine);
void listarCine(Cine *pCabCine);
Cine *fun_buscarCine(Cine *pCabCine,string codigo);
Sesiones *fun_buscarSes(Sesiones *pCabSes,string codigo);
void registroSalas(Salas *&pCabSalas,Salas *&pFinSalas);
void MostrarCine(Cine *pCabCine);
Salas *fun_buscarSala(Salas *pCabSala,string codigo);

int main(){
    setlocale(LC_CTYPE,"spanish");
	Cine *pCabCine=NULL;
	Cine *pFinCine=NULL;

    int op;
    do{
		system("cls");
        op=menu();
		operaciones(op,pCabCine,pFinCine);
		cout<<"Desea realizar otra operacion si(1): ";
		cin>>op;
		fflush(stdin);
    }while(op==1);
    getch();
    return 0;
}

int menu(){
	int op;
	cout<<"\t |      MENU PRINCIPAL    | "<<endl;
	cout<<"1. REGISTRAR CINES"<<endl;
	cout<<"2. REGISTRAR SALAS"<<endl;
	cout<<"3. REGISTRAR SESIONES"<<endl;
	cout<<"4. REGISTRAR PELICULAS"<<endl;
	cout<<"5. VISUALIZAR INFORMACION EN UNA SALA CONCRETA"<<endl;	
	cout<<"6. BUSCAR PELICULA"<<endl;
	cout<<"7. MODIFICAR UNA PELICULA DE CONCRETA"<<endl;
	cout<<"8. LISTAR PELICULAS POR EDADES"<<endl; //TP = todo publico, M13 = mayores de 13, M18 = mayores de 18
	cout<<"9. LISTAR CARTELERAS DE TODAS LAS EMPRESAS"<<endl;
	cout<<"10. SALIR"<<endl;
	do{
	cout<<endl;
	cout<<"DIGITE LA OPCION A UTILIZAR: ";
    cin>>op;
    fflush(stdin);
    	if(op<1||op>10){
    		cout<<"OPCION INCORRECTA.."<<endl<<endl;
		}
	}while(op<1||op>10);
return op;
}

void operaciones(int op,Cine *&pCabCine,Cine *&pFinCine){
	Cine *dirNodo=NULL,*dirNodoAnt=NULL ;
    Salas *dirSala=NULL, *aux1=NULL;
    Sesiones *dirSesion=NULL;
	Peliculas *dirPeli=NULL;
	Cine *dirEliminar, *aux=NULL;
	int resp;
	string dato;
	switch(op){
		case 1:
			system("cls");
			resp=menuRegistro();
			switch(resp){
				case 1:
					registroCine(pCabCine,pFinCine);
					break;
				case 2:
					cout<<"INGRESE EL SUCURSAL A MODIFICAR: "<<endl;
					cin>>dato;
					aux = fun_buscarCine(pCabCine,dato);
					if(aux==NULL){
						cout<<"El numero a modificar no existe en la lista"<<endl;
					}else{
						cout<<"INGRESE EL NOMBRE NUEVO: ";
						cin>>aux->nomCine;
						cout<<"INGRESE LA DIRECCION NUEVO: ";
						cin>>aux->direccionCine;
					}
					break;
				case 3:
					listarCine(pCabCine);
					break;
				case 4:

					break;
				}
			break;
		case 2:
			system("cls");
			resp=menuRegistro();
			switch(resp){
				case 1:
					int res;
					cout<<"CODIGO DEL CINE:";
					cin>>dato;
					MostrarCine(pCabCine);
					dirNodo=fun_buscarCine(pCabCine,dato);
					registroSalas(dirNodo->pCabSalas,dirNodo->pFinSalas);	
					fflush(stdin);
					break;
				case 2:
					cout<<"INGRESE EL SUCURSAL A MODIFICAR: "<<endl;
					cin>>dato;
					aux1 = fun_buscarSala(dirNodo->pCabSalas,dato);
					if(aux1==NULL){
						cout<<"El numero a modificar no existe en la lista"<<endl;
					}else{
						cout<<"INGRESE EL NOMBRE NUEVO: ";
						cin>>aux1->nomSala;
						cout<<"INGRESE DIA DE LA FUNCION NUEVO: ";
						cin>>aux1->diaSala;
						cout<<"INGRESE CATEGORIA DE SALA NUEVO: ";
						cin>>aux1->categoriaSala;
					}
					break;
				case 3:
					listarCine(pCabCine);
					break;
				case 4:

					break;
				}
			break;
		case 3:
			system("cls");
			resp=menuRegistro();
			
			break;
		case 4:
			system("cls");
			resp=menuRegistro();
			
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
	}
}

int menuRegistro(){
	int h;
	cout<<"\t |           MENU           | "<<endl;
	cout<<"1. INGRESO"<<endl;		
	cout<<"2. MODIFICAR"<<endl;
	cout<<"3. LISTAR"<<endl;
	cout<<"4. ELIMINAR"<<endl;
	do{
	cout<<endl;
	cout<<"DIGITE LA OPCION A UTILIZAR: ";
    cin>>h;
    fflush(stdin);
    	if(h<1||h>4){
    		cout<<"OPCION INCORRECTA.."<<endl<<endl;
		}
	}while(h<1||h>4);
	return h;
}

void registroCine(Cine *&pCabCine,Cine *&pFinCine){
	Cine *newNodo = new(Cine);
	//lectura de los datos
	cout<<"         |     DATOS DEL CINE    |         "<<endl;
	cout<<"Ingrese el código dela sucursal: ";
	cin>>newNodo->codCine;
	cout<<"Ingrese el nombre de la sucursal: ";
	fflush(stdin); getline(cin,newNodo->nomCine);
	cout<<"Ingrese la direccion de la sucursal:";
	fflush(stdin); getline(cin,newNodo->direccionCine);
	//crear el nodoProducto
	newNodo->sgteCine=NULL;
	newNodo->anteCine=NULL;	
		if(pCabCine==NULL){
			pCabCine=newNodo;		
		}else{
		     pFinCine->sgteCine=newNodo;
		     newNodo->anteCine=pFinCine;
		}	
		pFinCine=newNodo;
}

void MostrarCine(Cine *pCabCine){
	Cine *pActual=pCabCine;
	while(pActual!=NULL){
		cout<<"Codigo Provincia: "<<pActual->nomCine<<endl;
		cout<<"Nompre provincia: "<<pActual->direccionCine<<endl;
		pActual=pActual->sgteCine;
	}
}

void registroSalas(Salas *&pCabSalas,Salas *&pFinSalas){
	Salas *newNodo = new(Salas);
	//lectura de los datos
	cout<<"         |     DATOS DEL SALA    |         "<<endl;
	cout<<"Ingrese el código Sala: ";
	cin>>newNodo->codSala;
	cout<<"Ingrese el nombre Sala: ";
	fflush(stdin); getline(cin,newNodo->nomSala);
	cout<<"Ingrese la Dia de la Funcion: ";
	fflush(stdin); getline(cin,newNodo->diaSala);
	cout<<"Ingrese los catrgoria en 3D o Normal: ";
	fflush(stdin); getline(cin,newNodo->categoriaSala);
	//crear el nodoProducto
	newNodo->sgteSala=NULL;
	newNodo->anteSala=NULL;	
		if(pCabSalas==NULL){
			pCabSalas=newNodo;		
		}else{
		     pFinSalas->sgteSala=newNodo;
		     newNodo->anteSala=pFinSalas;
		}	
		pFinSalas=newNodo;
}

void registroSesiones(Sesiones *&pCabSes,Sesiones *&pFinSes){
	Sesiones *newNodo = new(Sesiones);
	//lectura de los datos
	cout<<"         |     DATOS DEL SESIONES    |         "<<endl;
	cout<<"Ingrese el código Sesiones: ";
	cin>>newNodo->codSes;
	cout<<"Ingrese el nombre Sesiones: ";
	fflush(stdin); getline(cin,newNodo->nomSes);
	cout<<"Ingrese la Hora de Funcion:";
	fflush(stdin); getline(cin,newNodo->horaSes);
	cout<<"Ingrese los catrgoria al publico:";
	fflush(stdin); getline(cin,newNodo->calificacion);
	//crear el nodoProducto
	newNodo->sgteSes=NULL;
	newNodo->anteSes=NULL;	
		if(pCabSes==NULL){
			pCabSes=newNodo;		
		}else{
		     pFinSes->sgteSes=newNodo;
		     newNodo->anteSes=pFinSes;
		}	
		pFinSes=newNodo;
}

void registroPeliculas(Peliculas *&pCabPeli,Peliculas *&pFinPeli){
	Peliculas *newNodo = new(Peliculas);
	//lectura de los datos
	cout<<"         |     DATOS DEL PELICULAS    |         "<<endl;
	cout<<"Ingrese el código Pelicula: ";
	cin>>newNodo->codPeli;
	cout<<"Ingrese el nombre Pelicula: ";
	fflush(stdin); getline(cin,newNodo->nomPeli);
	cout<<"Ingrese la direccion Pelicula:";
	fflush(stdin); getline(cin,newNodo->descriccionP);
	cout<<"Ingrese los protragonistas:";
	fflush(stdin); getline(cin,newNodo->protragonistas);
	//crear el nodoProducto
	newNodo->sgtePeli=NULL;
	newNodo->antePeli=NULL;	
		if(pCabPeli==NULL){
			pCabPeli=newNodo;		
		}else{
		     pFinPeli->sgtePeli=newNodo;
		     newNodo->antePeli=pFinPeli;
		}	
		pFinPeli=newNodo;
}

void listarCine(Cine *pCabCine){
	Cine *pActual=pCabCine;
	while(pActual!=NULL){
	    cout<<"CODIGO DE LA SUCURSAL: "<<pActual->codCine<<endl;
	    cout<<"NOMBRE DE LA SUCURSAL: "<<pActual->nomCine<<endl;
	    cout<<"DIRECCION DONDE ESTA UBICADA: "<<pActual->direccionCine<<endl;
		cout<<endl;
		//alterar bucle
		pActual=pActual->sgteCine;
	}
}

Cine *fun_buscarCine(Cine *pCabCine,string codigo){
	Cine *pActual=pCabCine;
	while(pActual!=NULL){
          if(pActual->codCine==codigo){
          	return pActual;
		  }
		//alterar bucle
		pActual=pActual->sgteCine;		
	}	
	return NULL;
}

Salas *fun_buscarSala(Salas *pCabSala,string codigo){
	Salas *pActual=pCabSala;
	while(pActual!=NULL){
          if(pActual->codSala==codigo){
          	return pActual;
		  }
		//alterar bucle
		pActual=pActual->sgteSala;		
	}	
	return NULL;
}

Sesiones *fun_buscarSes(Sesiones *pCabSes,string codigo){
	Sesiones *pActual=pCabSes;
	while(pActual!=NULL){
          if(pActual->codSes==codigo){
          	return pActual;
		  }
		//alterar bucle
		pActual=pActual->sgteSes;		
	}	
	return NULL;
}
