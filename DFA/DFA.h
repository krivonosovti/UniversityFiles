#pragma once
struct Node
{
	//int color;
	int key;
	int letter;
	Node* next;
};
struct State
{
	Node* head;
};
struct DFA
{
	int count;
	State* vertex;
	int* inital;
	int numberOfInital;
	int* final;
	int numberOfFinal;
};

DFA* DFA_init(int n, int initial[], int final[], int numberOfInitial, int numberOfFinal);
void DFA_print(DFA* root);
void DFA_free(DFA* root);
Node* node_init(int a, int f);
void add_arc(DFA* root, int from, int to, int);

DFA* DFA_read(const char* fileName);
void DFA_write(DFA* Automat, const char* fileName);


bool DFA_check(DFA* Automat, int x);

void DFA_printRange(DFA* a, int x);
DFA* DFA_int(const int a);
DFA* DFA_complement(DFA* dfa);
