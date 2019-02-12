//struct lưu trữ thông tin khối gạch
typedef struct {
    int **arr, Row, Col;  //ma trận khối gạch, số hàng, số cột
    int SRow, SCol;       //vị trí của khối gạch đó trong bảng toạ độ
} block;

//struct lưu trữ thông tin người chơi
typedef struct {
    char name[100] = "";
    int score, level, time;
} Player;

//Nhập tên người chơi mới
//Trả về 1 nếu người dùng nhấn Enter (bắt đầu game),
//trả về 0 nếu người dùng bấm Esc (thoát nhập tên, trở về Menu chính)
bool EnterName(Player *pplay);

//Vẽ khung viền khu vực chơi, các bảng thông báo trước lúc game bắt đầu
void DrawBorder();

//Vẽ tất cả các khối gạch hiện tại trong vùng gamezone
void Display();

//Kiểm tra nếu khối gạch vẫn còn trong vùng gamezone
int Inside(int i, int j);

//Kiểm tra có thể dịch trái được hay không
int Left(int i, int j);

//Kiểm tra có thể dịch phải được hay không
int Right(int i, int j);

//Kiểm tra có thể di chuyển xuống được hay không
int Down(int i, int j);

//Dịch toàn bộ khối gạch về phía trái 1 ô
void LeftMove (block *pblock);

//Dịch toàn bộ khối gạch về phía phải 1 ô
void RightMove (block *pblock);

//Dịch toàn bộ khối gạch về bên dưới 1 ô
bool DownMove (block *pblock);

//Kiểm tra có thể xoay khối gạch được hay không,
//nếu được thì xoay khối gạch và cập nhật lại thông tin của khối gạch đó
void BlockTurning (block *pblock);

//Vẽ khối gạch ra màn hình
void DrawBlock (block *pblock, int color);

//Xoá khối gạch
void EraseBlock (block *pblock);

//Random khối gạch
int BlockType();

//Khởi tạo thông tin khối gạch qua ID random được từ hàm BlockType()
block *BlockBuilding (int ID);

//Khi một khối gạch ngừng di chuyển, cập nhật vào ma trận toạ độ
void Update (block *pblock, int color);

//Kiểm tra game (0 - game over, 1 - still alive)
//Tính điểm và cập nhật thông tin người chơi
bool GameChecking (block *pblock, Player *pplay);

//Huỷ cấp phát bộ nhớ cho khối gạch
void BlockDeleting (block *pblock);

//Khởi tạo thông tin người chơi
void initPlayer (Player *pplay);

//Hiển thị thông tin ở 3 bảng thông báo
void AddInfo(Player *pplay, int extrapoints, bool check);

//Tính và hiển thị thông tin về thời gian chơi
void AddTime (Player *pplay);

//Vẽ khối gạch kế tiếp ở bảng thông báo
void DrawNextBlock (block *nextblock, int nextcolor);

//Xoá khối gạch kế tiếp ở bảng thông báo
void EraseNextBlock (block *nextblock);


/*-------REVERSE LEVEL-------*/


//Đảo ngược ma trận toạ độ và ma trận màu
void ReverseMatrix();

//Các hàm sau đây có chức năng tương tự như các hàm ở level thường,
//nhưng vì level Reverse nó "ngược ngược" nên em code riêng ra cho tiện :)

block *ReverseBlockBuilding (int ID);

void ReverseDrawBlock (block *pblock, int color);

void ReverseEraseBlock(block *pblock);

int ReverseDown (int i, int j);

bool ReverseDownMove (block *pblock);

bool ReverseGameChecking (block *pblock, Player *pplay);

void ReverseDisplay();

//------------------------

//Đếm ngược (3, 2, 1) trước khi bắt đầu chơi
void CountDown();

//Xử lí khi trong quá trình chơi người dùng nhấn phím ESC
bool ESC_handle(Player *pplay);

//Lưu thông tin người chơi ra file khi người dùng thoát và chọn save game
bool Write(Player *pplay, bool check);

//Lấy thông tin người chơi từ file SavedGame.txt
void GetInfo(Player *pplay);

//Xử lí khi game over, cho người dùng lựa chọn xem Scoreboard hoặc trở về màn hình chính
void EndGame(Player *pplay);
