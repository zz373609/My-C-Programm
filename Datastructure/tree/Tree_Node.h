#ifndef DWJ_TREE_NODE_H
#define DWJ_TREE_NODE_H
struct Tree_Node {
  std::string data;
  Tree_Node *left_child;
  Tree_Node *right_sibling;
};
#endif
