#include <iostream>
#include <iomanip>
#include <string>
#include "daes.h"
using namespace std;

void Usage(){

}

void decrypt(){
  cout << "\033[1;33mSelect decryption type: \033[0m\n";
  cout <<endl;
  cout << "\033[1;32m     1)\033[0m \033[1;31m 2-key Triple DES and SHA1 \033[0m\n";
  cout << "\033[1;32m     2)\033[0m \033[1;31m 2-key Triple DES,SHA1 and AES \033[0m\n";
  cout <<endl;
  string select;
  cin>>select;
  string despass,aespass,path;
  if(select == "1"){
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    aespass = "notused";
    Daes d(despass,aespass,path,false);
    d.dec();
    d.PrintKeys();
  }
  else if(select == "2"){
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter AES password(must be 16 characters long, if not will be padded with '*'): \033[0m"<<endl;
    cin>>aespass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    Daes d(despass,aespass,path,true);
    d.dec();
    d.PrintKeys();
  }

  //cout<<d.getCipher()<<endl;
  cout<<"\033[1;33m   Successfully decrypted \033[0m"<<endl;

}



void encrypt(){
  cout << "\033[1;33mSelect encryption type: \033[0m\n";
  cout <<endl;
  cout << "\033[1;32m     1)\033[0m \033[1;31m 2-key Triple DES and SHA1 \033[0m\n";
  cout << "\033[1;32m     2)\033[0m \033[1;31m 2-key Triple DES,SHA1 and AES \033[0m\n";
  cout <<endl;
  cout << "\033[1;31m** We highly recommend you option number 2, with AES nowadays it's impossible to break with bruteforce or mathematical solutions ** \033[0m\n";
  string select;
  cin>>select;
  string despass,aespass,path;
  if(select == "1"){
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    aespass = "notused";
    Daes d(despass,aespass,path,false);
    d.randd();
    d.PrintKeys();
  }
  else if(select == "2"){
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter AES password(must be 16 characters long, if not will be padded with '*'): \033[0m"<<endl;
    cin>>aespass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    Daes d(despass,aespass,path,true);
    d.randd();
    d.PrintKeys();
  }

  //cout<<d.getCipher()<<endl;
  cout<<"\033[1;33m   Successfully encrypted \033[0m"<<endl;
}

void Default(){
  cout << "\033[1;7;32m¡Welcome to DAES FileE&D!\033[0m\n";
  cout <<endl;
  cout << "\033[1;32m     1)\033[0m \033[1;31mEncrypt \033[0m\n";
  cout << "\033[1;32m     2)\033[0m \033[1;31mDecrypt \033[0m\n";
  cout <<endl;
  string select;
  cin>>select;
  if(select == "1"){encrypt();}
  else if(select == "2"){decrypt();}
  else exit;

}

int main(int argc, char* argv[]) {

  if(argc > 3){
    Usage();
  }
  else if(argc == 1){
    Default();
  }

}
