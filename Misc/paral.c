#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack{
	int top;
	unsigned capacity;
	char* array;
}*stack;

struct Stack* createStack( unsigned capacity ){
	struct Stack* new = malloc(sizeof(struct Stack));
	if (!new) return NULL;
	new->top = -1; new->capacity = capacity;
	new->array = (char*) malloc(new->capacity * sizeof(char));
	if (!new->array) return NULL;
	return new;
}

char pop(){
	if (stack->top == -1) return '$';
	return stack->array[stack->top--] ;
}
void push(char op){
	stack->array[++stack->top] = op;
}

int isMatchingPair(char character1, char character2){
    //printf("%c %c\n",character1,character2);
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
	int i = 0; stack = createStack(strlen(exp));
    while (exp[i]){
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
			push(exp[i]);
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (stack->top == -1)
				return 0;
            else if (!isMatchingPair(pop(), exp[i]))
				return 0;
		}
		i++;
	}
	return (stack->top == -1) ? 1 : 0;
}

int main(){
	char exp[100];
    scanf("%[^\n]s", exp);
    printf(areBracketsBalanced(exp)?"Balanced \n":"Not Balanced \n");
	return 0;
}