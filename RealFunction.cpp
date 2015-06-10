#include"RealFunction.h"

#define SIn(x) new Sin(x)
#define COs(x) new Cos(x)
#define TAn(x) new Tan(x)
#define COt(x) new Cot(x)
#define SEc(x) new Sec(x)
#define CSc(x) new Csc(x)
#define LN(x) new Ln(x)
#define EXp(x) new Exp(x)
#define COns(x) new ConstantFunction(x)
#define MUl(x,y) new Mul(x,y)
#define DIv(x,y) new Div(x,y)
#define ADd(x,y) new Add(x,y)
#define SUb(x,y) new Sub(x,y)
#define LOg(x,y) new Log(x,y)
#define POw(x,y) new Pow(x,y)

double UniaryFunction::integral(double from,double to){
    double delta = (to-from)/NUMOFPARTITIONS;
    double sum=0;
    for(double i=from;i<to;i=i+delta)
        sum+=value(i)*delta;
    return sum;
}
double X::integral(double from,double to){
    double delta = (to-from)/NUMOFPARTITIONS;
    double sum=0;
    for(double i=from;i<to;i=i+delta)
        sum += value(i)*delta;
    return sum;
}
RFunction*Sin::d(size_t i){return MUl(COs(var1),var1->d(i));}
RFunction*Cos::d(size_t i){return MUl(CONSN1, MUl(SIn(var1),var1->d(i)));}
RFunction*Tan::d(size_t i){return MUl(MUl(SEc(var1),SEc(var1)),var1->d(i));}
RFunction*Cot::d(size_t i){
    RFunction*a = MUl(SEc(var1),SEc(var1));
    return MUl(CONSN1,MUl(a,var1->d(i)));
}
RFunction*Sec::d(size_t i){return MUl(SEc(var1),MUl(TAn(var1),var1->d(i)));}
RFunction*Csc::d(size_t i){
    RFunction*a = MUl(CSc(var1),var1->d(i));
    return MUl(CONSN1,MUl(COt(var1),a));
}
RFunction*Add::d(size_t i){return ADd(var1->d(i),var2->d(i));}
RFunction*Sub::d(size_t i){return SUb(var1->d(i),var2->d(i));}
RFunction*Mul::d(size_t i){return ADd(MUl(var1,var2->d(i)),MUl(var1->d(i),var2));}
RFunction*Div::d(size_t i){
    RFunction*a = MUl(var2,var1->d(i));
    return DIv(SUb(a,MUl(var1,var2->d(i))),MUl(var2,var2));
}
RFunction*Pow::d(size_t i){
    RFunction*a = POw(var1,SUb(var2,CONS1));
    return MUl(var2->d(i),MUl(a,ADd(MUl(var2,var1->d(i)),MUl(var1,LN(var1)))));
}
RFunction*Log::d(size_t i){
    RFunction*a1 = DIv(MUl(LN(var1),var2->d(i)),var2);
    RFunction*a2 = DIv(MUl(var1->d(i),LN(var2)),var1);
    RFunction*m = MUl(LN(var1),LN(var1));
    return DIv(SUb(a1,a2),m);
}
RFunction*Exp::d(size_t i){return MUl(EXp(var1),var1->d(i));}
RFunction*Ln::d(size_t i){return DIv(var1->d(i),var1);}
RFunction*ConstantFunction::d(){return CONS0;}
RFunction*ConstantFunction::d(size_t i){return CONS0;}
vector<RFunction*>additionChain(RFunction*f){
    vector<RFunction*>res;
    if(f->type()!="+"&&f->type()!="-"){
        res.push_back(f);
        return res;
    }
    if(f->type()=="+"){
        vector<RFunction*>r1=additionChain(((Add*)f)->var1);
        vector<RFunction*>r2=additionChain(((Add*)f)->var2);
        res.insert(res.end(),r1.begin(),r1.end());
        res.insert(res.end(),r2.begin(),r2.end());
        return res;
    }
    if(f->type()=="-"){
        vector<RFunction*>r1=additionChain(((Add*)f)->var1);
        vector<RFunction*>r2=additionChain(((Add*)f)->var2);
        for(size_t i=0;i<r2.size();i++)
            r2[i] = new Mul(CONSN1,r2[i]);
        res.insert(res.end(),r1.begin(),r1.end());
        res.insert(res.end(),r2.begin(),r2.end());
        return res;
    }
    return res;
}
vector<RFunction*>multiplicationChain(RFunction*f){
    vector<RFunction*>res;
    if(f->type()!="*"&&f->type()!="/"){
        res.push_back(f);
        return res;
    }
    if(f->type()=="*"){
        vector<RFunction*>r1=multiplicationChain(((Mul*)f)->var1);
        vector<RFunction*>r2=multiplicationChain(((Mul*)f)->var2);
        res.insert(res.end(),r1.begin(),r1.end());
        res.insert(res.end(),r2.begin(),r2.end());
        return res;
    }
    if(f->type()=="/"){
        vector<RFunction*>r1=multiplicationChain(((Mul*)f)->var1);
        vector<RFunction*>r2=multiplicationChain(((Mul*)f)->var2);
        for(size_t i=0;i<r2.size();i++)
            r2[i] = new Pow(r2[i],CONSN1);
        res.insert(res.end(),r1.begin(),r1.end());
        res.insert(res.end(),r2.begin(),r2.end());
        return res;
    }
    return res;
}
#undef SIn
#undef COs
#undef TAn
#undef COt
#undef SEc
#undef CSc
#undef LN
#undef EXp
#undef COns
#undef MUl
#undef DIv
#undef ADd
#undef SUb
#undef LOg
#undef POw


