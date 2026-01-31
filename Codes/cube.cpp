/*
22-1학기 EEE2020 데이터구조 End-Term Project
Queue를 이용한 Rubik's Cube Solving - OP Algorithm 구현
2020132002 물리학과
전현빈(justbecoz@yonsei.ac.kr)
2022/05/10 ~ 2022/06/09
*/

// Cube Class 구현 .cpp File

#include <windows.h>
#include "cube.h"

char** setcubeface(char color) {
	char** cube = new char*[4];
	for (int i = 0; i < 3; i++) {
		cube[i] = new char[4];
		for (int j = 0; j < 3; j++) {
			cube[i][j] = color;
		}
	}
	return cube;
}

void scolor(unsigned short text = 15, unsigned short back = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

Cube::Cube() {
	up = setcubeface('W');
	down = setcubeface('Y');
	front = setcubeface('G');
	back = setcubeface('B');
	left = setcubeface('O');
	right = setcubeface('R');

	up_speffz = new char* [3];
	for (int i = 0; i < 3; i++) up_speffz[i] = new char[3];
	down_speffz = new char* [3];
	for (int i = 0; i < 3; i++) down_speffz[i] = new char[3];
	left_speffz = new char* [3];
	for (int i = 0; i < 3; i++) left_speffz[i] = new char[3];
	right_speffz = new char* [3];
	for (int i = 0; i < 3; i++) right_speffz[i] = new char[3];
	front_speffz = new char* [3];
	for (int i = 0; i < 3; i++) front_speffz[i] = new char[3];
	back_speffz = new char* [3];
	for (int i = 0; i < 3; i++) back_speffz[i] = new char[3];

	up_speffz[0][0] = up_speffz[0][1] = 'A';
	up_speffz[0][2] = up_speffz[1][2] = 'B';
	up_speffz[2][2] = up_speffz[2][1] = 'C';
	up_speffz[2][0] = up_speffz[1][0] = 'D';
	up_speffz[1][1] = ' ';
	left_speffz[0][0] = left_speffz[0][1] = 'E';
	left_speffz[0][2] = left_speffz[1][2] = 'F';
	left_speffz[2][2] = left_speffz[2][1] = 'G';
	left_speffz[2][0] = left_speffz[1][0] = 'H';
	left_speffz[1][1] = ' ';
	front_speffz[0][0] = front_speffz[0][1] = 'I';
	front_speffz[0][2] = front_speffz[1][2] = 'J';
	front_speffz[2][2] = front_speffz[2][1] = 'K';
	front_speffz[2][0] = front_speffz[1][0] = 'L';
	front_speffz[1][1] = ' ';
	right_speffz[0][0] = right_speffz[0][1] = 'M';
	right_speffz[0][2] = right_speffz[1][2] = 'N';
	right_speffz[2][2] = right_speffz[2][1] = 'O';
	right_speffz[2][0] = right_speffz[1][0] = 'P';
	right_speffz[1][1] = ' ';
	back_speffz[0][0] = back_speffz[0][1] = 'Q';
	back_speffz[0][2] = back_speffz[1][2] = 'R';
	back_speffz[2][2] = back_speffz[2][1] = 'S';
	back_speffz[2][0] = back_speffz[1][0] = 'T';
	back_speffz[1][1] = ' ';
	down_speffz[0][0] = down_speffz[0][1] = 'U';
	down_speffz[0][2] = down_speffz[1][2] = 'V';
	down_speffz[2][2] = down_speffz[2][1] = 'W';
	down_speffz[2][0] = down_speffz[1][0] = 'X';
	down_speffz[1][1] = ' ';
}

Cube::~Cube() { // 동적 할당된 메모리 해제
	for (int i = 0; i < 3; i++) delete[] up[i];
	delete[] up;
	for (int i = 0; i < 3; i++) delete[] down[i];
	delete[] down;
	for (int i = 0; i < 3; i++) delete[] left[i];
	delete[] left;
	for (int i = 0; i < 3; i++) delete[] right[i];
	delete[] right;
	for (int i = 0; i < 3; i++) delete[] front[i];
	delete[] front;
	for (int i = 0; i < 3; i++) delete[] back[i];
	delete[] back;

	for (int i = 0; i < 3; i++) delete[] up_speffz[i];
	delete[] up_speffz;
	for (int i = 0; i < 3; i++) delete[] down_speffz[i];
	delete[] down_speffz;
	for (int i = 0; i < 3; i++) delete[] left_speffz[i];
	delete[] left_speffz;
	for (int i = 0; i < 3; i++) delete[] right_speffz[i];
	delete[] right_speffz;
	for (int i = 0; i < 3; i++) delete[] front_speffz[i];
	delete[] front_speffz;
	for (int i = 0; i < 3; i++) delete[] back_speffz[i];
	delete[] back_speffz;
}

void Cube::cubeReset() {
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)	up[i][j] = 'W';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)	down[i][j] = 'Y';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)	front[i][j] = 'G';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)	back[i][j] = 'B';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)	left[i][j] = 'O';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)	right[i][j] = 'R';

	up_speffz[0][0] = up_speffz[0][1] = 'A';
	up_speffz[0][2] = up_speffz[1][2] = 'B';
	up_speffz[2][2] = up_speffz[2][1] = 'C';
	up_speffz[2][0] = up_speffz[1][0] = 'D';
	up_speffz[1][1] = ' ';
	left_speffz[0][0] = left_speffz[0][1] = 'E';
	left_speffz[0][2] = left_speffz[1][2] = 'F';
	left_speffz[2][2] = left_speffz[2][1] = 'G';
	left_speffz[2][0] = left_speffz[1][0] = 'H';
	left_speffz[1][1] = ' ';
	front_speffz[0][0] = front_speffz[0][1] = 'I';
	front_speffz[0][2] = front_speffz[1][2] = 'J';
	front_speffz[2][2] = front_speffz[2][1] = 'K';
	front_speffz[2][0] = front_speffz[1][0] = 'L';
	front_speffz[1][1] = ' ';
	right_speffz[0][0] = right_speffz[0][1] = 'M';
	right_speffz[0][2] = right_speffz[1][2] = 'N';
	right_speffz[2][2] = right_speffz[2][1] = 'O';
	right_speffz[2][0] = right_speffz[1][0] = 'P';
	right_speffz[1][1] = ' ';
	back_speffz[0][0] = back_speffz[0][1] = 'Q';
	back_speffz[0][2] = back_speffz[1][2] = 'R';
	back_speffz[2][2] = back_speffz[2][1] = 'S';
	back_speffz[2][0] = back_speffz[1][0] = 'T';
	back_speffz[1][1] = ' ';
	down_speffz[0][0] = down_speffz[0][1] = 'U';
	down_speffz[0][2] = down_speffz[1][2] = 'V';
	down_speffz[2][2] = down_speffz[2][1] = 'W';
	down_speffz[2][0] = down_speffz[1][0] = 'X';
	down_speffz[1][1] = ' ';
}

void cur(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Cube::printcube() {
	// 속도 향상을 위한 부분
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	cur(0, 0); // System("cls");는 매우 속도가 느리므로 Cube 출력에는 사용 X

	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		scolor(15, 0);
		std::cout << "         ";
		for (int j = 0; j < 3; j++) {
			if (up[i][j] == 'W') scolor(0, 15);
			else if (up[i][j] == 'Y') scolor(0, 14);
			else if (up[i][j] == 'G') scolor(0, 10);
			else if (up[i][j] == 'B') scolor(0, 9);
			else if (up[i][j] == 'R') scolor(0, 12);
			else if (up[i][j] == 'O') scolor(0, 13);
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		scolor(15, 0);
		std::cout << "  ";
		for (int j = 0; j < 3; j++) {
			if (left[i][j] == 'W') scolor(0, 15);
			else if (left[i][j] == 'Y') scolor(0, 14);
			else if (left[i][j] == 'G') scolor(0, 10);
			else if (left[i][j] == 'B') scolor(0, 9);
			else if (left[i][j] == 'R') scolor(0, 12);
			else if (left[i][j] == 'O') scolor(0, 13);
			std::cout << "  ";
		}
		scolor(15, 0);
		std::cout << " ";
		for (int j = 0; j < 3; j++) {
			if (front[i][j] == 'W') scolor(0, 15);
			else if (front[i][j] == 'Y') scolor(0, 14);
			else if (front[i][j] == 'G') scolor(0, 10);
			else if (front[i][j] == 'B') scolor(0, 9);
			else if (front[i][j] == 'R') scolor(0, 12);
			else if (front[i][j] == 'O') scolor(0, 13);
			std::cout << "  ";
		}
		scolor(15, 0);
		std::cout << " ";
		for (int j = 0; j < 3; j++) {
			if (right[i][j] == 'W') scolor(0, 15);
			else if (right[i][j] == 'Y') scolor(0, 14);
			else if (right[i][j] == 'G') scolor(0, 10);
			else if (right[i][j] == 'B') scolor(0, 9);
			else if (right[i][j] == 'R') scolor(0, 12);
			else if (right[i][j] == 'O') scolor(0, 13);
			std::cout << "  ";
		}
		scolor(15, 0);
		std::cout << " ";
		for (int j = 0; j < 3; j++) {
			if (back[i][j] == 'W') scolor(0, 15);
			else if (back[i][j] == 'Y') scolor(0, 14);
			else if (back[i][j] == 'G') scolor(0, 10);
			else if (back[i][j] == 'B') scolor(0, 9);
			else if (back[i][j] == 'R') scolor(0, 12);
			else if (back[i][j] == 'O') scolor(0, 13);
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		scolor(15, 0);
		std::cout << "         ";
		for (int j = 0; j < 3; j++) {
			if (down[i][j] == 'W') scolor(0, 15);
			else if (down[i][j] == 'Y') scolor(0, 14);
			else if (down[i][j] == 'G') scolor(0, 10);
			else if (down[i][j] == 'B') scolor(0, 9);
			else if (down[i][j] == 'R') scolor(0, 12);
			else if (down[i][j] == 'O') scolor(0, 13);
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
	scolor(15, 0);
	std::cout << std::endl;
}

void Cube::printSpeffz() {
	for (int i = 0; i < 3; i++) {
		std::cout << "      ";
		for (int j = 0; j < 3; j++) {
			std::cout << up_speffz[i][j] << " ";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << left_speffz[i][j] << " ";
		}
		for (int j = 0; j < 3; j++) {
			std::cout << front_speffz[i][j] << " ";
		}
		for (int j = 0; j < 3; j++) {
			std::cout << right_speffz[i][j] << " ";
		}
		for (int j = 0; j < 3; j++) {
			std::cout << back_speffz[i][j] << " ";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < 3; i++) {
		std::cout << "      ";
		for (int j = 0; j < 3; j++) {
			std::cout << down_speffz[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void RotateCornerClockwise(char** face) {
	char temp_corner = face[0][0];
	face[0][0] = face[2][0];
	face[2][0] = face[2][2];
	face[2][2] = face[0][2];
	face[0][2] = temp_corner;
}
void RotateEdgeClockwise(char** face) {
	char temp_edge = face[0][1];
	face[0][1] = face[1][0];
	face[1][0] = face[2][1];
	face[2][1] = face[1][2];
	face[1][2] = temp_edge;
}

void Cube::U() {
	RotateCornerClockwise(up);
	RotateEdgeClockwise(up);
	RotateCornerClockwise(up_speffz);
	RotateEdgeClockwise(up_speffz);

	// 옆면 회전
	char temp_side[3] = {0, 0, 0};
	for (int i = 0; i < 3; i++) temp_side[i] = front[0][i];
	for (int i = 0; i < 3; i++) front[0][i] = right[0][i];
	for (int i = 0; i < 3; i++) right[0][i] = back[0][i];
	for (int i = 0; i < 3; i++) back[0][i] = left[0][i];
	for (int i = 0; i < 3; i++) left[0][i] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[0][i];
	for (int i = 0; i < 3; i++) front_speffz[0][i] = right_speffz[0][i];
	for (int i = 0; i < 3; i++) right_speffz[0][i] = back_speffz[0][i];
	for (int i = 0; i < 3; i++) back_speffz[0][i] = left_speffz[0][i];
	for (int i = 0; i < 3; i++) left_speffz[0][i] = temp_side[i];
}

void Cube::U2() {
	U();
	U();
}

void Cube::Ur() {
	U();
	U();
	U();
}

void Cube::D() {
	RotateCornerClockwise(down);
	RotateEdgeClockwise(down);
	RotateCornerClockwise(down_speffz);
	RotateEdgeClockwise(down_speffz);

	// 옆면 회전
	char temp_side[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) temp_side[i] = front[2][i];
	for (int i = 0; i < 3; i++) front[2][i] = left[2][i];
	for (int i = 0; i < 3; i++) left[2][i] = back[2][i];
	for (int i = 0; i < 3; i++) back[2][i] = right[2][i];
	for (int i = 0; i < 3; i++) right[2][i] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[2][i];
	for (int i = 0; i < 3; i++) front_speffz[2][i] = left_speffz[2][i];
	for (int i = 0; i < 3; i++) left_speffz[2][i] = back_speffz[2][i];
	for (int i = 0; i < 3; i++) back_speffz[2][i] = right_speffz[2][i];
	for (int i = 0; i < 3; i++) right_speffz[2][i] = temp_side[i];
}

void Cube::D2() {
	D();
	D();
}

void Cube::Dr() {
	D();
	D();
	D();
}

void Cube::Dw() {
	RotateCornerClockwise(down);
	RotateEdgeClockwise(down);
	RotateCornerClockwise(down_speffz);
	RotateEdgeClockwise(down_speffz);

	// 옆면 회전
	char temp_side[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) temp_side[i] = front[2][i];
	for (int i = 0; i < 3; i++) front[2][i] = left[2][i];
	for (int i = 0; i < 3; i++) left[2][i] = back[2][i];
	for (int i = 0; i < 3; i++) back[2][i] = right[2][i];
	for (int i = 0; i < 3; i++) right[2][i] = temp_side[i];
	for (int i = 0; i < 3; i++) temp_side[i] = front[1][i];
	for (int i = 0; i < 3; i++) front[1][i] = left[1][i];
	for (int i = 0; i < 3; i++) left[1][i] = back[1][i];
	for (int i = 0; i < 3; i++) back[1][i] = right[1][i];
	for (int i = 0; i < 3; i++) right[1][i] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[2][i];
	for (int i = 0; i < 3; i++) front_speffz[2][i] = left_speffz[2][i];
	for (int i = 0; i < 3; i++) left_speffz[2][i] = back_speffz[2][i];
	for (int i = 0; i < 3; i++) back_speffz[2][i] = right_speffz[2][i];
	for (int i = 0; i < 3; i++) right_speffz[2][i] = temp_side[i];
	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[1][i];
	for (int i = 0; i < 3; i++) front_speffz[1][i] = left_speffz[1][i];
	for (int i = 0; i < 3; i++) left_speffz[1][i] = back_speffz[1][i];
	for (int i = 0; i < 3; i++) back_speffz[1][i] = right_speffz[1][i];
	for (int i = 0; i < 3; i++) right_speffz[1][i] = temp_side[i];
}

void Cube::Dw2() {
	Dw();
	Dw();
}

void Cube::Dwr() {
	Dw();
	Dw();
	Dw();
}

void Cube::R() {
	RotateCornerClockwise(right);
	RotateEdgeClockwise(right);
	RotateCornerClockwise(right_speffz);
	RotateEdgeClockwise(right_speffz);

	// 옆면 회전
	char temp_side[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) temp_side[i] = front[i][2];
	for (int i = 0; i < 3; i++) front[i][2] = down[i][2];
	for (int i = 0; i < 3; i++) down[i][2] = back[2 - i][0];
	for (int i = 0; i < 3; i++) back[2 - i][0] = up[i][2];
	for (int i = 0; i < 3; i++) up[i][2] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[i][2];
	for (int i = 0; i < 3; i++) front_speffz[i][2] = down_speffz[i][2];
	for (int i = 0; i < 3; i++) down_speffz[i][2] = back_speffz[2 - i][0];
	for (int i = 0; i < 3; i++) back_speffz[2 - i][0] = up_speffz[i][2];
	for (int i = 0; i < 3; i++) up_speffz[i][2] = temp_side[i];
}

void Cube::R2() {
	R();
	R();
}

void Cube::Rr() {
	R();
	R();
	R();
}

void Cube::L() {
	RotateCornerClockwise(left);
	RotateEdgeClockwise(left);
	RotateCornerClockwise(left_speffz);
	RotateEdgeClockwise(left_speffz);

	// 옆면 회전
	char temp_side[3] = {0, 0, 0};
	for (int i = 0; i < 3; i++) temp_side[i] = front[i][0];
	for (int i = 0; i < 3; i++) front[i][0] = up[i][0];
	for (int i = 0; i < 3; i++) up[i][0] = back[2 - i][2];
	for (int i = 0; i < 3; i++) back[2 - i][2] = down[i][0];
	for (int i = 0; i < 3; i++) down[i][0] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[i][0];
	for (int i = 0; i < 3; i++) front_speffz[i][0] = up_speffz[i][0];
	for (int i = 0; i < 3; i++) up_speffz[i][0] = back_speffz[2 - i][2];
	for (int i = 0; i < 3; i++) back_speffz[2 - i][2] = down_speffz[i][0];
	for (int i = 0; i < 3; i++) down_speffz[i][0] = temp_side[i];
}

void Cube::L2() {
	L();
	L();
}

void Cube::Lr() {
	L();
	L();
	L();
}

void Cube::Lw() {
	RotateCornerClockwise(left);
	RotateEdgeClockwise(left);
	RotateCornerClockwise(left_speffz);
	RotateEdgeClockwise(left_speffz);

	// 옆면 회전
	char temp_side[3] = {0, 0, 0};
	for (int i = 0; i < 3; i++) temp_side[i] = front[i][0];
	for (int i = 0; i < 3; i++) front[i][0] = up[i][0];
	for (int i = 0; i < 3; i++) up[i][0] = back[2 - i][2];
	for (int i = 0; i < 3; i++) back[2 - i][2] = down[i][0];
	for (int i = 0; i < 3; i++) down[i][0] = temp_side[i];
	for (int i = 0; i < 3; i++) temp_side[i] = front[i][1];
	for (int i = 0; i < 3; i++) front[i][1] = up[i][1];
	for (int i = 0; i < 3; i++) up[i][1] = back[2 - i][1];
	for (int i = 0; i < 3; i++) back[2 - i][1] = down[i][1];
	for (int i = 0; i < 3; i++) down[i][1] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[i][0];
	for (int i = 0; i < 3; i++) front_speffz[i][0] = up_speffz[i][0];
	for (int i = 0; i < 3; i++) up_speffz[i][0] = back_speffz[2 - i][2];
	for (int i = 0; i < 3; i++) back_speffz[2 - i][2] = down_speffz[i][0];
	for (int i = 0; i < 3; i++) down_speffz[i][0] = temp_side[i];
	for (int i = 0; i < 3; i++) temp_side[i] = front_speffz[i][1];
	for (int i = 0; i < 3; i++) front_speffz[i][1] = up_speffz[i][1];
	for (int i = 0; i < 3; i++) up_speffz[i][1] = back_speffz[2 - i][1];
	for (int i = 0; i < 3; i++) back_speffz[2 - i][1] = down_speffz[i][1];
	for (int i = 0; i < 3; i++) down_speffz[i][1] = temp_side[i];
}

void Cube::Lw2() {
	Lw();
	Lw();
}

void Cube::Lwr() {
	Lw();
	Lw();
	Lw();
}

void Cube::F() {
	RotateCornerClockwise(front);
	RotateEdgeClockwise(front);
	RotateCornerClockwise(front_speffz);
	RotateEdgeClockwise(front_speffz);

	// 옆면 회전
	char temp_side[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) temp_side[i] = up[2][i];
	for (int i = 0; i < 3; i++) up[2][i] = left[2 - i][2];
	for (int i = 0; i < 3; i++) left[i][2] = down[0][i];
	for (int i = 0; i < 3; i++) down[0][i] = right[2 - i][0];
	for (int i = 0; i < 3; i++) right[i][0] = temp_side[i];

	for (int i = 0; i < 3; i++) temp_side[i] = up_speffz[2][i];
	for (int i = 0; i < 3; i++) up_speffz[2][i] = left_speffz[2 - i][2];
	for (int i = 0; i < 3; i++) left_speffz[i][2] = down_speffz[0][i];
	for (int i = 0; i < 3; i++) down_speffz[0][i] = right_speffz[2 - i][0];
	for (int i = 0; i < 3; i++) right_speffz[i][0] = temp_side[i];
}

void Cube::F2() {
	F();
	F();
}

void Cube::Fr() {
	F();
	F();
	F();
}

void Cube::B() {
	RotateCornerClockwise(back);
	RotateEdgeClockwise(back);
	RotateCornerClockwise(back_speffz);
	RotateEdgeClockwise(back_speffz);

	// 옆면 회전
	char temp_side[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) temp_side[i] = up[0][i];
	for (int i = 0; i < 3; i++) up[0][i] = right[i][2];
	for (int i = 0; i < 3; i++) right[i][2] = down[2][2 - i];
	for (int i = 0; i < 3; i++) down[2][i] = left[i][0];
	for (int i = 0; i < 3; i++) left[i][0] = temp_side[2 - i];

	for (int i = 0; i < 3; i++) temp_side[i] = up_speffz[0][i];
	for (int i = 0; i < 3; i++) up_speffz[0][i] = right_speffz[i][2];
	for (int i = 0; i < 3; i++) right_speffz[i][2] = down_speffz[2][2 - i];
	for (int i = 0; i < 3; i++) down_speffz[2][i] = left_speffz[i][0];
	for (int i = 0; i < 3; i++) left_speffz[i][0] = temp_side[2 - i];
}

void Cube::B2() {
	B();
	B();
}

void Cube::Br() {
	B();
	B();
	B();
}

void Cube::rotatingCube(bool slow, int* count) {
	Node* currentNode = scramble.gethead();
	if(count != NULL) *count = 0; // 회전 수 Count
	
	if (currentNode == NULL) { // Queue가 비어있는 상태에서 Solve를 하면 깨지는 현상 방지
		this->printcube();
		std::cout << std::endl;
	}
	else {
		while (currentNode != NULL) {
			if (currentNode->getSymbol() == "U") this->U();
			else if (currentNode->getSymbol() == "U2") this->U2();
			else if (currentNode->getSymbol() == "U'") this->Ur();
			else if (currentNode->getSymbol() == "R") this->R();
			else if (currentNode->getSymbol() == "R2") this->R2();
			else if (currentNode->getSymbol() == "R'") this->Rr();
			else if (currentNode->getSymbol() == "D") this->D();
			else if (currentNode->getSymbol() == "D2") this->D2();
			else if (currentNode->getSymbol() == "D'") this->Dr();
			else if (currentNode->getSymbol() == "Dw") this->Dw();
			else if (currentNode->getSymbol() == "Dw2") this->Dw2();
			else if (currentNode->getSymbol() == "Dw'") this->Dwr();
			else if (currentNode->getSymbol() == "L") this->L();
			else if (currentNode->getSymbol() == "L2") this->L2();
			else if (currentNode->getSymbol() == "L'") this->Lr();
			else if (currentNode->getSymbol() == "Lw") this->Lw();
			else if (currentNode->getSymbol() == "Lw2") this->Lw2();
			else if (currentNode->getSymbol() == "Lw'") this->Lwr();
			else if (currentNode->getSymbol() == "F") this->F();
			else if (currentNode->getSymbol() == "F2") this->F2();
			else if (currentNode->getSymbol() == "F'") this->Fr();
			else if (currentNode->getSymbol() == "B") this->B();
			else if (currentNode->getSymbol() == "B2") this->B2();
			else if (currentNode->getSymbol() == "B'") this->Br();
			this->printcube();
			std::cout << std::endl;
			if (count != NULL) *count += 1;
			scramble.popFront();
			currentNode = scramble.gethead();
			
			if (slow == true) { // 느리게 회전
				Sleep(45);
			}
		}
	}
}

void Cube::inputtoQueue(std::string input) {
	scramble.inputtoqueue(input);
}