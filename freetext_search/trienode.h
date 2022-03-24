#ifndef TRIENODE_H
#define TRIENODE_H

#include "avltreedictionary.h"
#include "LinkedList.h"
/**
 *  Descripción de la clase: Nodo que guarda un diccionario con todos los hijos de un
 *  determinado nodo, el número de líneas donde aparece una palabra, un atributo que indica
 *  si el nodo representa el final de una palabra y un contador para saber la cantidad de palabras
 *  que "pasan" por ese prefijo. Se usa en la clase Trie.
 *  Funcionalidades generales: Agregar o eliminar un caracter, obtener los hijos de ese caracter.
 *  Autores: Mauricio Avilés Cisneros y Andrea Li Hernández
 */
class TrieNode {
private:
    AVLTreeDictionary<char, TrieNode*> children;
    LinkedList<int> numLineas; //lista con el número de las líneas en donde aparece la palabra

public:
    bool isFinal;
    int prefixCount;

    TrieNode() : children() {
        LinkedList<int> numLineas();
        isFinal = false;
        prefixCount = 0;
    }
    ~TrieNode() {}
    bool contains(char c) {
        return children.contains(c);
    }
    void add(char c) {
        TrieNode *newNode = new TrieNode();
        children.insert(c, newNode);
    }
    void remove(char c) {
        delete children.remove(c);
    }
    TrieNode *getChild(char c) {
        return children.getValue(c);
    }
    LinkedList<char>* getChildren() {
        return children.getKeys();
    }
    LinkedList<TrieNode*> *getChildrenPointers() {
        return children.getValues();
    }
    LinkedList<int>* getUbicaciones() {
        LinkedList<int> *p = new LinkedList<int>();
        p = &numLineas;
        return p; //retornar la lista con los números de líneas
    }

};

#endif // TRIENODE_H
