#include <iostream>
#include <string>
#include <cctype>
#include <numeric>
#include <stdexcept>
using namespace std;

const string ALPH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int M = 26;

// Nghịch đảo modulo
int modinv(int a, int m) {
    int t = 0, newt = 1, r = m, newr = a;
    while (newr != 0) {
        int q = r / newr;
        int tmp = t; t = newt; newt = tmp - q * newt;
        tmp = r; r = newr; newr = tmp - q * newr;
    }
    if (r > 1) return -1;
    if (t < 0) t += m;
    return t;
}

// Ánh xạ 1 ký tự
char mapChar(char ch, int a, int b, bool enc, int aInv) {
    if (!isalpha(ch)) return ch;
    bool lower = islower(ch);
    int idx = toupper(ch) - 'A';
    int mapped = enc ? (a * idx + b) % M : (aInv * ((idx - b + M) % M)) % M;
    char res = 'A' + mapped;
    return lower ? tolower(res) : res;
}

// Xử lý văn bản
string affine(const string& text, int a, int b, bool enc) {
    int aInv = modinv(a, M);
    if (!enc && aInv == -1) throw runtime_error("a không có nghịch đảo mod 26");
    string out;
    for (char ch : text) out += mapChar(ch, a, b, enc, aInv);
    return out;
}

// Brute-force
void brute(const string& ct) {
    for (int a = 1; a < M; a++) {
        if (gcd(a, M) != 1) continue;
        for (int b = 0; b < M; b++) {
            try {
                cout << "(" << a << "," << b << ") -> " << affine(ct, a, b, false) << "\n";
            }
            catch (...) {}
        }
    }
}

int main() {
    cout << "Mật mã Affine - C++\n";
    cout << "Nhập văn bản: ";
    string text; getline(cin, text);

    cout << "Chọn chức năng:\n1) Mã hóa\n2) Giải mã\n3) Brute-force\nLựa chọn: ";
    int opt; cin >> opt;
    cin.ignore();

    int a = 0, b = 0;
    if (opt == 1 || opt == 2) {
        cout << "Nhập a (coprime với 26): "; cin >> a;
        cout << "Nhập b (0-25): "; cin >> b;
    }

    try {
        if (opt == 1) cout << "Bản mã: " << affine(text, a, b, true) << "\n";
        else if (opt == 2) cout << "Bản rõ: " << affine(text, a, b, false) << "\n";
        else if (opt == 3) brute(text);
        else cout << "Chức năng không hợp lệ\n";
    }
    catch (exception& e) {
        cout << "Lỗi: " << e.what() << "\n";
    }
}
