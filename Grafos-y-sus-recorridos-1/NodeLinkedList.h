#ifndef _NODELINKEDLIST_H_
#define _NODELINKEDLIST_H_

template <class T>
class NodeLinkedList {
  private:
    T data;
    NodeLinkedList<T> *next;

  public:
    NodeLinkedList();
    NodeLinkedList(T value);
    // El template LinkedList<U> tiene accesso a las variables de clase privadas de esta clase
    template<typename U> friend class LinkedList;
    template<typename U> friend class Graph;
};

template <class T> 
NodeLinkedList<T>::NodeLinkedList() : data{}, next{nullptr} {}

template <class T> 
NodeLinkedList<T>::NodeLinkedList(T value) : data{value}, next{nullptr} {}


#endif // _NODELINKEDLIST_H_