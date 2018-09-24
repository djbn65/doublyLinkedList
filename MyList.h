/* Clean and simple version of the doubly linked std::list
 * This is your h file. Do not edit it!
 * If you want to know what the functions do,
 * read the links in the assignment description from en.cppreference.
 */ 

#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <exception>
using std::exception;
using std::cout;
using std::endl;
using std::cin;

// TODO add back name function next year -- it helps with cheatchecking

template <typename T>
class Node
{
    public:
        T m_element;

        Node<T> *m_prev;
        Node<T> *m_next;

        Node(const T &x, Node<T> *prev, Node<T> *next): m_element(x), m_prev(prev), m_next(next) {}
};


template <typename T>
class MyList
{
    private:
        Node<T> *m_head;
        Node<T> *m_tail;

        int m_size;

    public:
        MyList();

        ~MyList();

        MyList<T> & operator=(const MyList<T> &source);

        MyList(const MyList<T> &source);
        
        T & front();

        T & back();
        
        void assign(int count, const T &value);
        
        void clear();

        void push_front(const T &x);

        void push_back(const T &x);

        void pop_back();
        
        // next year -- forgot this one:
        //void pop_front();

        // Simplified version that only takes one position
        void insert(int i, const T &x);

        void remove(T i);

        void erase(int i);
        
        void reverse();

        void resize(int count);

        bool empty();
        
        int size();

        // Mimicking c++ iterator trickery from here down. 
        // You don't need to edit these two.
        int begin()
        {
            return 0;
        }

        int end()
        {
            return correct_size();
        }

        int correct_size() 
        {
            return m_size;
        }

        T & correct_back() 
        {
            return m_tail->m_element;
        }

        void correct_push_back(const T &x)
        {
            if(m_size == 0)
            {
                m_head = m_tail = new Node<T>(x, nullptr, nullptr);
            }
            else
            {
                m_tail = m_tail->m_next = new Node<T>(x, m_tail, nullptr);
            }
            
            m_size++;
        }

        void correct_pop_back()
        {
            m_tail = m_tail->m_prev;
            delete m_tail->m_next;
            m_tail->m_next = nullptr;
        }


};

#include "MyList.hpp"

#endif

