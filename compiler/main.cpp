#include <iostream>
#include <cstring>
#include "linked_list.h"
using namespace std;

int main()
{
    string choice ;
    string equ;
    while(choice != "2")
    {
        cout<<"1. to enter equation\n2. to Exit\nPlease enter your choice : ";
        cin>> choice  ;
        if(choice == "1")
        {
            cout << "Please enter your equation : ";
            cin >> equ;
            cout<<endl;
            Linked_Queue(equ);
        }
        else
        {
            if(choice == "2"){}
            else{cout<<"wrong choice\n";}
        }

    }
    return 0;
}
