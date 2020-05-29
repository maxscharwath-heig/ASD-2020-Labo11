//
// Created by Olivier Cuisenaire on 23.05.20.
//

#include <iostream>
#include "bst.h"

using namespace std;

int main() {

    bst<int> t{};

    for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
        t.insert(i);

    cout << t << endl;
}