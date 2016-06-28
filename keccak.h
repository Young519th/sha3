//
//  Keccak.h
//  SHA_3
//
//  Created by Young on 6/27/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#ifndef Keccak_h
#define Keccak_h

#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Keccak{
private:
    string keccak(string, int);
    string sponge(int, string, int);
    int pad101(int, int);
    unsigned char* f(unsigned char*, int);
    string trunc(unsigned char*, int);
    bool*** Rnd(bool***, int, int);
    bool*** step1(bool***, int);
    bool*** step2(bool***, int);
    bool*** step3(bool***, int);
    bool*** step4(bool***, int);
    bool*** step5(bool***, int, int);
    bool rc(int);
public:
    Keccak()
    {
    }
    ~Keccak()
    {
    }
    string sha3_224(string);
    string sha3_256(string);
    string sha3_384(string);
    string sha3_512(string);
};


#endif /* Keccak_h */
