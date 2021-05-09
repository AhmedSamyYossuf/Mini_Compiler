#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <iostream>
#include <graphics.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;


class linked_list
{
//---------------------------------structure for Node--------------------------------------------------//
    struct New_Node{
        int ID;
        string part;
        string result;
        New_Node *Next;
        New_Node *previous ;
    };
//-----------------------------------------------------------------------------------------------//
//----------------------------------prototype for add new Node  --------------------------------//
public :
    void Add_newNode(string part);
    void delete_all();
    void delete_Node();
    void delete_head();
    void show_linked();
    void delete_asterisk_Node(New_Node *);
//----------------------------------------------------------------------------------------------//
//-------------pointer for linked list in function [add new Node]----------------------------//
    New_Node *head ;            // re-fare to firs node in linked list(queue)
    New_Node *last ;            // to move between node in linked list to Search
    New_Node *Top = NULL;       // re-fare to firs close bracket
    New_Node *new1  ;           // to add new node in linked list
    New_Node *tail = NULL;      // re-fare to open bracket related close bracket
    New_Node *temp ;
    New_Node *before ;          //next of top in linked list
    New_Node *asterisk =NULL;
    New_Node *y , *z , *x;
    New_Node *last_open_bracets;
    char ListLength = 0;
    int Flag_Cbracket = 0;
    int Flag_Obracket = 0;
};

//---------------------------------------------------------------------------------//
/*-----------------------------------------------------------------------------------------//
                    to Add a new Node
//-------------------------------------------------------------------------------------------*/
void linked_list::Add_newNode(string part){
    if (ListLength == 0){
        head = new New_Node() ;
        head->ID=1;
        head->part=part;
        head->Next = NULL;
        head->previous = NULL;
        Top = head;
    }else{
        new1 = new New_Node();
        last = head;

        while (last->Next != NULL){
            //new1->previous = last->Next;
            last = last->Next;
        }
        if (last->Next == NULL){
            new1->previous = last;
        }
        new1->ID = (last->ID)+1;
        new1->part = part ;
        new1->Next = NULL;
        new1->previous = last;
        last->Next = new1;
        Top = new1;
    }
    ListLength++;
}
/*-----------------------------------------------------------------------------------------//
                    to delete all Node
//-------------------------------------------------------------------------------------------*/
void linked_list::delete_all(){
    if(head != NULL){
        last = head;
        while (head->Next != NULL){
            last = head->Next;
            delete head;
            head = last;
        }
        delete head;
        head = NULL ;
    }
}

/*-----------------------------------------------------------------------------------------//
                    to delete one Node from any place
//-------------------------------------------------------------------------------------------*/
void linked_list::delete_Node()
{
    if(before == NULL)
    {
        temp = Top->previous;
        delete Top;
        Top = temp ;
        Top->Next = NULL;
    }
    else
    {
        before->previous = Top->previous;
        delete Top;
        Top = before->previous;
        Top->Next  = before;
    }
}

/*-----------------------------------------------------------------------------------------------//
                    to delete node of asterisk and delete general if send address of node
//-----------------------------------------------------------------------------------------------*/
void linked_list::delete_asterisk_Node(New_Node *ttt)
{
    //  y    -->  x    -->  z
    // first    middle     last
    x = ttt;
    y = x->previous;
    z = x->Next;

    if(x->Next == NULL)
    {
        y = x->previous;
        delete x;
        y->Next = NULL;
    }
    else if(x->previous == NULL)
    {
        z = x->Next;
        head = x->Next;
        delete x;
        z->previous  = NULL;
    }
    else if(x->previous != NULL  && x->Next != NULL)
    {
        y = x->previous;
        z = x->Next;
        y->Next = z;
        z->previous = y ;
        delete x;
    }
    else if(x->previous == NULL  && x->Next == NULL)
    {
        delete x;
    }
}

/*-----------------------------------------------------------------------------------------//
                    to delete head Node
//-------------------------------------------------------------------------------------------*/
void linked_list::delete_head()
{
    if (head != NULL){
        temp = head->Next;
        delete head;
        head = temp;
    }else{
        delete head;
        head = NULL;
    }
}

/*-----------------------------------------------------------------------------------------//
                    to show Linked List
//-------------------------------------------------------------------------------------------*/
void linked_list::show_linked()
{
    last = head ;
    while(last != NULL)
    {
        cout<<last->part<<endl;
        if (last->Next != NULL)
        {
            last = last->Next;
        }else
        {
            last = NULL;
        }
    }
}

/*-----------------------------------------------------------------------------------------//
                    to confirm from (ab) to (S0(a)-->S1(ε)-->S2(b)-->S3)
//-------------------------------------------------------------------------------------------*/
void concatonate_line(string part , string *NFA  ,int *state)
{
    string character;
    int y = 0 ;
    while(part[(y)]!='\0')
    {
        std::stringstream ss;
        character = part[(y)] ;
        ss<<(*state) ;
        (*NFA).append("-->S");
        (*NFA)+=ss.str();
        (*NFA).append("(");
        (*NFA).append(character);
        (*NFA).append(")");

        (*state)++;
        (y)++;
        if(part[(y)]!='\0')
        {
           std::stringstream se;
            character = part[(y)] ;
            se<<(*state) ;
            (*NFA).append("-->S");
            (*NFA)+=se.str();
            (*NFA).append("(ε)");

            (*state)++;
        }
    }
    std::stringstream ss;
    ss<<(*state) ;
    (*NFA).append("-->S");
    (*NFA)+=ss.str();
}

void Linked_Queue(string equ)
{
    linked_list qu;
    string part , sub_part,oper , NFA , Final_Result = "";
    int  state = 0 , coun_ast = 1;

    int i = 0;
    while(equ[i] != '\0')
    {
        oper = equ[i];
        if (equ[i] == '(' || equ[i] == ')' || equ[i] == '/' || equ[i] == '|' || equ[i] == '*' )
        {
            if(part != "")
            {

                concatonate_line(part,&NFA  , &state);
                state++;
                qu.Add_newNode(NFA);
            }
            qu.Add_newNode(oper);
            part ="";

        }
        else
        {
            sub_part = equ[i];
            part.append(sub_part);
        }
        i++;
        NFA = "";

    }

    if(oper != ")" && part !="" )
    {

        concatonate_line(part,&NFA , &state);
        state++;
        qu.Add_newNode(NFA);
    }

    qu.show_linked();

    if (qu.ListLength > 1)
    {
        while(qu.Flag_Cbracket != 2)
        {

        /* ---------------To locate first close bracket ----------------------*/
            qu.last = qu.head ;

            while(qu.last != NULL)
            {
                if (qu.last->Next != NULL)
                {
                    if (qu.last->part == ")" && qu.Flag_Cbracket == 0)
                    {
                        qu.before = qu.last->Next;
                        qu.Top = qu.last ;
                        qu.Flag_Cbracket = 1;
                        qu.asterisk = qu.last->Next;
                        if(qu.asterisk->part != "*")
                        {
                            qu.asterisk = NULL;
                        }
                    }
                    else if (qu.Flag_Cbracket == 0)
                    {
                        qu.Top = NULL;
                    }
                    qu.last = qu.last->Next;
                }
                else
                {
                    if (qu.last->part == ")" && qu.Flag_Cbracket == 0)
                    {
                        qu.before = NULL;
                        qu.Top = qu.last ;
                        qu.Flag_Cbracket = 1;
                    }
                    qu.last = NULL;
                }
            }
        /*----------------------------------------------------------------------------*/

        /*---------------------------------to locate open bracket------------------------------------*/
            if(qu.Top != NULL)
            {
                qu.last = qu.Top ;
                while(qu.last != NULL)
                {
                    if(qu.last->previous != NULL)
                    {
                        if(qu.last->part == "(" && qu.Flag_Obracket == 0)
                        {
                            qu.tail = qu.last;
                            qu.Flag_Obracket = 1 ;
                            qu.last = NULL;
                        }
                        else if (qu.Flag_Obracket == 0)
                        {
                            qu.tail = NULL;
                            qu.last = qu.last->previous ;
                        }
                    }
                    else
                    {
                        if(qu.last->part == "(" && qu.Flag_Obracket == 0)
                        {
                            qu.tail = qu.last;
                            qu.Flag_Obracket = 1 ;
                        }
                        qu.last = NULL;
                    }
                }
            }
        /*------------------------------------------------------------------------------------------*/

        /*----------------------------------------------to calculate equation into bracket-----------------------*/

            while(qu.Top != NULL)
            {

                string part1 , part2 , result;
                if (qu.Top->part == ")")
                {
                    qu.delete_Node();

                }
                else
                {
                    part1 = qu.Top->part;
                    qu.delete_Node();
                    if(qu.Top->part != "(" )
                    {
                        if(qu.Top->part == "/" || qu.Top->part == "|")
                        {
                            qu.delete_Node();

                            part2 = qu.Top->part;
                            std::stringstream se;
                            se<< state ;
                            state++;
                            result = "-->S";
                            result+=se.str();
                            result.append("(ε) [ ( ");
                            result.append(part2);
                            result.append(") or ( ");
                            result.append(part1);
                            result.append(") ]-->(ε)-->S");
                            std::stringstream se2;
                            se2<<state;
                            state++;
                            result+=se2.str();
                            qu.Top->part=result;
                        }
                        else
                        {
                            part2 = qu.Top->part;
                            result = part2;
                            result.append("(ε)");
                            result.append(part1);
                            qu.Top->part=result;
                        }
                    }
                    else
                    {
                        //cout <<"test3"<<endl;
                        if (qu.asterisk != NULL)
                        {
                            string p1 , p2 ;
                            int a , b ,w;
                            std::stringstream se;
                            std::stringstream se1;
                            std::stringstream se2;
                            std::stringstream se3;
                            se<< state ;
                            state++;
                            se1<<state;
                            w = state ;
                            state++;
                            se2<< coun_ast;
                            a = coun_ast ;
                            coun_ast++;
                            se3<< coun_ast;
                            b = coun_ast ;
                            coun_ast++;
                            result = "-->S";
                            result+=se.str();
                            result.append("(ε)-->[ (");
                            result+=se2.str();
                            result.append(") or (");
                            result+=se3.str();
                            result.append(") ]  { and remember that : ");
                            cout<<"\n "<<a<<" is : "<<part1 <<"(ε)-->S"<<w<<endl;
                            cout<<"\n "<<b<<" is : S"<<w<<endl;
                            int z = 0 ;
                            while(part1[z]  != '\0')
                            {
                                if(part1[z] == 'S')
                                {
                                    string tem;
                                    p1 = part1[z];
                                    z++;
                                    tem = part1[z];
                                    p1.append(tem);
                                    break;
                                }
                                z++;
                            }
                            z = part1.length();

                            string tem;
                            z = z - 2;
                            p2 = part1[z];
                            z++;
                            tem = part1[z];
                            p2.append(tem);

                            result.append(p2);
                            result.append(" when get ε return to ");
                            result.append(p1);
                            result.append(" }");
                            part1 = result;
                            qu.delete_asterisk_Node(qu.asterisk);
                            qu.asterisk = NULL;
                        }

                        qu.Top->part = part1;

                        if(qu.Top->previous != NULL)
                        {
                            qu.last_open_bracets = qu.Top->previous;
                            if(qu.last_open_bracets->part != "/" && qu.last_open_bracets->part != "(")
                            {
                                part2 = qu.last_open_bracets->part;
                                result = part2 ;
                                result.append("(ε) ");
                                result.append(part1);
                                part1=result;
                                qu.delete_asterisk_Node(qu.last_open_bracets);
                                qu.Top->part = part1;
                            }
                            qu.last_open_bracets = NULL ;
                        }


                    }


                }
                if (qu.Top == qu.tail)
                {

                    qu.tail = NULL;
                    qu.Top = NULL;
                }
            }
            if (qu.Flag_Cbracket == 1 || qu.Flag_Obracket == 1)
            {
                qu.Flag_Obracket = 0 ;
                qu.Flag_Cbracket = 0 ;
            }
            else if (qu.Flag_Cbracket == 0 || qu.Flag_Obracket == 0)
            {
                qu.Flag_Obracket = 2 ;
                qu.Flag_Cbracket = 2 ;
            }
        }
    }

    /*---------------------------------------------------------------------------------------------*/

    /*-----------------------------------to final result-------------------------------------------*/
    if(qu.head->Next != NULL)
    {
         while(qu.head != NULL)
        {

                string part1 , part2 , result;

                part1 = qu.head->part;
                qu.delete_head();

                if(qu.head->part == "/" || qu.head->part == "|")
                {
                   qu.delete_head();
                }
                else if (qu.head->part == "--")
                {
                    while(qu.head->part != "/" || qu.head->part != "|"  )
                    {
                        part2 = qu.head->part;
                        result = part1 ;
                        result.append("(ε) ");
                        result.append(part2);
                        part1=result;
                        qu.delete_head();
                    }
                }

                if(qu.head->part != "(" )
                {

                    part2 = qu.head->part;
                    std::stringstream se;
                    se<< state ;
                    state++;
                    result = "-->S";
                    result+=se.str();
                    result.append("(ε) [ ( ");
                    result.append(part1);
                    result.append(") or ( ");
                    result.append(part2);
                    result.append(") ]-->(ε)-->S");
                    std::stringstream se2;
                    se2<<state;
                    state++;
                    result+=se2.str();
                    qu.head->part=result;
                    if(qu.head->Next == NULL)
                    {
                        Final_Result = qu.head->part;
                        qu.head = NULL;
                    }
                }
                else
                {

                    qu.head->part = part1;
                }

        }
    }
    else
    {
        Final_Result = qu.head->part;
        qu.head = NULL;
    }



    /*---------------------------------------------------------------------------------------------*/

    cout<<"-----------------------------------------------------------------------------------------------\n"<<endl;
    cout<<"-------------------------------------------------Final Result----------------------------------\n"<<endl;
    cout<<Final_Result<<"\n\n\n"<<endl;

    qu.delete_all();

}




#endif // LINKED_LIST_H_INCLUDED
