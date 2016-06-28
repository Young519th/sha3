//
//  keccak.cpp
//  sha3
//
//  Created by Young on 6/27/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#include "keccak.h"

void print(bool *** A, int w)
{
    //print the state for test
    cout << "###" << endl;
    for (int y = 0 ; y < 5 ; y ++)
        for (int x = 0 ; x < 5 ; x ++)
        {
            for (int z = 0 ; z < w ; z ++)
                cout << (int)A[x][y][z] << " ";
            cout << endl;
        }
    cout << "!!!" << endl;
}

bool*** Keccak::step1(bool *** A, int w)
{
    bool*** R = new bool**[5];
    for (int i = 0 ; i < 5 ; i ++)
    {
        R[i] = new bool* [5];
        for (int j = 0 ; j < 5 ; j ++)
        {
            R[i][j] = new bool[w];
            for (int k = 0 ; k < w ; k ++)
                R[i][j][k] = false;
        }
    }
    bool C[5][w];
    for (int x = 0 ; x < 5 ; x ++)
        for (int z = 0 ; z < w ; z ++)
            C[x][z] = ((((A[x][0][z] != A[x][1][z]) != A[x][2][z]) != A[x][3][z]) != A[x][4][z]);
    bool D[5][w];
    for (int x = 0 ; x < 5 ; x ++)
        for (int z = 0 ; z < w ; z ++)
            D[x][z] = (C[(x + 4) % 5][z] != C[(x + 1) % 5][(z + w - 1) % w]);
    for (int x = 0 ; x < 5 ; x ++)
        for (int y = 0 ; y < 5 ; y ++)
            for (int z = 0 ; z < w ; z ++)
                R[x][y][z] = (A[x][y][z] != D[x][z]);
    for (int i = 0 ; i < 5 ; i ++)
    {
        for (int j = 0 ; j < 5 ; j ++)
            delete[] A[i][j];
        delete[] A[i];
    }
    delete[] A;
    return R;
}

bool*** Keccak::step2(bool *** A, int w)
{
    bool*** R = new bool**[5];
    for (int i = 0 ; i < 5 ; i ++)
    {
        R[i] = new bool* [5];
        for (int j = 0 ; j < 5 ; j ++)
        {
            R[i][j] = new bool[w];
            for (int k = 0 ; k < w ; k ++)
                R[i][j][k] = false;
        }
    }
    for (int z = 0 ; z < w ; z ++)
        R[0][0][z] = A[0][0][z];
    int x = 1;
    int y = 0;
    for (int t = 0 ; t < 24 ; t ++)
    {
        for (int z = 0 ; z < w ; z ++)
        {
            R[x][y][z] = A[x][y][((z - (t + 1) * (t + 2) / 2 + w * w) % w)];
        }
        int newx = y;
        int newy = (2 * x + 3 * y) % 5;
        x = newx;
        y = newy;
    }
    for (int i = 0 ; i < 5 ; i ++)
    {
        for (int j = 0 ; j < 5 ; j ++)
            delete[] A[i][j];
        delete[] A[i];
    }
    delete[] A;
    return R;
}

bool*** Keccak::step3(bool *** A, int w)
{
    bool*** R = new bool**[5];
    for (int i = 0 ; i < 5 ; i ++)
    {
        R[i] = new bool* [5];
        for (int j = 0 ; j < 5 ; j ++)
        {
            R[i][j] = new bool[w];
            for (int k = 0 ; k < w ; k ++)
                R[i][j][k] = false;
        }
    }
    for (int x = 0 ; x < 5 ; x ++)
        for (int y = 0 ; y < 5 ; y ++)
            for (int z = 0 ; z < w ; z ++)
                R[x][y][z] = A[(x + 3 * y) % 5][x][z];
    for (int i = 0 ; i < 5 ; i ++)
    {
        for (int j = 0 ; j < 5 ; j ++)
            delete[] A[i][j];
        delete[] A[i];
    }
    delete[] A;
    return R;
}

bool*** Keccak::step4(bool *** A, int w)
{
    bool*** R = new bool**[5];
    for (int i = 0 ; i < 5 ; i ++)
    {
        R[i] = new bool* [5];
        for (int j = 0 ; j < 5 ; j ++)
        {
            R[i][j] = new bool[w];
            for (int k = 0 ; k < w ; k ++)
                R[i][j][k] = false;
        }
    }
    for (int x = 0 ; x < 5 ; x ++)
        for (int y = 0 ; y < 5 ; y ++)
            for (int z = 0 ; z < w ; z ++)
                R[x][y][z] = (A[x][y][z] != ((A[(x + 1) % 5][y][z] != 1) && A[(x + 2) % 5][y][z]));
    for (int i = 0 ; i < 5 ; i ++)
    {
        for (int j = 0 ; j < 5 ; j ++)
            delete[] A[i][j];
        delete[] A[i];
    }
    delete[] A;
    return R;
}

bool*** Keccak::step5(bool *** A, int i, int w)
{
    bool*** R = new bool**[5];
    for (int i = 0 ; i < 5 ; i ++)
    {
        R[i] = new bool* [5];
        for (int j = 0 ; j < 5 ; j ++)
        {
            R[i][j] = new bool[w];
            for (int k = 0 ; k < w ; k ++)
                R[i][j][k] = false;
        }
    }
    for (int x = 0 ; x < 5 ; x ++)
        for (int y = 0 ; y < 5 ; y ++)
            for (int z = 0 ; z < w ; z ++)
                R[x][y][z] = A[x][y][z];
    bool* RC = new bool[w];
    for (int i = 0 ; i < w ; i ++)
        RC[i] = false;
    for (int j = 0 ; j <= log2(w); j ++)
    {
        RC[(int)pow(2, j) - 1] = rc(j + 7 * i);
    }
    for (int z = 0 ; z < w ; z ++)
    {
        R[0][0][z] = (R[0][0][z] != RC[z]);
    }
    for (int i = 0 ; i < 5 ; i ++)
    {
        for (int j = 0 ; j < 5 ; j ++)
            delete[] A[i][j];
        delete[] A[i];
    }
    delete[] A;
    delete[] RC;
    return R;
}

bool Keccak::rc(int t)
{
    //used in step 5
    if (t % 255 == 0)
        return true;
    bool R[9];
    for (int i = 0 ; i < 9 ; i ++)
    {
        R[i] = false;
    }
    R[1] = true;
    for (int i = 1 ; i <= (t % 255) ; i ++)
    {
        R[0] = (R[0] != R[8]);
        R[4] = (R[4] != R[8]);
        R[5] = (R[5] != R[8]);
        R[6] = (R[6] != R[8]);
        for (int j = 8 ; j > 0 ; j --)
        {
            R[j] = R[j - 1];
        }
        R[0] = false;
    }
    return R[1];
}

bool*** Keccak::Rnd(bool *** A, int i, int w)
{
    //the round function
    return step5(step4(step3(step2(step1(A, w), w), w), w), i, w);
}

unsigned char* Keccak::f(unsigned char * s, int b)
{
    //the complex function
    int nr = 12 + 2 * log2(b / 25);
    int w = b / 25;
    bool*** A = new bool**[5];
    for (int i = 0 ; i < 5 ; i ++)
    {
        A[i] = new bool* [5];
        for (int j = 0 ; j < 5 ; j ++)
            A[i][j] = new bool[w];
    }
    for (int y = 0 ; y < 5 ; y ++)
        for (int x = 0 ; x < 5 ; x ++)
            for (int z = 0 ; z < w ; z ++)
                A[x][y][z] = s[(z + w * x + 5 * w * y) / 8] & (1 << (7 - (z + w * x + 5 * w * y) % 8));
    for (int i = 0 ; i < nr; i ++)
    {
        A = Rnd(A, i, w);
    }
    int num = -1;
    for (int i = 0 ; i < b / 8; i ++)
    {
        unsigned char c = 0;
        for (int j = 0 ; j < 8 ; j ++)
        {
            num ++;
            int tmp = num;
            int z = tmp % w;
            tmp = (tmp - z) / w;
            int x = tmp % 5;
            tmp = (tmp - x) / 5;
            int y = tmp;
            if (A[x][y][z])
                c = c ^ (1 << (7 - j));
        }
        s[i] = c;
    }
    for (int i = 0 ; i < 5 ; i ++)
    {
        for (int j = 0 ; j < 5 ; j ++)
            delete[] A[i][j];
        delete[] A[i];
    }
    delete[] A;
    return s;
}

string Keccak::trunc(unsigned char * s, int l)
{
    //cut s into the l bytes
    string res = "";
    for (int i = 0; i < l / 8; i ++)
    {
        res = res + (char)s[i];
    }
    return res;
}

int Keccak::pad101(int x, int m)
{
    //get the bytes of padding
    int j = (- m - 2) % x;
    j += x;
    j %= x;
    return (j + 4) / 8;
}

string Keccak::sponge(int b, string m, int d)
{
    //the sponge construction in sha3
    int r = b - 2 * d;
    int oldLength = 8 * (int)m.size() + 2;
    int padding = pad101(r, oldLength);
    int n = (8 * (int)m.size() + 8 * padding) / r;
    unsigned char* s = new unsigned char[b / 8];
    for (int i = 0 ; i < b / 8 ; i ++)
        s[i] = 0;
    for (int i = 0 ; i < n ; i ++)
    {
        unsigned char* p = new unsigned char[r / 8];
        if (i < n - 1)
        {
            for (int j = 0 ; j < r / 8 ; j ++)
            {
                p[j] = m[i * r / 8 + j];
            }
        }
        else
        {
            for (int j = 0 ; j < r / 8 - padding; j ++)
            {
                p[j] = m[i * r / 8 + j];
            }
            if (padding == 1)
            {
                p[r / 8 - 1] = (char)97;
            }
            else
            {
                p[r / 8 - padding] = (char)96;
                for (int j = r / 8 - padding + 1 ; j < r / 8 - 1 ; j ++)
                {
                    p[j] = (char)0;
                }
                p[r / 8 - 1] = (char)1;
            }
        }
        for (int k = 0 ; k < r / 8 ; k ++)
        {
            s[k] = s[k] ^ p[k];
        }
        s = f(s, b);
        delete[] p;
    }
    string z = "";
    while (true)
    {
        z = z + trunc(s, r);
        if (d <= z.size())
        {
            delete[] s;
            break;
        }
        else
        {
            s = f(s, b);
        }
    }
    return trunc((unsigned char*)z.c_str(), d);
}

string Keccak::keccak(string m, int d)
{
    //refer to standards
    return sponge(1600, m, d);
}

string Keccak::sha3_224(string m)
{
    //merge suffix and padding into one function later.
    return keccak(m, 224);
}

string Keccak::sha3_256(string m)
{
    //merge suffix and padding into one function later.
    return keccak(m, 256);
}

string Keccak::sha3_384(string m)
{
    //merge suffix and padding into one function later.
    return keccak(m, 384);
}

string Keccak::sha3_512(string m)
{
    //merge suffix and padding into one function later.
    return keccak(m, 512);
}