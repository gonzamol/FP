// DAMASO SANCHEZ ARENAS & GONZALO MOLINA DIAZ. GRUPO 1F
// VERSION 3
// LABORATORIO 2

#include <iostream> // bibliotecas
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

const int META = 31;
typedef enum {automata, persona, nadie} tJugador; 

// Cabeceras de las funciones
tJugador pasaCalculadora(); 
//Funcion que conduce el desarrollo el juego: intercambia turno, suma hasta la meta y elige el ganador
tJugador quienEmpieza(); // decide quien empieza la partida: el automata o el usuario
bool mismaFila (int ultimo, int nuevo); // determina si el nuevo digito elegido pertenece a la misma fila que el ultimo elegido por el rival
bool mismaColumna (int ultimo, int nuevo); // determina si el nuevo digito elegido pertenece a la misma columna que el ultimo elegido por el rival
bool digitoValido (int ultimo, int nuevo); // determina si el nuevo digito cumple las reglas del juego respecto al ultimo
void muestraTeclado(); // muestra por consola el teclado del juego
int digitoAleatorio(); // genera un numero aleatorio
int digitoAutomata(int ultimo); // genera numeros aleatorios para que el automata juegue (cumpliendo las restricciones)
int digitoPersona(); // el usuario elige por primera vez el numero con el que empieza el juego (cumpliendo las restricciones) 
int digitoPersona(int ultimo); // el usuario elige el nuevo digito respecto al ultimo elegido por el automata de modo que cumpla los requisitos
int menu(); // menu que presenta las opciones del juego
bool mostrar(string nombArch); // funcion encargada de mostrar el archivo 
bool actInforme(int jugadas, int ganadas, int abandonos);
void muestraTeclado();
// funcion que crea un archivo donde introduce las partidas jugadas, partidas ganadas y partidas abandonadas


int main() { // las funciones int son las que llaman a las funciones bool.
	int op;
	int jugadas = 0, ganadas = 0, abandonos =0;
	tJugador ganador, turno;
	string nombre;
	bool informebien;
	srand(time(NULL)); //Establece la semilla de los numeros aleatorios.
	cout << " Bienvenido a pasa Calculadora" << endl;
	cout << " \250Como te llamas? ";
	getline (cin, nombre);
	cout << " Hola " << nombre << endl << endl;
	op = menu();

	while (op!=0){
		switch(op){
		case 1:
			{
				ganador = pasaCalculadora();
				jugadas++;
				if (ganador==automata){
					cout << " Lo siento, has perdido. ";
					ganadas++;
				}

				else if (ganador==persona){
					cout << " Enhorabuena, has ganado!!! ";
				}

				else {
					cout << " Has abandonado la partida. ";
					abandonos++;
				}
				cout << endl << endl;
			}
			break;
		case 2:
			{
				mostrar("versionPC.txt");
			}
			break;
		}
		op = menu();
	
	}

	informebien = actInforme (jugadas, ganadas, abandonos);
	if (informebien){
		cout << " El archivo informePC se ha actualizado. " << endl;
	}
	else {
		cout << " El archivo informePC ha sido creado. " << endl;
	}

	
	cout << " Hasta la proxima " << nombre;
	return 0;
}

tJugador pasaCalculadora(){ 
	tJugador turno,ganador;
	int suma = 0, ultimo;
	turno = quienEmpieza(); // llama a la funcion quienEmpieza para decidir si empieza el usuario o el automata 
	cout << " Bienvenido a Pasa la Calculadora. Juguemos! " << endl;

	if (turno == automata){ //en caso de que comience la partida el automata
		ultimo = digitoAleatorio();
		cout << " Empiezo yo, elijo el " << ultimo << endl;
		suma= suma+ultimo;
		turno=persona;
		cout << " Suma = " << suma << endl << endl;
	}

	else { // en caso de que comience la partidas el usuario
		cout << " Empieza el usuario: " << endl;
		ultimo= digitoPersona();
		suma= suma+ultimo;
		if(ultimo!=0){ // si el digito introducido por el usuario es distinto de 0, la partida continuará con normalidad
			turno=automata;
			cout << " Suma = " << suma << endl << endl;
		}
		else{ // si el usuario introduce un 0, abandonará la partida y volverá al menú
			turno=nadie;
		}
		
	}

	while ((suma<META) && turno != nadie ) { // mientras que la suma no supere la META y no se haya abandonado, se entra en el bucle

		if (turno==persona){ // intercambia el turno entre ambos jugadores y suma ultimo+nuevo constantemente para ver si la meta es superada
			cout << " Es tu turno. " << endl; 
			ultimo= digitoPersona(ultimo);
			suma= suma+ultimo;

			if(ultimo!=0){
				turno=automata;
				cout << " Suma = " << suma << endl;
			}

			else{
				turno=nadie;
			}
		}


		else {
			ultimo = digitoAutomata(ultimo);
			cout << " Me toca, elijo el " << ultimo << endl;
			suma= suma+ultimo;
			turno=persona;
			cout << " Suma = " << suma << endl;
		}
		cout << endl;
	}

	if ((turno==automata) && suma>=META){ // muestra en pantalla el ganador de la partida ó si el usuario ha abandonado el juego
		ganador=automata;
	}

	else if ((turno==persona) && suma>=META){
		ganador=persona;
	}

	else {
		ganador=nadie;
	}

	return ganador;

}

tJugador quienEmpieza() { // si devuelve 0 empieza el automata, si devuelve 1 empieza el usuario
	tJugador jugador;
	int n;
	n=rand() % (2); // genera un numero aleatorio: 0 ó 1

	if (n == 0) {
		jugador = automata;
	}
	else {
		jugador = persona;
	}

	return jugador;
}

int digitoPersona (){ //utilizada cuando el juego le empieza el usuario, muestra el tablero por pantalla 
	int n;
	muestraTeclado(); // llama a la funcion void para mostrar el teclado del juego
	cin >> n;
	cout << endl;

	while(n<0 || n>9) { // te pide de nuevo el digito si no cumple los requisitos (que esté entre 0 y 9, ambos incluidos)
		cout << " El numero elegido no es valido. Pruebe de nuevo. " << endl;
		muestraTeclado();
		cin >> n;
	}

	return n;
}

int digitoPersona (int ultimo){// utilizada cuando el juego ya ha empezado y es tu turno

	int nuevo;
	nuevo=digitoPersona();
	
	while (nuevo!=0 && digitoValido(ultimo, nuevo)==false) { 
		
		cout << " Error. No cumple los requisitos del juego " << endl;
		nuevo=digitoPersona();
	}

	return nuevo;
}

int digitoAleatorio(){ /*Genera un numero aleatorio entre 1-9. Utilizas esta funcion para cuando el automata empieza la partida,
	                   entre otras cosas*/
	int n;
	n=(rand() % 9) + 1;

	return n;
} 

bool mismaFila(int ultimo, int nuevo){ // devuelve true si se nuevo esta en la misma fila que ultimo y false en caso contrario
	return (((nuevo-1)/3)==((ultimo-1)/3));
}

bool mismaColumna (int ultimo, int nuevo){ // devuelve true si se nuevo esta en la misma columna que ultimo y false en caso contrario
	return (((nuevo-1)%3)==((ultimo-1)%3));
}

bool digitoValido (int ultimo, int nuevo)  { //El numero sera valido cuando este en la misma fila, misma columna y nuevo sea distinto a ultimo.
	bool valido=false;
	
	if (( mismaColumna(ultimo,nuevo) || mismaFila(ultimo,nuevo))  && (ultimo!=nuevo)){
		valido=true;
	}

	return valido;
}

int digitoAutomata ( int ultimo) { // genera un aleatorio para el automata de modo que cumpla las reglas del juego respecto al ultimo
	int nuevo;
	nuevo=digitoAleatorio(); 
	
	while (digitoValido(ultimo,nuevo)==false) { /*generará nuevos digitos aleatorios hasta llegar a uno que cumpla las reglas del juego 
											 	y devolverá dicho digito*/
		nuevo=digitoAleatorio();
	}
	
	return nuevo;

	}

int menu(){ //muestra por pantallas las opciones dadas para elegir la que se desee
	int op;
	cout << " Selecciona una opcion. " << endl;
	cout << " 1. Jugar " << endl;
	cout << " 2. Acerca de " << endl;
	cout << " 0. Salir " << endl; 
	cout << " Opcion: " ;
	cin >> op;
	

	while(op >2){
		cout<<  " Opcion no valida. Introduzca de nuevo: " <<endl;
		cout << " 1. Jugar " << endl;
		cout << " 2. Acerca de " << endl;
		cout << " 0. Salir " << endl; 
		cout << " Opcion: " ;
		cin >> op;	
	}

	cout << endl;
	return op;
}

bool mostrar(string nombArch) {
	ifstream entrada;
	char c;
	entrada.open(nombArch); //abre al archivo
	bool muestra=false;

	if (entrada.is_open()){
		muestra = true;
		entrada.get(c); // toma el primer caracter del archivo (va caracter a caracter)
	
		while (!entrada.fail()){ // no saldrá del while hasta que no haya caracteres
			cout << c; // muestra los caracteres por pantalla
			entrada.get(c); // va tomando caracter a caracter de uno en uno
		}
	}

	else {
		cout  << " No se ha encontrado el archivo " << endl << endl;
	}
	
	cout << endl;
	entrada.close();
	return muestra;
}

bool actInforme(int jugadas, int ganadas, int abandonos){
	ifstream entrada;
	ofstream salida;
	int ses, jug, gan, ab, ejecuciones, totalJugadas, ganadasAutomata, abandonadas;
	entrada.open("informePC.txt"); //abre el archivo informe
	bool muestra = false;

	if (entrada.is_open()){ // si consigue abrirlo, muestra el archivo
		muestra = true;
		entrada >> ses;
		entrada >> jug;
		entrada >> gan;
		entrada >> ab;
		entrada.close(); // aqui lee lo que hay en el archivo y lo guarda en las variables declaradas
		
		ejecuciones = ses + 1;
		totalJugadas = jug + jugadas;
		ganadasAutomata = gan + ganadas;
		abandonadas = ab + abandonos;

		salida.open("informePC.txt"); // crea un archivo en el que suma lo leido anteriormente más las partidas ganadas/jugadas/abandonos

	}

	else {

		salida.open("informePC.txt");
		ejecuciones = 1;
		totalJugadas = jugadas;
		ganadasAutomata = ganadas;
		abandonadas = abandonos;
	}

		salida <<  ejecuciones << endl;
		salida << totalJugadas << endl;
		salida << ganadasAutomata << endl;
		salida << abandonadas << endl;
		salida.close();

	return muestra;
}

void muestraTeclado() {
	cout << " 7   8   9 " <<endl;    
	cout << " 4   5   6 " <<endl; 
	cout << " 1   2   3 " <<endl << endl;
	cout << " Introduce un numero entre 0-9 (0 para abandonar): " ;
}