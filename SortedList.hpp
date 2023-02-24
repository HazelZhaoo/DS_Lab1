#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include "List.hpp"

template <typename T>
class SortedList : public List<T>
{
private:
    bool order;
public:
    SortedList():order(true) {};//default constructor
    SortedList(T inputlist[], int size) : List<T>(inputlist , size) , order(true)
    {
        
    };
    SortedList(T v, int occ):List<T>(v, occ), order(true){};// add # of occurrances of v to sortedlist
    SortedList(T v):List<T>(v), order(true){} ; //sortedlist of size 1

    SortedList(const SortedList<T>& obj):List<T>(obj), order(true){};//copy constructor

    SortedList(SortedList<T>&& temp) noexcept :List<T>(move(temp)), order(temp.order){};//move constructor

    ~SortedList() override {};//destructor
    
    //getter for ascending/descending
    bool getOrder() const
    {
        return order;
    }

    // call sort after to make it a sortedlist
    void append(T v ) override
    {
        int n = (*this).getSize();
        if (n >= (*this).getCapacity()) // expand capacity in case size is equal or larger
        {
            (*this).expand(); //constant operation
        }
        List<T>::append(v); // call base class append function to add new value to list
        List<T>::sort(0, (*this).getSize() - 1,false); // sort the list using the base class sort function
        
    }
    
    void append(T v[], int size) override
    {
        List<T>::append(v, size); // call the base class's append function
        List<T>::sort(0, List<T>::getSize() - 1, order); // sort the list after appending
    }

    
   void insert(T v , int index) override
    {
        append(v);
        
    }
    void insert(T v[] , int size , int index) override
    {
        append(v, size);
    }

    void remove(T v, bool all) override
    {
        if (all) {
            // call base class remove function that takes a bool argument
            List<T>::remove(v, all);
        } else {
            // call derived class remove function that takes an int argument
            int remove_index =  search(v);
            List<T>::remove(remove_index);
        }
    }

 
    int search(T v) override // will return the index of the item -binary search
    {
        int low = 0, high = List<T>::n - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (List<T>::L[mid] < v)
            {
                low = mid + 1;
            }
            else if (List<T>::L[mid] > v)
            {
                high = mid - 1;
            }
            else
            {
                return mid;//found
                 
            }
        }
        

        return -1; //not found

    }



   const SortedList<T>& operator=(const SortedList<T>& obj)
    { // assignment operator
        if (this != &obj) // self assignment check
        {
            if (List<T>::L != nullptr)
            {
                delete[] List<T>::L;
            }
           
        }

        List<T>::n = obj.List<T>::n;
        List<T>::capacity = obj.List<T>::capacity;
        order = obj.order;
        List<T>::L = new T[List<T>::capacity];

        for (unsigned int i = 0; i < List<T>::n; i++)
        {
            List<T>::L[i] = obj.List<T>::L[i];
        }

        return (*this);
       cout << "Derived class assignment operator called" << endl;
    }
    
    SortedList<T>& operator=(SortedList<T>&& obj) noexcept//move assignment
    {
        if (this != &obj)
        {
            swap(List<T>::L, obj.List<T>::L);
            swap(List<T>::n, obj.List<T>::n);
            swap(List<T>::capacity, obj.List<T>::capacity);
            swap(order, obj.order);
        }

        return (*this);

    }


   SortedList<T>& operator-(const SortedList<T>& obj)
    {
        SortedList<T> L3 = (*this);

        if (obj.List<T>::n != 0)
        {
            for (unsigned int i = 0; i < obj.List<T>::n; i++)
            {
                L3.remove(obj.List<T>::L[i], false);
            }
        }

        return L3;
    }
   SortedList<T>& operator+(const SortedList<T>& obj) 
    {
        SortedList<T> L3 = (*this);
        L3.append(obj.List<T>::L, obj.List<T>::n);

        return L3;
    }

    SortedList<T>& operator--(int dummy) override
    {
        SortedList<T> temp(*this);
         List<T>::remove(List<T>::n - 1);

        return temp;
        cout << "Sorted list decrement op called" << endl;
    }

 
};
#endif /* SortedList_h */

