#ifndef NODE_H
#define NODE_H

/**
 *  Descripción de la clase: Nodo que guarda un elemento y un puntero al elemento siguiente a él.
 *  Esta clase se usa en la estructura LinkedList.
 *  Funcionalidades generales: Constructores, atributos públicos que representan al elemento y
 *  el puntero al siguiente.
 *  Autor: Mauricio Avilés Cisneros
 */
template <typename E>
class Node{
public:
    E element;
    Node<E> *next;

    Node(E element, Node<E> *next = nullptr) {
        this->element= element;
        this->next= next;
    }
    Node(Node<E> *next = nullptr) {
        this->next = next;
    }
};

#endif // NODE_H
