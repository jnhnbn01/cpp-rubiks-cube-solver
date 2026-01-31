/*
22-1학기 EEE2020 데이터구조 End-Term Project
Queue를 이용한 Rubik's Cube Solving - OP Algorithm 구현
2020132002 물리학과
전현빈(justbecoz@yonsei.ac.kr)
2022/05/10 ~ 2022/06/09
*/

// Queue Class 구현 .cpp File

#include "queue.h"

Node::Node(std::string symbol) {
	this->symbol = symbol;
	this->next = NULL;
	this->prev = NULL;
}

Node* Node::getNext() {
	return this->next;
}

Node* Node::getPrev() {
	return this->prev;
}

std::string Node::getSymbol() {
	return this->symbol;
}

void Node::setNext(Node* next) {
	this->next = next;
}

void Node::setPrev(Node* prev) {
	this->prev = prev;
}

Queue::Queue() {
	head = NULL;
	tail = NULL;
}

Queue::~Queue() {
	Node* deleteNode = head;
	while (deleteNode != NULL) {
		head = head->getNext();
		delete deleteNode;
		deleteNode = head;
	}
}

void Queue::insertBack(std::string symbol) {
	Node* newNode = new Node(symbol);
	Node* temp = tail;
	if (head == NULL) {
		head = newNode;
		tail = newNode;;
	} else {
		tail->setNext(newNode);
		tail = newNode;
		tail->setPrev(temp);
	}
}

bool Queue::popFront() {
	Node* deleteNode = head;
	if (head == NULL) {
		std::cout << "The Queue is empty." << std::endl;
		return false;
	} 
	if (head->getNext() == NULL) {
		head = NULL;
	}
	else {
		head = head->getNext();
		head->setPrev(NULL);
	}
	delete deleteNode;
	return true;
}

void Queue::printQueue() {
	Node* currentNode = head;
	if (head == NULL) {
		std::cout << "The Queue is empty." << std::endl;
	} else {
		while (currentNode != NULL) {
			std::cout << currentNode->getSymbol();
			if (currentNode->getNext() != NULL) {
				std::cout << " > ";
			}
			currentNode = currentNode->getNext();
		}
		std::cout << std::endl;
	}
	
}

Node* Queue::gethead() {
	return this->head;
}

void Queue::inputtoqueue(std::string symbols) { // 문자열을 ' '를 기준으로 끊어서 각각 Queue에 한 Node로 저장하는 함수
	int index = -1;
	std::string symbol = "";
	char tempsymbol;

	for (int i = 0; i < symbols.length(); i++) {
		tempsymbol = symbols[i];
		if (tempsymbol == ' ') {
			symbol = symbols.substr(index + 1, i - index - 1);
			index = i;
			this->insertBack(symbol);
		}
	}
	symbol = symbols.substr(index + 1, symbols.length());
	this->insertBack(symbol);
}