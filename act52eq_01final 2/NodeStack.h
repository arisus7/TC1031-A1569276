#ifndef _NODESTACK_H_
#define _NODESTACK_H_

template <class T>
class NodeStack {
  private:
    T data;
    NodeStack<T> *next;

  public:
    NodeStack();
    NodeStack(T value);
    // El template StackLL<U> tiene accesso a las variables de clase privadas de esta clase
    template<typename U> friend class StackLL;   
};

template <class T> 
NodeStack<T>::NodeStack() : data{}, next{nullptr} {}

template <class T> 
NodeStack<T>::NodeStack(T value) : data{value}, next{nullptr} {}


#endif // _NODESTACK_H_