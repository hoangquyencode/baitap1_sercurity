# baitap1_sercurity
BÀI TẬP MÔN: An toàn và bảo mật thông tin
BÀI TẬP 1:
TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
1. Caesar
2. Affine
3. Hoán vị
4. Vigenère
5. Playfair
Với mỗi phương pháp, hãy tìm hiểu:
1. Tên gọi
2. Thuật toán mã hoá, thuật toán giải mã
3. Không gian khóa
4. Cách phá mã (mà không cần khoá)
5. Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript

BÀI LÀM
I. Caesar
1.Tên gọi
Mật mã Caesar (Caesar cipher / shift cipher): mã thay thế tuyến tính dịch mỗi chữ cái theo một khóa k.
2.Thuật toán mã hóa / giải mã
Mã hóa: với ký tự số 𝑖 và khóa 𝑘 trên bảng chữ 𝑁 ký tự: C=(i+k)mod N.
Giải mã: P=(i−k)mod N.
(Thường N=26 cho A–Z; giữ nguyên ký tự không phải chữ.)
3. Không gian khóa 
K={0,1,…,25}. Tổng số khóa = 26 (khóa 0 không đổi).
4. Cách phá mã (không cần khóa)
- Brute-force: thử tất cả k (0–25).
- Phân tích tần suất: so sánh tần suất chữ trong ciphertext với tần suất ngôn ngữ (ví dụ E trong tiếng Anh).
- Known-plaintext / từ điển: đoán từ đã biết hoặc kiểm tra kết quả với từ điển.
  
