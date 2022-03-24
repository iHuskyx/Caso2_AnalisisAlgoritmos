/* Caso 2 - Analisis de algoritmos
   Estudiante: Andrea María Li Hernández - 2021028783
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <list>
#include <windows.h> //se utiliza para cambiar el idioma de stdin y stdout a español

#include "avltreedictionary.h"
#include "LinkedList.h"
#include "trie.h"

using namespace std::chrono;
using namespace std;

// Función para obtener la diferencia entre el tiempo de inicio y tiempo de fin
double timeDiffns(steady_clock::time_point start, steady_clock::time_point end) {
    return duration_cast<nanoseconds> (end - start).count();
}

// Función para obtener la tasa de crecimiento según los tiempos
vector<float> tasaTiempos(vector<double> tiempos, int n) {
    vector<float> dif;
    for (int i = 0; i < n-1; i++) {
        dif.push_back(float(tiempos[i+1] / tiempos[i]));
    }
    return dif;
}

/* Función para obtener la tasa de crecimiento entre los números según el orden que se está analizando.
    Por ejm: si es orden cuadratico, se calculará la tasa de los n^2
*/
vector<float> tasaOrden(vector<float> orden, int n) {
    vector<float> dif;
    for (int i = 0; i < n-1; i++) {
        dif.push_back(float(orden[i+1] / orden[i]));
    }
    return dif;
}
// Sobrecarga de la función anterior para tratar con números enteros
vector<float> tasaOrden(vector<int> orden, int n) {
    vector<float> dif;
    for (int i = 0; i < n-1; i++) {
        dif.push_back(float(orden[i+1] / orden[i]));
    }
    return dif;
}

// Función que retorna true si se encuentra alguno de los carácteres que no se deben tomar en cuenta para las palabras
bool ignore(char c) {
    char ap = char(39);
    if (c == ap)
        return true;
    switch(c)
    {
    case '(':
    case ')':
    case '-':
    case '»':
    case '«':
    case ']':
    case '[':
    case '/':
    case '*':
    case ',':
    case ';':
    case '.':
    case '~':
    case 'º':
    case '&':
    case '¿':
    case '?':
    case ':':
    case '"':
    case '¡':
    case '!':
    case 'ç':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '':
        return true;
    default:
        return false;
    }
}

//Función para eliminar los espacios de una palabra
bool ignoreSpace(char c) {
    switch(c)
    {
    case ' ':
        return true;
    default:
        return false;
    }
}

int main() {
    cout << "*********************************" << endl;
    cout << "*      Free text search         *" << endl;
    cout << "*********************************" << endl;
    setlocale(LC_ALL, "spanish"); // Establecer idioma español
    SetConsoleCP(1252); // Entrada de texto con acentos del idioma español
    SetConsoleOutputCP(1252); // Salida de texto con acentos del idioma español

    steady_clock::time_point start = steady_clock::now(); // Variables para medir el tiempo
    steady_clock::time_point end = steady_clock::now();

    Trie *palabras = new Trie(); //Trie donde se van a almacenar las palabras
    vector<string> lineas;  //almacenar las lineas originales del texto

    string nombreArchivo = "WarPeace.txt";
    ifstream archivo;
    archivo.open(nombreArchivo,ios::in); //abrir archivo con el texto

    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (!archivo.eof()) {
        getline(archivo,linea);
        lineas.push_back(linea);
    }
    archivo.close(); //cerrar el archivo


    // ---------------------- INICIA SECCIÓN PARA CARGAR LAS PALABRAS EN EL TRIE -------------

    string actual = "";     //linea que se va a recorrer
    string palabra = "";    //ir armando la palabra
    string espacio = " "; //strings para restricciones
    string noEspacio = "";
    int i = 0;  //caracter de la linea que se analiza
    int numLinea = 0;

    //ciclo que recorre las líneas
    for (int line = 0; line < lineas.size(); line++) {
        actual = lineas[line]; //analizar una línea de la lista

        while (i < actual.length()) {
            actual[i] = tolower(actual[i]);  //convertir en minúscula

            if (ignore(actual[i]))
                actual[i] = ' ';

            // si el carácter es diferente de un espacio en blanco
            if (actual[i] != ' ' ) {
                palabra += actual[i]; //concatenar carácter
                i++;

                if (ignore(actual[i]))
                    actual[i] = ' ';

            } else {   //si el carácter actual es igual a un espacio en blanco, se ha llegado al fin de una palabra
                if (palabra.length() >= 1) {
                    //que no haga nada si la comparación con un espacio o vacío es true
                    if (strcmp(palabra.c_str(), espacio.c_str()) == 0 ||
                    strcmp(palabra.c_str(), noEspacio.c_str()) == 0 ) {
                    } else {
                if (!palabras->containsWord(palabra)) { // Si la palabra no se encuentra en el trie
                        palabra.erase(remove_if(palabra.begin(),palabra.end(), &ignoreSpace), palabra.end());//borra espacios en blanco de la palabra
                        palabras->insert(palabra); //insertar en el Trie
                        palabras->insertIndex(palabra,numLinea); //insertar el número de la línea en la lista del TrieNode

                } else  //la palabra ya se encuentra en el Trie
                    palabras->insertIndex(palabra,numLinea); //agregar el número de la línea en la lista del TrieNode
                palabra = ""; //asignarlo a string vacío para volver a utilizarla
                i++;    //siguiente char

                if (ignore(actual[i]))
                    actual[i] = ' '; //ignorar si es un espacio
                    }
                } else {
                    i++; //pasar al siguiente carácter
                    if (ignore(actual[i]))
                    actual[i] = ' ';
                }
            }

    }//TERMINA EL WHILE
    // Llega aqui cuando es fin de linea, como no habrá un espacio, se debe crear la palabra manualmente
    if (strcmp(palabra.c_str(), espacio.c_str()) == 0 ||
                    strcmp(palabra.c_str(), noEspacio.c_str()) == 0) {  //ignorar si al final de linea es un espacio
    } else {
        if (!palabras->containsWord(palabra)) {
                palabra.erase(remove_if(palabra.begin(),palabra.end(), &ignoreSpace), palabra.end());
                palabras->insert(palabra);
                palabras->insertIndex(palabra,numLinea);
            } else
                palabras->insertIndex(palabra,numLinea);
    }
    numLinea++; //sumar al índice de línea
    i = 0; //reiniciar iterador
    palabra = ""; //asignar string vacío para volver a utilizar
    }

    // ---------------------- TERMINA SECCIÓN PARA CARGAR LAS PALABRAS EN EL TRIE -------------

    //Listas enlazadas para los matches de las palabras
    LinkedList<string> *matches1 = new LinkedList<string>();
    LinkedList<string> *matches2 = new LinkedList<string>();
    LinkedList<string> *matches3 = new LinkedList<string>();
    LinkedList<string> *matches4 = new LinkedList<string>();

//    string word1 = "dormir";    //palabras que se van a utilizar, luego se actualizan
//    string word2 = "cal";
//    string word3 = "cond";
//    string word4 = "amor";

    string word1 = "love";    //palabras que se van a utilizar, luego se actualizan
    string word2 = "war";
    string word3 = "crimes";
    string word4 = "cry";

    vector<double> tiempos;
    float time1, time2, time3, time4;

    // Medir el tiempo que dura en buscar las ubicaciones de la palabra en el texto
    start = steady_clock::now();
    palabras->getUbicaciones(word1);
    end = steady_clock::now();
    time1 = timeDiffns(start, end);

    start = steady_clock::now();
    palabras->getUbicaciones(word1);
    palabras->getUbicaciones(word2);
    end = steady_clock::now();
    time2 = timeDiffns(start, end);

    start = steady_clock::now();
    palabras->getUbicaciones(word1);
    palabras->getUbicaciones(word2);
    palabras->getUbicaciones(word3);
    end = steady_clock::now();
    time3 = timeDiffns(start, end);

    start = steady_clock::now();
    palabras->getUbicaciones(word1);
    palabras->getUbicaciones(word2);
    palabras->getUbicaciones(word3);
    palabras->getUbicaciones(word4);
    end = steady_clock::now();
    time4 = timeDiffns(start, end);

    // ------------ IMPRIMIR CANTIDAD DE APARICIONES Y APARICIONES DE LAS PALABRAS -------

    cout << endl;
    cout << " --------- Prueba para 1 elemento ----------" << endl;
    matches1 = palabras->getMatches(word1);
    cout << "Palabra a buscar: " << word1 << endl;
    cout << "Cantidad de apariciones en total para " << word1 <<  " = " << palabras->getCantApariciones(word1) << endl;
    cout << "Apariciones: " << endl;
    for (matches1->goToStart(); !matches1->atEnd(); matches1->next()) {
        cout << matches1->getElement() << endl;
    }
    cout << endl;


    cout << " --------- Prueba para 2 elementos ----------" << endl;
    word1 = "color";
    word2 = "cal";
    matches1 = palabras->getMatches(word1);
    matches2 = palabras->getMatches(word2);
    cout << "Palabras a buscar: " << word1 << ", " << word2 << endl;
    cout << "Cantidad de apariciones en total para " << word1 << " = " << palabras->getCantApariciones(word1) << endl;
    cout << "Apariciones: " << endl;
    for (matches1->goToStart(); !matches1->atEnd(); matches1->next()) {
        cout << matches1->getElement() << endl;
    }
    cout << endl;

    cout << "Cantidad de apariciones en total para " << word2 << " = " << palabras->getCantApariciones(word2) << endl;
    cout << "Apariciones: " << endl;
    for (matches2->goToStart(); !matches2->atEnd(); matches2->next()) {
        cout << matches2->getElement() << endl;
    }
    cout << endl;


    cout << " --------- Prueba para 3 elementos ----------" << endl;
    word1 = "cake";
    word2 = "monster";
    word3 = "fly";
    matches1 = palabras->getMatches(word1);
    matches2 = palabras->getMatches(word2);
    matches3 = palabras->getMatches(word3);
    cout << "Palabras a buscar: " << word1 << ", " << word2 << ", " << word3 << endl;
    cout << "Cantidad de apariciones en total para " << word1 << " = " << palabras->getCantApariciones(word1) << endl;
    cout << "Apariciones: " << endl;
    for (matches1->goToStart(); !matches1->atEnd(); matches1->next()) {
        cout << matches1->getElement() << endl;
    }
    cout << endl;

    cout << "Cantidad de apariciones en total para " << word2 << " = " << palabras->getCantApariciones(word2) << endl;
    cout << "Apariciones: " << endl;
    for (matches2->goToStart(); !matches2->atEnd(); matches2->next()) {
        cout << matches2->getElement() << endl;
    }
    cout << endl;

    cout << "Cantidad de apariciones en total para " << word3 << " = " << palabras->getCantApariciones(word3) << endl;
    cout << "Apariciones: " << endl;
    for (matches3->goToStart(); !matches3->atEnd(); matches3->next()) {
        cout << matches3->getElement() << endl;
    }
    cout << endl;

    cout << " --------- Prueba para 4 elementos ----------" << endl;
    word1 = "car";
    word2 = "smile";
    word3 = "jump";
    matches1 = palabras->getMatches(word1);
    matches2 = palabras->getMatches(word2);
    matches3 = palabras->getMatches(word3);
    matches4 = palabras->getMatches(word4);
    cout << "Palabras a buscar: " << word1 << ", " << word2 << ", " << word3 << ", " << word4 << endl;
    cout << "Cantidad de apariciones en total para " << word1 << " = " << palabras->getCantApariciones(word1) << endl;
    cout << "Apariciones: " << endl;
    for (matches1->goToStart(); !matches1->atEnd(); matches1->next()) {
        cout << matches1->getElement() << endl;
    }
    cout << endl;

    cout << "Cantidad de apariciones en total para " << word2 << " = " << palabras->getCantApariciones(word2) << endl;
    cout << "Apariciones: " << endl;
    for (matches2->goToStart(); !matches2->atEnd(); matches2->next()) {
        cout << matches2->getElement() << endl;
    }
    cout << endl;

    cout << "Cantidad de apariciones en total para " << word3 << " = " << palabras->getCantApariciones(word3) << endl;
    cout << "Apariciones: " << endl;
    for (matches3->goToStart(); !matches3->atEnd(); matches3->next()) {
        cout << matches3->getElement() << endl;
    }
    cout << endl;

    cout << "Cantidad de apariciones en total para " << word4 << " = " << palabras->getCantApariciones(word4) << endl;
    cout << "Apariciones: " << endl;
    for (matches4->goToStart(); !matches4->atEnd(); matches4->next()) {
        cout << matches4->getElement() << endl;
    }
    cout << endl;

    // ------------------- DEMO DE QUE ES DE ORDEN LINEAL ----------------------

    cout << "--------------- Demostracion de que es de orden lineal -----------------" << endl;

    tiempos.push_back(time1);
    tiempos.push_back(time2);
    tiempos.push_back(time3);
    tiempos.push_back(time4);

    vector<float> resultTiempos = tasaTiempos(tiempos, 4);

    vector<float> numeros;
    numeros.push_back(1);
    numeros.push_back(2);
    numeros.push_back(3);
    numeros.push_back(4);

    vector<float> resultNumeros = tasaOrden(numeros, 4);

    for (int i = 0; i < 4; i++) {
        cout << "T" << i << " = " << tiempos[i] << endl;
    }

    cout << endl;
    cout << "Cantidad de elementos: " << endl;
    for (int i = 0; i < 4; i++) {
        cout << "N" << i << " = " << i+1 << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < 4-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempos[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en la cantidad de elementos" << endl;
    for (int i = 0; i < 4-1; i++) {
        cout << "N" << i+1 << "/" << "N" << i << " = " << resultNumeros[i] << endl;
    }

    // Calcular un promedio entre ambas tasas de crecimiento
    float aux = 0;  // Auxiliar para ir sumando la diferencia entre las tasas
    for (int i = 0; i < 4-1; i++) {
        aux += abs(resultNumeros[i] - resultTiempos[i]); //agregar a aux la diferencia entre ambas tasas
    }

    float promedio = aux/4-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1; //esto es porque el abs no parecia funcionar

    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el free text search tiene un orden lineal" << endl;
    cout << endl;
    cout << "Fin del programa" << endl;

    return 0;
}
