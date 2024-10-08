/*
Nama Program : vigenere cipher
Nama         : Nabila Rahmanisa Putri Arzetta
NPM          : 140810220071
Tanggal Buat : 8/9/2024
Deskripsi    : Buatlah program vigenere Cipher dengan bahasa pemrograman
*/

#include <iostream>
#include <algorithm>
using namespace std;

string encryptVigenere(string plaintext, string key) {
    string ciphertext = "";
    int keyLength = key.length();

    for (int i = 0; i < plaintext.length(); i++) {
        key[i] = key[i % keyLength];
    }

    for (int i = 0; i < plaintext.length(); i++) {
        char encryptedChar = ((plaintext[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
        ciphertext += encryptedChar;
    }
    
    return ciphertext;
}

string encryptAutokey(string plaintext, string key) {
    string ciphertext = "";
    int keyLength = key.length();

    key += plaintext;

    for (int i = 0; i < plaintext.length(); i++) {
        char encryptedChar = ((plaintext[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
        ciphertext += encryptedChar;
    }
    
    return ciphertext;
}

int main() {
    string plaintext, key;

    cout << "Input kalimat (huruf besar tanpa spasi): ";
    cin >> plaintext;
    cout << "Input key (huruf besar): ";
    cin >> key;

    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    string encryptedVigenere = encryptVigenere(plaintext, key);
    cout << "Hasil Enkripsi Vigenère Cipher: " << encryptedVigenere << endl;

    string encryptedAutokey = encryptAutokey(plaintext, key);
    cout << "Hasil Enkripsi Autokey Cipher: " << encryptedAutokey << endl;

    return 0;
}
