#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <chrono>

#include "trienode.h"

using namespace std::chrono;
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;
/**
 *  Descripción de la clase: Estructura estilo "árbol enario" que guarda strings para una
 *  búsqueda rápida.
 *  Funcionalidades generales: Insertar una palabra, revisar si la palabra ya existe dentro de
 *  la estructura, obtener todas las palabras que inicien con determinado prefijo.
 *  Autores: Mauricio Avilés Cisneros y Andrea Li Hernández
 */
class Trie {
private:
    TrieNode *root;
    int size;

public:
    Trie() {
        root = new TrieNode();
    }
    ~Trie () {
        clear();
        delete root;
    }
    void insert(string word) {
        if (containsWord(word))
            throw runtime_error("Word already in trie. ");
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            current->prefixCount++;
            if (!current->contains(word[i]))
                current->add(word[i]);
            current = current->getChild(word[i]);
        }
        current->prefixCount++;
        current->isFinal = true;
    }
    void insert(string word,int linea) {
        TrieNode *current = root;
        if (containsWord(word) == true) {
            for (unsigned int i = 0; i < word.size(); i++) {
                if (current->contains(word[i]))
                    current = current->getChild(word[i]);
            }
        } else {
            for (unsigned int i = 0; i < word.size(); i++) {
            current->prefixCount++;
            if (!current->contains(word[i]))
                current->add(word[i]);
            current = current->getChild(word[i]);
            }
            current->prefixCount++;
            current->isFinal = true;
        }
        if (!current->getUbicaciones()->contains(linea))
            current->getUbicaciones()->append(linea);
    }
    void insertIndex(string word, int linea) { // Función para agregar un índice a la lista de un nodo
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            if (current->contains(word[i]))
                current = current->getChild(word[i]);
        }
        if (current->isFinal == true) { //solo el nodo final posee la lista con los índices
            current->getUbicaciones()->append(linea); //se agrega el número a la lista
        }
    }
    bool containsWord(string word) {
        TrieNode *current = root;
        // START
        for (unsigned int i = 0; i < word.size(); i++) {
            if (!current->contains(word[i]))
                return false;
            current = current->getChild(word[i]);
        }
        if (current->isFinal)
            return true;
        //END
        return false;
    }
    LinkedList<int>* getUbicaciones(string word) {
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++) { //recorrer para llegar a al nodo final de palabra
            current = current->getChild(word[i]);
        }
        return current->getUbicaciones(); //retorna la lista con los índices de líneas
    }
    int getCantApariciones(string word) {
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            if (current->contains(word[i]))
                current = current->getChild(word[i]);
        }
        int cant = 0;
        LinkedList<string> *matches = getMatches(word);
        if (matches->getSize() > 0) {
            for (matches->goToStart(); !matches->atEnd(); matches->next()) {
                cant += getUbicaciones(matches->getElement())->getSize();
            }
        } else {
            cant = getUbicaciones(word)->getSize();
        }
        return cant;
    }

    bool containsPrefix(string prefix) {
        TrieNode *current = root;
        for (unsigned int i = 0;i < prefix.size();i++) {
            if (!current->contains(prefix[i]))
                return false;
            current = current->getChild(prefix[i]);
        }
        return true;
    }
    //retorna la cantidad de elementos que pasan por ese prefijo
    int prefixCount(string prefix) {
        TrieNode *current = root;
        for (unsigned int i = 0; i < prefix.size(); i++) {
            if (!current->contains(prefix[i]))
                return 0;
            current = current->getChild(prefix[i]);
        }
        return current->prefixCount;
    }

    void remove(string word) {
        if (!containsWord(word))
            throw runtime_error("Word not found.");
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            current->prefixCount--;
            TrieNode *child = current->getChild(word[i]);
            if (current->prefixCount == 0)
                delete current;
            else if (child->prefixCount == 1)
                current->remove(word[i]);
            current = child;
        }
        current->prefixCount--;
        if (current->prefixCount == 0)
            delete current;
        else
            current->isFinal = false;
    }

    void clear() {
        clearAux(root);
        root = new TrieNode();
    }

private:
    void clearAux(TrieNode *current) {
        LinkedList<TrieNode*> *pointers = current->getChildrenPointers();
        for (pointers->goToStart(); !pointers->atEnd(); pointers->next())
            clearAux(pointers->getElement());
        delete current;
    }

public:
    LinkedList<string>* getMatches(string prefix) {
        LinkedList<string> *words = new LinkedList<string>();
        TrieNode *current = root;
        for (unsigned int i = 0; i < prefix.size(); i++) {
            if (!current->contains(prefix[i]))
                return words;
            current = current->getChild(prefix[i]);
        }
        getMatchesAux(current, prefix, words);
        return words;
    }
private:
    void getMatchesAux(TrieNode *current, string prefix, LinkedList<string> *words) {
        if (current->isFinal)
            words->append(prefix);
        LinkedList<char> *children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()) {
            char c = children->getElement();
            string newPrefix = prefix;
            newPrefix.append(1, c);
            getMatchesAux(current->getChild(c), newPrefix, words);
        }
        delete children;
    }
public:
    //imprime en pantalla todos los elementos de la estructura.
    void print() {
        LinkedList<string> *words = getMatches("");
        cout << "[ ";
        for (words->goToStart(); !words->atEnd(); words->next()) {
            cout << words->getElement() << " ";
        }
        cout << "]" << endl;
        delete words;
    }
    int getSize() {
        return root->prefixCount;
    }
};

#endif // TRIE_H
