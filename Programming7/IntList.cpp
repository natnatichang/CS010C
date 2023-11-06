#include <iostream>
#include "IntList.h"

using namespace std;

IntList::IntList() 
    : head(nullptr),
      tail(nullptr) 
{
}


IntList::~IntList(){

    for(IntNode*p = head; p != nullptr;){
        IntNode* nextOne = p->next;
        delete p;
        p = nextOne;     
    }
}

bool IntList::empty() const{
    return (head == nullptr);
}


void IntList::push_front(int value){

    IntNode * n = new IntNode(value); 
  
    n->next = head; 
    head = n; 
    
    if(tail == nullptr){ 
        tail = n; 
    }
}


void IntList::pop_front(){

    if(empty()) return;

    IntNode* victim = head; 
    head = head->next;
    delete victim; 

    if(empty()){
        tail = nullptr; 
    }
}


const int& IntList::front() const{
    return head->value;
}


const int& IntList::back() const{
    return tail->value;
}


ostream & operator<<(ostream &out, const IntList &rhs){

    IntNode *victim = rhs.head;

    if(victim != nullptr){
        out << victim->value;
        victim = victim->next;
    }

    while(victim != nullptr){
        out << " " << victim->value;
        victim = victim->next;
    }

    return out;
}


IntList::IntList(const IntList &cpy){

    if(cpy.head == nullptr){
        head = nullptr;
        return;
    } 
    
    head = new IntNode(cpy.head->value);
    IntNode* curr = head;
    IntNode* cpyCurr = cpy.head->next; 

    while(cpyCurr != nullptr){
        curr->next = new IntNode(cpyCurr->value);
        curr = curr->next;
        cpyCurr = cpyCurr->next;
    }
}


IntList & IntList::operator=(const IntList &rhs){

    if(this != &rhs){
        clear(); 
    }

    if(rhs.head == nullptr){
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = new IntNode(rhs.head->value);
        IntNode* curr = head; 
        IntNode* currRhs = rhs.head->next; 

        while(currRhs != nullptr){
            curr->next = new IntNode(currRhs->value);
            curr = curr->next;
            currRhs = currRhs->next;
        }
        tail = curr; 
    }
    return *this; 
}
	

void IntList::push_back(int value){

    IntNode* newNode = new IntNode(value);

    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode; 
    }
}
	

void IntList::clear(){

    IntNode* curr = head;
    while(curr != nullptr){
        IntNode* victim = curr; 
        victim = victim->next;
        delete victim;
    }

    head = nullptr;
    tail = nullptr;
}
	

void IntList::selection_sort(){
    if(head == nullptr || head->next == nullptr){
        return;
    }
    else {

        IntNode* minNode = nullptr;
        int temp = 0;

        for(IntNode* i = head; i->next != nullptr; i = i->next){
            minNode = i;

            for(IntNode* j = i->next; j != nullptr; j = j->next){
                if(minNode->value > j->value){
                    minNode = j;
                }
            }
            temp = i->value;
            i->value = minNode->value;
            minNode->value = temp; 
        }

    }
}


void IntList::insert_ordered(int value){

    IntNode* newNode = new IntNode(value);

    if(head == nullptr){
        head = newNode;
        tail = newNode; 
        return;
    }
    
    if(value < head->value){
        newNode->next = head;
        head = newNode;
        return;
    }

    if(value > tail->value){
        tail->next = newNode;
        tail = newNode; 
        return; 
    }

    IntNode* prev = head; 
    IntNode* curr = head->next; 

    while(curr != nullptr && curr->value < value){
        prev = curr;
        curr = curr->next;
    }
    
    newNode->next = curr;
    prev->next = newNode; 
}


void IntList::remove_duplicates(){

    IntNode* curr = nullptr;
    IntNode* prev = nullptr;
    
    for(curr = head; curr != nullptr; curr = curr->next){
        prev = curr;
        
        for(IntNode* checker = curr->next; checker != nullptr;){
            if(checker->value == curr->value){
                prev->next = checker->next; 
                delete checker;
                checker = prev->next;
            }
            else {
                prev = checker;
                checker = checker->next;
            }
        }
    }
}
