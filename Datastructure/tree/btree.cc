#include<iostream>
#include"btree.h"
#include<stack>
using namespace std;
btree::btree(){
	root = NULL;
}


btree::~btree(){
	destroy_tree(root);
}


void btree::destroy_tree(node* root){
	if(root==NULL)
		return;
	else{
		destroy_tree(root->left);
		destroy_tree(root->right);
		delete root;
		}
}


void btree::insert(node* p,int key){
	if(root==NULL){
		root = new node(key);
	}
	else if(k<root->key)
		insert(root->left,key);
	else
		insert(root->right,key);
	}
	
void printout1(node* p){
		if(root==NULL)
		return;
		else{
		cout<<root->key<<"  ";
		printout1(root->left);
		printout1(root->right);
		}
	
	}
	//void printout2(node* p);

