#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// Chuẩn hóa: giữ chữ, viết hoa, thay J -> I
string normalize_alpha(const string& s) {
    string out;
    for (unsigned char ch : s) {
        if (isalpha(ch)) {
            char C = toupper(ch);
            if (C == 'J') C = 'I';
            out.push_back(C);
        }
    }
    return out;
}

// Tạo ma trận 5x5 từ key (loại trùng, ghép J->I)
vector<char> create_table(const string& key) {
    string k = normalize_alpha(key);
    vector<bool> used(26, false);
    vector<char> table; table.reserve(25);
    for (char c : k) {
        int idx = c - 'A';
        if (!used[idx]) {
            used[idx] = true;
            if (c == 'J') continue; // J đã chuyển sang I nhưng bảo đảm
            table.push_back(c);
        }
    }
    // thêm các chữ còn lại (A..Z), bỏ J
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            used[ch - 'A'] = true;
            table.push_back(ch);
        }
    }
    // bảo đảm kích thước 25
    table.resize(25);
    return table;
}

// tìm vị trí char trong bảng (row, col)
pair<int, int> pos_in_table(const vector<char>& table, char c) {
    for (int i = 0; i < 25; i++) if (table[i] == c) return { i / 5, i % 5 };
    return { -1,-1 };
}

// Xử lý plaintext thành cặp (digraphs) theo quy tắc Playfair
vector<pair<char, char>> make_pairs(const string& plain_in) {
    string s = normalize_alpha(plain_in);
    vector<pair<char, char>> pairs;
    for (size_t i = 0; i < s.size();) {
        char a = s[i];
        char b = (i + 1 < s.size()) ? s[i + 1] : '\0';
        if (b == '\0') {
            // còn một ký tự, thêm X
            pairs.emplace_back(a, 'X');
            break;
        }
        if (a == b) {
            // hai ký tự giống nhau -> chèn X sau a, dịch chỉ tăng 1 ký tự
            pairs.emplace_back(a, 'X');
            i += 1;
        }
        else {
            pairs.emplace_back(a, b);
            i += 2;
        }
    }
    return pairs;
}

// Mã hóa/giải mã 1 cặp theo bảng
pair<char, char> process_pair(const vector<char>& table, pair<char, char> pr, bool encrypt) {
    auto pa = pos_in_table(table, pr.first);
    auto pb = pos_in_table(table, pr.second);
    int r1 = pa.first, c1 = pa.second, r2 = pb.first, c2 = pb.second;
    if (r1 == r2) {
        // cùng hàng: shift phải (encrypt) hoặc trái (decrypt)
        if (encrypt) {
            return { table[r1 * 5 + ((c1 + 1) % 5)], table[r2 * 5 + ((c2 + 1) % 5)] };
        }
        else {
            return { table[r1 * 5 + ((c1 + 4) % 5)], table[r2 * 5 + ((c2 + 4) % 5)] };
        }
    }
    else if (c1 == c2) {
        // cùng cột: shift xuống (encrypt) hoặc lên (decrypt)
        if (encrypt) {
            return { table[((r1 + 1) % 5) * 5 + c1], table[((r2 + 1) % 5) * 5 + c2] };
        }
        else {
            return { table[((r1 + 4) % 5) * 5 + c1], table[((r2 + 4) % 5) * 5 + c2] };
        }
    }
    else {
        // hình chữ nhật: đổi cột
        return { table[r1 * 5 + c2], table[r2 * 5 + c1] };
    }
}

// Mã hóa toàn bộ
string playfair_encrypt(const string& plaintext, const string& key) {
    auto table = create_table(key);
    auto pairs = make_pairs(plaintext);
    string out;
    out.reserve(pairs.size() * 2);
    for (auto& p : pairs) {
        auto q = process_pair(table, p, true);
        out.push_back(q.first);
        out.push_back(q.second);
    }
    return out;
}

// Giải mã toàn bộ
string playfair_decrypt(const string& ciphertext, const string& key) {
    auto table = create_table(key);
    // ciphertext đã là chỉ chữ cái; nếu có ký tự khác thì bỏ chúng
    string ct = normalize_alpha(ciphertext);
    // tạo cặp liên tiếp (2 ký tự)
    vector<pair<char, char>> pairs;
    for (size_t i = 0; i < ct.size(); i += 2) {
        char a = ct[i];
        char b = (i + 1 < ct.size()) ? ct[i + 1] : 'X';
        pairs.emplace_back(a, b);
    }
    string out; out.reserve(pairs.size() * 2);
    for (auto& p : pairs) {
        auto q = process_pair(table, p, false);
        out.push_back(q.first);
        out.push_back(q.second);
    }
    // LƯU Ý: kết quả có thể chứa ký tự X chèn vào khi mã hóa; người dùng có thể loại bỏ nếu biết luật.
    return out;
}

// Hiển thị bảng (debug)
void print_table(const vector<char>& table) {
    cout << "Ma tran 5x5 (Playfair):\n";
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) cout << table[r * 5 + c] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "=== Playfair Cipher (Mã hóa / Giải mã) ===\n";
    while (true) {
        cout << "\n1) Mã hóa\n2) Giải mã\n3) Thoát\nChọn: ";
        int ch; if (!(cin >> ch)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ch == 3) break;
        if (ch == 1) {
            string plaintext, key;
            cout << "Nhập khóa: "; getline(cin, key);
            cout << "Nhập bản rõ (plaintext): "; getline(cin, plaintext);
            auto table = create_table(key);
            print_table(table);
            string ct = playfair_encrypt(plaintext, key);
            cout << "Ciphertext: " << ct << "\n";
            cout << "(Lưu ý: chữ J được thay bằng I; X có thể là ký tự đệm.)\n";
        }
        else if (ch == 2) {
            string key, ciphertext;
            cout << "Nhập khóa: "; getline(cin, key);
            cout << "Nhập bản mã (ciphertext): "; getline(cin, ciphertext);
            auto table = create_table(key);
            print_table(table);
            string pt = playfair_decrypt(ciphertext, key);
            cout << "Plaintext (giải mã, có thể gồm X đệm): " << pt << "\n";
            cout << "Bạn có thể loại bỏ các X đệm nếu cần (tùy ngữ cảnh).\n";
        }
        else {
            cout << "Lựa chọn không hợp lệ.\n";
        }
    }
    cout << "Thoát chương trình.\n";
    return 0;
}
