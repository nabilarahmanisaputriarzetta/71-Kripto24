/*
Nama Program : shift cipher
Nama         : Nabila Rahmanisa Putri Arzetta
NPM          : 140810220071
Tanggal Buat : 8/9/2024
Deskripsi    : Buatlah program Shift Cipher dengan bahasa pemrograman
*/

#include <iostream>
#include <string>
using namespace std;

string encrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];

        if (isupper(ch)) {
            result += char(int(ch + shift - 65) % 26 + 65);
        }
        else if (islower(ch)) {
            result += char(int(ch + shift - 97) % 26 + 97);
        }
        else {
            result += ch;
        }
    }

    return result;
}

string decrypt(string text, int shift) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];

        if (isupper(ch)) {
            result += char(int(ch - shift - 65 + 26) % 26 + 65);
        }
        else if (islower(ch)) {
            result += char(int(ch - shift - 97 + 26) % 26 + 97);
        }
        else {
            result += ch;
        }
    }

    return result;
}

int main() {
    string text;
    int shift;

    cout << "Input teks yang mau dienkripsi: ";
    getline(cin, text);
    cout << "Input pergeserannya (input angka): ";
    cin >> shift;
    string encryptedText = encrypt(text, shift);
    cout << "Hasil enkripsi: " << encryptedText << endl;
    string decryptedText = decrypt(encryptedText, shift);
    cout << "Hasil dekripsi: " << decryptedText << endl;

    return 0;
}
