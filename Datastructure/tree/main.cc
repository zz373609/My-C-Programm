#include <iostream>

#include "Scanner.h"
#include "Tree_Node.h"
#include "BooleanFormula.cc"

using namespace std;



Tree_Node *get_next(istream &in, Scanner &obj) {
  int c;
  string token;
  c=obj.current_token(in,token);
  if (c==1) {
    // MAJORITY, AND, OR, NOT, INTEGER;
    // Base Case
    obj.get_next(in);
    Tree_Node *ptr;
    ptr = new Tree_Node;
    ptr->data = token;
    ptr->left_child = NULL;
    ptr->right_sibling = NULL;
    return ptr;
  } else { // Already got c
    if ((char)c == '(') {
      //cout << "Build Formula" << endl;
      obj.get_next(in);
      c=obj.current_token(in,token); 
      // Assert that c == 1
      Tree_Node *ptr;
      ptr = new Tree_Node;
      ptr->data = token;
      ptr->right_sibling = NULL;
      ptr->left_child = NULL;
      obj.get_next(in);
      c=obj.current_token(in,token);
      Tree_Node *ptr1;
      while (c!= ')') {
	Tree_Node *ptr2;
	ptr2 = get_next(in,obj);
	if (ptr->left_child ==NULL) {
	  ptr->left_child = ptr2;
	  ptr1=ptr2;
	} else {
	  ptr1->right_sibling = ptr2;
	  ptr1 = ptr2;
	}
	c=obj.current_token(in,token);
      }
      obj.get_next(in);
      return ptr;
    } else {
      //   cout << c << endl;
      return NULL;
    }
  }
}

void print(Tree_Node *ptr) {
  
  if (ptr==NULL) {
    return;
  }
  if (ptr->left_child == NULL) {
    cout << ptr->data;
    return;
  }
  cout << "(";
  cout << ptr->data;
  cout << " ";
  for (Tree_Node *ptr1=ptr->left_child;
       ptr1!=NULL;
       ptr1=ptr1->right_sibling) {
    print(ptr1);
    cout << " ";
  }
  cout << ")";
}

int main() {
  Scanner obj;
  obj.get_next(cin);  // Start reading
  Tree_Node *ptr;
  
  /* while (c=obj.current_token(cin,next_t)) {
    cout << c << " = " << next_t << endl;
    obj.get_next(cin);
  }

  exit(-1); */


  ptr = get_next(cin,obj);
  BooleanFormula b(ptr);
  b.print(cout);
  cout << endl;

  int l = b.largest_input();
  cout << "Largest Input # = " << l << endl;
  cout << "Height = " << b.height() << endl;
  cout << "Number of MAJORITY GATES " << b.operator_count("MAJORITY") << endl;
  cout << "Number of AND GATES " << b.operator_count("AND") << endl;
  cout << "Number of OR GATES " << b.operator_count("OR") << endl;
  cout << "Number of NOT GATES " << b.operator_count("NOT") << endl;

  cout.setf(ios::boolalpha);

  vector<bool> values;
  values.resize(l+1);
  for (int i=0;i<l+1;i++) {
    values[i] = true;
  }
  cout << "On all trues, this evaluates to " << b.evaluate(values) << endl;
  for (int i=0;i<l+1;i++) {
    values[i] = false;
  }
  cout << "On all falses, this evaluates to " << b.evaluate(values) << endl;
  for (int i=0;i<l+1;i++) {
    if (i%2==0) {
      values[i] = false;
    } else {
      values[i]=true;
    }
  }
  cout << "When only the odd values are true, this evaluates to " << b.evaluate(values) << endl;


  cout << endl;

}
