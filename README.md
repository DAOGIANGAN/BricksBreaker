# BricksBreaker
1.	Lấy ý tưởng từ game BRICKS BREAKER.
2.	Các phần của chương trình:  
  a.	Common.h: nơi khai báo các thông số không đổi ( kích thước mà hình , số khung hình trên giây ..), một số struct cần thiết cho các phần sau .  
  b.	Header : nơi khai báo các biến toàn cục cảu cả game mà khi cần có lấy trực tiếp để sử dụng.   
  c.	BaseObject: là như chương trình mẹ để lấy các thông số của hình ảnh để in nó lên màn hình game.   
  d.	MainObject : kế thừa một phần của BASEOBJECT để in hình ảnh thanh đỡ lên màn hình, và có thêm một số hàm để điều khiển thanh đỡ , kiểm tra va chạm giữa thanh đỡ và rìa bản đồ ( có một hàm setclip() em định cải tiến thêm hiệu ứng thanh đỡ cho bản 2, hiện tại chưa dùng tới ).  
  e.	Game_map: dùng kĩ thuật tilemap (tham khảo trên youtube) để lưu vị trí các viên gạch trên map theo màu định sẵn.  
  f.	BallObject : kế thừa một phần của MainObject , có nhiệm vụ là khai báo vận tốc , góc nảy tối đa của quả bóng, sử lí va chạm giữa quả bóng với thanh đỡ , rìa bản đồ và các viên gạch, kiểm tra thua hay thắng.  
  g.	Imptimer : lấy các mốc thời gian , để cho vào hàm main cài đặt độ trễ cho các đối tượng trong một vòng lặp .  
  h.	TextObject: lấy font chữ , vị trí , màu … chữ cần thiết trong game. 
  i.	Menu: phần hiện khi bắt đầu game , khi thua hoặc khi thắng , sử lí đổi màu các chữ khi di chuột vào và trả về một biến (VD : S_MENU ,..) là các biến cần thiết để vào hàm main dùng.  
3.	Hướng cải tiến trong tương lai:   
  a.	Thêm hiệu ứng cho thanh đỡ.   
  b.	Thêm một số vật phẩm rơi ra khi viên gạch vỡ.   
  c.	Thêm một số màn chơi thú vị hơn thay vì 3 màn như hiện tại.   
