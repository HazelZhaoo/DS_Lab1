#ifndef List_h
#define List_h
#include <iostream>
#include <fstream>
#include <utility>
 
using namespace std;

template <typename T>
class List
{
protected :
    T* L; // pointer to first item of the list
    int n; //number of items
    int capacity; //max number of items that can be in the list
    void expand()
    {
        capacity *= 2;
        T* temp = new T[capacity];
        for (unsigned int i = 0; i < n; i++)
        {
            temp[i] = L[i];
        }

        L = temp;//can make L point to temp here
        
        delete[] temp;
    }
    
public:
    
    List() : L(nullptr), n(0), capacity(10)//default constructor
    {
        cout << "default constructor called." << endl;
    }
    
    List(T inputList[], int size) : L(nullptr), n(0), capacity(10)//inputting a list
    {
        cout << "List parameter constructor called!" << endl;
        if (size < 0)
        {
            throw runtime_error("Cannot have negative size!");
        }

        while (size > capacity)
        {
            cout << "expand function called" << endl;
            expand();
        }

        n = size;
        L = new T[capacity];

        for (int i = 0; i < size; i++)
        {
            L[i] = inputList[i];
            cout << L[i] << " " ; //remove this afterwards//
        }
        cout <<endl;
    }
    
    List(T v, int occ) : L(nullptr), n(0), capacity(10)//adding # of occurrances
    {
        if (occ < 0)
        {
            throw runtime_error("Cannot have negative size!");
        }

        while (occ > capacity)
        {
            expand();
        }

        n = occ;
        L = new T[capacity];

        for (int i = 0; i < n; i++)
        {
            (*this)[i] = v;
            cout << (*this)[i] << " " ;
        }
        cout <<endl;
        cout << "one value occurance constructor called" << endl;
    }
   
    List(T v):L(new T[1]), n(1), capacity(10)
    {
        cout << "single value constructor called with value " << v << endl;
        L[0] = v;
    }//type conversion -> review
     
 
    virtual ~List()//destructor
    {
        if (L != nullptr) {
            delete[] L;
        }
    }

     
    List(const List<T>& obj) : L(nullptr), n(obj.n), capacity(obj.capacity)
    {
        if (obj.L != nullptr) {
            L = new T[capacity];
            for (unsigned int i = 0; i < n; i++) {
                L[i] = obj.L[i]; // deep copy
            }
        }
        cout << "Copy constructor called" << endl;
    }

    
    List(List&& temp) noexcept : L(temp.L), n(temp.n), capacity(temp.capacity)//move constructor
    {
        temp.L = nullptr;
        temp.n = 0;
        temp.capacity = 0;
    }

     
    int getSize() const//getter for size
    {
        return n;
    }

     
    int getCapacity() const//getter for capacity
    {
        return capacity;
    }
    
    T& getValue(int index) const//getter for value
    {
        return L[index];
    }
    
    const T& operator[](int index) const
    {
        if (index < 0 || index >= n) {
            throw std::out_of_range("Index out of bounds");
        }
        return L[index];
    }
     
    virtual void append(T v)
    {
        if (L == nullptr) {
            expand();
        }
        else if (n == capacity)
        {
            expand();
        }

        L[n] = v; //(index starts at 0)
        n++;
        
        for (int i = 0; i < n; i++)
        {
            cout << L[i] << " ";
        }
        cout << "appended the list with value " << v << endl;
    }

     
    virtual void append(T v[], int size) {
        while ((n + size) > capacity) {
            expand();
        }

        for(unsigned int i = n, j = 0; i < n + size; i++, j++)
        {
            L[i] = v[j];
        }
        n += size;
        
        cout << "appended with a list \n" ;
        for (unsigned int i = 0; i < n; i++) {
            cout << L[i] << " ";
        }
        cout << endl;
    }
    
    virtual void insert(T v, int index) //insert a value at an index
    {
        if (index < 0)
        {
            throw runtime_error("negative indices DNE");
        }

        if (n + 1 > capacity)
        {
            expand();
        }

        n++;

        for (unsigned int i = n; i >= index; i--)
        {
            L[i] = L[i - 1];

            if (i == index)
                L[i] = v;
        }
        for (unsigned int i = 0; i < n; i++) {
            cout << L[i] << " ";
        }
        cout << "inserted " << v << " at index " << index << endl;
    }

    
    virtual void insert(T v[], int index, int size)
    {
        if (index < 0 || index > n)
        {
            throw runtime_error("Index out of range.");
        }
         
        while (n + size > capacity)
        {
            expand();
        }

        n += size;

        for (int i = n - 1; i >= index + size; i--)
        {
            L[i] = L[i - size];
        }

        for (int i = 0; i < size; i++)
        {
            if (index + i >= n)
            {
                L[index + i] = v[i];
            }
            else
            {
                T temp = L[index + i];
                L[index + i] = v[i];
                v[i] = temp;
            }
        }
        cout << "inserted a list at index " << index <<endl;
        for (unsigned int i = 0; i < n; i++)
        {
            cout << L[i] << " ";
        }
        cout << endl;
    }
   
    int partition(List<T>* l, int start, int end, bool asc) // for quicksort
    {
        T pivot = (*l)[start]; // Choose the first element as the pivot
        int low = start + 1; // Index for forward search
        int high = end; // Index for backward search
        if (asc == true)
        {
            while (high > low)
            {
                // Search forward from left
                while (low <= high && (*l)[low] <= pivot)
                    low++;

                // Search backward from right
                while (low <= high && (*l)[high] > pivot)
                    high--;

                // Swap two elements in the list
                if (high > low)
                {
                    T temp = (*l)[high];
                    (*l)[high] = (*l)[low];
                    (*l)[low] = temp;
                }
            }

            while (high > start &&(*l)[high] >= pivot)
                high--;

            // Swap pivot with list[high]
            if (pivot > (*l)[high])
            {
                (*l)[start] = (*l)[high];
                (*l)[high] = pivot ;
                return high;
            }
            else
            {
                return start;
            }
        }
        else
        {
            while (high > low)
            {
                // Search forward from left
                while (low <= high && (*l)[low] > pivot)
                    low++;

                // Search backward from right
                while (low <= high && (*l)[high] <= pivot)
                    high--;

                // Swap two elements in the list
                if (high > low)
                {
                    T temp = (*l)[high];
                    (*l)[high] = (*l)[low];
                    (*l)[low] = temp;
                }
            }

            while (high > start && (*l)[high] <= pivot)
                high--;

            // Swap pivot with list[high]
            if (pivot <= (*l)[high])
            {
                (*l)[start] = (*l)[high];
                (*l)[high] = pivot ;
                return high;
            }
            else
            {
                return start;
            }
        }
    }
 
    void sort(int start, int end, bool asc)
    {
        if (end > start)
        {
            int pivotIndex = partition(this, start, end, true);
                sort(start, pivotIndex - 1, asc);
                sort(pivotIndex + 1, end, asc);
        }
        
         
    }
     
    virtual void remove(int index)//remove item at index
    {
        if (index < 0)
        {
            throw runtime_error("negative indices DNE");
        }

        n--;

        for (unsigned int i = index; i < n; i++)
        {
            L[i] = L[i + 1];
        }
        
        for (unsigned int i = index; i < n; i++)
        {
            cout << L[i] << " ";
        }
        cout << "removed index at " << index << endl;
    }

    
   virtual void remove(T v, bool all)//remove all or a single occurrance
    {                                // of an item
        int index = search(v);
        
        if (index != -1)
        {
            if (all == true)
            {
                T* temp = new T[capacity];
                int iTemp = 0;
                
                for (int i = 0; i < n; i++)
                {
                    if (L[i] != v)
                    {
                        temp[iTemp] = L[i];
                        iTemp++;
                    }
                }
                
                L = temp;
                n = iTemp;
                temp = nullptr;
                delete[] temp;

            }
            else if (all == false)
                remove(index);
            
            
            cout << "removed "<< v  << " based on occurances." << endl;
        }
    }
    
    virtual int search(T v) //performs a linear search on the list
    {
        for (int i = 0; i < n; i++)
        {
            T temp = L[i];

            if (temp == v)
            {
                return i;
            }
        }

        return -1;
    }
    
   virtual const List<T>& operator=(const List<T>& obj)//assignment operator
    {
        if (this != &obj)
        {
            if (L != nullptr)
            {
                delete[] L;
            }
        }

        n = obj.n;
        capacity = obj.capacity;
        L = new T[capacity];

        for (unsigned int i = 0; i < n; i++)
        {
            (*this)[i] = obj[i];
        }

        return (*this);//
    }

    T& operator[] (int i)//overloaded offset operator
    {
        if (i >= 0 && i < n)
        {
            return L[i];
        }
        else
        {
            throw logic_error("ERRORR: index is out of bounds.");
            exit(1);
        }
    }
    
    virtual List<T> operator+(const List<T>& obj)//overloaded addition
    {
        List<T> L3 = (*this);
        L3.append(obj.L, obj.n);

        return L3;
    }
    virtual List<T> operator-(const List<T>& obj)//overloaded subtraction
    {
        List<T> L3 = (*this);
        for (unsigned int i = 0; i < obj.n; i++)
        {
            L3.remove(obj[i] , false);
        }

        return L3;

    }
    
    List<T>& operator+=(const List<T>& obj)//review
    {
        if (n + obj.n > capacity)
        {
            expand();
        }

        if (obj.n == 0)
        {
            return (*this);
        }
        else if (obj.n == 1)
        {
            append(obj.L[0]);
            return (*this);
        }
        else
        {
            append(obj.L, obj.n);
        }

        return (*this);
    }

    
    List<T>& operator-=(const List<T>& obj)//review
    {
        for (int i = 0; i < obj.n; i++)
        {
            remove(obj[i], false);
        }

        //shrink capacity?

        return (*this);
    }
    
    List<T>& operator=(List&& obj) noexcept//move assignment operator
    {
        if (this != &obj)
        {
            swap(L, obj.L);
            swap(n, obj.n);
            swap(capacity, obj.capacity);
        }

        return (*this);
    }
    
    List<T>& operator--()//overloaded prefix decrement
    {
        remove(n - 1);

        return (*this);
        cout <<"prefix -- called" << endl;
    }

    
    virtual List<T>& operator--(int dummy)//overloaded postfix decrement
    {
        List<T> temp(*this);
        remove(n - 1);

        for(int i = 0 ; i < n; i++)
        {
            cout << L[i] << " ";
        }
        cout << "postfix -- called" << endl;
        return temp;
    }
    
    template <typename U>
    friend ostream& operator<<(ostream& out, const List<U>& l);//class implementation
     
    template <typename U>
    friend istream& operator>>(istream& input, List<U>& l);
     
};

template <typename T>
ostream& operator<<(ostream& out, const List<T>& l)//class implementation
{
    out << "The items in the list are: "  << endl;

    int size = l.getSize();
    out << "{" ;
    for (int i = 0; i < size; i++)
    {
        
        out << l[i];
        if (i != (size - 1))
        {
            out << ", ";
        }
    }

    out << "}";

    return out;
}

template <typename T>
istream& operator>>(istream& input, List<T>& l)
{
    //clear the list first
    l.L = nullptr;

    T value;

    while (input.peek() != '\n')
    {
        input >> value;
        l.append(value);
    }

    return input;
}
#endif /* List_h */
