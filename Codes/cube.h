/*
22-1학기 EEE2020 데이터구조 End-Term Project
Queue를 이용한 Rubik's Cube Solving - OP Algorithm 구현
2020132002 물리학과
전현빈(justbecoz@yonsei.ac.kr)
2022/05/10 ~ 2022/06/09
*/

// Cube 생성, 회전, Solve 관련 Class 선언 Header File

#ifndef CUBE
#define CUBE
#include "queue.h"

class Cube {
private:
	// 각 면을 저장할 3*3 배열
	char** up;
	char** down;
	char** front;
	char** back;
	char** left;
	char** right;
	
protected:
	// 각 조각의 면마다 기호를 붙인 Speffz 배치를 저장할 3*3 배열
	char** up_speffz;
	char** down_speffz;
	char** front_speffz;
	char** back_speffz;
	char** left_speffz;
	char** right_speffz;
	Queue scramble; // Scramble 저장 Queue

	// Cube 회전 Symbol Method
	void U();
	void U2();
	void Ur();
	void D();
	void D2();
	void Dr();
	void Dw();
	void Dw2();
	void Dwr();
	void R();
	void R2();
	void Rr();
	void L();
	void L2();
	void Lr();
	void Lw();
	void Lw2();
	void Lwr();
	void F();
	void F2();
	void Fr();
	void B();
	void B2();
	void Br();

public:
	Cube();
	~Cube();
	void printcube(); // Cube 출력 Method
	void printSpeffz();	// Speffz 배치 출력 Method
	void cubeReset(); // Cube 초기화 Method
	void rotatingCube(bool, int*); // Scramble 대로 Cube를 회전 Method
	void inputtoQueue(std::string); // input을 scramble에 적용
};

class cubeSolver : public Cube {
private:
	std::string solution; // 출력할 Solution
	double solvingtime; // 맞추는 시간
	int count; // 회전 수 Count
	Queue cornersolving, edgesolving; // 각각 Corner 공식 순서, Edge 공식 순서를 저장할 Queue

	//Corner Permutation Formula
	// Basic Formulas
	std::string YPerm = "R U' R' U' R U R' F' R U R' U' R' F R";
	// Setup Move + Basic Formulas + Reverse Setup Move
	std::string cformula[26] = {};
	cformula[1] = { "" }; // Buffer
	std::string c_B = "R D' " + YPerm + " D R'";
	std::string c_C = "F " + YPerm + " F'";
	std::string c_D = "F U' R' U' R U R' F' R U R' U' R' F R2 F'";
	std::string c_E = ""; // Buffer
	std::string c_F = "F2 " + YPerm + " F2";
	std::string c_G = "D2 R2 U' R' U' R U R' F' R U R' U' R' F D2";
	std::string c_H = "D2 " + YPerm + " D2";
	std::string c_I = "F' D " + YPerm + " D' F";
	std::string c_J = "R2 D' " + YPerm + " D R2";
	std::string c_K = "R F " + YPerm + " F' R'";
	std::string c_L = "D " + YPerm + " D'";
	std::string c_M = "U' R' U' R U R' F' R U R' U' R' F R2";
	std::string c_N = "R' U' R' U' R U R' F' R U R' U' R' F R'";
	std::string c_O = "R2 U' R' U' R U R' F' R U R' U' R' F";
	std::string c_P = YPerm;
	std::string c_Q = "R' F " + YPerm + " F' R";
	std::string c_R = ""; // Buffer
	std::string c_S = "D' R2 U' R' U' R U R' F' R U R' U' R' F D";
	std::string c_T = "D' " + YPerm + " D";
	std::string c_U = "F' " + YPerm + " F";
	std::string c_V = "F' U' R' U' R U R' F' R U R' U' R' F R2 F";
	std::string c_W = "R2 F " + YPerm + " F' R2";
	std::string c_X = "D F' " + YPerm + " F D'";

	//Edge Permutation Formula
	// Basic Formulas
	std::string TPerm = "R U R' U' R' F R2 U' R' U' R U R' F'";
	std::string JPerm = "R U R' F' R U R' U' R' F R2 U' R' U'";
	// Setup Move + Basic Formulas + Reverse Setup Move
	std::string e_A = "Lw2 D' L2 " + TPerm + " L2 D Lw2";
	std::string e_B = ""; // Buffer
	std::string e_C = JPerm;
	std::string e_D = TPerm;
	std::string e_E = "L' Dw L' " + TPerm + " L Dw' L";
	std::string e_F = "Dw' L " + TPerm + " L' Dw";
	std::string e_G = "D Lw' " + JPerm + " Lw D'";
	std::string e_H = "Dw L' " + TPerm + " L Dw'";
	std::string e_I = "Lw D' L2 " + TPerm + " L2 D Lw'";
	std::string e_J = "Dw2 L " + TPerm + " L' Dw2";
	std::string e_K = "Lw' " + JPerm + " Lw";
	std::string e_L = "L' " + TPerm + " L";
	std::string e_M = ""; // Buffer
	std::string e_N = "Dw L " + TPerm + " L' Dw'";
	std::string e_O = "D' Lw' " + JPerm + " Lw D";
	std::string e_P = "Dw' L' " + TPerm + " L Dw";
	std::string e_Q = "Lw " + JPerm + " Lw'";
	std::string e_R = "L " + TPerm + " L'";
	std::string e_S = "Lw' D' L2 " + TPerm + " L2 D Lw";
	std::string e_T = "Dw2 L' " + TPerm + " L Dw2";
	std::string e_U = "D' L2 " + TPerm + " L2 D";
	std::string e_V = "D2 L2 " + TPerm + " L2 D2";
	std::string e_W = "D L2 " + TPerm + " L2 D'";
	std::string e_X = "L2 " + TPerm + " L2";

	// Parity Remove Formula
	std::string RaPerm = "R U R' F' R U2 R' U2 R' F R U R U2 R' U'";

public:
	cubeSolver();
	void findCornerPiece(char, int*); // Corner 조각 Speffz 배치로 찾는 Method
	void findEdgePiece(char, int*); // Edge 조각 Speffz 배치로 찾는 Method
	bool cubeCornerSolver(); // Corner 조각을 맞추는 순서 생성 Method
	void cubeEdgeSolver(); // Edge 조각을 맞추는 순서 생성 Method
	void cubeSolving(bool); // 위 두 Method로 Cube를 맞추는 Method

	std::string getSolution();
	double getSolvingTime();
	int getCount();
};
#endif