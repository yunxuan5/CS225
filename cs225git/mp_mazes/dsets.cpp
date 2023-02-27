/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements(int num)	{
    for(int i = 0; i < num; i ++){
        elements.push_back(-1);
    }
}


int DisjointSets::find(int elem){
    if (elements[elem] < 0){
        return elem;
    }
    else{
        return find(elements[elem]);
    }
}


void DisjointSets::setunion(int a, int b){
    int roota = find(a);
    int rootb = find(b);
    int newSize = elements[roota] + elements[rootb];
    if(elements[roota] <= elements[rootb]){
        elements[rootb] = roota;
        elements[roota] = newSize;
    }
    else{
        elements[roota] = rootb;
        elements[rootb] = newSize;
    }
}

int DisjointSets::size(int elem){
    while(elements[elem] >= 0){
        elem = elements[elem];
    }
    return elements[elem] * -1;
}