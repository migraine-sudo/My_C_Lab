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







**坑**

传递参数char[]类型总是传递不完整，输入过长就会提前截断。但是在传参前对char[]执行printf语句，就能避免出现这个问题。非常奇怪，使用clang就这样，使用别人的GCC也没有出现过这种问题。[在mac下使用gcc而不是clang](https://blog.csdn.net/u010167269/article/details/51951582)

![3K8fsS](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/3K8fsS.png)

![rdEcEo](https://gitee.com/p0kerface/blog_image_management/raw/master/uPic/rdEcEo.png)



**收获**

终于会用C宏定义写函数了(逃

