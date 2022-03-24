# Caso2_AnalisisAlgoritmos
Estudiante: Andrea María Li Hernández - 2021028783

Para los experimentos de quicksort e insertionsort, se hicieron pruebas con arrays de diferente cantidad de elementos, que contienen números enteros aleatorios. Estas cantidades serían el 'n' del problema.
Luego, para el free text search, en vez de trabajar con arrays, se implementó el algoritmo 'n' veces para 'n' palabras.

      Para las pruebas se siguieron estos pasos:

1- Se midió el tiempo en nanosegundos, con una marca de tiempo al iniciar y al terminar el algoritmo. Se calculó la diferencia entre estas dos marcas y a eso se le denominó como la duración del algoritmo. Esto se realizó para medir la duración de las pruebas para cada cantidad de elementos.

2- Los tiempos se almacenaron en un vector, este vector se envía como parámetro a una función que calcula la tasa de crecimiento de la manera: tiempos[i+1]/tiempos[i] k cantidad de veces. Siendo k = tiempos.size()-1. Los resultados de esta función se almacenan en otro vector.

3- En otro vector se almacenaron las 'n' que corresponden al tiempo algoritmico que se desea demostrar. Por ejemplo, si tengo un array con 100 elementos y quiero demostrar un tiempo logarítmico, voy a almacenar el logaritmo base 2 de 100 en el vector. Si se quisiera demostrar un tiempo lineal, almacenaría el 100.

4- El vector con las 'n' se envía como parámetro a una función que calcula la tasa de crecimiento de la misma manera mencionada anteriormente y los resultados son almacenados en otro vector.

5- Ahora se va a calcular un promedio de crecimiento de las tasas, consiste en sumar las diferencias abs( tasaTiempos[i] - tasaN[i] ) hasta que i llegue al tamaño de los vectores, y luego dividir la suma entre la cantidad de elementos de los vectores. Por ejemplo, si se hicieron 8 pruebas, habrán 7 elementos en los vectores de tasa para tiempos y para 'n'. 

6- Finalmente, si el promedio o margen de error se aproxima a 0, significa que la diferencia entre ambas tasas es mínima. 

Entonces, si la diferencia entre la tasa de crecimiento de los tiempos y la tasa de crecimiento de las 'n' es mínima, se puede inferir que ambas poseen un comportamiento igual o muy similar. Por lo que se puede concluir que sí se cumple el tiempo algorítmico propuesto. Así concluye la demostración. 

***************************************************************
         Ejemplo de uno de los resultados obtenidos para insertion sort cuadrático

Se hará insertion_sort en 8 arrays de numeros enteros de size 100,500,1000,1500,2000,2500,3000 y 3500

    Tiempo medido en nanosegundos para cada array

T0 = 13900

T1 = 375600

T2 = 1.4776e+06   ------->      ** nota: esto es igual a = 1477600

T3 = 3.3969e+06   ------->    3396900

T4 = 6.0687e+06   ------->    6068700

T5 = 9.7713e+06   ------->    9771300

T6 = 1.3959e+07   ------->    13959000

T7 = 1.88236e+07  ------->    18823600

    n^2 de 100,500,1000,1500,2000,2500,3000,3500

pow2_0 = 10000

pow2_1 = 250000

pow2_2 = 1000000

pow2_3 = 2250000

pow2_4 = 4000000

pow2_5 = 6250000

pow2_6 = 9000000

pow2_7 = 12250000

    Tasa de crecimiento en los tiempos

T1/T0 = 27.0216

T2/T1 = 3.93397

T3/T2 = 2.29893

T4/T3 = 1.78654

T5/T4 = 1.61011

T6/T5 = 1.42857

T7/T6 = 1.34849

    Tasa de crecimiento en los n^2

N1/N0 = 25

N2/N1 = 4

N3/N2 = 2.25

N4/N3 = 1.77778

N5/N4 = 1.5625

N6/N5 = 1.44

N7/N6 = 1.36111

*******************************************************
Calcular promedio entre las tasas

suma = abs(T1/T0 - N1/N0) + abs(T2/T1 - N2/N1) + ... + abs(T7/T6 - N7/N6)

margen de error = suma/7

*******************************************************

Margen de error entre las tasas = 0.722879

El margen se aproxima a 0, por lo tanto, se puede concluir que el insertion_sort está teniendo un tiempo algorítmico cuadrático

**Si la tasa de los tiempos es muy similar a la tasa de las potencias cuadradas, significa que siguen un comportamiento igual de similar.
