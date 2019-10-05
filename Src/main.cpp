#include <iostream>
#include "translator.hpp"

using namespace std;

int main()
{
    uint8_t *c = (uint8_t*)calloc(sizeof(uint8_t), 1024);
    cin >> c;
    // cout << translator::contains(c, 'a') << endl;
    return 0;
}
