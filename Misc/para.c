#include <stdio.h>
#include <stdlib.h>

struct sNode {
	char data;
	struct sNode* next;
}*stack;

void push(int data){
	struct sNode* new = malloc(sizeof(struct sNode));
    new->data = data; new->next = stack;
    stack = new;
}

int pop(){
	if (stack) {
		struct sNode *top = stack;
		char res = top->data;
		stack = top->next;
		free(top);
		return res;
	}
    printf("Stack Underflow\n");
    exit(1);
}

int isMatchingPair(char character1, char character2){
	if (character1 == '(' && character2 == ')')
		return 1;
	else if (character1 == '{' && character2 == '}')
		return 1;
	else if (character1 == '[' && character2 == ']')
		return 1;
	else
		return 0;
}

int areBracketsBalanced(char exp[]){
	int i = 0; stack = NULL;
    while (exp[i]){
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
			push(exp[i]);
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (stack == NULL)
				return 0;
            else if (!isMatchingPair(pop(&stack), exp[i]))
				return 0;
		}
		i++;
	}
	return (stack == NULL) ? 1 : 0;
}

int main(){
	char exp[100];
    scanf("%s", exp);
    printf(areBracketsBalanced(exp)?"Balanced \n":"Not Balanced \n");
	return 0;
}