#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <algorithm>

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

vector<float> tasaTiempos(vector<double> tiempos) {
    vector<float> dif;
    for (int i = 0; i < 4; i++) {
        dif.push_back(float(tiempos[i+1] / tiempos[i]));
    }
    return dif;
}

vector<float> tasaOrden(vector<float> orden) {
    vector<float> dif;
    for (int i = 0; i < 4; i++) {
        dif.push_back(float(orden[i+1] / orden[i]));
    }
    return dif;
}

int main() {
    int arr0[100], arr1[1000], arr2[5000], arr3[10000], arr4[20000];

    fillArray(arr0, 100);
    fillArray(arr1, 1000);
    fillArray(arr2, 5000);
    fillArray(arr3, 10000);
    fillArray(arr4, 20000);

    double time0, time1, time2, time3, time4;
    vector<double> tiempos;

    steady_clock::time_point start = steady_clock::now();
    quicksort(arr0, 0, 100);
    steady_clock::time_point end = steady_clock::now();
    time0 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr1, 0, 1000);
    end = steady_clock::now();
    time1 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr2, 0, 5000);
    end = steady_clock::now();
    time2 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr3, 0, 10000);
    end = steady_clock::now();
    time3 = timeDiffns(start, end);

    start = steady_clock::now();
    quicksort(arr4, 0, 20000);
    end = steady_clock::now();
    time4 = timeDiffns(start, end);

    tiempos.push_back(time0);
    tiempos.push_back(time1);
    tiempos.push_back(time2);
    tiempos.push_back(time3);
    tiempos.push_back(time4);

    vector<float> resultadoTiempos = tasaTiempos(tiempos);

    float log0_test, log1_test, log2_test, log3_test, log4_test;
    vector<float> tasaLog;
    log0_test = log2(100);
    log1_test = log2(1000);
    log2_test = log2(5000);
    log3_test = log2(10000);
    log4_test = log2(20000);
    tasaLog.push_back(log0_test);
    tasaLog.push_back(log1_test);
    tasaLog.push_back(log2_test);
    tasaLog.push_back(log3_test);
    tasaLog.push_back(log4_test);

//    for (int i = 0; i < 5; i++) {
//        cout << tiempos[i] << endl;
//    }



//    cout << endl;
//    for (int i = 0; i < 4; i++) {
//        cout << resultadoTiempos[i] << endl;
//    }

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
