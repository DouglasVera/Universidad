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
	string categoriaPelicula;

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
void registroSesiones(Sesiones *&pCabSes,Sesiones *&pFinSes);
void registroPeliculas(Peliculas *&pCabPeli,Peliculas *&pFinPeli);
void MostrarCine(Cine *pCabCine);
Salas *fun_buscarSala(Salas *pCabSala,string codigo);
void listarSala(Salas *pCabSalas);
void listarSesiones(Sesiones *pCabSes);
Peliculas *fun_buscarPeli(Peliculas *pCabPeli,string codigo);
void listarPeliculas(Peliculas *pCabPeli);
void MostrarSala(Salas *pCabSalas);
void MostrarSes(Sesiones *pCabSes);
void MostrarPeliculas(Peliculas *pCabPeli);
void eliminarCine(Cine *&pCabCine,Cine *direliminar,Cine *direxAnt);
Cine *fun_Cineanterior(Cine *pCabCine,string dato);
Salas *fun_Salaanterior(Salas *pCabSala,string dato);
void eliminarSala(Cine *&pCabCine,Cine *&pFinCine,Salas *direliminar,Salas *direxAnt);
Sesiones *fun_Sesionesanterior(Sesiones *pCabSes,string dato);
void eliminarSesiones(Cine *&pCabCine,Cine *&pFinCine,Salas *&pCabSala,Salas *&pFinSala,Sesiones *direliminar,Sesiones *direxAnt);
Peliculas *fun_Peliculasanterior(Peliculas *pCabPeli,string dato);
void eliminarPeliculas(Cine *&pCabCine,Cine *&pFinCine,Salas *&pCabSala,Salas *&pFinSala,Sesiones *&pCabSes,Sesiones *&pFinSes,Peliculas *direliminar,Peliculas *direxAnt);
Peliculas *fun_buscarPeliCate(Peliculas *pCabPeli,string codigo);

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
	Cine *dirCine=NULL,*dirCineAnt=NULL ;
    Salas *dirSala=NULL, *aux1=NULL, *antSala=NULL;
    Sesiones *dirSesion=NULL, *aux2=NULL, *anteSes=NULL;
	Peliculas *dirPeli=NULL, *aux3=NULL, *antePeli=NULL, *bus=NULL;
	Cine *dirEliminar, *aux=NULL;
	int resp;
	string dato, datoS, datoSs, datoSsS, k,dt;
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
					MostrarCine(pCabCine);
					break;
				case 4:
					cout<<"Ingrese el numero de cedula que va a eliminar: ";
					cin>>dato;
					if (fun_buscarCine(pCabCine,dato)==NULL){
					cout<<"El dato ingresado para buscar no exite"<<endl;	
					}else{
			 			//llamar la funcion eliminar
			 			eliminarCine(pCabCine,fun_buscarCine(pCabCine,dato),fun_Cineanterior(pCabCine,dato));
			 			cout<<"Usuario ELiminado";
					}
					break;
				}
			break;
		case 2:
			system("cls");
			resp=menuRegistro();
			switch(resp){
				case 1:
					MostrarCine(pCabCine);
					cout<<"CODIGO DEL CINE:";
					cin>>dato;
					dirCine=fun_buscarCine(pCabCine,dato);
					registroSalas(dirCine->pCabSalas,dirCine->pFinSalas);	
					fflush(stdin);
					break;
				case 2:
					MostrarCine(pCabCine);
					cout<<"CODIGO CINE:";
					cin>>dato;
					dirCine=fun_buscarCine(pCabCine,dato);
					if(dirCine!=NULL){
						cout<<"INGRESE LA SALA A MODIFICAR: "<<endl;
						cin>>dato;
						aux1 = fun_buscarSala(dirCine->pCabSalas,dato);
						if(aux1==NULL){
							cout<<"El numero a modificar no existe en la lista"<<endl;
						}else{
							cout<<"INGRESE EL NOMBRE NUEVO DE LA SALA: ";
							getline(cin,aux1->nomSala);
							cout<<"INGRESE DIA DE LA FUNCION NUEVO: ";
							getline(cin,aux1->diaSala);
							cout<<"INGRESE CATEGORIA DE SALA NUEVO: 3D O NORMAL";
							getline(cin,aux1->categoriaSala);
						}
					}
					break;
				case 3:
					int a;
					do{
						cout<<"SALAS DISPONIBLES DE CADA SUCURSAL"<<endl;
						cout<<"Codigo cine: ";cin>>dato;
						dirCine=fun_buscarCine(pCabCine,dato);
						if(dirCine!=NULL){
							MostrarSala(dirCine->pCabSalas);
						}
					cout<<"Salas de cine de cada sucursal: "; cin>>a;
					}while (a==1);
					break;
				case 4:
					cout<<"Ingrese el numero de cedula del usuario: ";
					fflush(stdin);getline(cin,dato);
					aux=fun_buscarCine(pCabCine,dato);
					if (aux==NULL){
						cout<<"El dato ingresado para buscar no exite"<<endl;	
					}else{
			   			listarSala(aux->pCabSalas);
			   			cout<<endl;
			   			cout<<"Ingrese el numero que desea eliminar: ";
			   			fflush(stdin);getline(cin,datoS);
			   			aux1=fun_buscarSala(aux->pCabSalas,datoS);
			   			if(aux1==NULL){
			   			cout<<"El dato ingresado para buscar no exite"<<endl;
			   			}else{
			   				antSala=fun_Salaanterior(aux->pCabSalas,datoS);
			   				eliminarSala(aux,aux,aux1,antSala);
			   				cout<<"Sala eliminada "<<endl;
			   			}
					}
					break;
				}
			break;
		case 3:
			system("cls");
			resp=menuRegistro();
			switch(resp){
				case 1:
					MostrarCine(pCabCine);
		     		cout<<"CODIGO CINE:";
					cin>>dato;
					dirCine=fun_buscarCine(pCabCine,dato);
					if(dirCine!=NULL){
						MostrarSala(dirCine->pCabSalas);
				 		cout<<"CODIGO SALA:";
				    	cin>>datoS;
						dirSala=fun_buscarSala(dirCine->pCabSalas,datoS);
						registroSesiones(dirSala->pCabSes,dirSala->pFinSes);	
						fflush(stdin);
					}else{
						cout<<"Dato no existente"<<endl;
						break;
					}
					break;				 	
				case 2:
					MostrarCine(pCabCine);
					cout<<"CODIGO CINE:";
					cin>>dato;
					dirCine=fun_buscarCine(pCabCine,dato);
					if(dirCine!=NULL){
				 		cout<<"CODIGO SALA:";
				    	cin>>datoS;
						MostrarSala(dirCine->pCabSalas);
						dirSala=fun_buscarSala(dirCine->pCabSalas,datoS);
						if(dirSala!=NULL){
							cout<<"INGRESE LA SESION A MODIFICAR: "<<endl;
							cin>>datoSs;
							aux2 = fun_buscarSes(dirSala->pCabSes,datoSs);
							if(aux2==NULL){
								cout<<"El numero a modificar no existe en la lista"<<endl;
							}else{
								cout<<"INGRESE EL NOMBRE NUEVO: ";
								getline(cin,aux2->nomSes);
								cout<<"INGRESE DIA DE LA FUNCION NUEVO: ";
								getline(cin,aux2->horaSes);
								cout<<"INGRESE CATEGORIA DE SALA NUEVO: ";
								getline(cin,aux2->calificacion);
							}
						}
					}
					break;
				case 3:
					int a;
					do{
						cout<<"SALAS DISPONIBLES DE CADA SUCURSAL"<<endl;
						cout<<"Codigo cine: ";cin>>dato;
						dirCine=fun_buscarCine(pCabCine,dato);
						if(dirCine!=NULL){
							int b;
							do{
								cout<<"SESIONES DISPONIBLES DE LA SALA"<<endl;
								cout<<"Codigo Sala: ";cin>>datoS;
								dirSala=fun_buscarSala(dirCine->pCabSalas,datoS);
								if(dirSala!=NULL){
									MostrarSes(dirSala->pCabSes);
								}
							cout<<"SESIONES DISPONIBLE DE LA SALA: consultar(1) menu(2)"; cin>>a;
							}while (b==1);
						}
					cout<<"SALA DISPONIBLES DEL CINE: consultar(1) menu(2)"; cin>>a;
					}while (a==1);
					break;
				case 4:
					cout<<"CODIGO CINE: ";
					fflush(stdin);getline(cin,dato);
					aux=fun_buscarCine(pCabCine,dato);
					if (aux!=NULL){
						cout<<"CODIGO SALA: ";
						fflush(stdin);getline(cin,datoS);
						aux1=fun_buscarSala(aux->pCabSalas,datoS);
						if (aux1==NULL){
							cout<<"El dato ingresado para buscar no exite"<<endl;	
						}else{
			   				listarSesiones(dirSala->pCabSes);
			   				cout<<endl;
			   				cout<<"CODIGO DE LA SESION A ELIMINAR: ";
			   				fflush(stdin);getline(cin,datoSs);
			   				aux2=fun_buscarSes(aux1->pCabSes,datoSs);
			   				if(aux2==NULL){
			   				cout<<"El dato ingresado para buscar no exite"<<endl;
			   				}else{
			   					anteSes=fun_Sesionesanterior(aux1->pCabSes,datoSs);
			   					eliminarSesiones(aux,aux,aux1,aux1,aux2,anteSes);
			   					cout<<"Sesion eliminada "<<endl;
			   				}
						}
					}
					break;
				}
			break;
		case 4:
			system("cls");
			resp=menuRegistro();
			switch(resp){
				case 1:
					MostrarCine(pCabCine);
		     		cout<<"CODIGO CINE:";
					cin>>dato;
					dirCine=fun_buscarCine(pCabCine,dato);
					if(dirCine!=NULL){
						MostrarSala(dirCine->pCabSalas);
				 		cout<<"CODIGO SALA:";
				    	cin>>datoS;
						dirSala=fun_buscarSala(dirCine->pCabSalas,datoS);
						if(dirSala!=NULL){
							MostrarSes(dirSala->pCabSes);
				 			cout<<"CODIGO SESION:";
				    		cin>>datoSs;
							dirSesion=fun_buscarSes(dirSala->pCabSes,datoSs);
							registroPeliculas(dirSesion->pCabPeli,dirSesion->pFinPeli);
							fflush(stdin);
						}else{
							cout<<"Dato no existente"<<endl;
							break;
						}
					}else{
						cout<<"Dato no existente"<<endl;
						break;
					}
					break;				 	
				case 2:
					MostrarCine(pCabCine);
					cout<<"CODIGO CINE:";
					cin>>dato;
					dirCine=fun_buscarCine(pCabCine,dato);
					if(dirCine!=NULL){
						MostrarSala(dirCine->pCabSalas);
				 		cout<<"CODIGO SALA:";
				    	cin>>datoS;
						dirSala=fun_buscarSala(dirCine->pCabSalas,datoS);
						if(dirSala!=NULL){
							MostrarSes(dirSala->pCabSes);
							cout<<"CODIGO SESION: "<<endl;
							cin>>datoSs;
							dirSesion = fun_buscarSes(dirSala->pCabSes,datoSs);
							if(dirSesion!=NULL){
								MostrarSes(dirSala->pCabSes);
								cout<<"INGRESE LA PELICULA A MODIFICAR: "<<endl;
								cin>>datoSsS;
								aux3 = fun_buscarPeli(dirSesion->pCabPeli,datoSsS);
								if(aux3==NULL){
									cout<<"La pelicula a modificar no existe en la lista"<<endl;
								}else{
									cout<<"INGRESE EL NOMBRE NUEVO: ";
									getline(cin,aux3->nomPeli);
									cout<<"INGRESE DIA DE LA FUNCION NUEVO: ";
									getline(cin,aux3->descriccionP);
									cout<<"INGRESE PROTRAGONISTA DE SALA NUEVO: ";
									getline(cin,aux3->protragonistas);
									cout<<"INGRESE CATEGORIA DE SALA NUEVO: ";
									getline(cin,aux3->categoriaPelicula);
								}
							}
						}
					}
					break;
				case 3:
					int a;
					do{
						cout<<"SALAS DISPONIBLES DE CADA CINE"<<endl;
						cout<<"Codigo cine: ";cin>>dato;
						dirCine=fun_buscarCine(pCabCine,dato);
						if(dirCine!=NULL){
							int b;
							do{
								cout<<"SESIONES DISPONIBLES DE LA SALA"<<endl;
								cout<<"Codigo Sala: ";cin>>datoS;
								dirSala=fun_buscarSala(dirCine->pCabSalas,datoS);
								if(dirSala!=NULL){
									int c;
									do{
										cout<<"SESIONES DISPONIBLES DE LA SALA"<<endl;
										cout<<"Codigo Sala: ";cin>>datoS;
										dirSesion=fun_buscarSes(dirSala->pCabSes,datoSs);
										if(dirSesion!=NULL){
											MostrarPeliculas(dirSesion->pCabPeli);
										}
									cout<<"PELICULAS DISPONIBLES EN LA SESION: regreso(1) salir(2)"; cin>>a;
									}while (c==1);
								}
							cout<<"SESIONES DISPONIBLE DE LA SALA: regreso(1) salir(2)"; cin>>a;
							}while (b==1);
						}
					cout<<"SALAS DISPONIBLES DEL CINE: regreso(1) salir(1) "; cin>>a;
					}while (a==1);
					break;
				case 4:
					cout<<"CODIGO CINE: ";
					fflush(stdin);getline(cin,dato);
					aux=fun_buscarCine(pCabCine,dato);
					if (aux!=NULL){
						cout<<"CODIGO SALA: ";
						fflush(stdin);getline(cin,datoS);
						aux1=fun_buscarSala(aux->pCabSalas,datoS);
						if (aux1!=NULL){
							cout<<"CODIGO SESION: ";
							fflush(stdin);getline(cin,datoSsS);
							aux2=fun_buscarSes(aux1->pCabSes,datoSs);
							if (aux2==NULL){
								cout<<"El dato ingresado para buscar no exite"<<endl;	
							}else{
			   					listarPeliculas(aux2->pCabPeli);
			   					cout<<endl;
			   					cout<<"CODIGO DE LA PELICULA A ELIMINAR: ";
			   					fflush(stdin);getline(cin,datoSsS);
			   					aux3=fun_buscarPeli(aux2->pCabPeli,datoSsS);
			   					if(aux3==NULL){
			   						cout<<"El dato ingresado para buscar no exite"<<endl;
			   					}else{
			   						antePeli=fun_Peliculasanterior(aux2->pCabPeli,datoSsS);
			   						eliminarPeliculas(aux,aux,aux1,aux1,aux2,aux2,aux3,antePeli);
			   						cout<<"Pelicula eliminada "<<endl;
			   					}
							}
						}
					}
					break;
				}
			break;
		case 5:
			int a;
			do{
				cout<<"SALAS DISPONIBLES DE CADA SUCURSAL"<<endl;
				cout<<"Codigo cine: ";cin>>dato;
				dirCine=fun_buscarCine(pCabCine,dato);
				if(dirCine!=NULL){
					MostrarSala(dirCine->pCabSalas);
				}
			cout<<"Salas de cine de cada sucursal: "; cin>>a;
			}while (a==1);
			break;
		case 6:
			dirCine=pCabCine;
			if(dirCine!=NULL){
				dirSala=dirCine->pCabSalas;
				if (dirSala!=NULL){
					dirSesion=dirSala->pCabSes;
					if (dirSesion!=NULL){
						dirPeli=dirSesion->pCabPeli;
						cout<<"BUSCAR PELICULA: "<<endl;
						cin>>dt;
						bus=fun_buscarPeli(dirPeli,dt);
           				if(bus!=NULL){
							cout<<"NO SE A ENCONTRADO PELICULAS"<<endl;
						}else{
							MostrarPeliculas(bus);
						}
					}
				}
			}
			break;
		case 7:
			dirCine=pCabCine;
			if(dirCine!=NULL){
				dirSala=dirCine->pCabSalas;
				if (dirSala!=NULL){
					dirSesion=dirSala->pCabSes;
					if (dirSesion!=NULL){
						dirPeli=dirSesion->pCabPeli;
						cout<<"BUSCAR Y MODIFICAR PELICULA: "<<endl;
						cin>>dt;
						bus=fun_buscarPeli(dirPeli,dt);
           				if(bus!=NULL){
							cout<<"NO SE A ENCONTRADO PELICULAS"<<endl;
						}else{
							cout<<"INGRESE EL NOMBRE NUEVO: ";
							getline(cin,bus->nomPeli);
							cout<<"INGRESE DIA DE LA FUNCION NUEVO: ";
							getline(cin,bus->descriccionP);
							cout<<"INGRESE PROTRAGONISTA DE SALA NUEVO: ";
							getline(cin,bus->protragonistas);
							cout<<"INGRESE CATEGORIA DE SALA NUEVO: ";
							getline(cin,bus->categoriaPelicula);
						}
					}
				}
			}
			break;
		case 8:
			dirCine=pCabCine;
			if(dirCine!=NULL){
				dirSala=dirCine->pCabSalas;
				if (dirSala!=NULL){
					dirSesion=dirSala->pCabSes;
					if (dirSesion!=NULL){
						dirPeli=dirSesion->pCabPeli;
						cout<<"BUSCAR PELICULA POR CATEGORIA: TODO PUBLICO +13 +18"<<endl;
						cin>>dt;
						bus=fun_buscarPeliCate(dirPeli,dt);
           				if(bus!=NULL){
							do{
								MostrarPeliculas(bus->sgtePeli);
								break;
							}while(fun_buscarPeliCate(dirPeli,dt));
							
						}	
					}
				}
			}
			break;
		case 9:
			if(pCabCine==NULL){
				cout<<"NO SE A ENCOTRADO INFORMACION"<<endl;
			}else{
				listarCine(pCabCine);
			}
			break;
		case 10:
			exit;
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
		cout<<"Codigo de Cine: "<<pActual->codCine<<endl;
		cout<<"Nombre de Cine: "<<pActual->nomCine<<endl;
		cout<<"Direccion de la sucursal: "<<pActual->direccionCine<<endl;
		cout<<endl;
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

void MostrarSala(Salas *pCabSalas){
	Salas *pActual=pCabSalas;
	while(pActual!=NULL){
		cout<<"\tCodigo de la Sala: "<<pActual->codSala<<endl;
		cout<<"\tNombre de la Sala: "<<pActual->nomSala<<endl;
		cout<<"\tDia de la funcion: "<<pActual->diaSala<<endl;
		cout<<"\tctegoria: 3D Normal: "<<pActual->categoriaSala<<endl;
		cout<<endl;
		pActual=pActual->sgteSala;
	}
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

void MostrarSes(Sesiones *pCabSes){
	Sesiones *pActual=pCabSes;
	while(pActual!=NULL){
		cout<<"\t\tCodigo de la Sesion: "<<pActual->codSes<<endl;
		cout<<"\t\tNombre de la Sesion: "<<pActual->nomSes<<endl;
		cout<<"\t\thora de la funcion: "<<pActual->horaSes<<endl;
		cout<<"\t\tCalificacion: TB +13 +18: "<<pActual->calificacion<<endl;
		cout<<endl;
		pActual=pActual->sgteSes;
	}
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
	cout<<"Ingrese los CATEGORIA DE LA PELICULA:";
	fflush(stdin); getline(cin,newNodo->categoriaPelicula);
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

void MostrarPeliculas(Peliculas *pCabPeli){
	Peliculas *pActual=pCabPeli;
	while(pActual!=NULL){
		cout<<"\t\t\tCodigo Pelicula: "<<pActual->codPeli<<endl;
		cout<<"\t\t\tNombre de la Pelicula: "<<pActual->nomPeli<<endl;
		cout<<"\t\t\tDescriccion de la Pelicula: "<<pActual->descriccionP<<endl;
		cout<<"\t\t\tProtragonistas: "<<pActual->protragonistas<<endl;
		cout<<"\t\t\tCategoria de la Pelicula: "<<pActual->categoriaPelicula<<endl;
		cout<<endl;
		pActual=pActual->sgtePeli;
	}
}

void listarCine(Cine *pCabCine){
	Cine *pActual=pCabCine;
	while(pActual!=NULL){
	    cout<<"CODIGO DE LA SUCURSAL: "<<pActual->codCine<<endl;
	    cout<<"NOMBRE DE LA SUCURSAL: "<<pActual->nomCine<<endl;
	    cout<<"DIRECCION DONDE ESTA UBICADA: "<<pActual->direccionCine<<endl;
		cout<<endl;
		listarSala(pActual->pCabSalas);
		//alterar bucle
		pActual=pActual->sgteCine;
	}
}

void listarSala(Salas *pCabSalas){
	Salas *pActual=pCabSalas;
	while(pActual!=NULL){
	    cout<<"\tCODIGO DE LA SALA: "<<pActual->codSala<<endl;
	    cout<<"\tNOMBRE DE LA SALA: "<<pActual->nomSala<<endl;
	    cout<<"\tDIA DE LA FUNCION: "<<pActual->diaSala<<endl;
		cout<<"\tCATEGORIA: 3D O HD "<<pActual->categoriaSala<<endl;
		cout<<endl;
		listarSesiones(pActual->pCabSes);
		//alterar bucle
		pActual=pActual->sgteSala;
	}
}

void listarSesiones(Sesiones *pCabSes){
	Sesiones *pActual=pCabSes;
	while(pActual!=NULL){
	    cout<<"\t\tCODIGO SESION: "<<pActual->codSes<<endl;
	    cout<<"\t\tNOMBRE SESION: "<<pActual->nomSes<<endl;
	    cout<<"\t\tDURACION DE LA PELICULA: "<<pActual->horaSes<<endl;
		cout<<"\t\tCATEGORIA: TODO PUBLICO MAYORES DE 13 MAYORES DE 18 "<<pActual->calificacion<<endl;
		cout<<endl;
		listarPeliculas(pActual->pCabPeli);
		//alterar bucle
		pActual=pActual->sgteSes;
	}
}

void listarPeliculas(Peliculas *pCabPeli){
	Peliculas *pActual=pCabPeli;
	while(pActual!=NULL){
	    cout<<"\t\t\tCODIGO DE LA PELICULA: "<<pActual->codPeli<<endl;
	    cout<<"\t\t\tNOMBRE DE LA pELICULA: "<<pActual->nomPeli<<endl;
	    cout<<"\t\t\tDESCRICCION DE LA PELICULA: "<<pActual->descriccionP<<endl;
		cout<<"\t\t\tPROTRAGONISTAS: "<<pActual->protragonistas<<endl;
		cout<<"\t\t\tCATEGORIA DE LA PELICULA: "<<pActual->categoriaPelicula<<endl;
		cout<<endl;
		//alterar bucle
		pActual=pActual->sgtePeli;
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

Peliculas *fun_buscarPeli(Peliculas *pCabPeli,string codigo){
	Peliculas *pActual=pCabPeli;
	while(pActual!=NULL){
          if(pActual->codPeli==codigo){
          	return pActual;
		  }
		//alterar bucle
		pActual=pActual->sgtePeli;		
	}	
	return NULL;
}

void eliminarCine(Cine *&pCabCine,Cine *direliminar,Cine *direxAnt){
Cine *direccion;
	if(pCabCine==direliminar){
		//el nodo a eliminar es la cabecera 
		pCabCine=direliminar->sgteCine;
		delete(direliminar);
	}else{
		if(direliminar->sgteCine!=NULL){
		direxAnt->sgteCine=direliminar->sgteCine;
		delete(direliminar);	
		}else{
		direxAnt->sgteCine=direliminar->sgteCine;
		delete(direliminar);	
		}
	}
	
}

Cine *fun_Cineanterior(Cine *pCabCine,string dato){
	Cine *nodoAct=pCabCine;
	Cine *direccion;
	while(nodoAct->sgteCine!=NULL)
{
    if (nodoAct->sgteCine->codCine==dato) {
        direccion=nodoAct;
    }
    	nodoAct=nodoAct->sgteCine;
}
return direccion;
}

Salas *fun_Salaanterior(Salas *pCabSala,string dato){
	Salas *nodoAct=pCabSala;
	Salas *direccion;
	while(nodoAct->sgteSala!=NULL){
    if (nodoAct->sgteSala->codSala==dato) {
        direccion=nodoAct;
    }
    	nodoAct=nodoAct->sgteSala;
	}
	return direccion;
}

void eliminarSala(Cine *&pCabCine,Cine *&pFinCine,Salas *direliminar,Salas *direxAnt){
	Salas *direccion;
	if(pCabCine->pCabSalas==direliminar){
		//el nodo a eliminar es la cabecera
		pCabCine->pCabSalas=direliminar->sgteSala; 
		//pcab=di;
		delete(direliminar);
		
	}else{
		if(direliminar->sgteSala!=NULL){
			direxAnt->sgteSala=direliminar->sgteSala;
			delete(direliminar);	
		}else{
			direxAnt->sgteSala=direliminar->sgteSala;
			pFinCine->pFinSalas=direxAnt;
		delete(direliminar);	
		}
	}
	
}

Sesiones *fun_Sesionesanterior(Sesiones *pCabSes,string dato){
	Sesiones *nodoAct=pCabSes;
	Sesiones *direccion;
	while(nodoAct->sgteSes!=NULL){
    if (nodoAct->sgteSes->codSes==dato) {
        direccion=nodoAct;
    }
    	nodoAct=nodoAct->sgteSes;
	}
	return direccion;
}

void eliminarSesiones(Cine *&pCabCine,Cine *&pFinCine,Salas *&pCabSala,Salas *&pFinSala,Sesiones *direliminar,Sesiones *direxAnt){
	Sesiones *direccion;
	if(pCabCine->pCabSalas->pCabSes==direliminar){
		//el nodo a eliminar es la cabecera
		pCabCine->pCabSalas->pCabSes=direliminar->sgteSes; 
		//pcab=di;
		delete(direliminar);
		
	}else{
		if(direliminar->sgteSes!=NULL){
			direxAnt->sgteSes=direliminar->sgteSes;
			delete(direliminar);	
		}else{
			direxAnt->sgteSes=direliminar->sgteSes;
			pFinCine->pFinSalas->pFinSes=direxAnt;
		delete(direliminar);	
		}
	}
	
}

Peliculas *fun_Peliculasanterior(Peliculas *pCabPeli,string dato){
	Peliculas *nodoAct=pCabPeli;
	Peliculas *direccion;
	while(nodoAct->sgtePeli!=NULL){
    if (nodoAct->sgtePeli->codPeli==dato) {
        direccion=nodoAct;
    }
    	nodoAct=nodoAct->sgtePeli;
	}
	return direccion;
}

void eliminarPeliculas(Cine *&pCabCine,Cine *&pFinCine,Salas *&pCabSala,Salas *&pFinSala,Sesiones *&pCabSes,Sesiones *&pFinSes,Peliculas *direliminar,Peliculas *direxAnt){
	Sesiones *direccion;
	if(pCabCine->pCabSalas->pCabSes->pCabPeli==direliminar){
		//el nodo a eliminar es la cabecera
		pCabCine->pCabSalas->pCabSes->pCabPeli=direliminar->sgtePeli; 
		delete(direliminar);
		
	}else{
		if(direliminar->sgtePeli!=NULL){
			direxAnt->sgtePeli=direliminar->sgtePeli;
			delete(direliminar);	
		}else{
			direxAnt->sgtePeli=direliminar->sgtePeli;
			pFinCine->pFinSalas->pFinSes->pCabPeli=direxAnt;
			delete(direliminar);	
		}
	}
	
}

Peliculas *fun_buscarPeliCate(Peliculas *pCabPeli,string codigo){
	Peliculas *pActual=pCabPeli;
	while(pActual!=NULL){
          if(pActual->categoriaPelicula==codigo){
          	return pActual;
		  }
		//alterar bucle
		pActual=pActual->sgtePeli;		
	}	
	return NULL;
}
