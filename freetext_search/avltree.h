#ifndef AVLTREE_H
#define AVLTREE_H

#include "bstnode.h"
#include "LinkedList.h"
#include <stdexcept>

using std::runtime_error;

/**
 *  Descripción de la clase: Estructura estilo árbol autobalanceada por altura.
 *  Funcionalidades generales: Inserción, borrado, obtener elementos, encontrar elemento.
 *  Autor: Mauricio Avilés Cisneros y Andrea Li Hernández
 */

template <typename E>
class AVLTree
{
private:
    BSTNode<E> *root;
    int size;

public:
    AVLTree() {
        root = nullptr;
        size = 0;
    }
    ~AVLTree() {
        clear();
    }

    void insert(E element) {
        root = insertAux(root, element);
        size++;
    }

private:
    BSTNode<E>* insertAux(BSTNode<E> *current, E element) {
        if (current == nullptr)
            return new BSTNode<E>(element);
        if (element == current->element)
            throw runtime_error("Duplicated element.");
        if (element < current->element) {
            current->left = insertAux(current->left, element);
            return rebalanceLeft(current);
        } else {
            current->right = insertAux(current->right, element);
            return rebalanceRight(current);
        }

    }

    BSTNode<E>* rebalanceLeft(BSTNode<E> *current) {
        int leftHeight = height(current->left);
        int rightHeight = height(current->right);
        if (leftHeight - rightHeight > 1) {
            int leftLeftHeight = height(current->left->left);
            int leftRightHeight = height(current->left->right);
            if (leftLeftHeight >= leftRightHeight) {
                //rotación a la derecha en el abuelo
                return rotateRight(current);
            } else {
                //rotación a la izq en el abuelo
                //rotación a la derecha en el abuelo
                current->left = rotateLeft(current->left);
                return rotateRight(current);
            }
        }
        return current;
    }

    BSTNode<E>* rebalanceRight(BSTNode<E> *current) {
        int rightHeight = height(current->right);
        int leftHeight = height(current->left);
        if (rightHeight - leftHeight > 1) {
            int rightLeftHeight = height(current->right->left);
            int rightRightHeight = height(current->right->right);
            if (rightRightHeight >= rightLeftHeight) {
                //rotación a la derecha en el abuelo
                return rotateLeft(current);
            } else {
                //rotación a la izq en el abuelo
                //rotación a la derecha en el abuelo
                current->right = rotateRight(current->right);
                return rotateLeft(current);
            }
        }
        return current;
    }

    BSTNode<E>* rotateLeft(BSTNode<E> *current) {
        if (current == nullptr)
            throw runtime_error("Can't rotate left on null. ");
        if (current-> right == nullptr)
            throw runtime_error("Can't rotate left with null right child. ");
        BSTNode<E> *temp = current->right;
        current->right = temp->left;
        temp->left = current;
        return temp;
    }

    BSTNode<E>* rotateRight(BSTNode<E> *current) {
        if (current == nullptr)
            throw runtime_error("Can't rotate right on null. ");
        if (current-> left == nullptr)
            throw runtime_error("Can't rotate right with null left child. ");
        BSTNode<E> *temp = current->left;
        current->left = temp->right;
        temp->right = current;
        return temp;
    }

public:

    int height(BSTNode<E> *current) {
            if (current == nullptr)
                return 0;
            int leftHeight = height(current->left);
            int rightHeight = height(current->right);
            if (leftHeight > rightHeight)
                return 1 + leftHeight;
            else
                return 1 + rightHeight;
        }

public:

    bool contains(E element) {
        return containsAux(root, element);
    }
private:
    //función auxiliar usada por la función contains.
    bool containsAux(BSTNode<E> *current, E element) {
        if (current == nullptr)
            return false;
        if (element == current->element)
            return true;
        if (element < current->element)
            return containsAux(current->left, element);
        else
            return containsAux(current->right, element);
    }

public:

    E find(E element) {
        return findAux(root, element);
    }
private:
    //función auxiliar usada por el método "findAux"
    E findAux(BSTNode<E> *current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found. ");
        if (element == current->element)
            return current->element;
        if (element < current->element)
            return findAux(current->left, element);
        else
            return findAux(current->right, element);
    }

public:
    E remove(E element) {
        E result;
        root = removeAux(root, element, &result);
        size--;
        return result;
    }

private:
    //función auxiliar usada en la función remove, para utilizar recursión.
    BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
        if (current == nullptr)
            throw runtime_error("Element not found. ");
        if (element < current->element){
            current->left = removeAux(current->left, element, result);
            return rebalanceRight(current);
        }
        if (element > current->element) {
            current->right = removeAux(current->right, element, result);
            return rebalanceLeft(current);
        } else { //element == current->element
            *result = current->element;
            if (current->isLeaf()) {
                delete current;
                return nullptr;
            }
            if (current->childrenCount() == 1) {
                BSTNode<E>* child = current->getUniqueChild();
                delete current;
                return child;
            } else {
                //el nodo tiene dos hijos
                BSTNode<E>* successor = getSuccessor(current);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);
                return rebalanceLeft(current);
            }
        }
    }

    //Obtiene el sucesor de un nodo, o sea, el menor de los hijos mayores.
    BSTNode<E> *getSuccessor(BSTNode<E> *current) {
        if (current->left == nullptr)
            return current;
        else
            return getSuccessor(current->left);
    }
    //intercambia un nodo con otro.
    void swap(BSTNode<E>* node1, BSTNode<E>* node2) {
        E element = node1->element;
        node1->element = node2->element;
        node2->element = element;
    }

public:
    void clear() {
        clearAux(root);
        root = nullptr;
        size = 0;
    }
private:
    //función auxiliar que se usa al llamar a "clear", sirve para hacer
    //funcionar la recursión.
    void clearAux(BSTNode<E> *current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

public:
    LinkedList<E>* getElements() {
        LinkedList<E>* elements = new LinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }
private:
    //función auxiliar que se usa en getElements para hacer funcionar la
    //llamada recursiva.
    void getElementsAux(BSTNode<E> *current, LinkedList<E> *elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

public:
    int getSize() {
        return size;
    }
};

#endif // AVLTREE_H

