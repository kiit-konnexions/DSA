#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
typedef struct stack{
	int top;
	unsigned capacity;
	float *array;
}Stack;
Stack *createStack( unsigned capacity ){
	Stack *new = malloc(sizeof(Stack));
	new->top = -1; new->capacity = capacity;
	new->array = calloc(new->capacity , sizeof(float));
	if (!new->array) return NULL; return new;
}

int isEmpty(Stack *stack){
	return stack->top == -1 ;
}
float peek(Stack *stack){
	return stack->array[stack->top];
}
float pop(Stack *stack){
	if (!isEmpty(stack))
		return stack->array[stack->top--] ;
	return '$';
}
void push(Stack *stack, float op){
	stack->array[++stack->top] = op;
}

int Prec(char ch){
	switch (ch){
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}
void applyOP(Stack *stack, float val1, char ch, float val2){
	switch (ch) {
        case '+': push(stack, val1 + val2); break;
        case '-': push(stack, val1 - val2); break;
        case '*': push(stack, val1 * val2); break;
        case '/': push(stack, val1 / val2); break;
		case '^': push(stack, (float)pow(val1 ,val2)); break;
    }
}

float evaluateInfix(char *exp){
	Stack *values = createStack(strlen(exp));
	Stack *ops = createStack(strlen(exp));
	int l = strlen(exp);
    for(int i = 0; i < l; i++){
		if(exp[i] == ' ') continue;
		else if(exp[i] == '(')
            push(ops, exp[i]);
        
        else if(isdigit(exp[i])){
            int val = 0;
			while(i < l && isdigit(exp[i])){
                val = (val*10) + (exp[i]-'0');
                i++;
            }
			push(values,val); i--;
        }
		
		else if(exp[i] == ')'){
            while(!isEmpty(ops) && peek(ops) != '('){
                int val2 = pop(values);
				int val1 = pop(values);
				applyOP(values, val1, pop(ops), val2);
            }
             
            if(!isEmpty(ops)) pop(ops);
        }
         
        else{
			while(!isEmpty(ops) 
			&& Prec(peek(ops)) >= Prec(exp[i])){
                float val2 = pop(values);
				float val1 = pop(values);
                applyOP(values, val1, pop(ops), val2);
            }
			push(ops, exp[i]);
        }
    }
     
    while(!isEmpty(ops)){
        float val2 = pop(values);
		float val1 = pop(values);
		applyOP(values, val1, pop(ops), val2);
    }
     
    return pop(values);
}
float evaluatePostfix(char *exp){
	Stack *stack = createStack(strlen(exp));
	int i, num, sum;
	if (!stack) return -1;

	for (i = 0; exp[i]; ++i){
		if(exp[i] == ' ') continue;
		else if (isdigit(exp[i])){
			for(num=0; isdigit(exp[i]); i++)
				num = num*10 + (exp[i]-'0');
			i--;
			push(stack,num);
        }
		else{
			float val1 = pop(stack), val2 = pop(stack);
			applyOP(stack, val2,exp[i],val1);
		}
	}
	return pop(stack);
}
float evaluatePrefix(char *exp){
    Stack *stack = createStack(strlen(exp));
    for (int i = strlen(exp) - 1; i >= 0; i--) {
		if(exp[i] == ' ') continue;
		if (isdigit(exp[i])) {
			float num = 0, j = i;
            while (i < strlen(exp) && isdigit(exp[i]))
                i--;
            i++;
 
            for (int k = i; k <= j; k++)
                num = num  *10 + (exp[k] - '0');
			push(stack, num);
        }
        else {
			float val1 = pop(stack), val2 = pop(stack);
            applyOP(stack, val1, exp[i], val2);
        }
    }
	return pop(stack);
}

char *reverse(char *exp){
    int l = strlen(exp);
    char *out = malloc(l*sizeof(char));
    out[l] = '\0';
    for(int i=0,j=l-1; exp[i]; i++,j--){
        char ch = exp[i];
        if(ch == '(') out[j] = ')';
        else if(ch == ')') out[j] = '(';
        else out[j] = ch;
    }
    return out;
}
char *infixToPostfix(char *exp){
	int l = strlen(exp), i = 0, k = -1;;
	Stack *stack = createStack(l);
	if(!stack) return NULL ;
    char *out = malloc(l*sizeof(char));
	while(exp[i]){
		if(exp[i] == ' ') i++;
        else if (isalnum(exp[i]))
			out[++k] = exp[i++];
        else if (exp[i] == '(')
			push(stack, exp[i++]);
        else if (exp[i] == ')'){
			while (!isEmpty(stack) && peek(stack) != '(')
				out[++k] = pop(stack);
			if (!isEmpty(stack) && peek(stack) != '('){
                printf("Invalid Epression\n");
				return NULL;		
            }
            else pop(stack); i++;
		}
		else{
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
				out[++k] = pop(stack);
			push(stack, exp[i++]);
		}
	}

	while (!isEmpty(stack))
		out[++k] = pop(stack);
	out[++k] = '\0';
	return out;
}
char *infixToPrefix(char *exp){
    return reverse(infixToPostfix(reverse(exp)));
}

void convert(Stack *stack, char *exp, char *out, int i, int *j){
	if(exp[i] == ' ') return;
	else if (isalnum(exp[i])){
		out[(*j)++] = exp[i];
		while (!isEmpty(stack) && (stack->array[stack->top] == '$')) {
			char ch = pop(stack); out[(*j)++] = pop(stack);
		}
		push(stack,'$');
	}
	else push(stack,exp[i]);
}
void convert2(Stack *stack, char *exp, char *out, int i, int *j){
	if(exp[i] == ' ') return;
    else if (isalnum(exp[i])){
		out[(*j)++] = exp[i];
		if(!isEmpty(stack)) out[(*j)++] = pop(stack);
	}
	else push(stack, exp[i]);
}

char *postfixToPrefix(char *exp){
	int l = strlen(exp), i, j=0;
	Stack *stack = createStack(l);
	char *out = malloc(l*sizeof(char));
	for (i = l - 1; i >= 0; i--)
		convert(stack,exp,out,i,&j);
	out[j] = '\0';
	return strrev(out);
}
char *postfixToInfix(char *exp){
	int l = strlen(exp), i, j=0;
	Stack *stack = createStack(l);
	char *out = malloc(2*l*sizeof(char));
	for(i = l - 1; i >= 0; i--)
		convert2(stack, exp, out, i, &j);
	out[j] = '\0';
	return strrev(out);
}

char *prefixToPostfix(char *exp){
	int l = strlen(exp), i, j=0;
	Stack *stack = createStack(l);
	char *out = malloc(l*sizeof(char));
	for(i=0; i<l; i++)
		convert(stack, exp, out, i, &j);
	out[j] = '\0';
	return out;
}
char *prefixToInfix(char *exp){
	int l=strlen(exp), i, j=0;
	Stack *stack = createStack(l);
	char *out = malloc(2*l*sizeof(char));
	for(i=0; i<l; i++)
		convert2(stack, exp, out, i, &j);
	out[j] = '\0';
	return strrev(out);
}

int main(){
	char exp[100]; //char exp[] = "a+b*(c^d-e)^(f+g*h)-i"; (A+B)*(C-D)
	printf("\nEnter Infix expression : ");
	scanf("%[^\n]s",exp);
	printf ("Postfix Expression of %s : %s\n", exp, infixToPostfix(exp));
    printf ("Prefix Expression of %s : %s\n", exp, infixToPrefix(exp));

	getchar();
	printf("\nEnter Postfix expression : ");
	scanf("%[^\n]s",exp);
    printf ("Infix Expression of %s : %s\n", exp, postfixToInfix(exp));
    printf ("Prefix Expression of %s : %s\n", exp, postfixToPrefix(exp));
	
	getchar();
	printf("\nEnter Prefix expression : ");
	scanf("%[^\n]s",exp);
    printf ("Infix Expression of %s : %s\n", exp, prefixToInfix(exp));
    printf ("Postfix Expression of %s : %s\n", exp, prefixToPostfix(exp));

	getchar();
	printf("\nEnter Infix expression : ");
	scanf("%[^\n]s",exp);
	printf ("Infix evaluation: %.2f\n", evaluateInfix(exp));

	getchar();
	printf("\nEnter postfix expression : ");
	scanf("%[^\n]s",exp);
	printf ("postfix evaluation: %.2f\n", evaluatePostfix(exp));
	
	getchar();
	printf("\nEnter prefix expression : ");
	scanf("%[^\n]s",exp);
	printf ("prefix evaluation: %.2f\n", evaluatePrefix(exp));
	return 0;
}