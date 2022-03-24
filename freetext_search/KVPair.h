#ifndef KVPAIR_H
#define KVPAIR_H

#include <iostream>

using std::ostream;

/**
 *  Descripci�n de la clase: Clase que se utiliza al implementar la clase Dictionary, guarda en ella
 *  dos elementos que corresponden a la Llave y el Valor asociado a esa llave.
 *  Funcionalidades generales: Sobreescritura de los operadores de asignaci�n, comparaci�n y el operador "<<"
 *  Autor: Mauricio Avil�s Cisneros
 */
template <typename K, typename V>
class KVPair {
public:
    K key;
    V value;

    KVPair() {}
    KVPair(K key) {
        this->key = key;
    }

    KVPair(K key, V value) {
        this->key = key;
        this->value = value;
    }
    /**< Los m�todos encontrados ac� abajo corresponden a la sobreescritura de las funciones de
    asignaci�n, comparaci�n, etc.
     */
    void operator=(const KVPair& other) {
        this->key = other.key;
        this->value = other.value;
    }
    bool operator==(const KVPair& other) {
        return this->key == other.key;
    }
    bool operator!=(const KVPair& other) {
        return this->key != other.key;
    }
    bool operator<(const KVPair& other) {
        return this->key < other.key;
    }
    bool operator<=(const KVPair& other) {
        return this->key <= other.key;
    }
    bool operator>(const KVPair& other) {
        return this->key > other.key;
    }
    bool operator>=(const KVPair& other) {
        return this->key >= other.key;
    }

};

// Esta funci�n "solitaria" sirve para sobrescribir el funcionamiento
// del operador << con el KVPair.
// Aparentemente no se puede sobrescribir desde dentro de la clase
// y hay que hacerlo en una funci�n aparte.
template<typename K, typename V>
ostream& operator<<(ostream& os, const KVPair<K, V>& p) {
    os << p.key << "," << p.value;
    return os;
}

#endif // KVPAIR_H
