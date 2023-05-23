//#include <iostream>
//using namespace std;
//
////#define OPEN -1;
////#define PLUS -2;
////#define MINUS -3;
////#define MULT -4;
////#define DIV -5;
////#define GSD -6;
////#define LCM -7;
////#define CLOSE -8;
//
//int gcd(int a, int b)
//{
//	int remember;
//	while (b != 0)
//	{
//		remember = b;
//		b = a % b;
//		a = remember;
//	}
//	return abs(a);
//}
//int lcm(int n1, int n2)
//{                                              //caculating lcm using the formula: lcm x gcd = n1 x n2
//	int res, g;
//	g = gcd(n1, n2);
//	res = n1 * n2 / g;
//	return res;
//}
////ex2 Reverse Polish notation and Stack;
//struct token {
//	char type; // o - operator d - digit 
//	int priority;
//	int value;
//	token* next = NULL;
//	token* Head = NULL;
//};
//struct node
//{
//	token* data;
//	struct node* next;
//}; // должно быть int data;
//typedef struct stack
//{
//	struct node* head;
//} stack;
//int stack_init(stack* s)
//{
//	s->head = NULL;
//	return 0;
//}
//int token_init(token* TOKEN)
//{
//	TOKEN->Head = NULL;
//	return 0;
//}
///// if empty return 1; else return 0;
//int stack_is_empty(const stack* s)
//{
//	return !s->head;
//}
//void pushtoken(token* TOKEN, const char type, const int value, const int priority)
//{
//	token* elem = new token();
//	elem->type = type;
//	elem->value = value;
//	elem->priority = priority;
//	if (!TOKEN->Head)
//	{
//		TOKEN->Head = elem;
//		return;
//	}
//	token* cur = TOKEN->Head;
//	for (cur; cur->next != NULL; cur = cur->next);
//	cur->next = elem;
//}
//int stack_push(stack* s, token* e)
//{
//	node* n = (node*)malloc(sizeof(struct node));
//	if (!n) return -1;
//	n->next = s->head;
//	n->data = e;
//	s->head = n;
//	return  0;
//}
//int stack_pop(stack* s, token* e) // не знаю работоспособность 
//{
//	node* t = s->head;
//	if (!t) return -1;
//	//	if (*e) *e = t->data;
//	pushtoken(e, t->data->type, t->data->value, t->data->priority);
//	s->head = s->head->next;
//	free(t);
//	return 0;
//}
//int stack_free(stack* s)
//{
//	while (!stack_pop(s, NULL));
//	return !stack_is_empty(s);
//}
//int get_priority(char s)
//{
//	//if (!s) return 0;
//	char priority[] = { '(','-', '*' ,'g',')','+','/','l' };
//	int i = 0;
//	while (s != priority[i]) i++;
//	return i % 4;
//}
//
//token* str_to_token(const char* str)
//{
//	int i = 0, s = 0, value, size = strlen(str);
//	bool check = true;
//	token* a = (token*)malloc(sizeof(token));
//	token_init(a);
//	if (!a)
//	{
//		cout << "ERR: Memory is not allocated by the system.";
//		return NULL;
//	}
//	while (i < size)
//	{
//		if (check)
//		{
//			value = 0;
//			check = false;
//		}
//		if (isdigit(str[i]))
//		{
//			value = value * 10 + ((int)str[i] - 48);
//		}
//		else
//		{
//			check = true;
//			if (!(str[i] == '(' || str[i - 1] == ')'))
//			{
//				pushtoken(a, 'd', value, -1);
//			}
//			if (str[i] == '(')
//				pushtoken(a, 'o', -1, 0);
//			else if (str[i] == '+')
//				pushtoken(a, 'o', -2, 1);
//			else if (str[i] == '-')
//				pushtoken(a, 'o', -3, 1);
//			else if (str[i] == '*')
//				pushtoken(a, 'o', -4, 2);
//			else if (str[i] == '/')
//				pushtoken(a, 'o', -5, 2);
//			else if (str[i] == 'g')
//				pushtoken(a, 'o', -6, 3);
//			else if (str[i] == 'l')
//				pushtoken(a, 'o', -7, 3);
//			else if (str[i] == ')')
//				pushtoken(a, 'o', -8, 0);
//		}
//		i++;
//	}
//	if (value)
//		pushtoken(a, 'd', value, -1);
//	return a;
//}
//void print_token(token* TOKEN)
//{
//	token* cur;
//	for (cur = TOKEN->Head; cur != NULL; cur = cur->next)
//	{
//
//		cout << cur->type << ' ' << cur->priority << ' ' << cur->value << endl;
//
//	}
//	cout << endl;
//}
//void print_str(char* str, int size)
//{
//	for (int i = 0; i < size; i++)
//		cout << str[i];
//}
//void print_str_from_token(token* TOKEN)
//{
//	token* cur;
//	for (cur = TOKEN->Head; cur != NULL; cur = cur->next)
//	{
//		if (cur->type == 'd')
//			cout << cur->value << ' ';
//		if (cur->type == 'o')
//		{
//			if (cur->value == -1)
//				cout << '(' << ' ';
//			else if (cur->value == -2)
//				cout << '+' << ' ';
//			else if (cur->value == -3)
//				cout << '-' << ' ';
//			else if (cur->value == -4)
//				cout << '*' << ' ';
//			else if (cur->value == -5)
//				cout << '/' << ' ';
//			else if (cur->value == -6)
//				cout << 'g' << ' ';
//			else if (cur->value == -7)
//				cout << 'l' << ' ';
//			else if (cur->value == -8)
//				cout << ')' << ' ';
//		}
//	}
//	cout << endl;
//}
//token* Polish_notation(token* TOKEN)
//{
//	//char input_string[5];
//	token* input_string = (token*)malloc(sizeof(token));
//	token_init(input_string);
//	stack* Notation = (stack*)malloc(sizeof(stack));
//	token* tresh = (token*)malloc(sizeof(token));
//	token_init(tresh);
//	stack_init(Notation);
//	for (token* cur = TOKEN->Head; cur != NULL; cur = cur->next)
//	{
//		if (cur->type == 'd')
//		{
//			pushtoken(input_string, 'd', cur->value, cur->priority);
//			continue;
//		}
//		if (cur->type == 'o' && (!(cur->value == -1 || cur->value == -8)))
//		{
//			if (stack_is_empty(Notation))
//			{
//				stack_push(Notation, cur);
//				continue;
//			}
//			else if (!stack_is_empty(Notation))
//			{
//				if (Notation->head->data->priority < cur->priority)
//				{
//					stack_push(Notation, cur);
//					continue;
//				}
//			}
//			if (!stack_is_empty(Notation))
//			{
//				while (true)
//				{
//					if (Notation->head == nullptr) break;
//					else if (Notation->head->data->priority >= cur->priority)
//					{
//						stack_pop(Notation, input_string);
//					}
//					else break;
//				}
//				if (stack_is_empty(Notation))
//				{
//					stack_push(Notation, cur);
//					continue;
//				}
//				else if (!stack_is_empty(Notation))
//				{
//					if (Notation->head->data->priority < cur->priority)
//					{
//						stack_push(Notation, cur);
//						continue;
//					}
//				}
//			}
//
//		}
//		if (cur->value == -1)
//		{
//			stack_push(Notation, cur);
//			continue;
//		}
//		if (cur->value == -8)
//		{
//			while (Notation->head->data->value != -1)
//			{
//				stack_pop(Notation, input_string);
//			}
//			stack_pop(Notation, tresh);
//			continue;
//		}
//	}
//
//	while (!stack_is_empty(Notation))
//	{
//		stack_pop(Notation, input_string);
//	}
//	stack_free(Notation);
//	free(tresh);
//	return input_string;
//}
//
//token* calculate(int first, int second, token* operation)
//{
//	token* result = (token*)malloc(sizeof(token));
//	token_init(result);
//
//	if (operation->value == -2)
//		pushtoken(result, 'd', first + second, -1);
//	else if (operation->value == -3)
//		pushtoken(result, 'd', first - second, -1);
//	else if (operation->value == -4)
//		pushtoken(result, 'd', first * second, -1);
//	else if (operation->value == -5)
//		pushtoken(result, 'd', first / second, -1);
//	else if (operation->value == -6)
//		pushtoken(result, 'd', gcd(first, second), -1);
//	else if (operation->value == -7)
//		pushtoken(result, 'd', lcm(first, second), -1);
//
//	return result;
//
//}
//
//int find_value(token* polish_notation)
//{
//	stack* Notation = (stack*)malloc(sizeof(stack));
//	stack_init(Notation);
//	token* first = (token*)malloc(sizeof(token));
//	token* second = (token*)malloc(sizeof(token));
//	token_init(first);
//	token_init(second);
//	token* result = (token*)malloc(sizeof(token));
//	token_init(result);
//	for (token* cur = polish_notation->Head; cur != NULL; cur = cur->next)
//	{
//		if (cur->type == 'd')
//		{
//			stack_push(Notation, cur);
//			continue;
//		}
//		if (cur->type == 'o')
//		{
//			stack_pop(Notation, first);
//			stack_pop(Notation, second);
//			stack_push(Notation, calculate(first->Head->value, second->Head->value, cur)->Head);
//			token_init(first);
//			token_init(second);
//		}
//	}
//	stack_pop(Notation, result);
//	return result->Head->value;
//}
//int main()
//{
//	const char* str = "1+(2+4)*7g14";
//	token* a, * b;
//	a = (token*)malloc(sizeof(token));
//	a = str_to_token(str);
//	print_token(a);
//	print_str_from_token(a);
//	b = Polish_notation(a);
//	print_str_from_token(b);
//	cout << find_value(b);
//	return 0;
//}