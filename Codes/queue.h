/*
22-1학기 EEE2020 데이터구조 End-Term Project
Queue를 이용한 Rubik's Cube Solving - OP Algorithm 구현
2020132002 물리학과
전현빈(justbecoz@yonsei.ac.kr)
2022/05/10 ~ 2022/06/09
*/

// 입력을 저장하여 순차적으로 Cube를 섞거나 Cube를 맞출 때 사용할 공식을 저장하여 순차적으로 실행하기 위한 Queue
// Node, Queue Class 선언 Header File

#ifndef QUEUE
#define QUEUE

#include <string>
#include <iostream>

class Node {
private:
	std::string symbol;
	Node* next;
	Node* prev;

public:
	Node(std::string);
	Node* getNext();
	Node* getPrev();
	std::string getSymbol();

	void setNext(Node*);
	void setPrev(Node*);
};

class Queue {
private:
	Node* head = NULL;
	Node* tail = NULL;

public:
	Queue();
	~Queue();
	void insertBack(std::string);
	bool popFront();
	Node* gethead();
	void printQueue();
	void inputtoqueue(std::string);
};
#endif