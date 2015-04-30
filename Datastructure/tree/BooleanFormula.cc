//*******************************************************************
//
// File Name:	BooleanFormula
//
// Author:		Zhiqiang Zhang
//
// Email:		zz373609@ohio.edu
//
// Description:	To detemin the true or false of tree value
//
// Date: 		9/27/2013/my birthday
//
//*******************************************************************

//*******************************************************************
//Function:BooleanFormula(Tree_Node *r)
//Purpose: Inisilz the root
//Parameters: r
//calls: no
//**********************************************************************

//*******************************************************************
//Function:largest_input()
//Purpose: return the lagest value of this tree
//Parameters: no
//calls: call function of find_max(Tree_Node *root)
//**********************************************************************

//*******************************************************************
//Function:print(ostream &out)
//Purpose: out put the fuamlar
//Parameters: out
//calls: call function of print_out
//**********************************************************************

//*******************************************************************
//Function:~BooleanFormula()
//Purpose: delte the node
//Parameters: 
//calls: clla destry function
//**********************************************************************

//*******************************************************************
//Function:int height()
//Purpose: find the height of tree
//Parameters: 
//calls: max_height(Tree_Node* root)
//**********************************************************************

//*******************************************************************
//Function:bool evaluate(const vector<bool> &inputs)
//Purpose: evaluate the ture of false of famurlar
//Parameters:  inputs, but the parameter in cc is values it is confuse
//calls: get_evaluate
//**********************************************************************

//*******************************************************************
//Function:int operator_count(const string &op)
//Purpose: find the numbers of operator
//Parameters: op
//calls: find_operator
//**********************************************************************

//*******************************************************************
//Function:int find_operator(Tree_Node *root,const string &p)
//Purpose: help the operator_count to find the number of operator
//Parameters: root, p
//calls: no
//**********************************************************************

//*******************************************************************
//Function:void find_max(Tree_Node *root)
//Purpose: help to find the max value
//Parameters: root
//calls: no
//**********************************************************************

//*******************************************************************
//Function:void outs(ostream &in,Tree_Node* ptr1)
//Purpose: help to print out
//Parameters: root
//calls: no
//**********************************************************************

//*******************************************************************
//Function:int max_height(Tree_Node* root)
//Purpose: help to find the height
//Parameters: root
//calls: no
//**********************************************************************

//*******************************************************************
//Function: bool get_the_evalueat(Tree_Node *root, const vector<bool> &v)
//Purpose: help to evalueat the tree
//Parameters: root,v
//calls: no
//**********************************************************************

//*******************************************************************
//Function: void destroy(Tree_Node* root)
//Purpose: delete the root
//Parameters: root
//calls: no
//**********************************************************************

#include <iostream>
#include "Tree_Node.h"
#include <vector>
#include <cctype>
#include <sstream>
#include <cstring>
#include <cstdlib>
using namespace std;
class BooleanFormula {
  public:
  BooleanFormula(Tree_Node *r) {root=r;} // Constructor
  int largest_input(); // Find the largest input number
  void print(ostream &out); // Print out the formula  
  ~BooleanFormula();  // Destructor
  int height();        // Find the height of the tree
  bool evaluate(const vector<bool> &inputs); // Determine
                         // whether the formula evaluates to true
  int operator_count(const string &op); // Count # of operators in
                                           // formula
  bool satisfiable(); // Determines whether there is an
                         // input that makes this formula evaluate
                         // to true.  CS 561N only.	 
private:
  Tree_Node *root;
  int find_operator(Tree_Node *root,const string &p);
  void find_max(Tree_Node *root);
  vector<string> v;
  void outs(ostream &in,Tree_Node* ptr1);
  int max_height(Tree_Node* root);
  bool get_the_evalueat(struct Tree_Node *p, const string &item, const vector<bool> &values);
  void destroy(Tree_Node* root);
};

int BooleanFormula::find_operator(Tree_Node *root,const string &p){
	if(root==NULL)
		return 0;
	else{	
		if(root->data==p)
		return 1+find_operator(root->left_child,p)+find_operator(root->right_sibling,p);
		else
		return find_operator(root->left_child,p)+find_operator(root->right_sibling,p);
		}
}

int BooleanFormula::operator_count(const string &op) {
	return find_operator(root,op);
}

bool BooleanFormula::get_the_evalueat(struct Tree_Node *p, const string &item, const vector<bool> &values)
{
 int temp=0;
 if(p==NULL)
	return false;
 else if(p->left_child == NULL)
 {
    temp= atoi(p ->data.c_str());
	return values[temp];
  }
  else
  {
   int temp1=0, temp2=0;
   if(item == "MAJORITY")
   {
    for(struct Tree_Node *p1 = p->left_child; p1!=NULL;p1=p1->right_sibling)
	{
	 if(get_the_evalueat(p1,p1->data,values)==true)
	   temp1++;
	  else
	   temp2++;
	}
   }
  else if(item== "AND")
   return(get_the_evalueat(p->left_child, p->left_child->data,values) && get_the_evalueat(p->left_child->right_sibling, p->left_child->right_sibling->data,values));
  else if(item== "NOT")
   return(!get_the_evalueat(p->left_child, p->left_child->data,values));
  else if(item== "OR")
   return(get_the_evalueat(p->left_child, p->left_child->data,values) ||get_the_evalueat(p->left_child->right_sibling, p->left_child->right_sibling->data,values));
   
  if(temp1 > temp2)
	return true;
  else
	return false;
 }
}

bool BooleanFormula::evaluate(const vector<bool> &values){
  return get_the_evalueat(root, root->data,values);
}

int BooleanFormula::max_height(Tree_Node* root){
	int height_m = 0;
	if(root==NULL)
		return 0;
	else{
		if(root->left_child==NULL)
			return 0;
		Tree_Node* move;
		move = root->left_child;
		while(move!=NULL){
		int compare = max_height(move);
		if(compare>height_m)
			height_m = compare;
		move = move->right_sibling;
		}
}
return height_m+1;
}

int BooleanFormula::height() {
return max_height(root);
}
void BooleanFormula::destroy(Tree_Node* root){
	if(root!=NULL){
		destroy(root->left_child);
		destroy(root->right_sibling);
		delete root;
		root=NULL;
	}
}

BooleanFormula::~BooleanFormula() {
  destroy(root);
}
void BooleanFormula::outs(ostream &in,Tree_Node* root){
  if (root==NULL) {
    return;
  }
  if (root->left_child == NULL) {
    cout << root->data;
    return;
  }
  cout << "(";
  cout << root->data;
  cout << " ";
  for(Tree_Node *ptr1=root->left_child; ptr1!=NULL; ptr1=ptr1->right_sibling) {
    outs(in,ptr1);
    cout << " ";
  }
  cout << ")";
}

void BooleanFormula::print(ostream &out) {
return outs(out,root);
}

void BooleanFormula::find_max(Tree_Node *root){
string st1,st2,st3,st4;
st1="MAJORITY";
st2="AND";
st3="OR";
st4="NOT";
	if(root!=NULL){ 
		if((root->data!=st1)&&(root->data!=st2)&&(root->data!=st3)&&(root->data!=st4))
		v.push_back(root->data);
		find_max(root->left_child);
		find_max(root->right_sibling);
	}
else return;
	}

int BooleanFormula::largest_input() {
	int max=0;
	find_max(root);
	vector<int> t;
	for(size_t j =0;j<v.size();j++){
		t.push_back(atoi(v[j].c_str()));
		}
	for(size_t i=0;i<t.size();i++){
		if(t[i]>max)
		max=t[i];
	}
	return max;
}


bool BooleanFormula::satisfiable() {
  return false;
}

