#ifndef List_h
#define List_h
#include <fstream>
#include <utility>
 
using namespace std;

template <typename T>
class List
{
private :
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
        temp = nullptr;
        delete[] temp;
    }
    
public:
    
    List() : L(nullptr), n(0), capacity(10)//default constructor
    {
        cout << "defaulf constructor called." << endl;
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
     
 
   ~List()//destructor
    {
        delete[] L;
    }

     
    List(const List<T>& obj) : L(nullptr), n(0), capacity(10)//copy constructor
    {
        n = obj.n;
        capacity = obj.capacity;
        L = new T[capacity];

        for (unsigned int i = 0; i < n; i++)
        {
            (*this)[i] = obj[i];//deep copy
        }
        cout << "Copy constructor called " << endl;
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
    
    T getValue(int index) const//getter for value
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
     
    void append(T v)//append a value
    {
        if (n < capacity)
        {
            L[n] = v; //(index starts at 0)
        }
        else
        {
            expand();
            L[n] = v;
        }
        n++;
        for(int i = 0 ; i < n+1 ; i++)
        {
            cout << L[i] << " " ;
        }
        cout << "appended the list with value" << v << endl;
        
    }
     
    void append(T v[], int size) {
        while ((n + size) > capacity) {
            expand();
        }

        for (unsigned int i = n, j = 0; i < n + size; i++, j++)
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
    
    void insert(T v, int index) //insert a value at an index
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

    
    void insert(T v[], int index, int size)
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
    
    const List<T>& operator=(const List& obj)//assignment operator
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


        
};
#endif /* List_h */
