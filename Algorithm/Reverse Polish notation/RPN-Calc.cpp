//g++-9 RPN-Calc.cpp -o RPN-Calc

#include<stdio.h>
#include<stdlib.h>/*malloc&&free*/
#include<string.h>/*strlen*/

#define  ElemType int

#define IF_ITS_NUMBER(n) (n>=48&&n<=57)?1:0

//Struct
typedef struct Stack{
    ElemType data;
    char Operator;
    int count;
    struct Stack *next;
}*StackList,StackNode;

//Core
bool bracketcheck(char str[],int len);
int infix2suffix(char infix[],char suffix[],int len);
int RPN_Calc(char str[],unsigned long len);
//Stack(LinkList)
bool initStack(StackList &L);
bool Push(StackList &L,ElemType x);
bool Push(StackList &L,char x);
bool Pop(Stack &L,ElemType &x);
bool Pop(StackList &L,char &x);


bool initStack(StackList &L){
    StackNode *s;
    if(!(s=(StackList)malloc(sizeof(StackNode))))
        return 0;
    L->next=s;
    s->next=NULL;
    L->count=0;
    return 1;
}

bool Push(StackList &L,ElemType x){
    StackNode *p=L->next;
    StackNode *s;
    if(!(s=(StackList)malloc(sizeof(StackNode))))
        return 0;
    s->data=x;
    s->next=p->next;
    p->next=s;
    return 1;
}

bool Push(StackList &L,char x){ //PUSH Overload
    StackNode *p=L->next;
    StackNode *s;
    if(!(s=(StackList)malloc(sizeof(StackNode))))
        return 0;
    s->Operator=x;
    s->next=p->next;
    p->next=s;
    L->count++;
    return 1;
}

bool Pop(StackList &L,ElemType &x){
    StackNode *p=L->next,*pre;
    pre=p;
    p=p->next;
    if(p==NULL) return 0; //Stack Empty
    x=p->data;
    pre->next=p->next;
    free(p);
    return 1;
}

bool Pop(StackList &L,char &x){ //Pop Overload
    StackNode *p=L->next,*pre;
    pre=p;
    p=p->next;  
    //if(!p) return 0; //Stack Empty
    x=p->Operator;
    pre->next=p->next;
    L->count--;
    free(p);
    return 1;
}

bool GetTop(StackList &L,char &x){
    StackNode *p=L->next;
    p=p->next;
    if(!p) return 0;
    x=p->Operator;
    return 1;
}

bool StackEmpty(StackList L){
    if(L->count==0) return 1;
    return 0;
    /*StackNode *p=L->next;
    p=p->next;
    if(!p) return 1;
    return 0;
    */
}

//Read RPN and push the result
int RPN_Calc(char str[],unsigned long len){
    StackList L;
    ElemType a,b,num=0,top;
    initStack(L);

    for(int i=0;i<len;i++)
    {
        if(IF_ITS_NUMBER(str[i])) //If a number is detected, operate directly
            num=num*10+str[i]-48;
            //Push(L,str[i]-48);//char->int
        else if(str[i]=='.') //If a dot is detected, it means that a number has been entered
        {
            Push(L,num);
            num=0;
        }
        else //If the operator is detected, operate it, and push the result onto the stack after the end
        {
            Pop(L,a);
            Pop(L,b);
            if(str[i]=='+')
                Push(L,a+b);
            if(str[i]=='-')
                Push(L,b-a);
            if(str[i]=='*')
                Push(L,b*a);
            if(str[i]=='/')
                Push(L,b/a);
        }
    }
    Pop(L,top);
    printf("[*]%d\n",top);
    return 0;
}


/*
bool bracketcheck(char str[],int len){
    StackNode *S;
    if(!initStack(S))
        return 0;
    for(int i;i<len;i++){
        if(str[i]=='(')
            Push(S,str[i]);
        else if(str[i]==')'){
            char TopElem;
            if(!Pop(S,TopElem))
                return 0;
            if(TopElem!='(')
                return 0;
        }
    }
    return 1;
}
*/

int infix2suffix(char infix[],char suffix[],int len){
    int i=0,j=0;
    StackList L;
    initStack(L);

    for(;i<len;i++)
    {
        if(IF_ITS_NUMBER(infix[i]))//if a number is detected,add it into suffix
        {
            suffix[j++]=infix[i];
            suffix[j++]='.';
        }
        else if(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/')//if an operator is detected
        {
            char opt,top;
            GetTop(L,opt);
            //printf("opt:%c",opt);
            if(infix[i]=='+'||infix[i]=='-'){ //if meet +/-
                int Empty=StackEmpty(L); //Not Empty:0 Empty:1
                //printf("Empty=%d",Empty);
                if(opt=='+'||opt=='-'){ //Empty the Stack
                   while(!Empty){
                       char tmp;
                        Pop(L,tmp);
                        Empty=StackEmpty(L);
                        //printf("Empty:%d",Empty);
                        //printf("tmp:%d\n",tmp);
                        suffix[j++]=tmp;
                        //printf("suffix:%s\n",suffix);
                    }
                }
                Push(L,infix[i]);
            }
        }
        
    }
    char tmp;
    Pop(L,tmp);
    suffix[j++]=tmp;
    return strlen(suffix);
}

int main(){
    StackList L;
    char infix[200],suffix[200];
    printf("===Easy Calc===\n");
    printf("By Migraine\n");
    printf(">>");
    scanf("%s",infix);

    int len=infix2suffix(infix,suffix,strlen(infix));
    printf("suffix=%s\n",suffix);

/*
    char i='+';
    char s1,s2,s3;
    initStack(L);
    Push(L,i);
    Pop(L,s1);
    if(StackEmpty(L)) printf("Empty!\n");
    //if(!Pop(L,s2)) printf("No\n");
    printf("%c\n",s2);
*/

    //printf("len=%lu\n",strlen(suffix)); //?????没有这句，infix传参就传不全(clang-1001.0.46.4编译)
    RPN_Calc(suffix,len); //RPN2Result
    //bracketcheck(infix,strlen(infix));
    return 0;
}


