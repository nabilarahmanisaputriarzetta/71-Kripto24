/*
Nama Program : hill cipher
Nama         : Nabila Rahmanisa Putri Arzetta
NPM          : 140810220071
Tanggal Buat : 17/9/2024
Deskripsi    : Buatlah program untuk enkripsi, dekripsi, dan mencari kunci Hill Cipher (bahasa pemrograman bebas)
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int char_to_number(char x) {
    return (int)x - 65;
}

char number_to_char(int x) {
    return (char)(x + 65);
}

int mod_inverse(int A, int M) {
    for (int X = 1; X < M; X++) {
        if (((A % M) * (X % M)) % M == 1)
            return X;
    }
    return -1;
}

vector<vector<int>> input_key(int n) {
    vector<vector<int>> key(n, vector<int>(n));
    cout << "Input angka/nilai key matrix (dipisahkan spasi): ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> key[i][j];
            key[i][j] %= 26;
        }
    }
    cout << "Key Matrix: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << key[i][j] << (j != n - 1 ? " " : "");
        }
        cout << "]" << endl;
    }
    return key;
}

string input_text(string type) {
    string text;
    cout << "Input " << type << ": ";
    cin >> text;
    for (char &ch : text) {
        ch = toupper(ch);
    }
    return text;
}

string hill(string method, string text, vector<vector<int>> key, int n) {
    int key_det = round(key[0][0] * key[1][1] - key[0][1] * key[1][0]);

    if (key_det % 2 == 0 || key_det == 13) {
        cout << "Determinan bukan ganjil selain 13. Key ga ada karena invers ga ada." << endl;
        return "";
    }

    if (text.length() % n != 0) {
        char last_char = text[text.length() - 1];
        text.append(n - text.length() % n, last_char);
    }

    vector<int> text_in_number(text.length());
    for (int i = 0; i < text.length(); i++) {
        text_in_number[i] = char_to_number(text[i]);
    }

    vector<int> result(text.length());

    if (method == "dekripsi") {
        int det_inverse = mod_inverse(key_det % 26, 26);
        key = {{(key[1][1] * det_inverse) % 26, (-key[0][1] * det_inverse + 26) % 26},
               {(-key[1][0] * det_inverse + 26) % 26, (key[0][0] * det_inverse) % 26}};
    }

    for (int i = 0; i < text.length(); i += n) {
        for (int j = 0; j < n; j++) {
            result[i + j] = 0;
            for (int k = 0; k < n; k++) {
                result[i + j] += key[j][k] * text_in_number[i + k];
            }
            result[i + j] %= 26;
        }
    }

    string output = "";
    for (int i = 0; i < result.size(); i++) {
        output += number_to_char(result[i]);
    }

    return output;
}

vector<vector<int>> find_key(string pt, string ct, int m) {
    vector<vector<int>> key(m, vector<int>(m));

    vector<int> pt_in_number(pt.length()), ct_in_number(ct.length());
    for (int i = 0; i < pt.length(); i++) {
        pt_in_number[i] = char_to_number(pt[i]);
        ct_in_number[i] = char_to_number(ct[i]);
    }

    vector<vector<int>> p_matrix(m, vector<int>(m)), c_matrix(m, vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            p_matrix[i][j] = pt_in_number[i * m + j];
            c_matrix[i][j] = ct_in_number[i * m + j];
        }
    }

    int p_det = round(p_matrix[0][0] * p_matrix[1][1] - p_matrix[0][1] * p_matrix[1][0]);
    if (p_det % 2 == 0 || p_det == 13) {
        cout << "Determinan bukan ganjil selain 13. Key ga ada karena invers ga ada." << endl;
        return key;
    }

    int p_det_inverse = mod_inverse(p_det % 26, 26);
    p_matrix = {{(p_matrix[1][1] * p_det_inverse) % 26, (-p_matrix[0][1] * p_det_inverse + 26) % 26},
                {(-p_matrix[1][0] * p_det_inverse + 26) % 26, (p_matrix[0][0] * p_det_inverse) % 26}};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            key[i][j] = 0;
            for (int k = 0; k < m; k++) {
                key[i][j] += c_matrix[i][k] * p_matrix[k][j];
            }
            key[i][j] %= 26;
        }
    }

    return key;
}

int main() {
    while (true) {
        cout << "\n========Menu========" << endl;
        cout << "A. Enkripsi" << endl;
        cout << "B. Dekripsi" << endl;
        cout << "C. Cari Key" << endl;
        cout << "D. Exit" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "A" || pilihan == "B") {
            int n;
            cout << "\nInput ukuran key matrix (n x n): ";
            cin >> n;
            vector<vector<int>> key = input_key(n);

            string text;
            do {
                text = input_text("text");
                if (text.length() < n) {
                    cout << "n harus bilangan prima terkecil sebagai faktor dari jumlah karakter" << endl;
                }
            } 
            while (text.length() < n);

            if (pilihan == "A") {
                cout << "\nPlaintext: " << text << endl;
                string output = hill("enkripsi", text, key, n);
                cout << "Ciphertext: " << output << endl;
            } 
            else if (pilihan == "B") {
                cout << "\nCiphertext: " << text << endl;
                string output = hill("dekripsi", text, key, n);
                cout << "Plaintext: " << output << endl;
            }
        } else if (pilihan == "C") {
            string pt = input_text("plaintext");
            string ct = input_text("ciphertext");
            int m;
            cout << "\nInput nilai m: ";
            cin >> m;
            vector<vector<int>> key = find_key(pt, ct, m);
            cout << "\nPlaintext: " << pt << endl;
            cout << "Ciphertext: " << ct << endl;
            cout << "Key Matrix:" << endl;
            for (int i = 0; i < m; i++) {
                cout << "[";
                for (int j = 0; j < m; j++) {
                    cout << key[i][j] << (j != m - 1 ? " " : "");
                }
                cout << "]" << endl;
            }
        } 
        else if (pilihan == "D") {
            break;
        } 
        else {
            cout << "\nInput ga sesuai." << endl;
        }
    }

    return 0;

}