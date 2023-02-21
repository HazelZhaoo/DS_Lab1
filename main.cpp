 
#include <iostream>
using namespace std;
#include "List.hpp"

int main()
{
    List<int> L1;
    int arr[] = {5, 2, 7, 1, 8 , 6 , 9 , 0 , 1 , 4 , 6};
    int arr1[] = { 5  , 2 , 7 };
    int length = 3;
    int size = sizeof(arr) / sizeof(arr[0]);
    List<int> myList(arr, size);
    string str1 = "HAZEL";
    List<string> name_list(str1 , 5);
    List<string> single_name("Hazel");
    List<string> copy_name(single_name);

    List<int> num_list(arr1 , length);
    myList.append(arr1, 3);
    myList.insert( 3 , 4);
    myList.insert(arr1, 0, 3);
}
