#include <iostream>
#include "translator.hpp"
#include <fstream>

#define contains(a) find(a) != string::npos

using namespace std;

string split (string s, char a, char b)
{
    string ret = s.substr(s.find(a) + 1);
    ret = ret.substr(0, ret.find(b));
    return ret;
}

size_t includesCount(string s, char c)
{
    size_t a = 0;
    for(size_t i = 0; i < s.length(); i++)
    {
        if(s[i] == c)
            a++;
    }
    return a;
}

void foo0()
{
    cout << "foo0\n";
}

void foo1()
{
    cout << "foo1\n";
}

void foo2()
{
    cout << "foo2\n";
}


int main(int argc, char **argv) 
{
    // ifstream myfile ("a");
    FILE *fp;
    fp = fopen("a", "r");

    void (*funcArr [3])();
    funcArr[0] = foo0;
    funcArr[1] = foo1;
    funcArr[2] = foo2;
    uint8_t tgt[64];
    for(int i = 0; i < 64; i++)
        tgt[i] = 0;
    translator::generateCmd(1, tgt);
    // cout << tgt << endl;
    for(int i = 0; i < 64; i++)
    {
        // cout << ((int)tgt[i]) << ' ';
        putchar(tgt[i]);
    }
    cout << endl << translator::validate(tgt) << endl;
    size_t strsize = 64;
    uint8_t* strbuf = (uint8_t*)malloc(strsize);
    for(int a = 0; a < strsize; a++)
        strbuf[a] = 0;
    size_t i = 0;
    // for(int i = 0; i < 64; i++)
    //     strbuf[i] = tgt[i];
    while(!translator::validate(strbuf))
    {
        if(i >= strsize)
        {
            strsize += 64;
            strbuf = (uint8_t*)realloc(strbuf, strsize);
            for(int a = i; a < strsize; a++)
                strbuf[a] = 0;
        }
        strbuf[i] = getchar();
        cout << "GOT " << (int)strbuf[i] << " ";
        // strbuf[i] = fgetc(myfile);
        i++;
    }

    cout << endl;


    for(int i = 0; i < strsize; i++)
        // putchar(tgt[i]);
        cout << (int)tgt[i] << ' ';

    cout << endl;

    translator::parseCmd(strbuf, funcArr);
    cout << "i: " << translator::parseCmd(strbuf) << endl;
    
    
    cout << "SUCC" << endl;
    return 0;
}
