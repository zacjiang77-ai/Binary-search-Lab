//  BST.cpp
//  Lab 5 Search Through A Database
//  Created by Zicheng Jiang
#include "BST.h"
#include "Employee.h"
BST::BST(string order_) {
  root = NULL;
  order = order_;
}
BST::~BST() {delete root;}
void BST::insert(Employee* newEmployee){
  if(root==NULL) 
  {
    root=newEmployee;
    return;
  }

  Employee*current = root;
  bool goleft;
  while(1){
    if(order=="name") goleft=newEmployee->getName()<current->getName();
    else if(order=="ID") goleft=newEmployee->getID()<current->getID();
    else if(order=="age") goleft=newEmployee->getAge()<=current->getAge();
    if(goleft){
    if(current->getLeft()==NULL)
    {
      current->setLeft(newEmployee);
      return;
    }
    current=current->getLeft();
  } 
    else{
    if(current->getRight()==NULL)
    {
      current->setRight(newEmployee);
      return;
    }
    current=current->getRight();
  }
  }
}

void printHelper(Employee* n) {
  if (n == nullptr) return;
  printHelper(n->getLeft());
  n->print();
  printHelper(n->getRight());
}
void BST::printInOrder(){
  printHelper(root);
  cout<<endl;
}

Employee* searchHelper(Employee*n,int ID)
{
  if(n==nullptr) return nullptr;
  if(ID==n->getID()) return n;
  if(ID<n->getID()) return searchHelper(n->getLeft(),ID);
  return searchHelper(n->getRight(),ID);
}
Employee* BST::searchID(int ID) { 
  return searchHelper(root,ID);
}  
void searchAgeRangeHelper(Employee* n, double lowAge, double highAge) {
    if (n == nullptr) return;
    double age = n->getAge();
    if (age >= lowAge) searchAgeRangeHelper(n->getLeft(), lowAge, highAge);
    if (age >= lowAge && age <= highAge) n->print();
    if (age < highAge) searchAgeRangeHelper(n->getRight(), lowAge, highAge); 
//if two employees have the same age, the new employee's age should be considered lower than the existing employee in the database. 
}
void BST::searchAgeRange(double lowAge, double highAge) {
    searchAgeRangeHelper(root, lowAge, highAge);
}
//You can safely assume no two employees will have the same name
void autocompleteHelper(Employee*n , string prefix){
    if (n == nullptr) return;
    autocompleteHelper(n->getLeft(), prefix);
    string name = n->getName();
    bool same= prefix.size()<=name.size();
    if(same){
    for(string::size_type i = 0; i < prefix.size(); i++) {
        if (name[i] != prefix[i]) {
            same = false;
            break;
        }
      }
    }
    if (same)  n->print();
    autocompleteHelper(n->getRight(), prefix);
}
void BST::autocomplete(string prefix){
  autocompleteHelper(root,prefix);
}
