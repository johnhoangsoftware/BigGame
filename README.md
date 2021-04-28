# Game SpaceShooter
``` 
Nguyễn Việt Hoàng - 20020196.
Bài tập lớn của lớp lập trình nâng cao INT2215_2.
Sử dụng C / C ++, SDL2, SDL_ttf , SDL_image, SDL_mixer thư viện phát triển trên Code :: Blocks .
```
## Hướng dẫn cài đặt
1. Cài đặt:
- Chương trình sử dụng file project của Code::Blocks.
- Hày tải xuống đầy đủ [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) và các thư viện [SDL2](https://www.libsdl.org/), [SDL_image](https://www.libsdl.org/projects/SDL_image/), [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/), [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) bản tương thích với thiết bị được sử dụng.
- Tải thư mục BigGame và một trong 2 tệp trong thư mục SDL nếu chưa có: Trên Github https://github.com/johnhoangsoftware/BigGame trong mục "Code" , chọn "Download zip".
- Sửa lại đường dẫn vào file SDL:
	+ Nếu bạn chưa có sẵn các thư viện liên kết (các file .dll) trong System, hãy lấy chúng từ SDL2/bin và thả vào thư mục System32 (với máy 32 bit)/SysWOW64 (với máy 64 bit).
	+ Mở AgainBigGame.cbp bằng Code::Blocks, trong Project/Build options/Search directories/Compiler xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục include/SDL2.
					   trong Linkers xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục lib ứng với các thư viện trên.
  + Trong phần Other linker options trong Project/Build options/Linker settings ghi đầy đủ:
			-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
			
2. Chạy chương trình:
- Chọn Build/Build and run trên thanh điều khiển (hoặc ấn F9) để build và chạy chương trình.

## Các chức năng
1. Màn hình Menu: 
- Bắt đầu vào game bằng ấn nút Play hoặc phím cách trên bàn phím.
- Có 2 cách tắt chương trình: sử dụng nút tắt ở cửa sổ hoặc nút Exit ở Menu.
2. Màn hình chơi:
- Các đối tượng:
	+ Máy bay (màu xanh) do người chơi điều khiển.
	+ Các máy bay địch xuất hiện và xả đạn tấn công.
- Số điểm đang có và số mạng ở góc trên phía trái màn hình.
- Tốc độ sẽ tằng dần theo sô điểm bạn đạt được.
3. Màn hình kết thúc game:
- Có thể thực hiện 2 thao tác:
	+ Ấn nút PlayAgain để chơi lại ván mới.
	+ Ấn nút Exit để thoát game. 
## Hướng dẫn chơi
- Các bạn điều khiển máy bay (màu xanh) tránh các máy bay và đạn của địch, click chuột để bắn đạn tiêu diệt máy bay địch, với mỗi chiếc máy bay bị tiêu diệt bạn sẽ được thêm một điểm
- Dùng các phím mũi tên để điều khiển máy bay (màu xanh) 
- Bắn đạn:
+ Click chuột trái để bắn đạn Sphere.
+ Click chuột phải để bắn đạn Laser.  
## Nguồn tham khảo và tài nguyên game
- Chương trình được xây dựng trên  [Code::Blocks](https://www.codeblocks.org/). 
- Các thư viện [SDL](https://www.libsdl.org/).
- Tất cả các hình ảnh trong game được tải xuống từ Google Image.
- https://lazyfoo.net/tutorials/SDL/
- https://phattrienphanmem123az.com/
- Video demo: 
