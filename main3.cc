#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include "daes.h"
using namespace std;

void Usage(){

}

vector<string> getfiles(string p){
  DIR *dir;
  struct dirent *ent;
  vector<string> auxe;
  string path = p;
  if ((dir = opendir (path.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      string aux = path + ent->d_name;
      //printf ("%s\n", ent->d_name);
      string as = ent->d_name;
        struct stat s;
        const char* go = aux.c_str();
        if( stat(go,&s) == 0 )
        {
            if( s.st_mode & S_IFDIR )
            {
                //it's a directory
                if(as != ".."  && as != "."){
                  aux += "/";
                  vector<string> directories = getfiles(aux);
                  for(int i = 0; i < directories.size(); ++i){
                    auxe.push_back(directories[i]);
                  }
                }


            }
            else if( s.st_mode & S_IFREG )
            {
              //it's a file
              auxe.push_back(aux);
            }
            else
            {
              cout<<"//something else"<<endl;
            }
        }
        else
        {
            //error
        }
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    cout<<errno<<endl;
    //return EXIT_FAILURE;
  }
  return auxe;
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
    vector<string> gas = getfiles(path);
    if(gas.size() > 0){
      cout<<"Files found: "<<gas.size()<<endl;
      cout<<"Decrypting file(s):"<<endl;
      for(int i  = 0; i < gas.size(); ++i){
        cout<<gas[i]<<endl;
        Daes* d = new Daes(despass,aespass,gas[i],false);
        d->dec();
        delete d;
      }
    }
    else{
      cout<<"Decrypting file(s):"<<endl;
      cout<<path<<endl;
      Daes* d = new Daes(despass,aespass,path,false);
      d->dec();
      delete d;
    }
  }
  else if(select == "2"){
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter AES password(must be 16 characters long, if not will be padded with '*'): \033[0m"<<endl;
    cin>>aespass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    vector<string> gas = getfiles(path);
    cout<<endl;
    if(gas.size() > 0){
      cout<<"Files found: "<<gas.size()<<endl;
      cout<<"Decrypting file(s):"<<endl;
      for(int i  = 0; i < gas.size(); ++i){
        cout<<gas[i]<<endl;
        Daes* d = new Daes(despass,aespass,gas[i],true);
        d->dec();
        delete d;
      }
    }
    else{
      cout<<"Decrypting file(s):"<<endl;
      cout<<path<<endl;
      Daes* d = new Daes(despass,aespass,path,true);
      d->dec();
      delete d;
    }
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
  bool isaes = false;
  if(select == "1"){
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    aespass = "notused";
    vector<string> gas = getfiles(path);
    cout<<endl;
    if(gas.size() > 0){
      cout<<"Files found: "<<gas.size()<<endl;
      cout<<"Encrypting file(s):"<<endl;
      for(int i  = 0; i < gas.size(); ++i){
        cout<<gas[i]<<endl;
        Daes* d = new Daes(despass,aespass,gas[i],false);
        d->randd();
        delete d;
      }
    }
    else{
      cout<<"Encrypting file(s):"<<endl;
      cout<<path<<endl;
      Daes* d = new Daes(despass,aespass,path,false);
      d->randd();
      delete d;
    }
  }
  else if(select == "2"){
    isaes = true;
    cout << "\033[1;33mEnter DES password: \033[0m\n";
    cin>>despass;
    cout<<"\033[1;33mEnter AES password(must be 16 characters long, if not will be padded with '*'): \033[0m"<<endl;
    cin>>aespass;
    cout<<"\033[1;33mEnter path of the file or folder('.' if it's the actual directory): \033[0m"<<endl;
    cin>>path;
    vector<string> gas = getfiles(path);
    cout<<endl;
    if(gas.size() > 0){
      cout<<"Files found: "<<gas.size()<<endl;
      cout<<"Encrypting file(s):"<<endl;
      for(int i  = 0; i < gas.size(); ++i){
        cout<<gas[i]<<endl;
        Daes* d = new Daes(despass,aespass,gas[i],true);
        d->randd();
        delete d;
      }
    }
    else{
      cout<<"Encrypting file(s):"<<endl;
      cout<<path<<endl;
      Daes* d = new Daes(despass,aespass,path,true);
      d->randd();
      delete d;
    }
  }
  cout<<endl;
  cout << "\033[1;7;33mFINAL KEYS\033[0m\n";
  cout << "\033[1;33mDES password:\033[0m"<<despass<<endl;
  if(isaes) cout << "\033[1;33mAES password:\033[0m"<<aespass<<endl;
  cout<<endl;
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
