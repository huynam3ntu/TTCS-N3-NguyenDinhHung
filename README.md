# I. Phân tích bài toán
	Để đơn giản hóa việc xử lý các phép toán, đề tài này sẽ xử lý các phép toán liên quan đến số nguyên.
	Nếu chúng ta xem xét về giới hạn (số các chữ số có thể có) của các kiểu dữ liệu số nguyên trong C/C++,
	ví dụ như:
		int: khoảng 10 mũ 9
		long int: khoảng 10 mũ 12
		long long int khoảng 10 mũ 18
	Có thể thấy, chúng ta chỉ có thể lưu trữ tối đa 10 mũ 18 số nguyên, tức là chỉ một số có tối đa 19 chữ số.
  Vấn đề xảy ra nếu chúng ta phải đối phó với các số lớn hơn 19 chữ số. Hay nói các khác là vấn đề về việc tràn số!
# II. Tìm hiểu giải thuật
  Để lưu trữ các chữ số lớn hơn 19 chữ số, thông thường người ta sẽ lưu trữ số nguyên theo 3 cách:
1. Xâu ký tự hoặc mảng xâu: Trong đó, mỗi ký tự của một chuỗi tương ứng với một chữ số của số nguyên lớn tính từ trái sang phải.
2. Mảng các số: Sử dụng mảng để lưu trữ các chữ số (nhóm các chữ số), và một biến ghi nhận số chữ số để thuận tiện trong quá trình xử lý.
3. Danh sách liên kết các số: Sử dụng danh sách liên kết các chữ số (nhóm các chữ số), cách này sẽ linh hoạt hơn đối với việc sử dụng bộ nhớ.
  Chúng ta sẽ thực hiện lưu trữ số lớn bằng cách khai báo cấu trúc struct, trong đó có một biến để biểu diễn dấu của số nguyên lớn (âm / dương).
  Tiếp đó là một số hàm tạo nhận các đối số khác nhau cho kiểu dữ liệu bigint.
	Mỗi phần tử của vector a sẽ lưu một đoạn của số nguyên lớn – đoạn đó nhiều nhất sẽ có 9 chữ số. Như vậy, 1 số nguyên lớn có 90 chữ số chỉ cần sử dụng vector có kích thước size là 10. 
# III. Tìm hiểu công cụ lập trình
- Công cụ lập trình sử dụng: DEV-C++ / Visual Studio.

