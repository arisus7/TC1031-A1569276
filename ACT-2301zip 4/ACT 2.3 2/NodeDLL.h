#ifndef _NODEDLL_H_
#define _NODEDLL_H_

template <class T>
class NodeDLL {
  private:
    T data;
    NodeDLL<T> *next;
    NodeDLL<T> *prev;

  public:
    NodeDLL();
    NodeDLL(T value);
    // El template DoubleLinkedList<U> tiene accesso a las variables de clase privadas de esta clase
    template<typename U> friend class DoublyLinkedList;   
};

template <class T> 
NodeDLL<T>::NodeDLL() : data{}, next{nullptr}, prev{nullptr} {}

template <class T> 
NodeDLL<T>::NodeDLL(T value) : data{value}, next{nullptr}, prev{nullptr} {}


#endif // _NODEDLL_H_