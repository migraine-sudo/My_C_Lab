# 逆波兰式计算器实现



## 1.实现方案

输入---括号判断--->中缀表达式---解析---->后缀表达式----计算--->结果



## 2.细节

**中缀转后缀**

逐个词检测，检测到

- 遇到**操作数**直接加入后缀表达式
- 遇到**界限符**,如果是**(**则直接入栈，如果是**)**则弹出所有括号之间的运算符，加入后缀表达式。
- 遇到**运算符**依次从栈中弹出优先级大于或者等于当前运算符的所有运算符，直到碰到栈底或者**( 符号**

**后缀运算**

逐词检测，检测到

- **操作数**入栈
- 扫描到**运算符符**则弹出两个栈顶元素，运算出相应结果，**将结果写回栈顶**。

**PS**:为了能识别多位数，我生成的后缀表达式通过*.*来分割数字，例如*12+24*生成的后缀表达式为*12.24.+*

![zzBgQ1](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/zzBgQ1.png)

## 3.实现

后缀表达式计算

```c++

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
```

生成后缀表达式

```c++
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
```



因为时间原因，以下功能并没有实现

- 对乘法除法的支持
- 栈实现有一些内存问题
- 没有对括号的支持

运行效果，不过因为栈实现等关系，可能导致bus error，以后有时间再修改。

![braBK9](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/braBK9.png)



**坑**

传递参数char[]类型总是传递不完整，输入过长就会提前截断。但是在传参前对char[]执行printf语句，就能避免出现这个问题。非常奇怪，使用clang就这样，使用别人的GCC也没有出现过这种问题。[在mac下使用gcc而不是clang](https://blog.csdn.net/u010167269/article/details/51951582)

![3K8fsS](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/3K8fsS.png)

![rdEcEo](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/rdEcEo.png)



**收获**

终于会用C宏定义写函数了(逃

碰到的bus error，用mac下的gdb发现断在了Pop函数上。。脱离了peda的gdb调试，学了几个命令

 ```
display /20i $pc 自动输出ip指向的20行汇编
 ```

