#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;
/**
 *  Descripci�n de la clase: Implementaci�n de la clase abstracta List.
 *  Funcionalidades generales: Insertar, borrar, moverse al inicio, moverse al final  de la estructura, obtener
 *  el �ndice de un elemento.
 *  Autores: Mauricio Avil�s Cisneros y Andrea Li Hern�ndez
 */
template <typename E>
class LinkedList {
private:
    Node<E> *head;
    Node<E> *current;
    Node<E> *tail;
    int size;

public:
    LinkedList() {
        tail = current = head = new Node<E>();
        size = 0;
    }
    ~LinkedList() {
        clear();
        delete head;
    }

    void insert (E element) {
        current -> next = new Node<E> (element, current->next);
        if (current == tail) {
            tail = current -> next;
        }
        size++;
    }

    void append(E element) {
        tail = tail->next = new Node<E>(element);
        size++;
    }

    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == nullptr)
            throw runtime_error("No current element.");
        E result = current->next->element;
        Node<E> *temp = current->next;
        current->next = temp-> next;
        if (temp == tail)
            tail = current;
        delete temp;
        size--;
        return result;
    }

    void clear() {
        while(head->next != nullptr) {
            current = head->next;
            head-> next = current->next;
            delete current;
        }
        current = tail = head;
        size = 0;
    }

    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }
    //Mueve la posici�n actual al inicio de la estructura.
    void goToStart() {
        current = head;
    }
    //Mueve la posici�n actual al final de la estructura.
    void goToEnd() {
        current = tail;
    }
    //Mueve la posici�n actual a la posici�n indicada por par�metro.
    void goToPos(int pos) {
        if (pos < 0 || pos >size)
            throw runtime_error("Index out of range. ");
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }
    //Mueve la posici�n actual al elemento siguiente al elemento actual.
    void next() {
        if (current != tail)
            current = current->next;
    }
    //Mueve la posici�n actual al elemento anterior al elemento actual.
    void previous() {
        if (current != head) {
            Node<E> *temp = head;
            while (temp->next != current)
                temp = temp->next;
            current = temp;
        }
    }

    bool atStart() {
        return current == head;
    }

    bool atEnd() {
        return current == tail;
    }

    int getPos() {
        int pos = 0;
        Node<E> *temp = head;
        while (temp != current) {
            temp = temp->next;
            pos++;
        }
        return pos;
    }
    int getSize() {
        return size;
    }
    //imprime los elementos de la estructura
    void print() {
        Node<E> *oldCurrent = current;
        cout << "[ ";
        for (goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]" << endl;
        current = oldCurrent;
    }

    int indexOf (E element) {
        int copiaPos = getPos(); //copia de la posici�n
        goToStart(); // ir al inicio de la lista
        for (int i = 0; i < size; i++) {
            if (getElement() == element) { //si se encuentra el elemento
                goToPos(copiaPos); //volver a la posici�n original
                return i; //retornar el �ndice del elemento en la lista
            }
            next(); //si no se ha encontrado, va al siguiente elemento en la lista
        }
        goToPos(copiaPos); //volver a la posici�n original
        return -1; //si sali� del ciclo, significa que no se encontr� el elemento, retorna -1
    }

    bool contains(E element) {
        if (indexOf(element) >= 0) //si retorna un n�mero > 0, significa que encontr� el elemento
            return true;
        return false; // si indexOf retorna -1, significa que el elemento no se encontr�
    }


};

#endif // LINKEDLIST_H
