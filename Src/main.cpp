#include <iostream>
#include "strbase.hpp"

using namespace std;

int main()
{
    char *c = (char*)calloc(sizeof(char), 1024);
    cin >> c;
    cout << translator::contains(c, 'a') << endl;
    return 0;
}
