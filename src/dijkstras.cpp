//dijkstras.cpp
#include "dijkstras.h"

void print_path(const vector<int> &v, int total)
{
    for(int i : v)
        cout<<i<<' ';
    cout<<endl<<"Total cost is "<<total<<endl;
}