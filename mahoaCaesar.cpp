#include <iostream>
#include <string>
using namespace std;

string caesar_shift(const string& text, int k) {
    string result;
    // chuẩn hóa k về [0,25]
    k = (k % 26 + 26) % 26;
    for (char ch : text) {
        if (isupper(static_cast<unsigned char>(ch))) {
            result += char((ch - 'A' + k) % 26 + 'A');
        }
        else if (islower(static_cast<unsigned char>(ch))) {
            result += char((ch - 'a' + k) % 26 + 'a');
        }
        else {
            result += ch;
        }
    }
    return result;
}

string caesar_encrypt(const string& text, int k) {
    return caesar_shift(text, k);
}
string caesar_decrypt(const string& text, int k) {
    // giải mã = dịch -k
    return caesar_shift(text, -k);
}

void brute_force(const string& cipher) {
    cout << "\nBrute-force (k = 0..25):\n";
    for (int k = 0; k < 26; ++k) {
        cout << k << " : " << caesar_decrypt(cipher, k) << '\n';
    }
}

int main() {
    cout << "===== CAESAR CIPHER (Console) =====\n";
    cout << "Nhap chuoi (co the co dau cach):\n";
    string line;
    getline(cin, line);

    cout << "Nhap khoa (so nguyen): ";
    int k;
    if (!(cin >> k)) return 0;

    cout << "Chon: 1=Ma hoa  2=Giai ma  3=Brute-force\nLua chon: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "\nBan ma: " << caesar_encrypt(line, k) << "\n";
    }
    else if (choice == 2) {
        cout << "\nBan goc: " << caesar_decrypt(line, k) << "\n";
    }
    else if (choice == 3) {
        brute_force(line);
    }
    else {
        cout << "Lua chon khong hop le.\n";
    }
    return 0;
}
