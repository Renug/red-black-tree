#include "tree.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    tree* t=new tree();
    char buf[10]={'\0'};
    for (int index=0;index<20;++index)
    {
        sprintf(buf,"%d",index);
        std::string key(buf);
        t->setValueForKey(key,index);
    }
    
    for (int index=0;index<20;++index)
    {
        sprintf(buf,"%d",index);
        std::string key(buf);
//        std::cout<<t->valueForKey(key)<<std::endl;
        cout<<"remove "<<key<<endl;
        t->removeKey(key);
    }
    
    delete t;
    return 0;
}
