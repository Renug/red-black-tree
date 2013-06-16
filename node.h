#ifndef _RED_BLACK_NODE_H_
#define _RED_BLACK_NODE_H_
#include <string>

typedef enum
{
        red = 0,
        black = 1
}color;

class node
{
public:
        node();
        node(std::string key,int value);
        ~node();
        void setValue(int value);
        int value();
        void setKey(std::string key);
        std::string key();
        void setParentNode(node* parentNode);
        node* parentNode();
        void setLeftNode(node* leftNode);
        node* leftNode();
        void setRightNode(node* rightNode);
        node* rightNode();
        color nodeColor();
        void setNodeColor(color nodeColor);
private:
        int m_value;
        std::string m_key;
        node* m_leftNode;
        node* m_rightNode;
        node* m_parentNode;
        color m_color;
};

#endif
