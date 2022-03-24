#ifndef BSTNODE_H
#define BSTNODE_H

/**
 *  Descripción de la clase: Nodo que guarda el elemento, un puntero al hijo izquierdo y derecho de ese elemento.
 *  Se usa en estructuras tipo árbol, como el AVL.
 *  Funcionalidades generales: Conocer si el nodo es una hoja, obtener la cantidad de hijos de ese nodo
 *  obtener el hijo del nodo.
 *  Autores: Mauricio Avilés Cisneros y Andrea Li Hernández
 */
template <typename E>
class BSTNode
{
public:
    E element;
    BSTNode<E> *left;
    BSTNode<E> *right;

    //constructor
    BSTNode(E element, BSTNode<E> *left = nullptr, BSTNode<E> *right = nullptr) {
        this->element = element;
        this->left = left;
        this->right = right;
    }
    //Retorna true si el nodo actual es una hoja
    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }
    //Retorna un entero correspondiente a la cantidad de hijos de un nodo
    int childrenCount() {
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }
    //Retorna un puntero al hijo del nodo
    BSTNode<E>* getUniqueChild() {
        return left == nullptr? right : left;
    }

};

#endif // BSTNODE_H

