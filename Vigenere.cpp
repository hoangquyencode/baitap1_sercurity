#include <iostream>
#include <string>
#include <cctype>
using namespace std;

char up(char c) { return (c >= 'a' && c <= 'z') ? char(c - 'a' + 'A') : c; }

// process: encrypt=true -> mã hóa, false -> giải mã
string vigenere(const string& text, const string& key, bool encrypt = true) {
    if (key.empty()) return text;
    string out; out.reserve(text.size());
    string K;
    // chuẩn hóa khóa: chỉ giữ A-Z, viết hoa
    for (char c : key) if (isalpha((unsigned char)c)) K.push_back(up(c));
    if (K.empty()) return text;

    int j = 0; // chỉ tăng khi gặp chữ cái trong text
    int klen = (int)K.size();
    for (char ch : text) {
        char C = up(ch);
        if (C >= 'A' && C <= 'Z') {
            int pk = K[j % klen] - 'A';
            int t = C - 'A';
            int r = encrypt ? (t + pk) % 26 : (t - pk + 26) % 26;
            out.push_back(char(r + 'A'));
            ++j;
        }
        else {
            out.push_back(ch); // giữ nguyên ký tự không phải chữ
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, key;
    cout << "=== VIGENERE (Gọn, chính xác) ===\n";
    cout << "Nhập bản rõ (plaintext):\n"; getline(cin, text);
    cout << "Nhập khóa:\n"; getline(cin, key);
    cout << "\n-> Ciphertext:\n" << vigenere(text, key, true) << "\n\n";

    cout << "Nhập bản mã để giải (hoặc dùng ciphertext trên):\n"; getline(cin, text);
    cout << "Nhập khóa giải:\n"; getline(cin, key);
    cout << "\n-> Plaintext:\n" << vigenere(text, key, false) << "\n";

    return 0;
}
