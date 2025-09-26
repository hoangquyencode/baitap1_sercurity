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
  Hình ảnh web:

  <img width="1138" height="599" alt="image" src="https://github.com/user-attachments/assets/31da3a01-52e8-4a1b-9e02-45b9a1b5b76f" />

  

II. Affine

 Affine là một mã hóa thay thế đơn chữ cái, sử dụng một hàm toán học đơn giản để chuyển đổi mỗi chữ cái của văn bản gốc thành một chữ cái khác trong văn bản mã hóa, dựa trên công thức P = (aX + b) mod m. Trong đó, P là chữ cái mã hóa, X là chữ cái văn bản gốc, 'a' và 'b' là khóa mã hóa, và 'm' là độ dài của bảng chữ cái. 
Cách thức hoạt động:
Chuyển đổi chữ cái thành số: Đầu tiên, mỗi chữ cái trong văn bản gốc sẽ được ánh xạ tới một số tương ứng (ví dụ: A=0, B=1, ..., Z=25). 
Áp dụng hàm toán học: Sử dụng công thức mã hóa Affine, P = (aX + b) mod m, để tính toán vị trí của chữ cái mã hóa. 
Chuyển đổi trở lại thành chữ cái: Chuyển đổi kết quả số P trở lại thành chữ cái tương ứng. 
Ví dụ:
Giả sử ta có từ "HAT" và khóa mã hóa là a=5, b=3 với bảng chữ cái tiếng Anh (m=26). 
H: 7. (5 * 7 + 3) mod 26 = 38 mod 26 = 12 (chữ cái M).
A: 0. (5 * 0 + 3) mod 26 = 3 mod 26 = 3 (chữ cái D).
T: 19. (5 * 19 + 3) mod 26 = (95 + 3) mod 26 = 98 mod 26 = 20 (chữ cái U).
Vậy "HAT" được mã hóa thành "MDU". 
Giải mã:
Để giải mã, ta cần sử dụng nghịch đảo của 'a' (ký hiệu là a⁻¹) trong phép toán modulo. Công thức giải mã là X = a⁻¹(P - b) mod m. 
Điểm yếu:
Phân tích tần suất: Mật mã Affine có thể bị phá bằng phương pháp phân tích tần suất các ký tự, đặc biệt là với các bản mã có độ dài lớn. 
Số lượng khóa nhỏ: Số lượng các cặp khóa (a, b) cho mật mã Affine là tương đối nhỏ (chỉ 312 khóa cho tiếng Anh), cho phép thử vét cạn nhanh chóng để phá mã. 
  Hình ảnh web:
  
  <img width="1275" height="912" alt="image" src="https://github.com/user-attachments/assets/0e2d20ce-8ef9-4036-9a33-14ef763b7491" />


III. Hoán vị
Đây là mã hoán vị đơn giản. Viết các chữ của bản rõ theo đường chéo trên một số dòng. Sau đó đọc các chữ theo theo từng dòng sẽ nhận được bản mã. Số dòng chính là khoá của mã. Vì khi biết số dòng ta sẽ tính được số chữ trên mỗi dòng và lại viết bản mã theo các dòng sau đó lấy bản rõ bằng cách viết lại theo các cột.

Viết bản tin “meet me after the toga party” lần lượt trên hai dòng như sau

m e m a t r h t g p r y

e t e f e t e o a a t

Sau đó ghép các chữ ở dòng thứ nhất với các chữ ở dòng thứ hai cho bản mã:

MEMATRHTGPRYETEFETEOAAT


<img width="1057" height="849" alt="image" src="https://github.com/user-attachments/assets/3f1b9c1a-32f6-4553-87a5-0fa8612f2a27" />


IV. Vigenère

1. Mã hóa Vigenère là một phương pháp mã hóa cổ điển và mạnh mẽ, được sử dụng để bảo vệ tính bí mật của thông tin. Thuật toán này dựa trên việc sử dụng một bảng mã hoá dựa trên sự dịch chuyển của các ký tự theo các khóa khác nhau.
2. Mô tả thuật toán :Sử dụng bảng mã hóa Vigenere : Để mã hóa, ta ta dùng một hình vuông Vigenère (hình dưới). Gồm 26 hàng, mỗi hàng dịch về bên trái một bước so với hàng phía trên, tạo thành 26 bảng mã Caesar. Trong quá trình mã hóa, tùy theo từ khóa mà mỗi thời điểm ta dùng một dòng khác nhau để mã hóa văn bản.
   Quá trình mã hóa và giải mã được thực hiện bằng công thức đại số Vigenar, công thức này chuyển đổi các chữ cái (AZ) thành các số (0-25).
Công thức mã hóa
      Ea = (Pa + Ka) mod 26
Công thức giải mã
      Da = (Ea - Ka) mod 26

   <img width="1013" height="655" alt="image" src="https://github.com/user-attachments/assets/f234e564-3ff1-410e-a260-fc676dc85d37" />




V. Playfair

1. Mã Playfair là một phương pháp mã hóa cổ điển, sử dụng một lưới chữ cái 5x5 để mã hóa từng cặp ký tự (digram) của văn bản thay vì từng ký tự đơn lẻ, do Charles Wheatstone phát minh vào năm 1854 và được đặt theo tên Lord Playfair để quảng bá. Phương pháp này giúp chống lại kỹ thuật phân tích tần suất đơn giản, làm cho mật mã khó giải mã hơn, bằng cách sử dụng các quy tắc hoán đổi dựa trên vị trí của hai ký tự trong hình chữ nhật tạo bởi chúng trong lưới. 
2. Các bước thực hiện mã hóa Playfair:
  Chuẩn bị từ khóa và lưới Playfair:
Chọn một từ khóa và viết các chữ cái của nó vào một lưới 5x5, bỏ qua các chữ cái trùng lặp. 
Điền các chữ cái còn lại của bảng chữ cái vào lưới theo thứ tự, bỏ qua chữ cái đã có trong từ khóa. (Lưu ý: Chữ "I" và "J" thường được gộp chung hoặc bỏ qua chữ cái thứ 26 trong bảng chữ cái để phù hợp với lưới 5x5). 
  Chia văn bản thuần túy thành các cặp:
Chia văn bản cần mã hóa thành các cặp hai ký tự. 
Nếu văn bản có một ký tự đơn lẻ ở cuối, thêm một ký tự "x" vào cuối. 
Nếu có hai ký tự giống nhau nằm liền kề trong một cặp, xen một ký tự "x" (hoặc ký tự khác) vào giữa hai ký tự đó. 
  Áp dụng quy tắc mã hóa:
Cùng dòng: Nếu hai ký tự nằm cùng một hàng, thay thế mỗi ký tự bằng ký tự ngay bên phải nó trên cùng hàng. Ký tự cuối cùng của hàng sẽ được thay bằng ký tự đầu tiên. 
Cùng cột: Nếu hai ký tự nằm cùng một cột, thay thế mỗi ký tự bằng ký tự ngay bên dưới nó trong cùng cột. Ký tự cuối cùng của cột sẽ được thay bằng ký tự đầu tiên. 
Khác dòng, khác cột: Nếu hai ký tự tạo thành một hình chữ nhật, thay thế mỗi ký tự bằng ký tự tương ứng nằm ở góc đối diện cùng dòng trên hình chữ nhật đó.


 <img width="1125" height="760" alt="image" src="https://github.com/user-attachments/assets/f54018a2-9836-4218-bdb3-29b1bb267759" />


   

  
