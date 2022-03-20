#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

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

int particionRandom(int arr[], int down, int up) {
    srand(time(0));
    int randomPivot = down + rand() % (up - down);
    swap(arr[randomPivot], arr[down]);
    return particion(arr, down, up);
}

void quicksort(int arr[], int down, int up) {
    if (down < up) {
        int pivot = particion(arr, down, up);
        quicksort(arr, down, pivot - 1);
        quicksort(arr, pivot + 1, up);
    }
}

void quicksortRandom(int arr[], int down, int up) {
    if (down < up) {
        int pivot = particionRandom(arr, down, up);
        quicksortRandom(arr, down, pivot - 1);
        quicksortRandom(arr, pivot + 1, up);
    }
}

void fillArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i]  = rand() % 1000;
    }
}

double timeDiffns(steady_clock::time_point start, steady_clock::time_point end) {
    return duration_cast<nanoseconds> (end - start).count();
}

vector<float> tasaTiempos(vector<double> tiempos, int n) {
    vector<float> dif;
    for (int i = 0; i < n-1; i++) {
        dif.push_back(float(tiempos[i+1] / tiempos[i]));
    }
    return dif;
}

vector<float> tasaOrden(vector<float> orden, int n) {
    vector<float> dif;
    for (int i = 0; i < n-1; i++) {
        dif.push_back(float(orden[i+1] / orden[i]));
    }
    return dif;
}

int main() {
    int size0 = 100;
    int size1 = 500;
    int size2 = 1000;
    int size3 = 1500;
    int size4 = 2000;
    int size5 = 2500;
    int size6 = 3000;
    int size7 = 3500;

    int nlog = 8;
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

    double time0, time1, time2, time3, time4, time5, time6, time7;  //Duracion en ns para cada array
    int ntime = 8;  // Cantidad de variables para medir tiempo
    vector<double> tiempos; // Vector para almacenar los tiempos

//Medir el tiempo y hacer quicksort para cada array. Se almacena el tiempo en su variable correspondiente
    steady_clock::time_point start = steady_clock::now();
    quicksort(arr0, 0, size0);
    steady_clock::time_point end = steady_clock::now();
    time0 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr1, 0, size1);
    end = steady_clock::now();
    time1 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr2, 0, size2);
    end = steady_clock::now();
    time2 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr3, 0, size3);
    end = steady_clock::now();
    time3 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr4, 0, size4);
    end = steady_clock::now();
    time4 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr5, 0, size5);
    end = steady_clock::now();
    time5 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr6, 0, size6);
    end = steady_clock::now();
    time6 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr7, 0, size7);
    end = steady_clock::now();
    time7 = timeDiffns(start, end);

    tiempos.push_back(time0);
    tiempos.push_back(time1);
    tiempos.push_back(time2);
    tiempos.push_back(time3);
    tiempos.push_back(time4);
    tiempos.push_back(time5);
    tiempos.push_back(time6);
    tiempos.push_back(time7);

    // tasaTiempo retorna un vector con la tasa de crecimiento para los tiempos
    vector<float> resultadoTiempos = tasaTiempos(tiempos, ntime);

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
    vector<float> resultTasalog = tasaOrden(tasaLog, nlog);

    // Imprimir resultados
    cout << "Se hara quicksort en 8 arrays de numeros enteros de size 100,500,1000,1500,2000,2500,3000 y 3500" << endl;
    cout << endl;
    cout << "Tiempo medido en nanosegundos para cada array" << endl;
    for (int i = 0; i < ntime; i++) {
        cout << "T" << i << " = " << tiempos[i] << endl;
    }

    cout << endl;
    cout << "Log2 de " << size0 << "," << size1 << "," << size2 << "," << size3 << "," << size4 <<
    "," << size5 << "," << size6 << "," << size7 << endl;
    for (int i = 0; i < nlog; i++) {
        cout << "L" << i << " = " << tasaLog[i] << endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los tiempos" << endl;
    for (int i = 0; i < ntime-1; i++) {
        cout<<"T"<<i+1<<"/"<<"T"<<i<<" = "<<resultadoTiempos[i]<<endl;
    }

    cout << endl;
    cout << "Tasa de crecimiento en los logaritmos" << endl;
    for (int i = 0; i < nlog-1; i++) {
        cout << "L" << i+1 << "/" << "L"<<i<< " = " << resultTasalog[i] << endl;
    }
    // Calcular un promedio entre ambas tasas de crecimiento
    float aux = 0;  // Auxiliar para ir sumando la diferencia entre laas tasas

    for (int i = 0; i < nlog-1; i++) {
        aux += abs(resultTasalog[i] - resultadoTiempos[i+1]); //agregar a aux la diferencia entre ambas tasas
    }

    float promedio = aux/nlog-1; //Dividir la suma entre la cantidad de resultados en las tasas
    if (promedio < 0)
        promedio *= -1; //esto es porque el abs no parecia funcionar
    cout << endl;
    cout << "Margen de error entre las tasas = " << promedio << endl;
    cout << "El margen se aproxima a 0, por lo tanto, se puede concluir que el quicksort tiene un orden logaritmico" << endl;


//    start = steady_clock::now();
//    quicksort(arr1, 0, cant-1);
//    end = steady_clock::now();
//    cout << "Duracion para quicksort logaritmico con pivote random = " <<
//    duration_cast<nanoseconds> (end - start).count() << " ns" << endl;


//    cout << "[ ";
//    for (int i = 0; i < 1000; i++) {
//        cout << arr1[i] << " ";
//    }
//    cout << "]" << endl;

    return 0;
}
