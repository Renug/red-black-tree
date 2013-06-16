#include "node.h"

node::node()
    :m_value(0),
     m_leftNode(NULL),
     m_rightNode(NULL),
     m_parentNode(NULL),
     m_color(red)
{
}

node::node(std::string key,int value)
    :m_value(value),
     m_key(key),
     m_leftNode(NULL),
     m_rightNode(NULL),
     m_parentNode(NULL),
     m_color(red)
{
}

node::~node()
{
}

void node::setValue(int value)
{
    m_value=value;
}

void node::setKey(std::string key)
{
    m_key=key;
}

void node::setParentNode(node* parentNode)
{
    m_parentNode=parentNode;
}

void node::setLeftNode(node* leftNode)
{
    m_leftNode=leftNode;
}

void node::setRightNode(node* rightNode)
{
    m_rightNode=rightNode;
}

node* node::parentNode()
{
    return m_parentNode;
}

node* node::leftNode()
{
    return m_leftNode;
}

node* node::rightNode()
{
    return m_rightNode;
}

int node::value()
{
    return m_value;
}

std::string node::key()
{
    return m_key;
}

color node::nodeColor()
{
    return m_color;
}

void node::setNodeColor(color nodeColor)
{
    m_color=nodeColor;
}
