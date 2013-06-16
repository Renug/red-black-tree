#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
#include <string>

class node;
class tree
{
public:
        tree();
        ~tree();
        int valueForKey(std::string key);
        void setValueForKey(std::string key,int value);
        void removeKey(std::string key);
private:
        node* m_root;
        node* m_nil;
private:
        node* treeMinimum(node* n);
        node* treeSuccessor(node* n);
        void leftRotate(node* n);
        void rightRotate(node* n);
        void insert(node* n);
        void insertFixUp(node* n);
        void remove(node* n);
        void removeFixUp(node* n);
        node* findNode(std::string key);
        void deleteTree(node* t);
};

#endif
