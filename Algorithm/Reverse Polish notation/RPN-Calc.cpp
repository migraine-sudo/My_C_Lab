#include<stdio.h>
#include<stdlib.h>/*malloc&&free*/
#include<string.h>/*strlen*/

#define  ElemType int

#define IF_ITS_NUMBER(n) (n>=48&&n<=57)?1:0

//Struct
typedef struct Stack{
    ElemType data;
    struct Stack *next;
}*StackList,StackNode;

//Core
bool bracketcheck(char str,int len);
bool infix2suffix();
int RPN_Calc(char str[],unsigned long len);
//Stack(LinkList)
bool initStack(StackList &L);
bool Push(StackList &L,ElemType x);
bool Pop(Stack &L,ElemType &x);


bool initStack(StackList &L){
    StackNode *s;
    if(!(s=(StackList)malloc(sizeof(StackNode))))
        return 0;
    L->next=s;
    s->next=NULL;
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

bool Pop(StackList &L,ElemType &x){
    StackNode *p=L->next,*pre;
    pre=p;
    p=p->next;
    if(!p) return 0; //Stack Empty
    x=p->data;
    pre->next=p->next;
    free(p);
    return 1;
}

int RPN_Calc(char str[],unsigned long len){
    StackList L;
    ElemType a,b,num=0,top;
    initStack(L);
    //printf("%s",str);
    for(int i=0;i<len;i++)
    {
        if(IF_ITS_NUMBER(str[i]))
            num=num*10+str[i]-48;
            //Push(L,str[i]-48);//char->int
        else if(str[i]=='.')
        {
            Push(L,num);
            num=0;
        }
        else
        {
            Pop(L,a);
            Pop(L,b);
            if(str[i]=='+')
                Push(L,a+b);
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

int main(){
    StackList L;
    char infix[200];
    printf("===Easy Calc===\n");
    printf("By Migraine\n");
    printf(">>");
    scanf("%s",infix);

    printf("len=%lu\n",strlen(infix)); //?????没有这句，infix传参就传不全(clang-1001.0.46.4编译)
    RPN_Calc(infix,strlen(infix));
    //bracketcheck(infix,strlen(infix));
    //printf("%lu",strlen(infix));

    //printf("%s\n",infix);
    //if(IFNum(infix[0])) //Check if Num
        //printf("%d",infix[0]-48);//char->int
    return 0;
}


