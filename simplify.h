#ifndef SIMPLIFY
#define SIMPLIFY
#include"RealFunction.h"


RFunction*addSimplify(RFunction*f){return f;}
RFunction*subSimplify(RFunction*f){return f;}
RFunction*mulSimplify(RFunction*f){return f;}
RFunction*divSimplify(RFunction*f){return f;}
RFunction*powSimplify(RFunction*f){return f;}
RFunction*logSimplify(RFunction*f){return f;}
RFunction*lnSimplify(RFunction*f){return f;}
RFunction*sinSimplify(RFunction*f){return f;}
RFunction*cosSimplify(RFunction*f){return f;}
RFunction*tanSimplify(RFunction*f){return f;}
RFunction*cotSimplify(RFunction*f){return f;}
RFunction*secSimplify(RFunction*f){return f;}
RFunction*cscSimplify(RFunction*f){return f;}
RFunction*expSimplify(RFunction*f){return f;}

RFunction*simplify(RFunction*f){
    if(f->type()=="+"){return addSimplify(f);}
    if(f->type()=="-"){return subSimplify(f);}
    if(f->type()=="*"){return mulSimplify(f);}
    if(f->type()=="/"){return divSimplify(f);}
    if(f->type()=="^"){return powSimplify(f);}
    if(f->type()=="sin"){return sinSimplify(f);}
    if(f->type()=="cos"){return cosSimplify(f);}
    if(f->type()=="tan"){return tanSimplify(f);}
    if(f->type()=="cot"){return cotSimplify(f);}
    if(f->type()=="sec"){return secSimplify(f);}
    if(f->type()=="csc"){return cscSimplify(f);}
    if(f->type()=="exp"){return expSimplify(f);}
    if(f->tyoe()=="ln"){return lnSimplify(f);}
    if(f->type()=="log"){return logSimplify(f);}
    return f;
}


#endif


