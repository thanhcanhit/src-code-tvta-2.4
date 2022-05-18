#include "canhlib.h"
#include <ctime>
#include <vector>
#include <iomanip>
#include <cstdlib>

#pragma comment(lib, "Winmm.lib")

struct Player {
	wstring name = L"";
	int score = 0;
	double time = 0;
	wfstream data;
	string fileName = ".\\data\\player.p";
};

static locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);  // khai báo kiểu đọc viết tiếng việt cho file 

// Khởi tạo player
Player player;

// Khởi tạo các biến dùng chung
int SCORE = 0, numVocabulary;
vector <wstring> Voca;

static int musicChoose = 0, numMusic = 5;
LPCWSTR musicName[] = { L".\\sounds\\fred_eddy_vietnam .wav", L".\\sounds\\tiec_tra_sao.wav", L".\\sounds\\time_to_love.wav", L".\\sounds\\nevada_piano.wav", L"NULL" };

void initData();
void readData();
void writeData();
void getSong();
void setSong();
void playSong();
void getAllVocabulary();
wstring getRandomVocabulary();
wstring getEnglish(wstring vocabulary);
wstring getVietnamse(wstring vocabulary);

void newPlayer();
void sayHiPlayer();
void changeName();

void credit();
void nameSoftware();
void mainMenu();
void libManager();
void typePlay();
void MCLayout(int mode = 1);
void FWLayout();
void multipleChoice(int mode = 1);
void fillWord();
void printQuestion(wstring realAnswer, wstring answer[], int mode = 1);
void highScore();
void setting();
void author();

void addVocabulary();
void appendLib(wstring en, wstring vi);
void delAllLib();
void viewLib();
void delOneVocabulary();
void saveVocabulary();


int main() {
	// set input output to wide text
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
	(void)_setmode(_fileno(stdin), _O_U16TEXT);

	// set random seed
	srand(static_cast<unsigned int>(time(NULL)));

	// set console default
	SetTitle(L"Học Từ Vựng Tiếng Anh");
	SetSize();
	system("COLOR F3");
	SetColor(aqua);
	offScroll();
	DrawBorderWindow();
	getSong();
	playSong();


	//testing

	// start ui
	credit();
	nameSoftware();
	initData();

	return 0;
}

void initData() {
	player.data.open(player.fileName, ios::in);

	// Check xem file có tồn tại không
	if (!player.data) {
		player.data.open(player.fileName, ios::out);
		newPlayer();
	}
	player.data.close();
	readData();
	if (player.name.length() == 0) {
		newPlayer();
	}
	else {
		getAllVocabulary();
		sayHiPlayer();
		mainMenu();
	}
}

void readData() {
	player.data.open(player.fileName, ios::in);
	player.data.imbue(loc);
	getline(player.data, player.name);
	player.data >> player.score >> player.time;
	player.data.close();
}

void writeData() {
	player.data.open(player.fileName, ios::out);
	player.data.imbue(loc);
	player.data << player.name << endl << player.score << ' ' << player.time;
	player.data.close();
}

void setSong() {
	ofstream file(".\\data\\setting.se");

	file << musicChoose;

	file.close();
}

void getSong() {
	ifstream file(".\\data\\setting.se");

	file >> musicChoose;

	file.close();
}

void playSong() {
	if (musicChoose < numMusic - 1) {
		PlaySound(musicName[musicChoose], NULL, SND_ASYNC | SND_LOOP);// phát nhạc lặp lại + trong nền 
	}
	else {
		PlaySound(NULL, NULL, 0);
	}
}
void sayHiPlayer() {
	system("color f3");

	// khởi tạo đối tượng để lấy thời gian
	tm current_time;
	time_t now = time(0);
	localtime_s(&current_time, &now);

	wstring hi = L"Chào buổi ";

	// lấy giờ hiện tại
	short current_hour = current_time.tm_hour;

	// đưa ra lời chào thích hợp vào các mốc thời gian
	if (current_hour >= 0 && current_hour < 5) hi = L"Ngủ thôi " + player.name + L" ơi, thức khuya thế này không tốt cho sức khỏe đâu nha!";
	else if (current_hour < 11) hi += L"sáng " + player.name + L", làm tách coffee cho tỉnh táo rùi học thoi nào!";
	else if (current_hour < 14) hi += L"trưa " + player.name + L", ngủ trưa rất tốt cho sức khỏe đó!";
	else if (current_hour < 17) hi += L"chiều " + player.name + L", làm tách coffee chiều thoi nào";
	else if (current_hour < 19) hi = L"Tầm giờ này ra ngắm hoàng hôn là tuyệt nhất đó " + player.name + L" ơi!!";
	else if (current_hour <= 23) hi += L"tối " + player.name + L", có giỏi thì làm tách coffee buổi tối rồi học từ vựng tiếp heh...";

	Notice(hi);
}

void newPlayer() {
	system("cls && color f3");
	DrawBorderWindow();

	// Hi
	int hiWord[] = { H, I, COMMA };
	PrintWordASCII(hiWord, 3, 44);

	int complete = 2; // false
	do {
		DelSomeLine(10, 20);
		onCursor();
		PrintCenter(L"Đây là lần đầu bạn sử dụng phần mềm, tên của bạn là gì?", 10);
		GoToPrint(40, 15, L"Tên tôi là: ");
		getline(wcin, player.name);

		DelSomeLine(10, 15);
		if (player.name.length() > 15) {
			PrintCenter(L"Tên ngắn ngắn thui, dưới 15 ký tự nha bạn ơi...", 12);
			(void)_getch();
		}
		else {
			offCursor();
			GoTo((WIDTH - player.name.length()) / 2 - 7, 10);
			wcout << L"Tên bạn là " << player.name << L" đúng chứ?";
			wstring confirm[] = { L"Đúng rồi", L"Nhập lại" };
			complete = PrintMenu(confirm, 2, 46, 14, 2);
		}
	} while (complete != 1);
	writeData();
	sayHiPlayer();
	mainMenu();
}


void credit() {
	system("cls && color fc");
	DrawBorderWindow();

	offScroll();
	offCursor();
	offSelect();

	int nameWord[] = { T, H, A, N, H, SPACE, C, A, N, H };
	PrintWordASCII(nameWord, 10, 10, 12);
	GoToPrint(85, 18, L"IUHer");

	Sleep(1200);
	onSelect();
	return;
}

void nameSoftware() {
	system("cls && color f3");

	DrawBorderWindow();
	offCursor();
	offSelect();

	// TU VUNG TIENG ANH 2.4
	int tuvungWord[] = { T, U, SPACE, V, U, N, G };
	PrintWordASCII(tuvungWord, 7, 20, 4);
	int tienganhWord[] = { T, I, E, N, G, SPACE, A, N, H };
	PrintWordASCII(tienganhWord, 9, 16, 14);
	int v2_4Word[] = { 2,DOT, 4 };
	PrintWordASCII(v2_4Word, 3, 40, 24);

	Sleep(1700);
	onSelect();
	system("cls");
	return;
}

void mainMenu() {
	system("cls && color fc");
	DrawBorderWindow();
	NormalConsole();
	offCursor();
	offSelect();

	SetColor(gray);
	GoToPrint(4, HEIGHT - 2, L"*Dùng phím mũi tên và phím Enter để chọn");


	// MENU
	SetColor(light_red);
	int menuWord[] = { M, E, N, U };
	PrintWordASCII(menuWord, 4, 32, 4);

	//Hi and Time
	tm crTime;
	time_t now = time(0);
	localtime_s(&crTime, &now);

	SetColor(light_white, gray);
	wstring sayHi = L" Chào, " + player.name + L" ";
	GoToPrint(4, 1, sayHi);

	wstring timeString;
	wstring weekDay[] = { L"Chủ Nhật", L"Thứ 2", L"Thứ 3", L"Thứ 4", L"Thứ 5", L"Thứ 6", L"Thứ 7" };
	wstring DMY = to_wstring(crTime.tm_mday) + L"/" + to_wstring(crTime.tm_mon + 1) + L"/" + to_wstring(crTime.tm_year + 1900);
	timeString = L" " + weekDay[crTime.tm_wday] + L", " + DMY + L" ";
	GoToPrint(78, HEIGHT - 2, timeString);

	// In menu
	wstring menu[] = { L"Học từ vựng ngay!", L"Quản lí từ vựng", L"Thành tích cao nhất", L"Cài đặt", L"Về tác giả", L"Thoát" };

	SetColor(gray, light_white);
	switch (PrintMenu(menu, 6, 40, 14)) {
	case 1:
		SetColor(light_red);
		getAllVocabulary();
		if (Voca.size() == 0) {
			Notice(L"Hiện tại bạn chưa có từ vựng nào hết, hãy vào \"Quản lí từ vựng\" để thêm nha!");
			mainMenu();
		}
		else if (Voca.size() < 4) {
			Notice(L"Bạn phải thêm ít nhất 4 từ để học nha bạn ơi, tiếp tục nàoo");
			mainMenu();
		}
		else typePlay();
		break;
	case 2:
		libManager();
		break;
	case 3:
		highScore();
		break;
	case 4:
		setting();
		break;
	case 5:
		author();
		break;
	case 6:
		exit(0);
		break;
	};
}

void libManager() {
	system("cls && color fc");
	NormalConsole();
	offScroll();
	offCursor();
	onSelect();

	DrawBorderWindow();

	int col = 18;
	// LIBRARY
	int libWord[] = { L, I, B, R, A, R, Y };
	PrintWordASCII(libWord, 7, 27);

	SetColor(gray);
	wstring lib[] = { L"Thêm từ vựng mới", L"Xem từ vựng của bạn", L"Xóa 1 từ vựng", L"Xóa hết từ vựng", L"Quay lại" };
	int choose = PrintMenu(lib, 5, 40, 13, 2);
	switch (choose) {
	case 1:
		addVocabulary();
		break;
	case 2:
		viewLib();
		break;
	case 3:
		delOneVocabulary();
		break;
	case 4:
		delAllLib();
		break;
	case 5:
		mainMenu();
		break;
	};
}

void getAllVocabulary() {
	//clean data before
	Voca.clear();

	wifstream lib(L".\\data\\library.ca");
	lib.imbue(loc);
	wstring tmp_string;

	while (getline(lib, tmp_string)) {
		Voca.push_back(tmp_string);
	}

	lib.close();
}

wstring getRandomVocabulary() {
	return Voca[rand() % Voca.size()];
}

wstring getEnglish(wstring vocabulary) {
	return vocabulary.substr(0, vocabulary.find(':'));
}

wstring getVietnamse(wstring vocabulary) {
	return vocabulary.substr(vocabulary.find(':') + 1);
}


void MCLayout(int mode) {
	system("cls");
	SetColor(gray);
	DrawRect(2, 1, 20, 3);
	DrawRect(76, 1, WIDTH - 2, 3);
	//cau hoi
	DrawRect2(2, 5, WIDTH - 2, 11);
	SetColor(light_white, gray);
	wstring question;
	if (mode == 1) {
		question = L" Từ này trong Tiếng Việt là: ";
	}
	else {
		question = L" Từ này trong Tiếng Anh là: ";
	}
	GoToPrint(4, 6, question);

	SetColor(green);
	GoToPrint(4, 2, L" Score: ");
	SetColor(gray);
	GoToPrint(77, 2, L" Time remaining: ");
	GoToPrint(43, HEIGHT - 1, L"*Chọn đáp án bằng các phím A, B, C, D hoặc 1, 2, 3, 4");


	// 4 ô
	SetColor(gray);
	DrawRect(2, 14, 48, 18);
	DrawRect(51, 14, WIDTH - 2, 18);
	DrawRect(2, 20, 48, 24);
	DrawRect(51, 20, WIDTH - 2, 24);

	// In 4 chữ đại diện đáp án
	SetColor(light_red);
	GoToPrint(4, 15, L"╔═╗");
	GoToPrint(4, 16, L"╠═╣");
	GoToPrint(4, 17, L"╩ ╩");
	GoToPrint(WIDTH - 6, 15, L"╔╗");
	GoToPrint(WIDTH - 6, 16, L"╠╩╗");
	GoToPrint(WIDTH - 6, 17, L"╚═╝");
	GoToPrint(4, 21, L"╔═╗");
	GoToPrint(4, 22, L"║");
	GoToPrint(4, 23, L"╚═╝");
	GoToPrint(WIDTH - 6, 21, L"╔╦╗");
	GoToPrint(WIDTH - 6, 22, L" ║║");
	GoToPrint(WIDTH - 6, 23, L"═╩╝");
}

void multipleChoice(int mode) {
	// xoá màn hình trước, in viền
	system("cls");
	offSelect();
	offCursor();
	offScroll();

	getAllVocabulary();
	MCLayout(mode);
	SetColor(gray);

	// Reset score
	SCORE = 0;
	double totalTime = 0;

	// sinh mạng
	bool life = true;

	// Còn thở là còn gỡ
	while (life == true) {

		// khởi tạo đáp án
		wstring answer[5];
		for (int i = 0; i < 4; i++) {
			// chắc rằng không có cái nào trùng nhau
			bool replace = false;
			do {
				replace = false;
				answer[i] = getRandomVocabulary();

				if (answer[i].empty()) replace = true;
				for (int j = i; j > 0; j--)
					if (answer[i] == answer[j - 1]) replace = true;
			} while (replace == true);
		}

		// chọn ngẫu nhiên một đáp án để hỏi
		wstring realAnswer = answer[rand() % 4];

		// in giao diện câu hỏi
		printQuestion(realAnswer, answer, mode);

		// Nhận đáp án từ người dùng
		SetColor(light_white, gray);
		GoToPrint(40, 26, L" Bạn Chọn ");
		char reply = 'o';

		// không nhập sẽ thua
		life = false;

		// in thời gian ban đầu
		int time = 10;
		SetColor(green, light_white);
		GoTo(94, 2); wcout << time;

		// nhận đáp án từ người dùng mỗi 0.1s, mỗi một giây in lại time
		int count = 1;
		while (time > 0) {
			//dừng 0.1 s
			totalTime += 0.1;
			count++;
			Sleep(100);

			if (count % 10 == 0) {
				// vì 10 - 0 + 1 = 11 nên để v cho nó chuẩn
				count -= 8;
				time--;
				if (time >= 7) SetColor(green);
				else if (time >= 3) SetColor(yellow);
				else SetColor(red);
				GoToPrint(94, 2, L"  ");
				GoTo(94, 2); wcout << time;
				Sleep(100);
			}

			// nếu ng dùng nhập cái gì đó sẽ đem đi xử lí và thoát khỏi đây
			if (_kbhit()) {
				DelLine(HEIGHT - 1);
				reply = _getch();
				life = true; // đã ấn nên tạm thời cho sống lại
				break;
			}
		}

		// Xử lí kết quả
		int indexReply;
		SetColor(light_white, gray);
		GoToPrint(54, 26, L"   ");
		GoTo(55, 26);

		switch (reply) {
		case '1':
		case 'a':
		case 'A':
			indexReply = 0;
			wcout << 'A';
			break;
		case '2':
		case 'b':
		case 'B':
			indexReply = 1;
			wcout << 'B';
			break;
		case '3':
		case 'c':
		case 'C':
			indexReply = 2;
			wcout << 'C';
			break;
		case '4':
		case 'd':
		case 'D':
			indexReply = 3;
			wcout << 'D';
			break;
		default:
			indexReply = 4;
			SetColor(green, light_white);
			DelLine(26);

			if (reply == 'o' || reply == '\n') {
				SetColor(red, light_white);
				GoToPrint(46, 26, L"Hết giờ!!");
			}
			else {
				SetColor(gray);
				GoTo(22, 26);
				if (reply != 13) wcout << reply; // loại trừ phím enter
				wcout << L" là seo, bạn hãy nhập a, b, c, d hoặc 1, 2, 3, 4!";
			}
			break;
		}
		SetColor(gray, light_white);

		// kiểm tra đúng sai
		if (getVietnamse(answer[indexReply]) == getVietnamse(realAnswer)) {
			// nếu đúng + điểm chơi tiếp
			SetColor(green);
			PrintCenter(L"Bạn đã trả lời đúng, bạn được cộng 10 điểm !!", 30);

			if (SCORE == 0) GoTo(15, 2); else GoTo(17 + SCORE / 100, 2); // hiển thị cho chính xác
			GoToPrint(22, 2, L"+ 10");
			SCORE += 10;

			// đợi 1 chút r xoá 1 số chỗ
			Sleep(600);
			GoToPrint(22, 2, L"        ");
			DelSomeLine(26, 32);
		}
		else { // Trả lời sai thì kết thúc
			life = false;

			// in ra đáp án chính xác
			wstring dap_an = getVietnamse(realAnswer);
			SetColor(black);
			GoToPrint(50 - (dap_an.length() + 22) / 2, 28, L"Nghĩa của từ trên là ");
			SetColor(green);
			wcout << "\"" << dap_an << "\"";

			// Thông báo số câu trả lời đúng
			SetColor(green);
			if (SCORE > player.score || SCORE == player.score && totalTime < player.time) {
				GoTo(24, 30);
				player.score = SCORE;
				player.time = totalTime;
				writeData();
				wcout << L"Chúc mừng, Bạn đã tiến bộ hơn trước đó với " << SCORE / 10 << L" từ trong " << setprecision(2) << totalTime << L"s";
			}
			else if (SCORE / 10 >= 5) {
				GoTo(27, 32);
				wcout << L"Chúc mừng bạn đã trả lời đúng " << SCORE / 10 << L" câu liên tiếp !!!";
			}

			(void)_getch();
			// hỏi ng ta muốn chơi lại không
			SetColor(light_green);
			if (Confirm(L"Bạn có muốn thử lại không?") == 1) multipleChoice(mode);
			else typePlay();
		}
	}
}


void printQuestion(wstring realAnswer, wstring answer[], int mode) {
	// xoá điểm cũ, in điểm mới
	GoToPrint(13, 2, L"      ");
	SetColor(green);
	GoTo(13, 2);
	wcout << SCORE;

	SetColor(gray);
	// xoá câu hỏi, đáp án trước
	GoTo(3, 8);
	for (int i = 0; i < 94; i++) {
		wcout << ' ';
	}
	GoTo(8, 16); for (int i = 0; i <= 39; i++) wcout << ' ';
	GoTo(8, 22); for (int i = 0; i <= 39; i++) wcout << ' ';
	GoTo(52, 16); for (int i = 0; i <= 40; i++) wcout << ' ';
	GoTo(52, 22); for (int i = 0; i <= 40; i++) wcout << ' ';

	// in câu hỏi 
	SetColor(light_white, aqua);
	wstring question;
	if (mode == 1) question = L" " + getEnglish(realAnswer) + L" ";
	else question = L" " + getVietnamse(realAnswer) + L" ";
	PrintCenter(question, 8);

	// in lần lượt mỗi lần 2 đáp án theo chiều ngang
	SetColor(black);
	wstring choice;
	// 5 - > 47, 51 -> 91 -> 40
	for (int i = 0, y = 16; i < 4; i += 2, y += 6) {
		if (mode == 1) choice = getVietnamse(answer[i]);
		else choice = getEnglish(answer[i]);
		GoToPrint(26 - choice.length() / 2, y, choice);

		if (mode == 1) choice = getVietnamse(answer[i + 1]);
		else choice = getEnglish(answer[i + 1]);
		GoToPrint(74 - choice.length() / 2, y, choice);
	}

	return;
}

void highScore() {
	readData(); // chắc rằng dữ liệu luôn đúng

	system("cls");
	SetColor(light_red);
	DrawBorderWindow();

	int hsRow = 5, hsCol = 5;
	// HIGH
	int hsWord[] = { H, I, G, H, SPACE, S, C, O,R,E };
	PrintWordASCII(hsWord, 10, 15, 5);

	SetColor(gray);
	wstring hs = L"Điểm cao nhất của " + player.name + L" đây nè:";
	PrintCenter(hs, 15);

	int highScore = player.score;
	int fisrt = highScore / 1000 % 10, second = highScore / 100 % 10, thirst = highScore / 10 % 10, four = highScore % 10;

	int col = 28, row = 18;
	SetColor(gray, gray);
	DrawRect(28, row + 7, 72, row + 8);
	SetColor(gray, light_white);
	GoToPrint(WIDTH - 30, HEIGHT - 2, L"♦ Ấn phím bất kỳ để tiếp tục");

	SetColor(light_red);

	// NHAP NHAY CAC THU
	while (!_kbhit()) {
		DelSomeLine(18, 23);
		Sleep(500);
		// 4 Ô ĐIỂM
		PrintCharASCII(BIGCHAR[fisrt], col, row);
		PrintCharASCII(BIGCHAR[second], col + 12, row);
		PrintCharASCII(BIGCHAR[thirst], col + 24, row);
		PrintCharASCII(BIGCHAR[four], col + 36, row);
		Sleep(700);
	}
	char tmp = _getch();
	mainMenu();
}

void setting() {
	system("cls && color fc");
	DrawBorderWindow();

	int setCol = 25;
	// SETTING
	int settingWord[] = { S, E, T, T, I, N, G };
	PrintWordASCII(settingWord, 7, 25, 3);

	wstring settingMenu[] = { L"Âm nhạc: ", L"Đổi tên người dùng", L"Xóa điểm cao nhất", L"Trở về menu" };
	wstring music[] = { L" Fred Eddy ", L" Tiệc trà sao ", L" Time to love ", L" Nevada Piano ",  L" Tắt nhạc " };
	SetColor(light_white, gray);
	GoToPrint(51, 12, music[musicChoose]);

	SetColor(gray, light_white);
	switch (PrintMenu(settingMenu, 4, 40, 12, 2)) {
	case 1:
		musicChoose += 1;
		if (musicChoose >= numMusic) musicChoose -= numMusic;
		playSong();
		system("exit");
		setSong();
		setting();
		break;
	case 2:
		changeName();
		break;
	case 3:
		SetColor(light_red);
		if (Confirm(L"Bạn có muốn xóa thành tích cao nhất của mình không?") == 1) {
			player.score = 0;
			player.time = 0;
			writeData();
		}
		setting();
		break;
	default:
		mainMenu();
		return;
	}
}

void changeName() {
	system("cls && color fc");
	DrawBorderWindow();

	// RENAME
	int renameWord[] = { R, E, N, A, M, E };
	PrintWordASCII(renameWord, 6, 24);

	int complete = 2; // false
	do {
		DelSomeLine(10, 20);
		onCursor();
		PrintCenter(L"Bạn muốn đổi tên thành gì đếy?", 10);
		GoToPrint(40, 15, L"Tên tôi là: ");
		wstring tmp_name;
		getline(wcin, tmp_name);

		DelSomeLine(10, 15);
		if (player.name.length() > 15) {
			PrintCenter(L"Tên ngắn ngắn thui, dưới 15 ký tự nha bạn ơi...", 12);
			(void)_getch();
		}
		else {
			offCursor();
			GoTo((WIDTH - tmp_name.length()) / 2 - 12, 10);
			wcout << L"Bạn muốn đổi tên thành " << tmp_name << L" đúng chứ?";
			wstring confirm[] = { L"Đúng rồi", L"Nhập lại", L"Không đổi tên nữa" };
			complete = PrintMenu(confirm, 3, 42, 14, 2);
			if (complete == 3) {
				system("exit");
				setting();
				return;
			}
			else if (complete == 1) {
				player.name = tmp_name;
			}
		}
	} while (complete != 1);
	writeData();
	sayHiPlayer();
	mainMenu();
}

void author() {
	system("cls && color fc");
	DrawBorderWindow();
	onSelect();

	int col = 28;
	// AUTHOR
	int authorWord[] = { A, U, T, H, O, R };
	PrintWordASCII(authorWord, 6, 28);

	// INFOMATIONS
	PrintCenter(L"Nguyễn Thanh Cảnh - 2003 - Gia Lai", 12);
	SetColor(gray);
	PrintCenter(L"Học tại Đại Học Công Nghiệp K17 - KTPM", 14);
	SetColor(blue);
	PrintCenter(L"Facebook: https://www.facebook.com/Canh.IUH.IT/", 16);
	SetColor(aqua);
	PrintCenter(L"Website: https://thanhcanh203c.github.io/library/", 18);
	SetColor(purple);
	PrintCenter(L"Có ý tưởng, góp ý hay nhận xét chi đó cứ nhắn tin fb mình he", 20);
	SetColor(yellow);
	PrintCenter(L"Cảm ơn bạn đã tải và sử dụng phần mềm này của mình ( •̀ ω •́ )y", 22);

	SetColor(gray);
	while (!_kbhit()) {
		PrintCenter(L"Nhấn phím bất kỳ để trở về Menu", 26);
		Sleep(500);
		DelLine(26);
		Sleep(500);
	}
	mainMenu();
}

void addVocabulary() {
	system("cls && color fc");
	DrawBorderWindow();
	onCursor();

	int addCol = 38;
	// ADD
	int addWord[] = { A, D, D };
	PrintWordASCII(addWord, 3, 38);

	SetColor(gray);
	DrawRect(4, 10, WIDTH / 2 - 4, 20);
	DrawRect(WIDTH / 2 + 4, 10, WIDTH - 4, 20);

	SetColor(light_red);
	GoToPrint(20, 11, L"ENGLISH");
	GoToPrint(70, 11, L"VIETNAMSE");

	SetColor(white, gray);
	GoToPrint(5, 11, L" 1 ");
	GoToPrint(WIDTH / 2 + 5, 11, L" 2 ");
	SetColor(gray, light_white);
	GoToPrint(10, 13, L"Nhập từ Tiếng Anh bạn muốn thêm:");
	GoToPrint(WIDTH / 2 + 10, 13, L"Nhập nghĩa Tiếng Việt của từ ấy: ");

	wstring mn[] = { L"Thêm ngay!", L"Nhập lại", L"Không thêm nữa" };
	wcin.clear();
	wstring en, vi;
	SetColor(black);
	do {
		GoTo(8, 15);
		getline(wcin, en);
	} while (en.empty());
	do {
		GoTo(WIDTH / 2 + 8, 15);
		getline(wcin, vi);
	} while (vi.empty());

	// Standard string
	StandardWString(en);
	StandardWString(vi);

	wstring quest = L"Bạn muốn thêm từ \"" + en + L" : " + vi + L"\" vào thư viện không?";
	PrintCenter(quest, 23);
	switch (PrintMenu(mn, 3, 60, 25))
	{
	case 1:
		appendLib(en, vi);
		break;
	case 2:
		system("exit");
		addVocabulary();
		break;
	default:
		break;
	}
	libManager();
}

void appendLib(wstring en, wstring vi) {
	wofstream lib(".\\data\\library.ca", ios::app);
	lib.imbue(loc);
	lib << en << L":" << vi << endl;
	lib.close();
}

void delAllLib() {
	if (Confirm(L"Bạn có muốn xóa toàn bộ từ vựng của mình không ?") == 1) {
		wofstream lib(".\\data\\library.ca", ios::out);
		lib.imbue(loc);
		lib.close();
		Notice(L"Đã xóa toàn bộ từ vựng của bạn :D");
	};

	libManager();
}

void viewLib() {
	system("cls && color f8");
	getAllVocabulary();

	onScroll();
	offCursor();

	SetColor(light_red);
	int yourWord[] = { Y, O, U, R, SPACE, L, I, B, R, A, R, Y };
	PrintWordASCII(yourWord, 12, 4);

	if (Voca.size() == 0) {
		int isEmptyWord[] = { I, S, SPACE, E, M, P, T, Y, EXCLAMATION };
		PrintWordASCII(isEmptyWord, 9, 17, 10);
	}
	else {
		unsigned int maxLength = 0;
		const int xStart = 20, yStart = 10;
		int y = 12;

		for (unsigned int i = 0; i < Voca.size(); i++) {
			if (i & 1) SetColor(black);
			else SetColor(red);

			GoTo(xStart + 2, y);
			wcout << i + 1 << L'.';
			wstring tmp_voca = getEnglish(Voca.at(i)) + L" : " + getVietnamse(Voca.at(i));
			GoToPrint(xStart + 7, y, tmp_voca);

			y += 2;
			if (tmp_voca.length() > maxLength) maxLength = tmp_voca.length();
		}

		SetColor(gray);
		int xEnd = maxLength + xStart + 6;
		if (xEnd < 80) xEnd = 80;
		DrawRect2(xStart, yStart, xEnd, (Voca.size() + 1) * 2 + yStart);
		GoTo(0, 0);
	}

	(void)_getch();
	NormalConsole();
	libManager();
}

void delOneVocabulary()
{
	system("cls && color f8");
	getAllVocabulary();
	onScroll();
	onCursor();

	SetColor(light_red);
	int yourWord[] = { Y, O, U, R, SPACE, L, I, B, R, A, R, Y };
	PrintWordASCII(yourWord, 12, 4);

	if (Voca.size() == 0) {
		int isEmptyWord[] = { I, S, SPACE, E, M, P, T, Y, EXCLAMATION };
		PrintWordASCII(isEmptyWord, 9, 17, 10);
		(void)_getch();
	}
	else {
		unsigned int maxLength = 0;
		const int xStart = 20, yStart = 20;
		int y = yStart + 2;

		for (unsigned int i = 0; i < Voca.size(); i++) {
			if (i & 1) SetColor(black);
			else SetColor(red);

			GoTo(xStart + 2, y);
			wcout << i + 1 << L'.';
			wstring tmp_voca = getEnglish(Voca.at(i)) + L" : " + getVietnamse(Voca.at(i));
			GoToPrint(xStart + 7, y, tmp_voca);

			y += 2;
			if (tmp_voca.length() > maxLength) maxLength = tmp_voca.length();
		}

		SetColor(gray);
		int xEnd = maxLength + xStart + 6;
		if (xEnd < 80) xEnd = 80;
		DrawRect2(xStart, yStart, xEnd, (Voca.size() + 1) * 2 + yStart);
		GoTo(0, 0);

		SetColor(gray);
		int inputX = 25;
		DrawRect(inputX, 10, 75, 18);
		SetColor(light_white, gray);
		GoToPrint(inputX + 5, 11, L" Nhập vào STT của từ muốn xóa: ");
		SetColor(red, light_white);
		GoToPrint(inputX + 3, 14, L"Bạn chọn từ số: ");
		SetColor(gray);
		GoToPrint(inputX + 3, 19, L"*Nhập 0 để quay lại");

		unsigned int choose = 0;
		do {
			SetColor(black);
			GoTo(inputX + 19, 14);
			wcout << L"          ";
			GoTo(inputX + 19, 14);
			wcin >> choose;
			SetColor(light_red);
			if (choose < 1 || choose > Voca.size()) GoToPrint(24, 16, L"Không cóa!");
			if (choose == 0) {
				libManager();
				return;
			}
		} while (choose < 1 || choose > Voca.size());

		wstring vocaChoose = Voca.at(choose - 1);
		SetColor(red);
		wstring confirmQuest = L"Bạn thật sự muốn xóa từ \"" + vocaChoose + L"\" chứ?";

		if (Confirm(confirmQuest) == 1) {
			wstring noticeComplete = L"Đã xóa thành công \"" + vocaChoose + L"\"";
			Voca.erase(Voca.begin() + choose - 1);
			saveVocabulary();
			Notice(noticeComplete);
		}
	}

	NormalConsole();
	offScroll();
	libManager();
}

void saveVocabulary() {
	wofstream lib(".\\data\\library.ca", ios::out);
	lib.imbue(loc);

	vector<wstring>::iterator p;
	for (p = Voca.begin(); p < Voca.end(); p++) {
		lib << *p << endl;
	}

	lib.close();
}

void typePlay() {
	system("cls && color fc");
	DrawBorderWindow();
	offCursor();
	offScroll();

	int learnWord[] = { L, E, A, R, N };
	PrintWordASCII(learnWord, 5, 32, 3);

	SetColor(light_white, gray);
	PrintCenter(L" Bạn hãy chọn kiểu để học: ", 12);

	SetColor(gray, light_white);
	wstring typePlay[] = { L"Trắc nghiệm Tiếng Anh", L"Trắc nghiệm Tiếng Việt", L"Điền từ Tiếng Anh",  L"Trở về menu" };
	switch (PrintMenu(typePlay, 4, 38, 14)) {
	case 1:
		multipleChoice();
		break;
	case 2:
		multipleChoice(2);
		break;
	case 3:
		fillWord();
		break;
	default:
		mainMenu();
		return;
		break;
	}
}

void fillWord() {
	getAllVocabulary();
	system("cls && color fc");
	DrawBorderWindow();
	FWLayout();
	onCursor();
	onSelect();

	vector<wstring> lastQ;

	SCORE = 0;

	bool life = true;

	while (life) {
		if (lastQ.size() == Voca.size()) {
			PrintCenter(L"Wao, bạn đã học được hết số từ vựng trong thư viện", 26);
			break;
		}
		wstring answer;
		bool repeat;
		do {
			repeat = false;
			answer = getRandomVocabulary();
			for (unsigned int i = 0; i < lastQ.size(); i++) {
				if (lastQ[i] == answer) {
					repeat = true;
					break;
				}
			}
		} while (repeat);
		lastQ.push_back(answer);

		GoToPrint(13, 2, L"      ");
		SetColor(green);
		GoTo(13, 2);
		wcout << SCORE;
		wstring question = L" " + getVietnamse(answer) + L" ";
		SetColor(light_white, light_white);
		DelLine(8, 3);
		SetColor(light_white, aqua);
		PrintCenter(question, 8);
		SetColor(black, light_white);
		DelLine(21, 11, WIDTH - 11);
		DelLine(14);

		wstring input = L"";
		PrintCenter(input, 21);
		WCHAR c = L' ';
		do {
			c = _getch();
			if (c != 13 && c != 8) input += c;
			if (c == 8 && input.size() > 0) input.pop_back();
			DelLine(21, 11, WIDTH - 11);
			PrintCenter(input, 21);
		} while (c != 13);

		// Check
		if (!input.empty()) StandardWString(input);
		wstring en = getEnglish(answer);
		StandardWString(en);
		if (en == input) {
			SCORE += 10;
			SetColor(green);
			PrintCenter(L" Correct! ", 14);
			Sleep(500);
		}
		else {
			SetColor(light_red);
			offCursor();
			wstring notice = L"Đáp án đúng là: " + en;
			PrintCenter(notice, 14);
			DelLine(21, 11, WIDTH - 11);
			GoTo(WIDTH / 2 - input.size() / 2, 21);
			for (unsigned int i = 0; i < input.size(); i++) {
				if (i > en.size() - 1) SetColor(light_red);
				else if (input[i] != en[i]) SetColor(light_red);
				else (SetColor(light_green));
				wcout << input[i];
			}
			SetColor(gray);
			for (unsigned int i = input.size(); i < en.size(); i++) {
				wcout << en[i];
			}
			life = false;
		}
		DelLine(HEIGHT - 1);
	}

	SetColor(green);
	if (SCORE > player.score) {
		GoTo(20, 28);
		player.score = SCORE;
		writeData();
		wcout << L"Chúc mừng, Bạn đã tiến bộ hơn trước đó với " << SCORE / 10 << L" từ đúng liên tiếp!";
	}

	(void)_getch();
	if (Confirm(L"Bạn có muốn thử lại không?") == 1) fillWord();
	else typePlay();

	return;
}


void FWLayout() {
	system("cls");
	SetColor(gray);
	DrawRect(2, 1, 20, 3);
	//cau hoi
	DrawRect2(2, 5, WIDTH - 2, 11);
	SetColor(light_white, gray);
	wstring question = L" Điền từ tiếng anh cúa ";
	GoToPrint(4, 6, question);
	PrintCenter(L" Đáp án của bạn là: ", 18);

	SetColor(green);
	GoToPrint(4, 2, L" Score: ");

	SetColor(black);
	DrawRect(10, 17, WIDTH - 10, 24);

	SetColor(light_red);
	GoToPrint(50, HEIGHT - 1, L"*Bạn chỉ cần nhập chữ thường, không cần in hoa");
}