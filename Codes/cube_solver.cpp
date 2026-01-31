/*
22-1학기 EEE2020 데이터구조 End-Term Project
Queue를 이용한 Rubik's Cube Solving - OP Algorithm 구현
2020132002 물리학과
전현빈(justbecoz@yonsei.ac.kr)
2022/05/10 ~ 2022/06/09
*/

// Cube 클래스 중 Solve와 관련된 구현 .cpp File

#include <time.h>
#include "cube.h"

cubeSolver::cubeSolver() {
	solution = "";
	solvingtime = 0;
	count = 0;
}

void cubeSolver::findCornerPiece(char Piece, int* index) {
	cubeSolver compare;
	for (int i = 0; i < 3; i += 2) {
		for (int j = 0; j < 3; j += 2) {
			if (compare.up_speffz[i][j] == Piece) {
				index[0] = i;
				index[1] = j;
				index[2] = 0;
			}
			else if (compare.down_speffz[i][j] == Piece) {
				index[0] = i;
				index[1] = j;
				index[2] = 1;
			}
			else if (compare.left_speffz[i][j] == Piece) {
				index[0] = i;
				index[1] = j;
				index[2] = 2;
			}
			else if (compare.right_speffz[i][j] == Piece) {
				index[0] = i;
				index[1] = j;
				index[2] = 3;
			}
			else if (compare.front_speffz[i][j] == Piece) {
				index[0] = i;
				index[1] = j;
				index[2] = 4;
			}
			else if (compare.back_speffz[i][j] == Piece) {
				index[0] = i;
				index[1] = j;
				index[2] = 5;
			}
		}
	}
}

void cubeSolver::findEdgePiece(char Piece, int* index) {
	cubeSolver compare;
	for (int i = 0; i < 2; i++) {
		if (compare.up_speffz[i][i + 1] == Piece) {
			index[0] = i;
			index[1] = i + 1;
			index[2] = 0;
		}
		else if (compare.down_speffz[i][i + 1] == Piece) {
			index[0] = i;
			index[1] = i + 1;
			index[2] = 1;
		}
		else if (compare.left_speffz[i][i + 1] == Piece) {
			index[0] = i;
			index[1] = i + 1;
			index[2] = 2;
		}
		else if (compare.right_speffz[i][i + 1] == Piece) {
			index[0] = i;
			index[1] = i + 1;
			index[2] = 3;
		}
		else if (compare.front_speffz[i][i + 1] == Piece) {
			index[0] = i;
			index[1] = i + 1;
			index[2] = 4;
		}
		else if (compare.back_speffz[i][i + 1] == Piece) {
			index[0] = i;
			index[1] = i + 1;
			index[2] = 5;
		}

		else if (compare.up_speffz[i + 1][i] == Piece) {
			index[0] = i + 1;
			index[1] = i;
			index[2] = 0;
		}
		else if (compare.down_speffz[i + 1][i] == Piece) {
			index[0] = i + 1;
			index[1] = i;
			index[2] = 1;
		}
		else if (compare.left_speffz[i + 1][i] == Piece) {
			index[0] = i + 1;
			index[1] = i;
			index[2] = 2;
		}
		else if (compare.right_speffz[i + 1][i] == Piece) {
			index[0] = i + 1;
			index[1] = i;
			index[2] = 3;
		}
		else if (compare.front_speffz[i + 1][i] == Piece) {
			index[0] = i + 1;
			index[1] = i;
			index[2] = 4;
		}
		else if (compare.back_speffz[i + 1][i] == Piece) {
			index[0] = i + 1;
			index[1] = i;
			index[2] = 5;
		}
	}
}

bool cubeSolver::cubeCornerSolver() {
	std::string corner = ""; // Corner를 맞추는 순서가 저장될 string 변수
	cubeSolver compare; // 이미 맞춰진 조각인지 확인을 위한 임시 Cube
	bool cornersolved = false, paritycheck = false; // corner가 전부 맞춰졌는지 확인, parity가 있는지 확인
	char target = this->up_speffz[0][0]; // 조각이 원래 있어야할 위치 저장
	char buffer[3] = { 'A', 'E', 'R' }; // first buffer
	// buffer로 사용할 수 있는 조각 list(맞춰지지 않은 조각)
	int bufferlist[24] = { 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 ,1, 1, 1, 1, 1 }; 
	int index[3] = { -1, -1, -1 }; // 조각을 찾을 때 위치를 저장할 배열

	// 이미 맞춰진 조각은 bufferlist에서 해제
	for (int i = 0; i < 3; i += 2) {
		for (int j = 0; j < 3; j += 2) {
			if (compare.up_speffz[i][j] == this->up_speffz[i][j]) 
				bufferlist[(int)(this->up_speffz[i][j] - 65)] = 0;
			if (compare.down_speffz[i][j] == this->down_speffz[i][j]) 
				bufferlist[(int)(this->down_speffz[i][j] - 65)] = 0;
			if (compare.left_speffz[i][j] == this->left_speffz[i][j]) 
				bufferlist[(int)(this->left_speffz[i][j] - 65)] = 0;
			if (compare.right_speffz[i][j] == this->right_speffz[i][j]) 
				bufferlist[(int)(this->right_speffz[i][j] - 65)] = 0;
			if (compare.front_speffz[i][j] == this->front_speffz[i][j]) 
				bufferlist[(int)(this->front_speffz[i][j] - 65)] = 0;
			if (compare.back_speffz[i][j] == this->back_speffz[i][j]) 
				bufferlist[(int)(this->back_speffz[i][j] - 65)] = 0;
		}
	}
	
	// 첫 Buffer에 있는 조각이 원래 있어야할 위치 추가
	if (target != 'A' && target != 'E' && target != 'R') {
		corner += target;
		corner += " ";
	}

	while (cornersolved == false) { // Corner가 모두 맞춰질 때까지 반복
		char newtarget = target; // Buffer의 위치에 있는 조각을 잠깐 담아두기 위한 변수
		while (1) {
			newtarget = target;
			// Buffer 조각이 되면, Buffer에 있는 조각을 한번 더 넣고 종료
			// 바뀐 버퍼를 다시 제일 처음 버퍼로 돌려놓기 위함
			if (target == buffer[0] || target == buffer[1] || target == buffer[2]) {
				//Buffer에서 시작하여 각 조각의 면이 원래 있어야할 조각 위치로 이동
				this->findCornerPiece(target, index);
				if (index[2] == 0) 
					target = this->up_speffz[index[0]][index[1]];
				else if (index[2] == 1) 
					target = this->down_speffz[index[0]][index[1]];
				else if (index[2] == 2) 
					target = this->left_speffz[index[0]][index[1]];
				else if (index[2] == 3) 
					target = this->right_speffz[index[0]][index[1]];
				else if (index[2] == 4) 
					target = this->front_speffz[index[0]][index[1]];
				else if (index[2] == 5) 
					target = this->back_speffz[index[0]][index[1]];
				else 
					std::cout << "Error" << std::endl;

				// Buffer가 제일 처음 Buffer일 경우 한 번 더 넣을 필요 X
				if (newtarget != 'A' && newtarget != 'E' && newtarget != 'R') {
					corner += target;
					corner += " ";
				}
				break;
			}

			// 버퍼로 선택할 조각을 고르기 위해 위에서 이미 사용된 조각을 bufferlist 변수에서 off(= 0) 함
			if (target == 'B' || target == 'N' || target == 'Q') 
				bufferlist[1] = bufferlist[13] = bufferlist[16] = 0;
			else if (target == 'C' || target == 'J' || target == 'M') 
				bufferlist[2] = bufferlist[9] = bufferlist[12] = 0;
			else if (target == 'D' || target == 'I' || target == 'F') 
				bufferlist[3] = bufferlist[8] = bufferlist[5] = 0;
			else if (target == 'U' || target == 'L' || target == 'G') 
				bufferlist[20] = bufferlist[11] = bufferlist[6] = 0;
			else if (target == 'V' || target == 'K' || target == 'P') 
				bufferlist[21] = bufferlist[10] = bufferlist[15] = 0;
			else if (target == 'W' || target == 'O' || target == 'T') 
				bufferlist[22] = bufferlist[14] = bufferlist[19] = 0;
			else if (target == 'X' || target == 'S' || target == 'H') 
				bufferlist[23] = bufferlist[18] = bufferlist[7] = 0;

			//Buffer에서 시작하여 각 조각의 면이 원래 있어야할 조각 위치로 이동
			this->findCornerPiece(target, index);
			if (index[2] == 0) 
				target = this->up_speffz[index[0]][index[1]];
			else if (index[2] == 1) 
				target = this->down_speffz[index[0]][index[1]];
			else if (index[2] == 2) 
				target = this->left_speffz[index[0]][index[1]];
			else if (index[2] == 3) 
				target = this->right_speffz[index[0]][index[1]];
			else if (index[2] == 4) 
				target = this->front_speffz[index[0]][index[1]];
			else if (index[2] == 5) 
				target = this->back_speffz[index[0]][index[1]];
			else std::cout << "Error" << std::endl;

			// Corner를 맞추는 순서에 추가
			if (target != 'A' && target != 'E' && target != 'R') { // 첫 Cycle의 버퍼는 뒤에 붙일 필요 없으므로.
				corner += target;
				corner += " ";
			}
		}

		cornersolved = true;

		// Corner 조각이 모두 맞춰지지 않았으면, buffer 재설정
		for (int i = 0; i < 24; i++) {
			if (bufferlist[i] == 1) {
				buffer[0] = (char)(65 + i);
				cornersolved = false;
				break;
			}
		}

		if (cornersolved == false) {
			// Buffer 재설정
			this->findCornerPiece(buffer[0], index);
			if (index[2] == 0) 
				target = this->up_speffz[index[0]][index[1]];
			else if (index[2] == 1) 
				target = this->down_speffz[index[0]][index[1]];
			else if (index[2] == 2) 
				target = this->left_speffz[index[0]][index[1]];
			else if (index[2] == 3) 
				target = this->right_speffz[index[0]][index[1]];
			else if (index[2] == 4) 
				target = this->front_speffz[index[0]][index[1]];
			else if (index[2] == 5) 
				target = this->back_speffz[index[0]][index[1]];
			else 
				std::cout << "Error" << std::endl;
			corner += target;
			corner += " ";

			// 선택한 Buffer를 bufferlist에서 삭제
			if (buffer[0] == 'B' || buffer[0] == 'N' || buffer[0] == 'Q')
				bufferlist[1] = bufferlist[13] = bufferlist[16] = 0;
			else if (buffer[0] == 'C' || buffer[0] == 'J' || buffer[0] == 'M') 
				bufferlist[2] = bufferlist[9] = bufferlist[12] = 0;
			else if (buffer[0] == 'D' || buffer[0] == 'I' || buffer[0] == 'F') 
				bufferlist[3] = bufferlist[8] = bufferlist[5] = 0;
			else if (buffer[0] == 'U' || buffer[0] == 'L' || buffer[0] == 'G') 
				bufferlist[20] = bufferlist[11] = bufferlist[6] = 0;
			else if (buffer[0] == 'V' || buffer[0] == 'K' || buffer[0] == 'P') 
				bufferlist[21] = bufferlist[10] = bufferlist[15] = 0;
			else if (buffer[0] == 'W' || buffer[0] == 'O' || buffer[0] == 'T') 
				bufferlist[22] = bufferlist[14] = bufferlist[19] = 0;
			else if (buffer[0] == 'X' || buffer[0] == 'S' || buffer[0] == 'H') 
				bufferlist[23] = bufferlist[18] = bufferlist[7] = 0;

			// Buffer 조각으로 다시 돌아왔을 때의 종료 조건을 위한 변수 설정 
			if (buffer[0] == 'B' || buffer[0] == 'N' || buffer[0] == 'Q') { 
				buffer[0] = 'B'; buffer[1] = 'N'; buffer[2] = 'Q'; 
			}
			else if (buffer[0] == 'C' || buffer[0] == 'J' || buffer[0] == 'M') { 
				buffer[0] = 'C'; buffer[1] = 'J'; buffer[2] = 'M'; 
			}
			else if (buffer[0] == 'D' || buffer[0] == 'I' || buffer[0] == 'F') { 
				buffer[0] = 'D'; buffer[1] = 'I'; buffer[2] = 'F'; 
			}
			else if (buffer[0] == 'U' || buffer[0] == 'L' || buffer[0] == 'G') { 
				buffer[0] = 'U'; buffer[1] = 'L'; buffer[2] = 'G'; 
			}
			else if (buffer[0] == 'V' || buffer[0] == 'K' || buffer[0] == 'P') {
				buffer[0] = 'V'; buffer[1] = 'K'; buffer[2] = 'P'; 
			}
			else if (buffer[0] == 'W' || buffer[0] == 'O' || buffer[0] == 'T') { 
				buffer[0] = 'W'; buffer[1] = 'O'; buffer[2] = 'T'; 
			}
			else if (buffer[0] == 'X' || buffer[0] == 'S' || buffer[0] == 'H') {
				buffer[0] = 'X'; buffer[1] = 'S'; buffer[2] = 'H'; 
			}
		}
	}

	if (corner == "") solution += "[Corners Already Solved]\n";
	else solution += "Corner Solving[Modified Y-Perm]: " + corner + "\n";

	// Queue에 삽입
	cornersolving.inputtoqueue(corner);

	// Queue에서 하나씩 꺼내가며 공식 실행
	Node* currentNode = cornersolving.gethead();
	while (currentNode != NULL) {
		if (currentNode->getSymbol() == "A") {
			scramble.inputtoqueue(c_A); 
			solution += "→ A: " + c_A + "\n"; 
		}
		else if (currentNode->getSymbol() == "B") {
			scramble.inputtoqueue(c_B); 
			solution += "→ B: " + c_B + "\n"; 
		}
		else if (currentNode->getSymbol() == "C") {
			scramble.inputtoqueue(c_C); 
			solution += "→ C: " + c_C + "\n"; 
		}
		else if (currentNode->getSymbol() == "D") {
			scramble.inputtoqueue(c_D); 
			solution += "→ D: " + c_D + "\n"; 
		}
		else if (currentNode->getSymbol() == "E") {
			scramble.inputtoqueue(c_E); 
			solution += "→ E: " + c_E + "\n"; 
		}
		else if (currentNode->getSymbol() == "F") {
			scramble.inputtoqueue(c_F); 
			solution += "→ F: " + c_F + "\n"; 
		}
		else if (currentNode->getSymbol() == "G") {
			scramble.inputtoqueue(c_G); 
			solution += "→ G: " + c_G + "\n"; 
		}
		else if (currentNode->getSymbol() == "H") {
			scramble.inputtoqueue(c_H); 
			solution += "→ H: " + c_H + "\n"; 
		}
		else if (currentNode->getSymbol() == "I") {
			scramble.inputtoqueue(c_I); 
			solution += "→ I: " + c_I + "\n"; 
		}
		else if (currentNode->getSymbol() == "J") {
			scramble.inputtoqueue(c_J); 
			solution += "→ J: " + c_J + "\n"; 
		}
		else if (currentNode->getSymbol() == "K") {
			scramble.inputtoqueue(c_K); 
			solution += "→ K: " + c_K + "\n"; 
		}
		else if (currentNode->getSymbol() == "L") {
			scramble.inputtoqueue(c_L); 
			solution += "→ L: " + c_L + "\n"; 
		}
		else if (currentNode->getSymbol() == "M") {
			scramble.inputtoqueue(c_M); 
			solution += "→ M: " + c_M + "\n"; 
		}
		else if (currentNode->getSymbol() == "N") {
			scramble.inputtoqueue(c_N); 
			solution += "→ N: " + c_N + "\n"; 
		}
		else if (currentNode->getSymbol() == "O") {
			scramble.inputtoqueue(c_O); 
			solution += "→ O: " + c_O + "\n"; 
		}
		else if (currentNode->getSymbol() == "P") {
			scramble.inputtoqueue(c_P); 
			solution += "→ P: " + c_P + "\n"; 
		}
		else if (currentNode->getSymbol() == "Q") {
			scramble.inputtoqueue(c_Q); 
			solution += "→ Q: " + c_Q + "\n"; 
		}
		else if (currentNode->getSymbol() == "R") {
			scramble.inputtoqueue(c_R); 
			solution += "→ R: " + c_R + "\n"; 
		}
		else if (currentNode->getSymbol() == "S") {
			scramble.inputtoqueue(c_S); 
			solution += "→ S: " + c_S + "\n"; 
		}
		else if (currentNode->getSymbol() == "T") {
			scramble.inputtoqueue(c_T); 
			solution += "→ T: " + c_T + "\n"; 
		}
		else if (currentNode->getSymbol() == "U") {
			scramble.inputtoqueue(c_U); 
			solution += "→ U: " + c_U + "\n"; 
		}
		else if (currentNode->getSymbol() == "V") {
			scramble.inputtoqueue(c_V); 
			solution += "→ V: " + c_V + "\n"; 
		}
		else if (currentNode->getSymbol() == "W") {
			scramble.inputtoqueue(c_W); 
			solution += "→ W: " + c_W + "\n"; 
		}
		else if (currentNode->getSymbol() == "X") {
			scramble.inputtoqueue(c_X); 
			solution += "→ X: " + c_X + "\n"; 
		}
		cornersolving.popFront();
		currentNode = cornersolving.gethead();
	}

	// Parity 제거
	if ((corner.length() / 2) % 2 == 1) {
		scramble.inputtoqueue(RaPerm);
		paritycheck = true;
	}

	if (paritycheck == true) solution += "\n[Parity Exists] Ra-Perm(R U R' F' R U2 R' U2 R' F R U R U2 R' U') Used\n";
	return paritycheck;
}

void cubeSolver::cubeEdgeSolver() { // Corner 조각 맞출 때 사용한 공식의 개수를 불러옴
	std::string edge = ""; // Edge를 맞추는 순서가 저장될 string 변수
	cubeSolver compare; // 이미 맞춰진 조각인지 확인을 위한 임시 Cube
	bool edgesolved = false; // edge가 전부 맞춰졌는지 확인
	char target = this->up_speffz[1][2]; // 조각이 원래 있어야할 위치 저장
	char buffer[2] = { 'B', 'M' }; // first buffer
	// buffer로 사용할 수 있는 조각 list(맞춰지지 않은 조각)
	int bufferlist[24] = { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 }; 
	int index[3] = { -1, -1, -1 }; // 조각을 찾을 때 위치를 저장할 배열

	// 이미 맞춰진 조각은 bufferlist에서 해제
	for (int i = 0; i < 2; i++) {
		if (compare.up_speffz[i][i + 1] == this->up_speffz[i][i + 1]) 
			bufferlist[(int)(this->up_speffz[i][i + 1] - 65)] = 0;
		if (compare.down_speffz[i][i + 1] == this->down_speffz[i][i + 1]) 
			bufferlist[(int)(this->down_speffz[i][i + 1] - 65)] = 0;
		if (compare.left_speffz[i][i + 1] == this->left_speffz[i][i + 1]) 
			bufferlist[(int)(this->left_speffz[i][i + 1] - 65)] = 0;
		if (compare.right_speffz[i][i + 1] == this->right_speffz[i][i + 1]) 
			bufferlist[(int)(this->right_speffz[i][i + 1] - 65)] = 0;
		if (compare.front_speffz[i][i + 1] == this->front_speffz[i][i + 1])
			bufferlist[(int)(this->front_speffz[i][i + 1] - 65)] = 0;
		if (compare.back_speffz[i][i + 1] == this->back_speffz[i][i + 1])
			bufferlist[(int)(this->back_speffz[i][i + 1] - 65)] = 0;
		if (compare.up_speffz[i + 1][i] == this->up_speffz[i + 1][i]) 
			bufferlist[(int)(this->up_speffz[i + 1][i] - 65)] = 0;
		if (compare.down_speffz[i + 1][i] == this->down_speffz[i + 1][i]) 
			bufferlist[(int)(this->down_speffz[i + 1][i] - 65)] = 0;
		if (compare.left_speffz[i + 1][i] == this->left_speffz[i + 1][i])
			bufferlist[(int)(this->left_speffz[i + 1][i] - 65)] = 0;
		if (compare.right_speffz[i + 1][i] == this->right_speffz[i + 1][i]) 
			bufferlist[(int)(this->right_speffz[i + 1][i] - 65)] = 0;
		if (compare.front_speffz[i + 1][i] == this->front_speffz[i + 1][i]) 
			bufferlist[(int)(this->front_speffz[i + 1][i] - 65)] = 0;
		if (compare.back_speffz[i + 1][i] == this->back_speffz[i + 1][i]) 
			bufferlist[(int)(this->back_speffz[i + 1][i] - 65)] = 0;
	}

	// 첫 Buffer에 있는 조각이 원래 있어야할 위치 추가
	if (target != 'B' && target != 'M') {
		edge += target;
		edge += " ";
	}

	while (edgesolved == false) { // Edge가 모두 맞춰질 때까지 반복
		char newtarget = target; // Buffer의 위치에 있는 조각을 잠깐 담아두기 위한 변수
		while (1) {
			newtarget = target;
			// Buffer 조각이 되면, Buffer에 담긴 조각을 한번 더 넣고 종료
			// 바뀐 버퍼를 다시 제일 처음 버퍼로 돌려놓기 위함
			if (target == buffer[0] || target == buffer[1]) {
				//Buffer에서 시작하여 각 조각의 면이 원래 있어야할 조각 위치로 이동
				this->findEdgePiece(target, index);
				if (index[2] == 0) 
					target = this->up_speffz[index[0]][index[1]];
				else if (index[2] == 1) 
					target = this->down_speffz[index[0]][index[1]];
				else if (index[2] == 2) 
					target = this->left_speffz[index[0]][index[1]];
				else if (index[2] == 3) 
					target = this->right_speffz[index[0]][index[1]];
				else if (index[2] == 4) 
					target = this->front_speffz[index[0]][index[1]];
				else if (index[2] == 5) 
					target = this->back_speffz[index[0]][index[1]];
				else 
					std::cout << "Error" << std::endl;
				if (newtarget != 'B' && newtarget != 'M') { // Buffer가 제일 처음 Buffer일 경우 한 번 더 넣을 필요 X
					edge += target;
					edge += " ";
				}
				break;
			}

			// 버퍼로 선택할 조각을 고르기 위해 위에서 이미 사용된 조각을 bufferlist 변수에서 off(= 0) 함
			if (target == 'A' || target == 'Q') 
				bufferlist[0] = bufferlist[16] = 0;
			else if (target == 'C' || target == 'I') 
				bufferlist[2] = bufferlist[8] = 0;
			else if (target == 'D' || target == 'E') 
				bufferlist[3] = bufferlist[4] = 0;
			else if (target == 'H' || target == 'R') 
				bufferlist[7] = bufferlist[17] = 0;
			else if (target == 'F' || target == 'L') 
				bufferlist[5] = bufferlist[11] = 0;
			else if (target == 'J' || target == 'P') 
				bufferlist[9] = bufferlist[15] = 0;
			else if (target == 'N' || target == 'T') 
				bufferlist[13] = bufferlist[19] = 0;
			else if (target == 'U' || target == 'K') 
				bufferlist[20] = bufferlist[10] = 0;
			else if (target == 'V' || target == 'O') 
				bufferlist[21] = bufferlist[14] = 0;
			else if (target == 'W' || target == 'S') 
				bufferlist[22] = bufferlist[18] = 0;
			else if (target == 'X' || target == 'G') 
				bufferlist[23] = bufferlist[6] = 0;

			//Buffer에서 시작하여 각 조각의 면이 원래 있어야할 조각 위치로 이동
			this->findEdgePiece(target, index);
			if (index[2] == 0) 
				target = this->up_speffz[index[0]][index[1]];
			else if (index[2] == 1) 
				target = this->down_speffz[index[0]][index[1]];
			else if (index[2] == 2) 
				target = this->left_speffz[index[0]][index[1]];
			else if (index[2] == 3) 
				target = this->right_speffz[index[0]][index[1]];
			else if (index[2] == 4) 
				target = this->front_speffz[index[0]][index[1]];
			else if (index[2] == 5) 
				target = this->back_speffz[index[0]][index[1]];
			else std::cout << "Error" << std::endl;

			// Edge를 맞추는 순서에 추가
			if (target != 'B' && target != 'M') { // 첫 Cycle의 버퍼는 뒤에 붙일 필요 없으므로.
				edge += target;
				edge += " ";
			}
		}

		edgesolved = true;

		// Edge 조각이 모두 맞춰지지 않았으면, buffer 재설정
		for (int i = 0; i < 24; i++) {
			if (bufferlist[i] == 1) {
				buffer[0] = (char)(65 + i);
				edgesolved = false;
				break;
			}
		}

		if (edgesolved == false) {
			// Buffer 재설정
			this->findEdgePiece(buffer[0], index);
			if (index[2] == 0) 
				target = this->up_speffz[index[0]][index[1]];
			else if (index[2] == 1) 
				target = this->down_speffz[index[0]][index[1]];
			else if (index[2] == 2) 
				target = this->left_speffz[index[0]][index[1]];
			else if (index[2] == 3) 
				target = this->right_speffz[index[0]][index[1]];
			else if (index[2] == 4) 
				target = this->front_speffz[index[0]][index[1]];
			else if (index[2] == 5) 
				target = this->back_speffz[index[0]][index[1]];
			else 
				std::cout << "Error" << std::endl;
			edge += target;
			edge += " ";

			// 선택한 Buffer를 bufferlist에서 삭제
			if (buffer[0] == 'A' || buffer[0] == 'Q') 
				bufferlist[0] = bufferlist[16] = 0;
			else if (buffer[0] == 'C' || buffer[0] == 'I') 
				bufferlist[2] = bufferlist[8] = 0;
			else if (buffer[0] == 'D' || buffer[0] == 'E') 
				bufferlist[3] = bufferlist[4] = 0;
			else if (buffer[0] == 'H' || buffer[0] == 'R') 
				bufferlist[7] = bufferlist[17] = 0;
			else if (buffer[0] == 'F' || buffer[0] == 'L') 
				bufferlist[5] = bufferlist[11] = 0;
			else if (buffer[0] == 'J' || buffer[0] == 'P') 
				bufferlist[9] = bufferlist[15] = 0;
			else if (buffer[0] == 'N' || buffer[0] == 'T') 
				bufferlist[13] = bufferlist[19] = 0;
			else if (buffer[0] == 'U' || buffer[0] == 'K') 
				bufferlist[20] = bufferlist[10] = 0;
			else if (buffer[0] == 'V' || buffer[0] == 'O') 
				bufferlist[21] = bufferlist[14] = 0;
			else if (buffer[0] == 'W' || buffer[0] == 'S') 
				bufferlist[22] = bufferlist[18] = 0;
			else if (buffer[0] == 'X' || buffer[0] == 'G') 
				bufferlist[23] = bufferlist[6] = 0;

			// Buffer 조각으로 다시 돌아왔을 때의 종료 조건을 위한 변수 설정 
			if (buffer[0] == 'A' || buffer[0] == 'Q') { 
				buffer[0] = 'A'; buffer[1] = 'Q'; 
			}
			else if (buffer[0] == 'C' || buffer[0] == 'I') { 
				buffer[0] = 'C'; buffer[1] = 'I'; 
			}
			else if (buffer[0] == 'D' || buffer[0] == 'E') { 
				buffer[0] = 'D'; buffer[1] = 'E'; 
			}
			else if (buffer[0] == 'H' || buffer[0] == 'R') { 
				buffer[0] = 'H'; buffer[1] = 'R'; 
			}
			else if (buffer[0] == 'F' || buffer[0] == 'L') { 
				buffer[0] = 'F'; buffer[1] = 'L'; 
			}
			else if (buffer[0] == 'J' || buffer[0] == 'P') { 
				buffer[0] = 'J'; buffer[1] = 'P'; 
			}
			else if (buffer[0] == 'N' || buffer[0] == 'T') { 
				buffer[0] = 'N'; buffer[1] = 'T'; 
			}
			else if (buffer[0] == 'U' || buffer[0] == 'K') { 
				buffer[0] = 'U'; buffer[1] = 'K'; 
			}
			else if (buffer[0] == 'V' || buffer[0] == 'O') { 
				buffer[0] = 'V'; buffer[1] = 'O'; 
			}
			else if (buffer[0] == 'W' || buffer[0] == 'S') { 
				buffer[0] = 'W'; buffer[1] = 'S'; 
			}
			else if (buffer[0] == 'X' || buffer[0] == 'G') { 
				buffer[0] = 'X'; buffer[1] = 'G'; 
			}
		}
	}

	if (edge == "") solution += "\n[Edges Already Solved]\n";
	else solution += "\nEdge Solving[T-Perm & J-Perm]: " + edge + "\n";

	// Queue에 삽입
	edgesolving.inputtoqueue(edge);

	// Queue에서 하나씩 꺼내가며 공식 실행 후 Solution 출력용 문자열에 추가
	Node* currentNode = edgesolving.gethead();
	while (currentNode != NULL) {
		if (currentNode->getSymbol() == "A") {
			scramble.inputtoqueue(e_A); 
			solution += "→ A: " + e_A + "\n"; 
		}
		else if (currentNode->getSymbol() == "B") {
			scramble.inputtoqueue(e_B); 
			solution += "→ B: " + e_B + "\n"; 
		}
		else if (currentNode->getSymbol() == "C") {
			scramble.inputtoqueue(e_C); 
			solution += "→ C: " + e_C + "\n"; 
		}
		else if (currentNode->getSymbol() == "D") {
			scramble.inputtoqueue(e_D); 
			solution += "→ D: " + e_D + "\n"; 
		}
		else if (currentNode->getSymbol() == "E") {
			scramble.inputtoqueue(e_E); 
			solution += "→ E: " + e_E + "\n"; 
		}
		else if (currentNode->getSymbol() == "F") {
			scramble.inputtoqueue(e_F); 
			solution += "→ F: " + e_F + "\n"; 
		}
		else if (currentNode->getSymbol() == "G") {
			scramble.inputtoqueue(e_G); 
			solution += "→ G: " + e_G + "\n"; 
		}
		else if (currentNode->getSymbol() == "H") {
			scramble.inputtoqueue(e_H); 
			solution += "→ H: " + e_H + "\n"; 
		}
		else if (currentNode->getSymbol() == "I") {
			scramble.inputtoqueue(e_I); 
			solution += "→ I: " + e_I + "\n"; 
		}
		else if (currentNode->getSymbol() == "J") {
			scramble.inputtoqueue(e_J); 
			solution += "→ J: " + e_J + "\n"; 
		}
		else if (currentNode->getSymbol() == "K") {
			scramble.inputtoqueue(e_K); 
			solution += "→ K: " + e_K + "\n"; 
		}
		else if (currentNode->getSymbol() == "L") {
			scramble.inputtoqueue(e_L); 
			solution += "→ L: " + e_L + "\n"; 
		}
		else if (currentNode->getSymbol() == "M") {
			scramble.inputtoqueue(e_M); 
			solution += "→ M: " + e_M + "\n"; 
		}
		else if (currentNode->getSymbol() == "N") {
			scramble.inputtoqueue(e_N); 
			solution += "→ N: " + e_N + "\n"; 
		}
		else if (currentNode->getSymbol() == "O") {
			scramble.inputtoqueue(e_O); 
			solution += "→ O: " + e_O + "\n"; 
		}
		else if (currentNode->getSymbol() == "P") {
			scramble.inputtoqueue(e_P); 
			solution += "→ P: " + e_P + "\n"; 
		}
		else if (currentNode->getSymbol() == "Q") {
			scramble.inputtoqueue(e_Q); 
			solution += "→ Q: " + e_Q + "\n"; 
		}
		else if (currentNode->getSymbol() == "R") {
			scramble.inputtoqueue(e_R); 
			solution += "→ R: " + e_R + "\n"; 
		}
		else if (currentNode->getSymbol() == "S") {
			scramble.inputtoqueue(e_S);
			solution += "→ S: " + e_S + "\n";
		}
		else if (currentNode->getSymbol() == "T") {
			scramble.inputtoqueue(e_T); 
			solution += "→ T: " + e_T + "\n";
		}
		else if (currentNode->getSymbol() == "U") {
			scramble.inputtoqueue(e_U); 
			solution += "→ U: " + e_U + "\n"; 
		}
		else if (currentNode->getSymbol() == "V") {
			scramble.inputtoqueue(e_V); 
			solution += "→ V: " + e_V + "\n"; 
		}
		else if (currentNode->getSymbol() == "W") {
			scramble.inputtoqueue(e_W); 
			solution += "→ W: " + e_W + "\n"; 
		}
		else if (currentNode->getSymbol() == "X") {
			scramble.inputtoqueue(e_X); 
			solution += "→ X: " + e_X + "\n"; 
		}
		edgesolving.popFront();
		currentNode = edgesolving.gethead();
	}
}

void cubeSolver::cubeSolving(bool slow) {
	clock_t start, end; // Solving 시간 측정을 위한 변수

	start = clock(); // 시간 측정 시작
	cubeCornerSolver(); // Corner 조각 Solving + Parity Check
	cubeEdgeSolver(); // edge 조각 Solving
	rotatingCube(slow, &count); // 풀어낸 대로 Cube 회전
	end = clock(); // 시간 측정 종료

	solvingtime = (double)(end - start) / CLOCKS_PER_SEC;
}

std::string cubeSolver::getSolution() {
	// solution 문자열 Return 후, solution 문자열 비우기
	std::string tempstr = solution;
	solution = "";
	return tempstr;
}

double cubeSolver::getSolvingTime() {
	return solvingtime;
}

int cubeSolver::getCount() {
	return count;
}