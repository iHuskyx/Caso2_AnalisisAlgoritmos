#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H

#include <stdexcept>
#include "avltree.h"
#include "KVPair.h"
#include "LinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 *  Descripción de la clase: Implementación de la clase abstracta Dictionary.
 *  Utiliza un AVLTree para almacenar los pares KVPair(llave-valor) del diccionario.
 *  Funcionalidades generales: Insertar, borrar, modificar un KVPair. Obtener la lista de
 *  llaves, obtener la lista de valores.
 *  Autores: Mauricio Avilés Cisneros y Andrea Li Hernández
 */
template <typename K, typename V>
class AVLTreeDictionary {
private:
    AVLTree<KVPair<K,V>> elements;

public:
    AVLTreeDictionary() {}
    ~AVLTreeDictionary() {
        clear();
    }

    void clear() {
        elements.clear(); //ejecutar el clear del AVLTree
    }

    void insert(K key, V value) {
        KVPair<K, V> p(key,value); //crear par con los valores enviados por parámetro
        elements.insert(p); //ejecutar el insert del AVLTree con el par creado
    }

    V remove(K key) {
        KVPair<K, V> p(key); //crear un par con la llave enviada por parámetro
        p = elements.remove(p); //guardar el par que se borrará
        return p.value; //retornar el valor del par que se borró
    }

    V getValue(K key) {
        KVPair<K, V> p(key); //crear un par con la llave enviada por parámetro
        p = elements.find(p); //guardar el par que se mandó a buscar
        return p.value; //retornar el valor del par que se mandó a buscar
    }

    void setValue(K key, V value) {
        KVPair<K, V> p(key, value); //crear par con los valores enviados por parámetro
        elements.remove(p); //ejecutar el remove del AVLTree
        elements.insert(p); //ejecutar el insert del AVLTree
    }

    bool contains(K key) {
        KVPair<K, V> p(key); //crear par con la llave enviada por parámetro
        return elements.contains(p); //retornar el booleano resultado del contains del AVLTree
    }

    LinkedList<K>* getKeys() {
        LinkedList<K> *keys = new LinkedList<K>(); //puntero a lista con las llaves
        LinkedList<KVPair<K, V>> *pairs = elements.getElements(); //puntero a lista con los pares del AVLTree
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) { //recorrer los pares
            KVPair<K, V> p = pairs->getElement();  //obtener un par
            keys->append(p.key); //agregar la llave del par a la lista de llaves
        }
        delete pairs;
        return keys; //retornar el puntero a la lista con llaves
    }

    LinkedList<V>* getValues() {
        LinkedList<V> *values = new LinkedList<V>(); //puntero a lista con los valores
        LinkedList<KVPair<K, V>> *pairs = elements.getElements();  //puntero a lista con los pares del AVLTree
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) { //recorrer los pares
            KVPair<K, V> p = pairs->getElement(); //obtener un par
            values->append(p.value); //agregar el valor del par a la lista de valores
        }
        delete pairs;
        return values; //retornar el puntero a la lista con valores
    }
    //retorna la cantidad de elementos de la estructura
    int getSize() {
        return elements.getSize(); //retornar el resultado del getSize del AVLTree
    }

};


#endif // AVLTREEDICTIONARY_H
