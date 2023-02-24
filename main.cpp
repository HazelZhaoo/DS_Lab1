#include <iostream>
using namespace std;
#include "List.hpp"
#include "SortedList.hpp"
 
int main()
{
    //***Test function for list******************/////////////////////
    List<int> L1;
    int arr[] = {5, 2, 7, 1, 8 , 6 , 9 , 0 , 1 , 4 , 6};
    int arr1[] = { 5  , 2 , 7  , 6};
    int length = 4;
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
    myList.sort(0 ,17 , true);
    
    for(int i = 0 ; i < myList.getSize() ; i++)
    {
        cout << myList.getValue(i) << " ";
    }
    cout <<endl;
    myList.remove(0);
    myList.remove(2 , false);
    for(int i = 0 ; i < myList.getSize() ; i++)
    {
        cout << myList.getValue(i) << " ";
    }
    cout <<endl;
    myList.remove(2 , true);
    for(int i = 0 ; i < myList.getSize() ; i++)
    {
        cout << myList.getValue(i) << " ";
    }
    cout <<endl;
    
    List<string> first_name("Aniyah");
    List<string> last_name("Bohnen");
    List<string> full_name;
    full_name = first_name + last_name;
    full_name = full_name - last_name;
    
    List<string> A_name("Arvin");
    List<string> L_name("KMS");
    List<string> F_name = A_name + L_name ;
    F_name -= L_name;
    F_name += L_name;
    char a_arr[] ={ 'a' , 'b' , 'c' , 'd' , 'e'};
    List<char> alpha(a_arr , 5);
//    List<char> post_alpha = alpha--;
    List<char> pre_alpha = --alpha;
    
    for(int i = 0 ; i < pre_alpha.getSize() ; i++)
    {
        cout << pre_alpha.getValue(i) << " ";
    }
    cout <<endl;
    cout << pre_alpha << endl;
    List <double> input_test;
    cout << "Enter some double values for the list." << endl;
    cin >> input_test ;
    cout << "The list you entered is: " << endl;
    for(int i = 0 ; i < input_test.getSize() ; i++)
    {
        cout << input_test.getValue(i)<< " ";
    }
    cout << endl;
    ///////************************************************SortedList_Test*******//////////////////////////////////////////////////////////
    
    int Sorted1[] = { 2 , 3 , 4 , 9 , 6};
    SortedList<int> S1(Sorted1, 5);
    SortedList<double> single_value(2);
    SortedList<int> single_occ_list(5 , 4);
    SortedList<int> copy_list(S1);
    copy_list.append(-45);
    copy_list.append(-45);
    
    cout << "testing the append function here :" ;
    for(int i = 0 ; i < copy_list.getSize() ; i++)
    {
        cout << copy_list[i] << " ";
    }
    cout << endl;
    
   
    SortedList<int>S3;
    S3 = copy_list;
//    S3.append(Sorted2, 4);
    copy_list.remove(-45, true);
    
    int show_search = copy_list.search(3);
    cout <<"testing search function" << show_search << endl;
    for(int i = 0 ; i< copy_list.getSize() ; i++)
    {
        cout << copy_list[i] <<  " ";
    }
    cout <<endl;
     
    double D1[] ={2.3 , 4.5 , 6.7 ,7.8};
    double D2[] = {4.5 , 7.8};
    SortedList<double> S4(D1, 4);
    SortedList<double> S5(D2 ,2);
    SortedList<double> S6;
      S4 - S5;
      S4 + S5;
    
    int Sorted2[] = { 3, 1 , 5 ,6};
    SortedList<int> S7(Sorted2, 4);
    int insert_arr[] ={ 2 , 4 ,5 };
    S7.append(insert_arr , 3);
    
    cout<< "Inserting an item for a sortedlist :";
     
    cout << endl;
    S7.insert(insert_arr , 3 , 0);
    cout<< "Inserting a list for a sortedlist :";
    for(int i = 0 ; i < S7.getSize() ;i++)
    {
        cout << S7[i] << " ";
    }
    cout << endl;
    
};
