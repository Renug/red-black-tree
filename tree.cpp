#include "node.h"
#include "tree.h"
#include <assert.h>
#include <stack>

tree::tree()
{
    m_nil=new node();
    m_nil->setNodeColor(black);
    m_root=m_nil;
}

tree::~tree()
{
    if (m_nil!=m_root)
        deleteTree(m_root);
    delete m_nil;
}

node* tree::treeMinimum(node* n)
{
    node* no=n;
    while(no->leftNode()!=m_nil)
    {
        no=no->leftNode();
    }
    return no;
}

node* tree::treeSuccessor(node* n)
{
    node* retval=m_nil;
    if(n->rightNode()!=m_nil)
    {
        retval=treeMinimum(n->rightNode());
    }
    else
    {
        node* y=n->parentNode();
        node* x=n;
        while(y!=m_nil&&x==y->rightNode())
        {
            x=y;
            y=y->parentNode();
        }
        retval=x;
    }
    return retval;
}

int tree::valueForKey(std::string key)
{
    node* retval=findNode(key);
    assert(retval); 
    return retval->value();
}

void tree::setValueForKey(std::string key,int value)
{
    node* retval=findNode(key);
    if (retval)
    {
        assert(NULL);   
        retval->setValue(value);
    }
    else
    {   
        node* newNode=new node(key,value);
        newNode->setParentNode(m_nil);
        newNode->setLeftNode(m_nil);
        newNode->setRightNode(m_nil);
        insert(newNode);
    }
}


void tree::leftRotate(node* x)
{
    node* y=x->rightNode();
    x->setRightNode(y->leftNode());
    if (m_nil!=y->leftNode())
    {
        y->leftNode()->setParentNode(x);
    }
    y->setParentNode(x->parentNode());
    if (x->parentNode()==m_nil)
    {
        m_root=y;
    }
    else if (x==x->parentNode()->leftNode())
    {
        x->parentNode()->setLeftNode(y);
    }
    else
    {
        x->parentNode()->setRightNode(y);
    }
    y->setLeftNode(x);
    x->setParentNode(y);
}

void tree::rightRotate(node* y)
{
    node* x=y->leftNode();
    y->setLeftNode(x->rightNode());
    if (x->rightNode()!=m_nil)
    {
        x->rightNode()->setParentNode(y);
    }
    x->setParentNode(y->parentNode());
    if (m_nil==y->parentNode())
    {
        m_root=x;
    }
    else if (y == y->parentNode()->leftNode())
    {
        y->parentNode()->setLeftNode(x);
    }
    else
    {
        y->parentNode()->setRightNode(x);
    }
    x->setRightNode(y);
    y->setParentNode(x);
}

void tree::insert(node* z)
{
    node* y=m_nil;
    node* x=m_root;
    while(m_nil!=x)
    {
        y=x;
        if (z->key()<x->key())
            x=x->leftNode();
        else
            x=x->rightNode();
    }   
    z->setParentNode(y);
    if (m_nil==y)
    {
        m_root=z;
    }
    else if (z->key()<y->key())
    {
        y->setLeftNode(z);
    }
    else
    {
        y->setRightNode(z);
    }
    z->setLeftNode(m_nil);
    z->setRightNode(m_nil);
    z->setNodeColor(red);
    insertFixUp(z);
}

void tree::insertFixUp(node* n)
{
    node* z=n;
    while(red==z->parentNode()->nodeColor())
    {
        if (z->parentNode()==z->parentNode()->parentNode()->leftNode())
        {
            node* y=z->parentNode()->parentNode()->rightNode();
            if (red==y->nodeColor())
            {
                z->parentNode()->setNodeColor(black);
                y->setNodeColor(black);
                z->parentNode()->parentNode()->setNodeColor(red);
                z=z->parentNode()->parentNode();
            }
            else
            {   
                if (z->parentNode()->rightNode()==z)
                {
                    z=z->parentNode();
                    leftRotate(z);
                }
                z->parentNode()->setNodeColor(black);
                z->parentNode()->parentNode()->setNodeColor(red);
                rightRotate(z->parentNode()->parentNode());
            }
        }
        else if (z->parentNode()==z->parentNode()->parentNode()->rightNode())
        {
            node* y=z->parentNode()->parentNode()->leftNode();
            if (red==y->nodeColor())
            {
                z->parentNode()->setNodeColor(black);
                y->setNodeColor(black);
                z->parentNode()->parentNode()->setNodeColor(red);
                z=z->parentNode()->parentNode();
            }
            else
            {   
                if (z==z->parentNode()->leftNode())
                {
                    z=z->parentNode();
                    rightRotate(z);
                }
                z->parentNode()->setNodeColor(black);
                z->parentNode()->parentNode()->setNodeColor(red);
                leftRotate(z->parentNode()->parentNode());
            }
        }
        else
        {
            assert(false);
        }
    }
    m_root->setNodeColor(black);
}

void tree::remove(node* z)
{
    node* y=(z->leftNode()==m_nil||z->rightNode()==m_nil)?z:treeSuccessor(z);
    node* x=m_nil!=y->leftNode()?y->leftNode():y->rightNode();
    x->setParentNode(y->parentNode());
    if (y->parentNode()==m_nil)
    {
        m_root=x;
    }
    else if (y->parentNode()->leftNode()==y)
    {
        y->parentNode()->setLeftNode(x);
    }
    else
    {
        y->parentNode()->setRightNode(x);
    }
    
    if (y!=z)
    {
        z->setValue(y->value());
        z->setKey(y->key());
    }
    
    if (y->nodeColor()==black)
    {
        removeFixUp(x);
    }
    delete y;
}

void tree::removeFixUp(node* x)
{
    while (black==x->nodeColor()&&m_root!=x)
    {
        if(x->parentNode()->leftNode()==x)
        {
            node* w=x->parentNode()->rightNode();
            if (red==w->nodeColor())
            {
                w->setNodeColor(black);
                x->parentNode()->setNodeColor(red);
                leftRotate(x->parentNode());
                w=x->parentNode()->rightNode();
            }
            if (w->rightNode()->nodeColor()==black&&w->leftNode()->nodeColor()==black)
            {
                w->setNodeColor(red);
                x=x->parentNode();
            }
            else
            {
                if (black==w->rightNode()->nodeColor())
                {
                    w->leftNode()->setNodeColor(black);
                    w->setNodeColor(red);
                    rightRotate(w);
                    w=x->parentNode()->rightNode();
                }
                w->setNodeColor(x->parentNode()->nodeColor());
                x->parentNode()->setNodeColor(black);
                w->rightNode()->setNodeColor(black);
                leftRotate(x->parentNode());
                x=m_root;
            }
        }
        else if (x->parentNode()->rightNode()==x)
        {
            node* w=x->parentNode()->leftNode();
            if (red==w->nodeColor())
            {
                w->setNodeColor(black);
                x->parentNode()->setNodeColor(red);
                rightRotate(x->parentNode());
                w=x->parentNode()->leftNode();
            }
            if (w->rightNode()->nodeColor()==black&&w->leftNode()->nodeColor()==black)
            {
                w->setNodeColor(red);
                x=x->parentNode();
            }
            else
            {
                if (black==w->leftNode()->nodeColor())
                {
                    w->rightNode()->setNodeColor(black);
                    w->setNodeColor(red);
                    leftRotate(w);
                    w=x->parentNode()->leftNode();
                }
                w->setNodeColor(x->parentNode()->nodeColor());
                x->parentNode()->setNodeColor(black);
                w->leftNode()->setNodeColor(black);
                rightRotate(x->parentNode());
                x=m_root;
            }
        }
    }
    x->setNodeColor(black);
}

void tree::deleteTree(node* t)
{
    if (t->leftNode()!=m_nil)
    {
        deleteTree(t->leftNode());
    }
    if (t->rightNode()!=m_nil)
    {
        deleteTree(t->rightNode());
    }
    
    if (t==t->parentNode()->leftNode())
    {
        t->parentNode()->setLeftNode(m_nil);
    }
    else
    {
        t->parentNode()->setRightNode(m_nil);
    }
    delete t;
}

node* tree::findNode(std::string key)
{
    std::stack<node*> stack;
    node* current=m_root;
    while(NULL!=current||stack.size()!=0)
    {
        while(NULL!=current)
        {
            stack.push(current);
            current=current->leftNode();
        }
        if (stack.size()!=0)
        {
            current=stack.top();
            stack.pop();
            if(current->key()==key)
            {
                return current;
            }
            current=current->rightNode();
        }
    }
    return NULL;
}

void tree::removeKey(std::string key)
{
    node* n=findNode(key);
    if (m_nil!=n)
    {
        remove(n);
    }
}
