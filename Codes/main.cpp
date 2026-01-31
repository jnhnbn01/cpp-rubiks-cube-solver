/*
22-1학기 EEE2020 데이터구조 End-Term Project
Queue를 이용한 Rubik's Cube Solving - OP Algorithm 구현
2020132002 물리학과
전현빈(justbecoz@yonsei.ac.kr)
2022/05/10 ~ 2022/06/09
*/

// Main File
#include "cube.h"

int main() {
	cubeSolver rubikscube; // Rubik's Cube 생성
	std::string input = ""; // 입력한 값을 저장할 String

	while (input != "4") { // Quit이 입력되기 전까지 반복
		input = ""; // input 초기화
		
		// Cube 출력
		rubikscube.printcube();
		std::cout << "1: Reset Cube | 2: Solve Cube | 3: Solve Cube Slowly | 4: Stop Program\n\n> ";
		getline(std::cin, input, '\n'); // 회전기호를 ' '로 구분하여 입력

		if (input == "1") { // 입력이 1이면 Cube 초기화
			system("cls");
			rubikscube.cubeReset();
		}
		else if (input == "2") { // 입력이 2면 Solve면 빠르게 Cube 맞추기
			system("cls");
			rubikscube.cubeSolving(false); 
			
			// Cube를 맞추는데 걸린 시간과 Solution 출력
			std::cout << "\n\n\nSolving Time : " << rubikscube.getSolvingTime() << " seconds"  << std::endl;
			std::cout << "Rotation Count : " << rubikscube.getCount() << " rotates\n" << std::endl;
			std::cout << rubikscube.getSolution() << std::endl;
		} 
		else if (input == "3") { // 입력이 3이면 느리게 Cube 맞추기
			system("cls");
			rubikscube.cubeSolving(true);

			std::cout << "\n\n\nSolving Time : " << rubikscube.getSolvingTime() << " seconds\n" << std::endl;
			std::cout << "Rotation Count : " << rubikscube.getCount() << " rotates\n" << std::endl;
			std::cout << rubikscube.getSolution() << std::endl;
		}
		else {
			//회전 기호 입력을 Cube에 적용하여 출력
			system("cls");
			rubikscube.inputtoQueue(input);
			rubikscube.rotatingCube(false, 0);
		}
	}
}