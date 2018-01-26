#ifndef DAES_H
#define DAES_H

#include <string>
using namespace std;



class Daes
{
private:
    string m_cipher;
    string aes_cipher;
    string d_pass;
    string a_pass;
    string path;
    bool doaes;
    
public:
    Daes(string a,string b,string c,bool d);

    void randd();
    void ewaes();
    void dec();
    string decriptaes(string ciphertext);
    void WriteIntoFile();
    void PrintKeys();
    string getCipher() { return m_cipher; }
};

#endif
