#ifndef RFUNCTION
#define RFUNCTION
#ifndef NUMOFPARTITIONS
#define NUMOFPARTITIONS 5000.0
#endif
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
#ifdef X
#undef X
#endif

using namespace std;
class Mul;
class Cos;
class RFunction{
    public:
        virtual RFunction*d()=0;
        virtual RFunction*d(size_t i)=0;
        virtual string type()=0;
        virtual string expr()=0;
        virtual double value(double x)=0;
        virtual double value(vector<double>p)=0;
        virtual double integral(double from,double to)=0;
        virtual RFunction*integral(size_t i,double from,double to)=0;
};
class UniaryFunction:public RFunction{
    public:
        UniaryFunction(RFunction*var):var1(var),t("u"){}
        ~UniaryFunction()=default;
        RFunction*var1;
        string t;
        RFunction*d(){return d(0);}
        RFunction*d(size_t i){return nullptr;}
        string expr(){return t+"("+var1->expr()+")";}
        string type(){return t;}
        double value(double x){return 0;}
        double value(vector<double>p){return 0;}
        double integral(double from,double to);
        RFunction*integral(size_t i,double from,double to){return nullptr;}
};
class ConstantFunction:public RFunction{
    public:
        ConstantFunction(double c):c(c){}
        ~ConstantFunction()=default;
        double c;
        RFunction*d();
        RFunction*d(size_t i);
        string expr(){return to_string(c);}
        string type(){return "c";}
        double value(double x){return c;}
        double value(vector<double>p){return c;}
        double integral(double from,double to){return (to-from)*c;}
        RFunction*integral(size_t i,double from,double to){return nullptr;}
};
RFunction*const CONS0=new ConstantFunction(0.0);
RFunction*const CONS1=new ConstantFunction(1.0);
RFunction*const CONS05=new ConstantFunction(0.5);
RFunction*const CONSN1=new ConstantFunction(-1.0);
class X:public RFunction{
    public:
        X():index(0){}
        X(size_t i):index(i){}
        ~X()=default;
        size_t index;
        RFunction*d(){return CONS1;}
        RFunction*d(size_t i){
            if(i==index)return CONS1;
            return CONS0;
        }
        string expr(){return "x"+(index?to_string(index):"");}
        string type(){return "x";}
        double value(double x){return x;}
        double value(vector<double>p){return p[index];}
        double integral(double from,double to);
        RFunction*integral(size_t i,double from,double to){return nullptr;}
};
RFunction*const VX=new X();
class BinaryFunction:public UniaryFunction{
    public:
        BinaryFunction(RFunction*var1,RFunction*var2):UniaryFunction(var1),var2(var2){t="b";}
        ~BinaryFunction()=default;
        RFunction*var2;
        string expr(){return var1->expr()+type()+var2->expr();}
};
class Sin:public UniaryFunction{
    public:
        Sin(RFunction*var1):UniaryFunction(var1){t="sin";}
        ~Sin()=default;
        RFunction*d(size_t i);
        double value(double x){return sin(var1->value(x));}
        double value(vector<double>p){return sin(var1->value(p));}
};
class Cos:public UniaryFunction{
    public:
        Cos(RFunction*var1):UniaryFunction(var1){t="cos";}
        ~Cos()=default;
        RFunction*d(size_t i);
        double value(double x){return cos(var1->value(x));}
        double value(vector<double>p){return cos(var1->value(p));}
};
class Tan:public UniaryFunction{
    public:
        Tan(RFunction*var1):UniaryFunction(var1){t="tan";}
        ~Tan()=default;
        RFunction*d(size_t i);
        double value(double x){return tan(var1->value(x));}
        double value(vector<double>p){return tan(var1->value(p));}
};
class Cot:public UniaryFunction{
    public:
        Cot(RFunction*var1):UniaryFunction(var1){t="cot";}
        ~Cot()=default;
        RFunction*d(size_t i);
        double value(double x){return 1.0/tan(var1->value(x));}
        double value(vector<double>p){return 1.0/tan(var1->value(p));}
};
class Sec:public UniaryFunction{
    public:
        Sec(RFunction*var1):UniaryFunction(var1){t="sec";}
        ~Sec()=default;
        RFunction*d(size_t i);
        double value(double x){return 1.0/cos(var1->value(x));}
        double value(vector<double>p){return 1.0/cos(var1->value(p));}
};
class Csc:public UniaryFunction{
    public:
        Csc(RFunction*var1):UniaryFunction(var1){t="csc";}
        ~Csc()=default;
        RFunction*d(size_t i);
        double value(double x){return 1.0/sin(var1->value(x));}
        double value(vector<double>p){return 1.0/sin(var1->value(p));}
};
class Add:public BinaryFunction{
    public:
        Add(RFunction*var1,RFunction*var2):BinaryFunction(var1,var2){t="+";}
        ~Add()=default;
        RFunction*d(size_t i);
        double value(double x){return(var1->value(x)+var2->value(x));}
        double value(vector<double>p){return(var1->value(p)+var2->value(p));}
};
class Sub:public BinaryFunction{
    public:
        Sub(RFunction*var1,RFunction*var2):BinaryFunction(var1,var2){t="-";}
        ~Sub()=default;
        RFunction*d(size_t i);
        string expr(){
            string res = var1->expr()+"-";
            bool b = var2->type()=="+"||var2->type()=="-";
            return res + (b?"(":"")+var2->expr()+(b?")":"");
        }
        double value(double x){return(var1->value(x)-var2->value(x));}
        double value(vector<double>p){return(var1->value(p)-var2->value(p));}
};
class Mul:public BinaryFunction{
    public:
        Mul(RFunction*var1,RFunction*var2):BinaryFunction(var1,var2){t="*";}
        ~Mul()=default;
        RFunction*d(size_t i);
        string expr(){
            bool a=var1->type()=="+" || var1->type()=="-";
            bool b=var2->type()=="+" || var2->type()=="-";
            return (a?"(":"")+var1->expr()+(a?")":"")+"*"+(b?"(":"")+var2->expr()+(b?")":"");
        }
        double value(double x){return var1->value(x)*(var2->value(x));}
        double value(vector<double>p){return(var1->value(p)*(var2->value(p)));}
};
class Div:public BinaryFunction{
    public:
        Div(RFunction*var1,RFunction*var2):BinaryFunction(var1,var2){t="/";}
        ~Div()=default;
        RFunction*d(size_t i);
        string expr(){
            bool a=var1->type()=="+"||var1->type()=="-";
            return (a?"(":"")+var1->expr()+(a?")":"")+"/("+var2->expr()+")";
        }
        double value(double x){return var1->value(x)/var2->value(x);}
        double value(vector<double>p){return(var1->value(p)/var2->value(p));}
};
class Pow:public BinaryFunction{
    public:
        Pow(RFunction*var1,RFunction*var2):BinaryFunction(var1,var2){t="^";}
        ~Pow()=default;
        RFunction*d(size_t i);
        string expr(){
            return "("+var1->expr()+")^("+var2->expr()+")";
        }
        double value(double x){return pow(var1->value(x),var2->value(x));}
        double value(vector<double>p){return pow(var1->value(p),var2->value(p));}
};
class Log:public BinaryFunction{
    public:
        Log(RFunction*var1,RFunction*var2):BinaryFunction(var1,var2){t="log";}
        ~Log()=default;
        string expr(){return "log("+var1->expr()+","+var2->expr()+")";}
        RFunction*d(size_t i);
        double value(double x){return log(var2->value(x))/log(var1->value(x));}
        double value(vector<double>p){return log(var1->value(p))/log(var2->value(p));}
};
class Exp:public UniaryFunction{
    public:
        Exp(RFunction*var1):UniaryFunction(var1){t="exp";}
        ~Exp()=default;
        RFunction*d(size_t i);
        double value(double x){return exp(var1->value(x));}
        double value(vector<double>p){return exp(var1->value(p));}
};
class Ln:public UniaryFunction{
    public:
        Ln(RFunction*var1):UniaryFunction(var1){t="ln";}
        ~Ln()=default;
        RFunction*d(size_t i);
        double value(double x){return log(var1->value(x));}
        double value(vector<double>p){return log(var1->value(p));}
};
vector<RFunction*>additionChain(RFunction*f);
vector<RFunction*>multiplicationChain(RFunction*f);
RFunction*simplify(RFunction*f);
#endif

