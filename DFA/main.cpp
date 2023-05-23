#include <iostream>
#include "DFA.h"

#pragma warning(disable : 4996)

constexpr auto INTSIZE = 4;
using namespace std;

void DFA_Creat(DFA* TEST)
{
	add_arc(TEST, 0, 1, 0);
	add_arc(TEST, 0, 2, 1);
	add_arc(TEST, 2, 1, 0);
	add_arc(TEST, 2, 3, 1);
	add_arc(TEST, 3, 0, 0);
}

DFA* DFA_union(DFA* A, DFA* B)
{
	struct parenode
	{
		int A;
		int B;
	};
	
	struct help
	{
		parenode from;
		parenode to;
		int letter;
	}state;

	bool check = true; 
	Node* curA = NULL;
	Node* curB = NULL;
	
	int i = 0;
	int aCounter = A->inital[0], bCounter = B->inital[0];
	
	help* VERTEX = (help*)malloc(sizeof(help) * (A->count + B->count));

	while (aCounter - A->count && bCounter - B->count)
	{
		for (curA = A->vertex[aCounter].head; curA != NULL; curA = curA->next)
		{
			for (curB = B->vertex[bCounter].head; curB != NULL; curB = curB->next)
			{
				if (curA->letter = curB->letter)
				{
					state.letter = curA->letter;
					state.from.A = aCounter;
					state.from.B = bCounter;
					state.to.A = curA->key;
					state.to.B = curB->key;

					VERTEX[i] = state;
					i++;
					check = true;
				}

			}
			if (!check)
			{

				state.letter = curA->letter;
				state.from.A = aCounter;
				state.to.A = curA->key;

				VERTEX[i] = state;
				i++;
				check = true;
			}
		}
	}

	// переименовать вершины:
	// построить по VERTX автомат
	return NULL;
}
void DFA_test()
{
	//int n = 4;

	////int numberOfInitial = 2; int namberOfFinal = 1;
	//int inital[] = { 0 };
	//int final[] = { 3 };

	//DFA* TEST = DFA_init(n, inital, final, sizeof(inital) / INTSIZE, sizeof(final) / INTSIZE);
	//DFA_Creat(TEST);
	//DFA_check(TEST, 7);
	//DFA_print(TEST);
	//cout << endl;
	DFA* A = DFA_int(12);
	//DFA* B = DFA_int(12);

	
	//DFA_print(DFA_union(A,B));
	DFA_printRange(A, 20);
	DFA_write(A, "outputA.txt");
	DFA_printRange(DFA_read( "outputA.txt"),20);
}


int main()
{
	DFA_test();
	return 0;
}