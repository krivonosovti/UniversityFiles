#include <iostream>
#include <fstream>
#pragma warning(disable : 4996)

constexpr auto MAX = 100;
constexpr auto INTSIZE = 4;
using namespace std;

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

DFA* DFA_init(int n, int initial[], int final[],int numberOfInitial, int numberOfFinal)
{
	DFA* g = (DFA*)malloc(sizeof(DFA) * n);
	g->numberOfFinal = numberOfFinal;
	g->numberOfInital = numberOfInitial;
	g->count = n;
	g->inital = initial;
	g->final = final;

	State* VERTEX = (State*)malloc(sizeof(State) * n);
	for (int i = 0; i < n; i++)
	{
		VERTEX[i].head = NULL;
		g->vertex = VERTEX;
	}
	return g;
}

void DFA_print(DFA* root)
{
	cout << "size = " << root->count<<endl;
	cout << "Initial states: ";
	for (int i = 0; i < root->numberOfInital; i++)
	{
		cout << root->inital[i] << ' ';
	}
	cout << endl;
	cout << "Final states: ";
	for (int i = 0; i < root->numberOfFinal; i++)
	{
		cout << root->final[i] << ' ';
	}
	cout << endl;
	//cout << "Final states: " << ;
	Node* cur;
	for (int i = 0; i < root->count; i++)
	{
		cur = root->vertex[i].head;
		while (cur)
		{
			cout << i << ' ' << cur->key<< " <" << cur->letter << ">" << endl;
			cur = cur->next;
		}	
	}
}

void DFA_free(DFA* root)
{
	for (int i = 0; i < root->count; i++)
	{
		Node* Cur = root->vertex[i].head, * temp = nullptr;
		while (Cur)
		{
			temp = Cur;
			Cur = Cur->next;
			free(temp);
		}
	}
	free(root->vertex);
	free(root);
}

Node* node_init(int a,int f) {
	Node* Cur = (Node*)malloc(sizeof(Node));
	if (Cur) {
		Cur->key = a;
		Cur->letter = f;
		Cur->next = NULL;
	}
	return Cur;
}

void add_arc(DFA* root, int from, int to, int f)
{
	if (root->count < from || root->count < to)
	{
		cout << "ERR: there is no such vertex";
		return;
	}
	if (!root->vertex[from].head)
	{
		root->vertex[from].head = node_init(to,f);
	}
	else 
	{
		Node* Cur = nullptr;
		for (Cur = root->vertex[from].head; Cur->next; Cur = Cur->next)
		{
			if (Cur->next->key == to)
				return;
		}
		Cur->next = node_init(to,f);
	}
}

DFA* DFA_read(const char* fileName)
{
	int numberOfInital, numberOfFinal, count;
	int i;
	char help[MAX], * token;

	ifstream fin(fileName);
	if (!fin)
		return NULL;

	// get number
	fin.getline(help, sizeof(help));

	token = strtok(help, ",");
	count = strtol(token, &token, 10);

	token = strtok(NULL, ",");
	numberOfInital = strtol(token, &token, 10);

	token = strtok(NULL, ",");
	numberOfFinal = strtol(token, &token, 10);

	int* inital = (int*)malloc(sizeof(int) * numberOfInital);
	int* final = (int*)malloc(sizeof(int) * numberOfFinal);
	//get initial 
	fin.getline(help, sizeof(help));
	i = 0;
	token = strtok(help, ",");

	while (token != NULL)
	{
		if (i > numberOfInital - 1)
		{
			cout << "ERR: number of Initial";
			return NULL;
		}
		inital[i] = strtol(token,&token,10);
		i++;
		token = strtok(NULL, ",");
	}

	//get final 
	fin.getline(help, sizeof(help));
	i = 0;
	token = strtok(help, ",");

	while (token != NULL)
	{
		if (i > numberOfFinal - 1)
		{
			cout << "ERR: number of Final";
			return NULL;
		}

		final[i] = strtol(token, &token, 10);
		i++;
		token = strtok(NULL, ",");
	}

	DFA* A = DFA_init(count, inital, final, numberOfInital, numberOfFinal);
	// get args		
	//i = 0;
	int f = 0;
	int to = 0;

	while (!fin.eof())
	{
		fin.getline(help, sizeof(help));

		token = strtok(help, ",");
		i = strtol(token, &token, 10);

		token = strtok(NULL, ",");
		to = strtol(token, &token, 10);

		token = strtok(NULL, ",");
		f = strtol(token, &token, 10);

		add_arc(A, i, to, f);
	}

	fin.close();
	return A;
}

void DFA_write(DFA* Automat, const char* fileName)
{
	ofstream fout(fileName);

	if (!fout)
		return;
	//write numbers 
	fout << Automat->count<<',' << Automat->numberOfInital << ',' << Automat->numberOfFinal;
	//write the initial states
	fout << " \n";
	if (Automat->numberOfInital == 0)
		fout << 0;
	else
	{
		fout << Automat->inital[0];
		for (int i = 1; i < Automat->numberOfInital; i++)
			fout << "," << Automat->inital[i];
	}
	//write the final states
	fout << " \n";
	if (Automat->numberOfFinal == 0)
		fout << 0;
	else
	{
		fout << Automat->final[0];
		for (int i = 1; i < Automat->numberOfFinal; i++)
			fout << "," << Automat->inital[i];
	}

	//write edges 
	
	for (int i = 0; i < Automat->count; i++)
	{
		Node* cur = Automat->vertex[i].head;
		for (cur; cur != NULL; cur = cur->next) 
		{
			fout <<"\n" << i << ',' << cur->key << ',' << cur->letter;
		}
	}

	fout.close();
}

bool isFinal(DFA* A, int state)
{
	for (int i = 0; i < A->numberOfFinal; i++)
	{
		if (A->final[i] == state)
			return true;
	}
	return false;
}

bool DFA_check(DFA* Automat, int x)
{
	int state = Automat->inital[0];
	Node* cur;
	for (;x;x >>= 1)
	{
		cur = Automat->vertex[state].head;
		for (; cur; cur = cur->next)
		{
			if ((x & 1) == cur->letter)
			{
				state = cur->key;
				break;
			}
			// какой-то выход 
		}
		if (!cur) return false;
	}
	if (isFinal(Automat, state))
		return true;
	else
	{
		for (int i = 0; i < Automat->count; i++)
		{
			cur = Automat->vertex[state].head;
			for (; cur; cur = cur->next)
			{
				if (0 == cur->letter)
				{
					state = cur->key;
					if (isFinal(Automat, state))
						return true;
				}
			}
			if (!cur) return false;
		}
		
	}
	return false; // state \in Automat->final
}

void DFA_printRange(DFA* a, int x)
{
	for (int i = 0; i <= x; i++)
	{
		if (DFA_check(a, i))
			cout << i << ' ';
	}
}

DFA* DFA_int(const int a)
{
	int x = a;
	int size = 0;
	while (x)
	{
		size++;
		x >>= 1;
	}

	int* inital = (int*)calloc(sizeof(int),1);
	int* final = (int*)malloc(sizeof(int));
	final[0] = size;


	DFA* res = DFA_init(size + 2, inital, final, 1, 1);
	x = a;
	int n = 0;
	for (int n = 0; n < size; x >>= 1, n++)
	{
		add_arc(res, n, n + 1, x & 1);
		add_arc(res, n, size+1, !(x & 1));	
	}
	return res;
}

DFA* DFA_complement(DFA* dfa)
{

	DFA* res = DFA_init(dfa->count, dfa->final, dfa->inital, dfa->numberOfFinal, dfa->numberOfInital);
	Node* cur = (Node*)malloc(sizeof(Node));

	for (int i = 0; i < dfa->count; i++)
	{
		for (cur = dfa->vertex[i].head; cur != NULL; cur = cur->next)
			add_arc(res, i,cur->key, cur->letter);
	}
	return res;
}