/* Caso 2 - Analisis de algoritmos
   Estudiante: Andrea María Li Hernández - 2021028783
*/
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Función que se utiliza en insertion_sort para insertar el siguiente elemento en next_pos
void insert(int first, int next_pos, int arr[]) {
    while (next_pos != first && arr[next_pos] < arr[next_pos - 1]) {
        swap(arr[next_pos], arr[next_pos - 1]);
        --next_pos;
    }
}

/* Normalmente la función es void pero debido a la medición del tiempo se va a retornar un vector
    con los time_points start y end
*/
vector<steady_clock::time_point> insertion_sort(int first, int last, int arr[], steady_clock::time_point start, steady_clock::time_point end) {
    start = steady_clock::now();
    for (int next_pos = first + 1; next_pos != last; next_pos++) {
        insert(first, next_pos, arr);
    }
    end = steady_clock::now();
    vector<steady_clock::time_point> tiempos;
    tiempos.push_back(start);
    tiempos.push_back(end);
    return tiempos;
}

// Función para llenar arrays con números aleatorios
void fillArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i]  = rand() % 1000;
    }
}

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

int main() {
    steady_clock::time_point start = steady_clock::now(); // Variables para medir el tiempo
    steady_clock::time_point end = steady_clock::now();
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

    // Vector con 2 elementos, start y end, para cada array en el insertion_sort cuadratico
    vector<steady_clock::time_point> timeCuad0, timeCuad1, timeCuad2, timeCuad3, timeCuad4, timeCuad5, timeCuad6, timeCuad7; //Duracion en ns para cada array log test

    // Diferencia entre start y end para cada array en el insertion_sort cuadratico
    double timeDiffCuad0, timeDiffCuad1, timeDiffCuad2, timeDiffCuad3, timeDiffCuad4, timeDiffCuad5, timeDiffCuad6, timeDiffCuad7;

    // Vector con 2 elementos, start y end, para cada array en el insertion_sort lineal
    vector<steady_clock::time_point> timeLin0, timeLin1, timeLin2, timeLin3, timeLin4, timeLin5, timeLin6, timeLin7; //Duracion en ns para cada array log test

    // Diferencia entre start y end para cada array en el insertion_sort lineal
    double timeDiffLin0, timeDiffLin1, timeDiffLin2, timeDiffLin3, timeDiffLin4, timeDiffLin5, timeDiffLin6, timeDiffLin7;

    vector<double> tiemposN2; // Vector para almacenar los tiempos para insertion_sort cuadratico
    vector<double> tiemposN; // Vector para almacenar los tiempos para insertion_sort lineal

//Medir el tiempo y hacer insertion_sort para cada array. Se almacena el tiempo en su variable correspondiente
    // insertion_sort va a retornar un vector con start y end
    timeCuad0 = insertion_sort(0, size0 - 1, arr0, start, end); //insertion_sort cuadratico
    start = timeCuad0[0];
    end = timeCuad0[1];
    timeDiffCuad0 = timeDiffns(start, end);

    timeLin0 = insertion_sort(0, size0 - 1, arr0, start, end); //insertion_sort lineal
    start = timeLin0[0];
    end = timeLin0[1];
    timeDiffLin0 = timeDiffns(start, end);

    timeCuad1 = insertion_sort(0, size1 - 1, arr1, start, end); //insertion_sort cuadratico
    start = timeCuad1[0];
    end = timeCuad1[1];
    timeDiffCuad1 = timeDiffns(start, end);

    timeLin1 = insertion_sort(0, size1 - 1, arr1, start, end); //insertion_sort lineal
    start = timeLin1[0];
    end = timeLin1[1];
    timeDiffLin1 = timeDiffns(start, end);

    timeCuad2 = insertion_sort(0, size2 - 1, arr2, start, end); //insertion_sort cuadratico
    start = timeCuad2[0];
    end = timeCuad2[1];
    timeDiffCuad2 = timeDiffns(start, end);

    timeLin2 = insertion_sort(0, size2 - 1, arr2, start, end); //insertion_sort lineal
    start = timeLin2[0];
    end = timeLin2[1];
    timeDiffLin2 = timeDiffns(start, end);

    timeCuad3 = insertion_sort(0, size3 - 1, arr3, start, end); //insertion_sort cuadratico
    start = timeCuad3[0];
    end = timeCuad3[1];
    timeDiffCuad3 = timeDiffns(start, end);

    timeLin3 = insertion_sort(0, size3 - 1, arr3, start, end); //insertion_sort lineal
    start = timeLin3[0];
    end = timeLin3[1];
    timeDiffLin3 = timeDiffns(start, end);

    timeCuad4 = insertion_sort(0, size4 - 1, arr4, start, end); //insertion_sort cuadratico
    start = timeCuad4[0];
    end = timeCuad4[1];
    timeDiffCuad4 = timeDiffns(start, end);

    timeLin4 = insertion_sort(0, size4 - 1, arr4, start, end); //insertion_sort lineal
    start = timeLin4[0];
    end = timeLin4[1];
    timeDiffLin4 = timeDiffns(start, end);

    timeCuad5 = insertion_sort(0, size5 - 1, arr5, start, end); //insertion_sort cuadratico
    start = timeCuad5[0];
    end = timeCuad5[1];
    timeDiffCuad5 = timeDiffns(start, end);

    timeLin5 = insertion_sort(0, size5 - 1, arr5, start, end); //insertion_sort lineal
    start = timeLin5[0];
    end = timeLin5[1];
    timeDiffLin5 = timeDiffns(start, end);

    timeCuad6 = insertion_sort(0, size6 - 1, arr6, start, end); //insertion_sort cuadratico
    start = timeCuad6[0];
    end = timeCuad6[1];
    timeDiffCuad6 = timeDiffns(start, end);

    timeLin6 = insertion_sort(0, size6 - 1, arr6, start, end); //insertion_sort lineal
    start = timeLin6[0];
    end = timeLin6[1];
    timeDiffLin6 = timeDiffns(start, end);

    timeCuad7 = insertion_sort(0, size7 - 1, arr7, start, end); //insertion_sort cuadratico
    start = timeCuad7[0];
    end = timeCuad7[1];
    timeDiffCuad7 = timeDiffns(start, end);

    timeLin7 = insertion_sort(0, size7 - 1, arr7, start, end); //insertion_sort lineal
    start = timeLin7[0];
    end = timeLin7[1];
    timeDiffLin7 = timeDiffns(start, end);

    tiemposN2.push_back(timeDiffCuad0);
    tiemposN2.push_back(timeDiffCuad1);
    tiemposN2.push_back(timeDiffCuad2);
    tiemposN2.push_back(timeDiffCuad3);
    tiemposN2.push_back(timeDiffCuad4);
    tiemposN2.push_back(timeDiffCuad5);
    tiemposN2.push_back(timeDiffCuad6);
    tiemposN2.push_back(timeDiffCuad7);

    tiemposN.push_back(timeDiffLin0);
    tiemposN.push_back(timeDiffLin1);
    tiemposN.push_back(timeDiffLin2);
    tiemposN.push_back(timeDiffLin3);
    tiemposN.push_back(timeDiffLin4);
    tiemposN.push_back(timeDiffLin5);
    tiemposN.push_back(timeDiffLin6);
    tiemposN.push_back(timeDiffLin7);

    // tasaTiempo retorna un vector con la tasa de crecimiento para los tiemposN2
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

    vector<float> resultTasaN2 = tasaOrden(pows2, cant_arrays);

    // Imprimir resultados
    cout << "Se hara insertion_sort en 8 arrays de numeros enteros de size 100,500,1000,1500,2000,2500,3000 y 3500" << endl;
    cout << endl;
    cout << "------------- Prueba para insertion_sort cuadratico -------------" << endl;
    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "T" << i << " = " << tiemposN2[i] << endl;
    }

    cout << endl;
    cout << "n^2 de " << size0 << "," << size1 << "," << size2 << "," << size3 << "," << size4 <<
    "," << size5 << "," << size6 << "," << size7 << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "pow2_" << i << " = " << pows2print[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempoN2[i]<<endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los n^2" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "N" << i+1 << "/" << "N"<<i<< " = " << resultTasaN2[i] << endl;
    }
    // Calcular un promedio entre ambas tasas de crecimiento
    float aux = 0;  // Auxiliar para ir sumando la diferencia entre las tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasaN2[i] - resultTiempoN2[i]); //agregar a aux la diferencia entre ambas tasas
    }

    float promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1; //esto es porque el abs no parecia funcionar
    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el insertion_sort tiene un tiempo algoritmico cuadratico" << endl;
    cout << endl;

    // ----------------- Demostracion para insertion_sort lineal ------------------------
    cout << "------------- Prueba para insertion_sort lineal -------------" << endl;
    vector<float> resultTiempoN = tasaTiempos(tiemposN, cant_arrays);

    vector<int> nums;
    nums.push_back(size0);
    nums.push_back(size1);
    nums.push_back(size2);
    nums.push_back(size3);
    nums.push_back(size4);
    nums.push_back(size5);
    nums.push_back(size6);
    nums.push_back(size7);

    vector<float> resultTasaN = tasaOrden(nums, cant_arrays);

    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < cant_arrays; i++) {
        cout << "T" << i << " = " << tiemposN[i] << endl;
    }

    cout << endl;
    cout << "Los n son: " << endl;
    cout << "N0 = " << size0 << endl;
    cout << "N1 = " << size1 << endl;
    cout << "N2 = " << size2 << endl;
    cout << "N3 = " << size3 << endl;
    cout << "N4 = " << size4 << endl;
    cout << "N5 = " << size5 << endl;
    cout << "N6 = " << size6 << endl;
    cout << "N7 = " << size7 << endl;

    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "T" << i+1 << "/" << "T" << i << " = " << resultTiempoN[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en las n" << endl;
    for (int i = 0; i < cant_arrays-1; i++) {
        cout << "N" << i+1 << "/" << "N" << i << " = " << resultTasaN[i] << endl;
    }

    // Calcular un promedio entre ambas tasas de crecimiento
    aux = 0;  // Auxiliar para ir sumando la diferencia entre laas tasas
    for (int i = 0; i < cant_arrays-1; i++) {
        aux += abs(resultTasaN[i] - resultTiempoN[i]); //agregar a aux la diferencia entre ambas tasas
    }

    promedio = aux/cant_arrays-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1; //esto es porque el abs no parecia funcionar
    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el insertion_sort tiene un tiempo algoritmico lineal" << endl;
    cout << endl;
    cout << "Fin del programa" << endl;
    return 0;
}
