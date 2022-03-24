/* Caso 2 - Analisis de algoritmos
   Estudiante: Andrea María Li Hernández - 2021028783
*/
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <string>

using namespace std::chrono;
using namespace std;

// Elección del pivote fijo, se llama en quicksort
int particion(int arr[], int down, int up) {
    int pivot = down, i = down;
    int j = i + 1;

    while (j <= up) {
        if (arr[j] < arr[pivot]) {
            i++;
            swap(arr[i], arr[j]);
        }
        j++;
    }
    swap(arr[i], arr[pivot]);
    return i;
}

// Elección del pivote random, retorna a particion una vez que se implementa el pivote aleatorio
int particionRandom(int arr[], int down, int up) {
    srand(time(0));
    int randomPivot = down + rand() % (up - down);
    swap(arr[randomPivot], arr[down]);
    return particion(arr, down, up);
}

// Quicksort que llama a particion para utilizar el pivote fijo
void quicksort(int arr[], int down, int up) {
    if (down < up) {
        int pivot = particion(arr, down, up);
        quicksort(arr, down, pivot - 1);
        quicksort(arr, pivot + 1, up);
    }
}

// Quicksort que llama a particionRandom para utilizar el pivote aleatorio
void quicksortRandom(int arr[], int down, int up) {
    if (down < up) {
        int pivot = particionRandom(arr, down, up);
        quicksortRandom(arr, down, pivot - 1);
        quicksortRandom(arr, pivot + 1, up);
    }
}

// Función para llenar arrays con números aleatorios
void fillArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i]  = rand() % 1000;
    }
}

// Función para obtener la diferencia entre el tiempo de inicio y tiempo de fin
float timeDiffns(steady_clock::time_point start, steady_clock::time_point end) {
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

int main() {
    int size0 = 100;    // Tamaño de los arrays con los que se harán las pruebas
    int size1 = 500;
    int size2 = 1000;
    int size3 = 1500;
    int size4 = 2000;
    int size5 = 2500;
    int size6 = 3000;
    int size7 = 3500;

    int cant_arrays = 8;    // Cantidad de arrays con los que se harán las pruebas
    int arr0[size0], arr1[size1], arr2[size2], arr3[size3], arr4[size4], arr5[size5], arr6[size6], arr7[size7];

    // Llenar los arrays con numeros enteros aleatorios
    fillArray(arr0, size0);
    fillArray(arr1, size1);
    fillArray(arr2, size2);
    fillArray(arr3, size3);
    fillArray(arr4, size4);
    fillArray(arr5, size5);
    fillArray(arr6, size6);
    fillArray(arr7, size7);

    double time0 = 0, time1 = 0, time2 = 0, time3 = 0, time4 = 0, time5 = 0, time6 = 0, time7 = 0; //Duracion en ns para cada array log test

    //Duracion en ns para cada array n^2 test
    double timeCuad0 = 0, timeCuad1 = 0, timeCuad2 = 0, timeCuad3 = 0, timeCuad4 = 0, timeCuad5 = 0, timeCuad6 = 0, timeCuad7 = 0;

    vector<double> tiemposLog; // Vector para almacenar los tiempos para quicksort logaritmico
    vector<double> tiemposN2; // Vector para almacenar los tiempos para quicksort cuadratico

//Medir el tiempo y hacer quicksort para cada array. Se almacena el tiempo en su variable correspondiente
    steady_clock::time_point start = steady_clock::now();   //Quicksort logaritmico
    quicksort(arr0, 0, size0);
    steady_clock::time_point end = steady_clock::now();
    time0 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr0, 0, size0);
    end = steady_clock::now();
    timeCuad0 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr1, 0, size1);
    end = steady_clock::now();
    time1 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr1, 0, size1);
    end = steady_clock::now();
    timeCuad1 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr2, 0, size2);
    end = steady_clock::now();
    time2 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr2, 0, size2);
    end = steady_clock::now();
    timeCuad2 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr3, 0, size3);
    end = steady_clock::now();
    time3 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr3, 0, size3);
    end = steady_clock::now();
    timeCuad3 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr4, 0, size4);
    end = steady_clock::now();
    time4 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr4, 0, size4);
    end = steady_clock::now();
    timeCuad4 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr5, 0, size5);
    end = steady_clock::now();
    time5 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr5, 0, size5);
    end = steady_clock::now();
    timeCuad5 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr6, 0, size6);
    end = steady_clock::now();
    time6 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr6, 0, size6);
    end = steady_clock::now();
    timeCuad6 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort logaritmico
    quicksort(arr7, 0, size7);
    end = steady_clock::now();
    time7 = timeDiffns(start, end);

    start = steady_clock::now();    //Quicksort cuadratico
    quicksort(arr7, 0, size7);
    end = steady_clock::now();
    timeCuad7 = timeDiffns(start, end);

    tiemposLog.push_back(time0);
    tiemposLog.push_back(time1);
    tiemposLog.push_back(time2);
    tiemposLog.push_back(time3);
    tiemposLog.push_back(time4);
    tiemposLog.push_back(time5);
    tiemposLog.push_back(time6);
    tiemposLog.push_back(time7);

    tiemposN2.push_back(timeCuad0);
    tiemposN2.push_back(timeCuad1);
    tiemposN2.push_back(timeCuad2);
    tiemposN2.push_back(timeCuad3);
    tiemposN2.push_back(timeCuad4);
    tiemposN2.push_back(timeCuad5);
    tiemposN2.push_back(timeCuad6);
    tiemposN2.push_back(timeCuad7);

    // tasaTiempo retorna un vector con la tasa de crecimiento para los tiemposLog
    vector<float> resultTiempoLog = tasaTiempos(tiemposLog, cant_arrays);

    // Variables para almacenar el logaritmo base 2 de los sizes de los arrays
    float log_test0, log_test1, log_test2, log_test3, log_test4, log_test5, log_test6, log_test7;
    vector<float> tasaLog; // Vector para almacenar los resultados de los logaritmos
    log_test0 = log2(size0);
    log_test1 = log2(size1);
    log_test2 = log2(size2);
    log_test3 = log2(size3);
    log_test4 = log2(size4);
    log_test5 = log2(size5);
    log_test6 = log2(size6);
    log_test7 = log2(size7);
    tasaLog.push_back(log_test0);
    tasaLog.push_back(log_test1);
    tasaLog.push_back(log_test2);
    tasaLog.push_back(log_test3);
    tasaLog.push_back(log_test4);
    tasaLog.push_back(log_test5);
    tasaLog.push_back(log_test6);
    tasaLog.push_back(log_test7);

    // tasaOrden retorna un vector con la tasa de crecimiento para los logaritmos
    vector<float> resultTasalog = tasaOrden(tasaLog, cant_arrays);

    // Imprimir resultados
    cout << "Se hara quicksort con pivote fijo en 8 arrays de numeros enteros de size 100,500,1000,1500,2000,2500,3000 y 3500" << endl;
    cout << endl;
    cout << "------------- Prueba para quicksort logaritmico con pivote fijo -------------" << endl;
    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "T" << i << " = " << tiemposLog[i] << endl;
    }

    cout << endl;
    cout << "Log2 de " << size0 << "," << size1 << "," << size2 << "," << size3 << "," << size4 <<
    "," << size5 << "," << size6 << "," << size7 << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "L" << i << " = " << tasaLog[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempoLog[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los logaritmos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "L" << i+1 << "/" << "L" << i << " = " << resultTasalog[i] << endl;
    }

    // Calcular un promedio entre ambas tasas de crecimiento
    float aux = 0;  // Auxiliar para ir sumando la diferencia entre las tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasalog[i] - resultTiempoLog[i]); //agregar a aux la diferencia entre ambas tasas
    }

    float promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1; //esto es porque el abs no parecia funcionar

    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el quicksort tiene un orden logaritmico" << endl;
    cout << "Ademas, se puede apreciar que las tasas llegan a punto de estabilizacion" << endl;
    cout << "lo cual coincide con el comportamiento de una funcion logaritmica" << endl;
    cout << endl;

    // ----------------- Demostracion para quicksort cuadratico ------------------------
    cout << "------------- Prueba para quicksort cuadratico con pivote fijo -------------" << endl;
    vector<float> resultTiempoN2 = tasaTiempos(tiemposN2, cant_arrays);

    int cuad_test0, cuad_test1, cuad_test2, cuad_test3, cuad_test4, cuad_test5, cuad_test6, cuad_test7;
    vector<int> pows2print; // Vector para almacenar los resultados de la elevacion al cuadrado e imprimirlos
    vector<float> pows2;
    cuad_test0 = pow(size0, 2);
    cuad_test1 = pow(size1, 2);
    cuad_test2 = pow(size2, 2);
    cuad_test3 = pow(size3, 2);
    cuad_test4 = pow(size4, 2);
    cuad_test5 = pow(size5, 2);
    cuad_test6 = pow(size6, 2);
    cuad_test7 = pow(size7, 2);
    pows2print.push_back(cuad_test0);
    pows2print.push_back(cuad_test1);
    pows2print.push_back(cuad_test2);
    pows2print.push_back(cuad_test3);
    pows2print.push_back(cuad_test4);
    pows2print.push_back(cuad_test5);
    pows2print.push_back(cuad_test6);
    pows2print.push_back(cuad_test7);
    pows2.push_back(cuad_test0);
    pows2.push_back(cuad_test1);
    pows2.push_back(cuad_test2);
    pows2.push_back(cuad_test3);
    pows2.push_back(cuad_test4);
    pows2.push_back(cuad_test5);
    pows2.push_back(cuad_test6);
    pows2.push_back(cuad_test7);

    // tasaOrden retorna un vector con la tasa de crecimiento para las pows2
    vector<float> resultTasaN2 = tasaOrden(pows2, cant_arrays); //se reutiliza cant_arrays porque es la misma cant de elementos

    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "T" << i << " = " << tiemposN2[i] << endl;
    }

    cout << endl;
    cout << "n^2 de " << size0 << "," << size1 << "," << size2 << "," << size3 << "," << size4 <<
    "," << size5 << "," << size6 << "," << size7 << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "N" << i << " = " << pows2print[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempoN2[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en las pows2" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "N" << i+1 << "/" << "N" << i << " = " << resultTasaN2[i] << endl;
    }

    // Calcular un promedio entre ambas tasas de crecimiento
    aux = 0;  // Auxiliar para ir sumando la diferencia entre laas tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasaN2[i] - resultTiempoN2[i]); //agregar a aux la diferencia entre ambas tasas
    }

    promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1; //esto es porque el abs no parecia funcionar
    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el quicksort tiene un orden cuadratico" << endl;
    cout << endl;

    // --------------- Prueba pivote random para quicksort logaritmico ------------------
    cout << "Se hara quicksort con pivote random en 8 arrays de numeros enteros de size 100,500,1000,1500,2000,2500,3000 y 3500" << endl;
    cout << endl;
    cout << "------------ Prueba para quicksort logaritmico con pivote random ---------" << endl;
    // Llenar los arrays con numeros enteros aleatorios nuevamente
    fillArray(arr0, size0);
    fillArray(arr1, size1);
    fillArray(arr2, size2);
    fillArray(arr3, size3);
    fillArray(arr4, size4);
    fillArray(arr5, size5);
    fillArray(arr6, size6);
    fillArray(arr7, size7);

    start = steady_clock::now();   //quicksortRandom logaritmico
    quicksortRandom(arr0, 0, size0);
    end = steady_clock::now();
    time0 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr0, 0, size0);
    end = steady_clock::now();
    timeCuad0 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr1, 0, size1);
    end = steady_clock::now();
    time1 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr1, 0, size1);
    end = steady_clock::now();
    timeCuad1 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr2, 0, size2);
    end = steady_clock::now();
    time2 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr2, 0, size2);
    end = steady_clock::now();
    timeCuad2 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr3, 0, size3);
    end = steady_clock::now();
    time3 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr3, 0, size3);
    end = steady_clock::now();
    timeCuad3 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr4, 0, size4);
    end = steady_clock::now();
    time4 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr4, 0, size4);
    end = steady_clock::now();
    timeCuad4 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr5, 0, size5);
    end = steady_clock::now();
    time5 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr5, 0, size5);
    end = steady_clock::now();
    timeCuad5 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr6, 0, size6);
    end = steady_clock::now();
    time6 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr6, 0, size6);
    end = steady_clock::now();
    timeCuad6 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom logaritmico
    quicksortRandom(arr7, 0, size7);
    end = steady_clock::now();
    time7 = timeDiffns(start, end);

    start = steady_clock::now();    //quicksortRandom cuadratico
    quicksortRandom(arr7, 0, size7);
    end = steady_clock::now();
    timeCuad7 = timeDiffns(start, end);

    tiemposLog.clear();
    tiemposN2.clear();
    tiemposLog.push_back(time0);
    tiemposLog.push_back(time1);
    tiemposLog.push_back(time2);
    tiemposLog.push_back(time3);
    tiemposLog.push_back(time4);
    tiemposLog.push_back(time5);
    tiemposLog.push_back(time6);
    tiemposLog.push_back(time7);

    tiemposN2.push_back(timeCuad0);
    tiemposN2.push_back(timeCuad1);
    tiemposN2.push_back(timeCuad2);
    tiemposN2.push_back(timeCuad3);
    tiemposN2.push_back(timeCuad4);
    tiemposN2.push_back(timeCuad5);
    tiemposN2.push_back(timeCuad6);
    tiemposN2.push_back(timeCuad7);

    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "T" << i << " = " << tiemposLog[i] << endl;
    }

    resultTiempoLog = tasaTiempos(tiemposLog, cant_arrays);
    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempoLog[i] << endl;
    }

    cout << endl;
    cout << "**Se utiliza la misma tasa de crecimiento de logaritmos mostrada anteriormente porque trabajamos con la misma cantidad de elementos" << endl;

    aux = 0;  // Auxiliar para ir sumando la diferencia entre las tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasalog[i] - resultTiempoLog[i]); //agregar a aux la diferencia entre ambas tasas
    }

    promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1;

    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "Como se puede observar, con un pivote random los tiempos poseen un valor mayor, sin embargo, el pivote " << endl;
    cout << "se sigue aproximando a 0, por lo tanto, se puede concluir que al tener un pivote" << endl;
    cout << "random sigue siendo de orden logaritmico" << endl;
    cout << endl;

    cout << "------------ Prueba para quicksort cuadratico con pivote random ---------" << endl;
    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "T" << i << " = " << tiemposN2[i] << endl;
    }

    resultTiempoN2 = tasaTiempos(tiemposN2, cant_arrays);
    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempoN2[i] << endl;
    }

    aux = 0;  // Auxiliar para ir sumando la diferencia entre las tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasaN2[i] - resultTiempoN2[i]); //agregar a aux la diferencia entre ambas tasas
    }

    promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1;

    cout << endl;
    cout << "Con el quicksort cuadratico y pivote random, se da un caso particular" << endl;
    cout << "**Se utiliza la misma tasa de crecimiento de n^2 mostrada anteriormente porque trabajamos con la misma cantidad de elementos" << endl;
    cout << "Margen de error entre las tasas de n^2 y los tiempos de quicksort cuadratico = " << promedio << endl;
    cout << "El margen ya no se aproxima a 0, por lo que puede ser que ya no sea cuadratico" << endl;
    cout << endl;
    cout << "Calculemos el margen de error entre las tasas de logaritmos y la tasa de los tiempos que tenemos ahora" << endl;

    aux = 0;  // Auxiliar para ir sumando la diferencia entre las tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasalog[i] - resultTiempoN2[i]); //agregar a aux la diferencia entre ambas tasas
    }

    promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1;
    string promediostr = to_string(promedio);
    cout << "Margen de error entre las tasas de log y los tiempos de quicksort cuadratico = " << promediostr << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el quicksort cuadratico posee un orden logaritmico al utilizar" <<
    " un pivote random" << endl;

    cout << endl;
    cout << "Fin del programa" << endl;
    cout << endl;
    return 0;
}
