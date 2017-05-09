
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int CARTASPORPALO = 13, MAXCARTAS = 53, CENTINELA = 52, MAZOTRESMONTONES=21;
typedef enum {picas, treboles, diamantes, corazones} tPalo;
typedef enum {as, dos, tres, cuatro, cinco, seis, siete, ocho, nueve, diez, jota, qu, ka} tNumero;
typedef int tCarta; // define tCarta como sinonimo de int
typedef tCarta tMazo [MAXCARTAS];

void crearMazoVacio (tMazo mazo); 
int cuantasEnMazo (const tMazo mazo); 
tPalo darPalo (tCarta carta); 
tNumero darNumero (tCarta carta); 
void escribirCarta (tCarta carta); 
void escribirMazo (const tMazo mazo); 
bool cargarMazo (tMazo mazo); 
void barajarMazo (tMazo mazo); 
bool unirMazos (tMazo mazoOriginal, const tMazo nuevoMazo); // *
bool partirMazo (tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino); 
void cortarMazo (tMazo mazo, int cuantas);
void guardarMazo (const tMazo mazo); 
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirIntercalando (const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo); //MIRAR
void trucoTresMontones(); 
void trucoPosada();
int menu();
tCarta transformacion (int n, char c);


int main(){
	srand(time(NULL)); //Establece la semilla de los numeros aleatorios.
	tMazo mazoOriginal, mazoNuevo,nuevoMazo, mazo,mazoNegro,mazoRojo, mazoAltas, mazoBajas;
	bool mostrar=false,cargar2,unir;
	int cuantas=0,op,enCuantosMazos,queMazoPido;

	cout << "RECUERDE SI DESEA BARAJAR,UNIR,CORTAR O GUARDAR UN MAZO, ANTES DEBE CARGARLE!! " <<endl <<endl;
	op = menu();

	while (op!=0){
		switch (op){
			case 1: 
				mostrar = cargarMazo(mazo);
				if (mostrar){
					cout << " El mazo es el siguiente : " <<endl<<endl;
					escribirMazo(mazo);
				}
				else 
					cout << "El archivo no existe" << endl;
			break;
			case 2:
					barajarMazo(mazo);
					cout << " El mazo ha sido barajado. " <<endl<<endl;
					escribirMazo(mazo);
			break;
			case 3: 
				cargar2 = cargarMazo(nuevoMazo);
				if (cargar2){
					unir = unirMazos(mazo, nuevoMazo);
					if (unir){
						cout << " La union ha tenido exito. "<<endl;
						escribirMazo(mazo);
					}

					else{
						cout << "No se ha podido unir. Revise que ha hecho el procedimiento bien"<<endl <<endl ;
					}
				}

				else {
					cout << "El archivo donde esta el mazo que desea unir al original no existe. " <<endl <<endl;
				}
				
			break;
			case 4:
				cout << " Introduce cuantas cartas deseas cortar del mazo: " ;
				cin >> cuantas;
				cortarMazo(mazo, cuantas);
				escribirMazo(mazo);
			break;
			case 5:
				guardarMazo (mazo);
			break;
			case 6:
				repartirNegroRojo(mazo,mazoNegro,mazoRojo);
				cout << " El mazo Rojo es: " <<endl<<endl;
				escribirMazo(mazoRojo);
				cout << " El mazo Negro es: " <<endl<<endl;
				escribirMazo(mazoNegro);
			break;
			case 7:
				repartirBajaAlta(mazo,mazoBajas,mazoAltas);
				cout << " El mazo de bajas es: " <<endl<<endl;
				escribirMazo(mazoBajas);
				cout << " El mazo de altas es: " <<endl<<endl;
				escribirMazo(mazoAltas);
			break;
			case 8:
				//cout << " Introduce en cuantos mazos quiere dividir " <<endl;
				//cin >> enCuantosMazos;
				cout << " introduce que mazo te pides " <<endl;
				cin >> queMazoPido;

				repartirIntercalando(mazo,3,queMazoPido,mazoNuevo);
				cout << " El mazo que has elegido es : " <<endl;
				escribirMazo(mazoNuevo);
			break;
			case 9:
				trucoTresMontones();
			break;
			case 10:
				trucoPosada();
			break;
		}

		op=menu();
	}

	return 0;
}

void crearMazoVacio(tMazo mazo){
	mazo[0]=CENTINELA; // conseguimos el mazo vacio colocando el centinela en la primera posicion del array
}

int cuantasEnMazo (const tMazo mazo){
	int i=0;
	while (mazo[i]!= CENTINELA){ // cuenta el numero de posiciones totales del mazo
	i++;
	}

	return i;
}

tPalo darPalo (tCarta carta){
	return tPalo (carta/ CARTASPORPALO); // se obtiene el palo de la carta dada. Se consigue gracias al enumerado tPalo donde en cada posicion hay un palo determinado
}

tNumero darNumero (tCarta carta){
	return tNumero(carta% CARTASPORPALO); // se obtiene el numero de la carta dada. Se consigue gracias al enumerado tNumero donde en cada posicion hay un numero determinado
}

void escribirCarta (tCarta carta){ // escribe la carta por consola mostrando primero el numero y a continuacion su palo
	tPalo tipo = darPalo(carta);
	tNumero num = darNumero(carta);
	string palo, numero;
	if (tipo == picas)
		palo = "picas";
	else if (tipo == treboles)
		palo = "treboles";
	else if (tipo == diamantes)
		palo = "diamantes";
	else 
		palo = "corazones";

	if (num>diez){
		if (num == jota)
			numero = "J";
		else if (num == qu)
			numero = "Q"; 
		else
			numero = "K";
	}

	else if (num==as)
		numero= "AS";

	else {
		cout << int(num)+1; // para el resto de numeros que no son figuras ni as
	}

	cout << numero << " de " << palo <<endl;
}

bool cargarMazo (tMazo mazo){ // carga el mazo dentro del array metiendo una carta en cada posicion del array
	int i=0, n;
	char c;
	bool existe=true;
	ifstream entrada;
	string nombArch;
	cout << "Nombre de archivo:" ;
	cin >> nombArch;
	cout <<endl;
	entrada.open(nombArch); // abre el archivo donde se encuentran las futuras cartas a cargar

	if (!entrada.is_open())
		existe=false;

	else {
		entrada >> c;
		entrada >> n;
	
		while (!entrada.fail() && i<MAXCARTAS){
				mazo[i]=transformacion(n,c); // hace la transformacion del archivo a la forma de enumerado
				i++;
				entrada >> c;
				entrada >> n;
		}
			mazo[i] = CENTINELA; //CUANDO ACABE EL MAZO LA POSICION SIGUIENTE ES PARA EL CENTINELA
			entrada.close();
	}
	return existe; // devolverá el mazo cargado o false, que conllevará a error
}

void escribirMazo(const tMazo mazo){ // escribe el mazo sirviendose de la funcion escribirCarta. muestra carta a carta 
	int i=0;
	while (mazo[i] != CENTINELA){
		escribirCarta(mazo[i]);
		i++;
	}
	cout << endl;
}

void barajarMazo (tMazo mazo){ //barajea el mazo de cartas el triple de veces que el numero de cartas que haya en el mazo
	// para ello intercambia una posicion por otras las veces determinadas
	int aleatorio1, aleatorio2, cuantas;
	//int i=0;
	tCarta aux; // nos servimos de un tCarta auxiliar para realizar el intercambio correctamente
	cuantas = cuantasEnMazo(mazo);
		/*while ( i < cuantas*3){*/
		for (int i=0; i<cuantas*3; i++){														
		aleatorio1 = rand() % ((cuantas -1) +1);
		aleatorio2 = rand() % ((cuantas -1) +1);

		aux = mazo[aleatorio1];
		mazo[aleatorio1] = mazo[aleatorio2];
		mazo[aleatorio2] = aux;
		//i++;
	}
}

bool unirMazos (tMazo mazoOriginal, const tMazo nuevoMazo){ // añade al final de un mazoOriginal un nuevoMazo, siendo mazoOriginal la suma de ambos al finalizar la funcion

	bool unir=true;
	int cuantasTotal=0 ,i=0,cuantasOriginal, cuantasNuevo;

	cuantasOriginal = cuantasEnMazo(mazoOriginal); // numero de cartas del mazoOriginal
	cuantasNuevo = cuantasEnMazo (nuevoMazo); // numero de cartas del nuevoMazo
	cuantasTotal= cuantasOriginal + cuantasNuevo; // suma de ambas

	if (cuantasTotal > CENTINELA)
		unir = false;

	else {
		 /*while (cuantasOriginal <= cuantasTotal)*/
		for (cuantasOriginal; cuantasOriginal <= cuantasTotal; cuantasOriginal++){		//se pone el <= para que la primera posicion del nuevoMazo se sobreescriba sobre la ultima de mazoOriginal donde está el centinela											 //
			mazoOriginal[cuantasOriginal] = nuevoMazo[i];
			//cuantasOriginal++;
			i++;
		}
	}
	return unir;
}

bool partirMazo (tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino){ // parte el mazo por cuantasCoger, llevando una parte a mazoDestino y modificando mazoOrigen quitandole
	// lo movido a mazoDestino
	int cuantas, i=0, j=0;
	bool partir = true;
	cuantas = cuantasEnMazo(mazoOrigen);

	//cout << "Indica el numero de cartas que quieres coger: ";
	//cin >> cuantasCoger;

	if (cuantasCoger > cuantas){
		mazoDestino[i] = CENTINELA;
		partir = false;
	}

	else{

		while (i<cuantasCoger){ // while para modificar el mazoDestino   //CAMBIAR POR FOOOOOORRRRRRR
			mazoDestino[i]= mazoOrigen[i];
			i++;
		}
		mazoDestino[i]= CENTINELA; // siempre colocamos el centinela al final de cada mazo

		/*while (j<cuantas){*/ // while para modificar el mazoOrigen, desplaza a la izquierda rellenando las posiciones vacias de mazoOrigen
		for (j; j<cuantas; j++){ //En el for no podemos poner int j=0; porque la j la usaremos despues del for, luego hay que declarala en la funcion entera no solo en el for.
		mazoOrigen[j] = mazoOrigen[j+cuantasCoger];
			//j++;
		}
		mazoOrigen[j] = CENTINELA;
	}

	return partir;

}

void cortarMazo(tMazo mazo, int cuantas){ // se sirve de partirMazo para "intercambiar" de posiciones el mazo por cuantas
	int cuantasHay;
	tMazo mazoAux;
	bool cortado, unir;
	cuantasHay = cuantasEnMazo(mazo);

	if (cuantas > cuantasHay)
		cout << "El mazo no ha sido modificado " ;

	else{

		cortado=partirMazo(mazo, cuantas, mazoAux); // primero parte el mazo en dos gracias al mazo auxiliar

		if (cortado)
			unir=unirMazos(mazo, mazoAux); // si es cierto que ha sido cortado se unen inversamente //teniamos unirMazos(mazoAux, mazo) pero no funcionaba, pensar xq asi si!

		else 
			cout << " No se cortaron los mazos. " << endl;

		}
}

void guardarMazo (const tMazo mazo){ // guarda el mazo escribiendolo en un archivo en el formato de archivo
	ofstream salida;
	string nombreArchivo;
	int i =0;
	
	cout << " Nombre del fichero a guardar en mazo: " ;
	cin >> nombreArchivo;
	salida.open(nombreArchivo);

	while(mazo[i]!=CENTINELA){
	tPalo palo = darPalo(mazo[i]);
	tNumero num= darNumero(mazo[i]);

		if (palo == picas)
			salida << 'p';
		else if (palo == treboles)
			salida << 't';
		else if (palo == diamantes)
			salida << 'd';
		else 
			salida << 'c';

		salida << ' ';

		if (num>diez){
			if (num == jota)
				salida << "11";
			else if (num == qu)
				salida << "12"; 
			else
				salida << "13";
		}

	else if (num==as)
		salida << "1";

	else 
		salida << int(num)+1;

	salida << endl;
	i++;

	}
	salida.close();
	cout << " Su fichero ha sido creado con exito" <<endl<<endl;
}

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo){ // separa el mazo en negras y rojas
	int cuantas,rojo=0,negro=0;
	tPalo palo;
	cuantas = cuantasEnMazo(mazo);

	for (int i=0; i<cuantas; i++){  
		palo = darPalo(mazo[i]);

		if (palo == picas || palo == treboles){
			mazoNegro[negro] = mazo[i];
			negro++;
		}

		else {
			mazoRojo[rojo] = mazo[i];			
			rojo++;
		}
	}
	mazoNegro[negro]=CENTINELA;
	mazoRojo[rojo]=CENTINELA;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas){ // separa el mazo en altas (8-k) y bajas (1-7)
	int cuantas, alta=0, baja=0;
	cuantas = cuantasEnMazo(mazo);
	tNumero num;

	for (int i=0; i<cuantas; i++){
		num = darNumero(mazo[i]);
	
		if (num>=0 && num <7){
			mazoBajas[baja]=mazo[i];
			baja++;
		}
		else {
			mazoAltas[alta]=mazo[i];
			alta++;
		}
	}
	mazoBajas[baja]=CENTINELA;
	mazoAltas[alta]=CENTINELA;
}

void repartirIntercalando (const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo){
	// reparte en enCuantosMazos el mazo del principio y el usuario elige el mazo a mostrar con queMazopido
	int cuantas,j=0,cont=0; // j es el contador del mazoNuevo, cont el contador auxiliar
	cuantas = cuantasEnMazo(mazo); 
	// mirar con un while: while(mazo[i]!=CENTINELA) { EN PRINCIPIO CON ESE WHILE NO FUNCIONA. CON FOR SI! PERO SERIA CONVENIENTO CAMBIAR A WHILE!!

	for (int i=0; i<cuantas; i++){ // i es el contador del mazo 
		if(i==(queMazoPido-1)+cont){ // pasara al if en el momento en el que coincida i con la posicion a escribir en mazoNuevo
		mazoNuevo[j]=mazo[i]; // la carta de la posicion i de mazo se escribirá en la posicion j de mazoNuevo
		cont = cont + enCuantosMazos; // imprescindible para ver la proxima entrada al if, cont será la posicion a escribir en mazoNuevo en la siguiente vuelta
		j++;
		i++;
		}
	}
	mazoNuevo[j]=CENTINELA;
}

void trucoTresMontones(){  
	tMazo mazo,mazoAux, mazoNuevo1,mazoNuevo2,mazoNuevo3,mazo1,mazo2,mazo3;
	bool cargar, unir;
	int i=0, cuantas, tuMazo;

	cargar = cargarMazo(mazo);
	
	if (!cargar)
		cout << "No se ha cargado ningun mazo. El archivo no existe. " << endl;

	else{
		cuantas = cuantasEnMazo(mazo);

		if(cuantas!=MAZOTRESMONTONES) // el numero de cartas del mazo debe ser igual a 21, para el que se ha creado una constante
			cout << " Numero de cartas no valido para este truco(necesita 21 cartas). " << endl << endl;

		else{
			barajarMazo(mazo);

			repartirIntercalando (mazo, 3, 1, mazoNuevo1); // a continuacion muestra los tres montones repartidos del mazo
			escribirMazo(mazoNuevo1);

			repartirIntercalando (mazo, 3, 2, mazoNuevo2);
			escribirMazo(mazoNuevo2);

			repartirIntercalando (mazo, 3, 3, mazoNuevo3);
			escribirMazo(mazoNuevo3);

			cout << " Dime en que mazo esta tu carta: ";
			cin >> tuMazo;
			crearMazoVacio(mazoAux); //Hacemos esto para que el mazoAux tenga tan solo el centinela.	

			for (int i=0; i<=1;i++){

							

				if	(tuMazo == 1){
				unir = unirMazos(mazoAux,mazoNuevo2);  //Une los mazos de manera que el mazo elegido, en este caso el primero este en medio.
				unir = unirMazos(mazoAux, mazoNuevo1);
				unir = unirMazos (mazoAux, mazoNuevo3);

				repartirIntercalando(mazoAux, 3, 1, mazoNuevo1);
					escribirMazo(mazoNuevo1);
				repartirIntercalando(mazoAux, 3, 2, mazoNuevo2);
					escribirMazo(mazoNuevo2);
				repartirIntercalando(mazoAux, 3, 3, mazoNuevo3);
					escribirMazo(mazoNuevo3);
				}

				else if (tuMazo == 2){
				unir = unirMazos(mazoAux,mazoNuevo1); //Une los mazos de manera que el mazo elegido, en este caso el segundo este en medio.
				unir = unirMazos (mazoAux, mazoNuevo2);
				unir = unirMazos(mazoAux, mazoNuevo3);

				repartirIntercalando(mazoAux, 3, 1, mazoNuevo1);
					escribirMazo(mazoNuevo1);
				repartirIntercalando(mazoAux, 3, 2, mazoNuevo2);
					escribirMazo(mazoNuevo2);
				repartirIntercalando(mazoAux, 3, 3, mazoNuevo3);
					escribirMazo(mazoNuevo3);
				}

				else {
				unir = unirMazos (mazoAux,mazoNuevo1); //Une los mazos de manera que el mazo elegido, en este caso el tercero este en medio.
				unir = unirMazos (mazoAux, mazoNuevo3);
				unir = unirMazos (mazoAux,mazoNuevo2);

				repartirIntercalando(mazoAux, 3, 1, mazoNuevo1);
					escribirMazo(mazoNuevo1);
				repartirIntercalando(mazoAux, 3, 2, mazoNuevo2);
					escribirMazo(mazoNuevo2);
				repartirIntercalando(mazoAux, 3, 3, mazoNuevo3);
					escribirMazo(mazoNuevo3);
				}
			
				cout << " Recuerda. Elige la misma carta que antes ";
				cin >> tuMazo;
				cout <<endl<<endl;
				crearMazoVacio(mazoAux); //Hacemos esto para que el mazoAux tenga tan solo el centinela.	
			}

			cout << "Tu carta elegida es: " ; // la carta elegida por el usuario estará en la posicion 10 del mazo final (la undécima)
		
			if ( tuMazo == 1){
				
				unir = unirMazos(mazoAux,mazoNuevo2);  //Une los mazos de manera que el mazo elegido, en este caso el primero este en medio.
				unir = unirMazos(mazoAux, mazoNuevo1);
				unir = unirMazos(mazoAux, mazoNuevo3);
				escribirCarta(mazoAux[10]);
				cout <<endl;
			}

			else if (tuMazo == 2) {
				
				unir = unirMazos(mazoAux,mazoNuevo1); //Une los mazos de manera que el mazo elegido, en este caso el segundo este en medio.
				unir = unirMazos (mazoAux, mazoNuevo2);
				unir = unirMazos(mazoAux, mazoNuevo3);
				escribirCarta(mazoAux[10]);
				cout <<endl;
			}

			else {
			
				unir = unirMazos (mazoAux,mazoNuevo1); //Une los mazos de manera que el mazo elegido, en este caso el tercero este en medio.
				unir = unirMazos (mazoAux, mazoNuevo3);
				unir = unirMazos (mazoAux,mazoNuevo2);
				escribirCarta(mazoAux[10]);
				cout<<endl;
			}
		}
	}
}

void trucoPosada(){
	tMazo mazo, mazo1,mazo2,mazo3, mazo4,mazoFinal1,mazoFinal2,mazoFinal3,mazoFinal4;
	tNumero num;
	bool cargar;/*unir,reunir,rereunir;*/
	int cuantas,cuantasCortar;

	cargar = cargarMazo(mazo);

	if (!cargar)
		cout << "No se ha cargado ningun mazo. El archivo no existe. " << endl;

	else{
		cuantas = cuantasEnMazo(mazo);
		for (int i=0; i<cuantas; i++){
			num= darNumero(mazo[i]);
		}

		repartirIntercalando (mazo, 4, 1, mazo1);
		escribirMazo(mazo1);

		repartirIntercalando (mazo, 4, 2, mazo2);
		escribirMazo(mazo2);

		repartirIntercalando (mazo, 4, 3, mazo3);
		escribirMazo(mazo3);

		repartirIntercalando (mazo, 4, 4, mazo4);
		escribirMazo(mazo4);


		unirMazos(mazo1,mazo2);
		unirMazos(mazo1,mazo3);
		unirMazos(mazo1,mazo4);

		cout << " Introduce cuantas cartas deseas cortar del mazo: " ;
		cin >> cuantasCortar; 
		cout << endl;

		if (cuantasCortar<cuantas){
		cortarMazo(mazo1, cuantasCortar);

		repartirIntercalando (mazo1, 4, 1, mazoFinal1);
		escribirMazo(mazoFinal1);

		repartirIntercalando (mazo1, 4, 2, mazoFinal2);
		escribirMazo(mazoFinal2);

		repartirIntercalando (mazo1, 4, 3, mazoFinal3);
		escribirMazo(mazoFinal3);

		repartirIntercalando (mazo1, 4, 4, mazoFinal4);
		escribirMazo(mazoFinal4);
		}

		else
			cout << "Numero de cartas que quieres cortar es mayor que el numero de cartas total"  << endl << endl;

		


	}
}

int menu(){
	int op;
	cout << " Selecciona una opcion. " << endl;
	cout << " 1. Cargar un mazo de cartas de fichero " << endl;
	cout << " 2. Barajar mazo de cartas " << endl;
	cout << " 3. Aniadir mazo " << endl;
	cout << " 4. Cortar mazo" << endl;
	cout << " 5. Guardar mazo de cartas en fichero" << endl;
	cout << " 6. Separar en negras y rojas" <<endl;
	cout << " 7. Separar en altas y bajas " << endl; 
	cout << " 8. Repartir mazo de manera alterna en montones " << endl; 
	cout << " 9. Truco de los tres montones. " << endl;
	cout << " 10. Truco de la posada. " << endl;
	cout << " 0. Salir " << endl; 
	cout << " Opcion: " ;
	cin >> op;
	

	while(op >10){
		cout<<  " Opcion no valida. Introduzca de nuevo: " <<endl;
		cout << " 1. Cargar un mazo de cartas de fichero " << endl;
		cout << " 2. Barajar mazo de cartas " << endl;
		cout << " 3. Aniadir mazo " << endl;
		cout << " 4. Cortar mazo" << endl;
		cout << " 5. Guardar mazo de cartas en fichero" << endl;
		cout << " 6. Separar en negras y rojas" <<endl;
		cout << " 7. Separar en altas y bajas " << endl;
		cout << " 8. Repartir mazo de manera alterna en montones " << endl; 
		cout << " 9. Truco de los tres montones. " << endl;
		cout << " 10. Truco de la posada. " << endl;
		cout << " 0. Salir " << endl; 
		cout << " Opcion: " ;
		cin >> op;	
	}

	cout << endl;
	return op;
}

tCarta transformacion (int n, char c){
	tCarta carta;

				switch (c){
					case 'p' : carta = tCarta (CARTASPORPALO*0 + (n-1));
					break;

					case 't' : carta = tCarta (CARTASPORPALO*1 + (n-1));
					break;

					case 'd' : carta = tCarta (CARTASPORPALO*2 + (n-1));
					break;

					case 'c' : carta = tCarta (CARTASPORPALO*3 + (n-1));
					break;
					
				}
return carta;
}



