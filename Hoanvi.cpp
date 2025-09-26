#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <chrono>

using namespace std;

// Chuyển thành chữ hoa, loại bỏ khoảng trắng (và giữ chữ/ số)
// Bạn có thể điều chỉnh để giữ dấu hay khoảng trắng nếu muốn
string normalize(const string& s) {
    string out;
    for (unsigned char c : s) {
        if (isspace(c)) continue;
        // giữ chữ và số, chuyển sang chữ hoa
        if (isalnum(c)) out.push_back((char)toupper(c));
        else {
            // nếu muốn loại bỏ ký tự khác, comment dòng dưới
            out.push_back((char)toupper(c));
        }
    }
    return out;
}

// Tạo thứ tự cột từ key: trả về vector order, order[original_index] = rank
vector<int> keyOrder(const string& key) {
    int n = (int)key.size();
    vector<pair<char, int>> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) v.emplace_back((char)toupper((unsigned char)key[i]), i);
    stable_sort(v.begin(), v.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.first < b.first;
        });
    vector<int> order(n);
    for (int rank = 0; rank < n; ++rank) {
        order[v[rank].second] = rank;
    }
    return order;
}

string encrypt(const string& plaintext, const string& key, char pad = 'X') {
    if (key.empty()) return plaintext;
    string pt = normalize(plaintext);
    int cols = (int)key.size();
    int rows = (pt.size() + cols - 1) / cols;
    int fullSize = rows * cols;
    pt.append(fullSize - (int)pt.size(), pad);

    // điền bảng theo hàng
    vector<string> table(rows, string(cols, pad));
    int p = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) table[r][c] = pt[p++];
    }

    // đọc theo thứ tự cột từ key
    vector<int> order = keyOrder(key);
    string ct; ct.reserve(fullSize);
    for (int rank = 0; rank < cols; ++rank) {
        for (int c = 0; c < cols; ++c) {
            if (order[c] == rank) {
                for (int r = 0; r < rows; ++r) ct.push_back(table[r][c]);
                break;
            }
        }
    }
    return ct;
}

string decrypt(const string& ciphertext, const string& key, char pad = 'X') {
    if (key.empty()) return ciphertext;
    string ct = normalize(ciphertext);
    int cols = (int)key.size();
    int rows = (ct.size() + cols - 1) / cols;
    vector<int> order = keyOrder(key);
    vector<string> colData(cols, string());

    int p = 0;
    for (int rank = 0; rank < cols; ++rank) {
        for (int c = 0; c < cols; ++c) {
            if (order[c] == rank) {
                int take = rows;
                if (p + take > (int)ct.size()) take = (int)ct.size() - p;
                if (take < 0) take = 0;
                colData[c] = ct.substr(p, take);
                p += take;
                break;
            }
        }
    }

    string pt;
    pt.reserve(rows * cols);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r < (int)colData[c].size()) pt.push_back(colData[c][r]);
        }
    }

    // loại pad ở cuối
    while (!pt.empty() && pt.back() == pad) pt.pop_back();
    return pt;
}

// Brute-force: thử tất cả hoán vị ký tự A,B,C,... cho mỗi độ dài từ minLen..maxLen
// LƯU Ý: số hoán vị = factorial(len), tăng nhanh.
// Hàm sẽ dừng nếu đã in đủ maxPrint kết quả.
void bruteForceAttack(const string& ciphertext, int minLen = 2, int maxLen = 6, int maxPrint = 200) {
    string ct = normalize(ciphertext);
    if (ct.empty()) {
        cout << "Bản mã rỗng, không thể phá mã.\n";
        return;
    }
    if (maxLen > 8) {
        cout << "Chú ý: maxLen > 8 có thể rất chậm. Giới hạn đề xuất <= 7.\n";
    }

    int printed = 0;
    auto tstart = chrono::steady_clock::now();

    for (int len = minLen; len <= maxLen; ++len) {
        // tạo vector ký tự đầu tiên: 'A','B',... tùy len
        string key(len, 'A');
        for (int i = 0; i < len; ++i) key[i] = 'A' + i;
        // sắp xếp để next_permutation duyệt tất cả
        sort(key.begin(), key.end());
        cout << "==== Thử các hoán vị cho độ dài khóa = " << len << " (tổng " << (len <= 12 ? 1 : 0) << " hoán vị hiển thị ước lượng) ====\n";
        // vì số hoán vị có thể lớn, ta có thể chọn chỉ in ra một số lượng giới hạn maxPrint
        // Duyệt hoán vị
        long long countPerm = 0;
        do {
            ++countPerm;
            string pt = decrypt(ct, key);
            // in ra (key, plaintext)
            cout << "Khóa thử: " << key << "  =>  " << pt << "\n";
            ++printed;
            if (printed >= maxPrint) {
                cout << "\nĐã in " << maxPrint << " kết quả. Dừng (để tránh quá nhiều kết quả).\n";
                auto tend = chrono::steady_clock::now();
                chrono::duration<double> diff = tend - tstart;
                cout << "Thời gian thực hiện: " << diff.count() << "s\n";
                return;
            }
            // Next permutation
        } while (next_permutation(key.begin(), key.end()));
        cout << "(Đã thử " << countPerm << " hoán vị cho chiều " << len << ")\n\n";
    }

    auto tend = chrono::steady_clock::now();
    chrono::duration<double> diff = tend - tstart;
    cout << "Kết thúc phá mã. Tổng kết thời gian: " << diff.count() << "s\n";
}

// giao diện menu tiếng việt
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "===== Chương trình MÃ HÓA HOÁN VỊ CỘT (Columnar Transposition) =====\n";
    cout << "Giao diện Tiếng Việt - Visual Studio 2022 (Console)\n\n";

    while (true) {
        cout << "\nChọn thao tác:\n";
        cout << "1) Mã hóa (Encrypt)\n";
        cout << "2) Giải mã (Decrypt)\n";
        cout << "3) Phá mã (Brute-force attack khi không biết khóa)\n";
        cout << "4) Thoát\n";
        cout << "Lựa chọn (1-4): ";
        int choice;
        if (!(cin >> choice)) {
            cout << "Lỗi nhập. Thoát.\n";
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        if (choice == 4) {
            cout << "Thoát chương trình. Tạm biệt!\n";
            break;
        }
        else if (choice == 1) {
            cout << "Nhập khóa (key): ";
            string key; getline(cin, key);
            if (key.empty()) { cout << "Khóa không được để rỗng.\n"; continue; }
            cout << "Nhập chuỗi cần mã hóa: ";
            string text; getline(cin, text);
            string ct = encrypt(text, key, 'X');
            cout << "Kết quả mã hóa:\n" << ct << "\n";
        }
        else if (choice == 2) {
            cout << "Nhập khóa (key): ";
            string key; getline(cin, key);
            if (key.empty()) { cout << "Khóa không được để rỗng.\n"; continue; }
            cout << "Nhập chuỗi cần giải mã: ";
            string text; getline(cin, text);
            string pt = decrypt(text, key, 'X');
            cout << "Kết quả giải mã:\n" << pt << "\n";
        }
        else if (choice == 3) {
            cout << "Nhập chuỗi bản mã (ciphertext) cần phá: ";
            string ct; getline(cin, ct);
            cout << "Nhập độ dài khóa tối thiểu (>=2, mặc định 2): ";
            int minLen; if (!(cin >> minLen)) minLen = 2;
            cout << "Nhập độ dài khóa tối đa (<=8 khuyến nghị, mặc định 6): ";
            int maxLen; if (!(cin >> maxLen)) maxLen = 6;
            cout << "Giới hạn số kết quả in ra tối đa (mặc định 200): ";
            int maxPrint; if (!(cin >> maxPrint)) maxPrint = 200;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (minLen < 2) minLen = 2;
            if (maxLen < minLen) maxLen = minLen;
            if (maxLen > 8) {
                cout << "Cảnh báo: maxLen lớn sẽ rất chậm (số hoán vị = factorial(maxLen)). Bạn có muốn tiếp tục? (y/n): ";
                char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (c != 'y' && c != 'Y') { cout << "Hủy phá mã.\n"; continue; }
            }
            cout << "Bắt đầu phá mã... (lưu ý: sẽ thử mọi hoán vị cho mỗi độ dài)\n";
            bruteForceAttack(ct, minLen, maxLen, maxPrint);
        }
        else {
            cout << "Lựa chọn không hợp lệ.\n";
        }
    }

    return 0;
}
