#include "daes.h"
#include <iostream>
#include <iomanip>
#include <string>


#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/default.h"
#include "cryptopp/hex.h"

using namespace std;
// Daes constructor
Daes::Daes(string a,string b,string c,bool d)
{
  d_pass = a; a_pass = b; path = c;
  if(d) doaes = true;
  else doaes = false;
}

void Daes::WriteIntoFile(){ //read and des
  //STORE File
  const char *aux= path.c_str();
      if(doaes)      CryptoPP::StringSource ss(aes_cipher, true,new CryptoPP::FileSink(aux)); // StringSource
      else       CryptoPP::StringSource ss(m_cipher, true,new CryptoPP::FileSink("./aesencript.jpg")); // StringSource

}

void Daes::PrintKeys(){ //read and des
  //STORE File
  cout<<endl;
  cout << "\033[1;7;33mFINAL KEYS\033[0m\n";
      if(doaes){
        cout << "\033[1;33mDES password:\033[0m"<<d_pass<<endl;
        cout << "\033[1;33mAES password:\033[0m"<<a_pass<<endl;
      }
      else{
        cout << "\033[1;33mDES password:\033[0m"<<d_pass<<endl;
      }
      cout<<endl;
}




// Daes member function
void Daes::ewaes()
{
  //begins. DEFAULT_KEYLENGTH= 16 bytes
  byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
  memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
  std::string sKey = a_pass;

  if(CryptoPP::AES::DEFAULT_KEYLENGTH < sKey.size()) sKey = sKey.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH); // chop if too long
  else if(CryptoPP::AES::DEFAULT_KEYLENGTH > sKey.size()) sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*'); // pad
  memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
  //
  // String and Sink setup
  //
  //
  // Create Cipher Text
  //
  CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
  CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

  CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( aes_cipher ) );
  stfEncryptor.Put( reinterpret_cast<const unsigned char*>( m_cipher.c_str() ), m_cipher.length() + 1 );
  stfEncryptor.MessageEnd();
  a_pass = sKey;
  WriteIntoFile();
}

void Daes::randd(){ //read and des
  const char *aux= path.c_str();
  CryptoPP::FileSource fs3(aux, true,
      new   CryptoPP::DefaultEncryptorWithMAC(
          (byte*)d_pass.data(), d_pass.size(),
          new CryptoPP::HexEncoder(
              new CryptoPP::StringSink(m_cipher)
          )
      )
  );
  if(doaes)  ewaes();
  else WriteIntoFile();
}
///root/Documents/FileEncryptor/gos.jpg

string Daes::decriptaes(string ciphertext){
  //Key and IV setup
  //AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
  //bit). This key is secretly exchanged between two parties before communication
  //begins. DEFAULT_KEYLENGTH= 16 bytes
  byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
  memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
  std::string sKey = a_pass;

  if(CryptoPP::AES::DEFAULT_KEYLENGTH < sKey.size()) sKey = sKey.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH); // chop if too long
  else if(CryptoPP::AES::DEFAULT_KEYLENGTH > sKey.size()) sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*'); // pad
  memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
  //
  // String and Sink setup
  //
  std::string decryptedtext;
  // Decrypt
  //
  CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
  CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

  CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
  stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
  stfDecryptor.MessageEnd();

  return decryptedtext;

}


void Daes::dec(){ //read and des
  const char *aux= path.c_str();
  string plain;
  CryptoPP::FileSource file( aux, true, new CryptoPP::StringSink( plain ) );
  string aux_decrypted = decriptaes(plain);
  CryptoPP::StringSource ss2(aux_decrypted, true,
      new CryptoPP::HexDecoder(
          new CryptoPP::DefaultDecryptorWithMAC(
          (byte*)d_pass.data(), d_pass.size(),
              new CryptoPP::FileSink(aux,true)
          )
      )
  );
}
