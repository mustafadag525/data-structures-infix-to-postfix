#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
  
// Stack tipi
struct Stack 
{ 
    int top; 
    unsigned kapasite; 
    int* array; 
}; 
  
// Stack Operasyonları
struct Stack* createStack( unsigned kapasite ) 
{ 
    struct Stack* stack = (struct Stack*)  
           malloc(sizeof(struct Stack)); 
  
    if (!stack)  
        return NULL; 
  
    stack->top = -1; 
    stack->kapasite = kapasite; 
  
    stack->array = (int*) malloc(stack->kapasite *  
                                   sizeof(int)); 
  
    return stack; 
} 
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1 ; 
} 
char peek(struct Stack* stack) 
{ 
    return stack->array[stack->top]; 
} 
char pop(struct Stack* stack) 
{ 
    if (!isEmpty(stack)) 
        return stack->array[stack->top--] ; 
    return '$'; 
} 
void push(struct Stack* stack, char op) 
{ 
    stack->array[++stack->top] = op; 
} 
  
  
// Verilen karakterin işlenen olup olmadığını kontrol etmek için bir yardımcı program işlevi için:
int isOperand(char ch) 
{ 
    return (ch >= 'a' && ch <= 'z') ||  
           (ch >= 'A' && ch <= 'Z'); 
} 
  
// Döndürülecek bir yardımcı program işlevi
// belirli bir operatörün önceliği
// Daha yüksek döndürülen değer,
// daha yüksek öncelik
int Prec(char ch) 
{ 
    switch (ch) 
    { 
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
  
  
// Ana işlev
// verilen infix ifadesini dönüştürür
// postfix ifadesi için. 
int infixToPostfix(char* exp) 
{ 
    int i, k; 
  
    // Bir kapasite yığını oluşturun
     // ifade boyutuna eşittir 
    struct Stack* stack = createStack(strlen(exp)); 
    if(!stack) // See if stack was created successfully  
        return -1 ; 
  
    for (i = 0, k = -1; exp[i]; ++i) 
    { 
          
        // Taranan karakter
         // bir işlenen, çıktıya ekleyin.
        if (isOperand(exp[i])) 
            exp[++k] = exp[i]; 
          
        // If the scanned character is an  
        // ‘(‘, push it to the stack. 
        else if (exp[i] == '(') 
            push(stack, exp[i]); 
          
        // Taranan karakter bir ")" ise,
         // yığından pop ve çıktı
         // bir ‘(‘ ile karşılaşılıncaya kadar.
        else if (exp[i] == ')') 
        { 
            while (!isEmpty(stack) && peek(stack) != '(') 
                exp[++k] = pop(stack); 
            if (!isEmpty(stack) && peek(stack) != '(') 
                return -1; // invalid expression              
            else
                pop(stack); 
        } 
        else // operatör tanımı
        { 
            while (!isEmpty(stack) &&  
                 Prec(exp[i]) <= Prec(peek(stack))) 
                exp[++k] = pop(stack); 
            push(stack, exp[i]); 
        } 
  
    } 
  
    //  stekteki tüm işlemler:
    while (!isEmpty(stack)) 
        exp[++k] = pop(stack ); 
  
    exp[++k] = '\0'; 
    printf( "%s", exp ); 
} 
  
// Programı test edelim
int main() 
{ 
    char exp[] = "a+b*(c^d-e)^(f+g*h)-i"; 
    printf( "\nInfix: %s\nPostfix: ", exp );
    infixToPostfix(exp); 
    return 0; 
}
