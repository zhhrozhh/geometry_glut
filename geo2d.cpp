#include"geo2d.h"

#define p1 pList[0]
#define p2 pList[1]
#define p3 pList[2]
ostream&operator<<(ostream&os,const Point&p){
    os<<"("<<p.x<<","<<p.y<<")";
    return os;
}
ostream&operator<<(ostream&os,const Line&l){
    os<<l.A<<"x"<<(l.B>=0?"+":"")<<l.B<<"y"<<(l.C>=0?"+":"")<<l.C<<"=0";
    return os;
}
ostream&operator<<(ostream&os,const Circle&c){
    os<<"circle{center:"<<c.c<<"radius:"<<c.r<<"}";
    return os;
}
ostream&operator<<(ostream&os,const Angle&a){
    os<<"angle{"<<a.p1<<"-"<<a.p2<<"-"<<a.p3<<"}";
    return os;
}
ostream&operator<<(ostream&os,const Triangle&t){
    os<<"triangle{"<<t.p1<<"-"<<t.p2<<"-"<<t.p3<<"}";
    return os;
}
ostream&operator<<(ostream&os,const LineSeg&l){
    os<<"line segement{"<<l.p1<<"-"<<l.p2<<"}";
    return os;
}
void Point::rotate(Point c,double rad){
    double nx = (x-c.x)*cos(rad)-(y-c.y)*sin(rad)+c.x;
    double ny = (x-c.x)*sin(rad)+(y-c.y)*cos(rad)+c.y;
    x = nx;
    y = ny;
}
void Point::reflect(const Line&l){
    PLSystem pls(*this,l);
    Point p = pls.orthogonalPoint();
    rotate(p,pi()/2);
}
void Line::rotate(Point c,double rad){
    Point pa=LLSystem(*this,Line(A+1,B,C)).intersectionPoint();
    pa.rotate(c,rad);
    Point pb=LLSystem(*this,Line(A,B+1,C)).intersectionPoint();
    pb.rotate(c,rad);
    Line res = LineSeg(pa,pb).lineExpr();
    A=res.A;
    B=res.B;
    C=res.C;
}
void Line::reflect(Line l){
    Point pa=LLSystem(*this,Line(A+1,B,C)).intersectionPoint();
    pa.reflect(l);
    Point pb=LLSystem(*this,Line(A,B+1,C)).intersectionPoint();
    pb.reflect(l);
    Line res=LineSeg(pa,pb).lineExpr();
    A=res.A;
    B=res.B;
    C=res.C;
}
void nPoints::rotate(Point c,double rad){
    for(int i=0;i<pList.size();i++)
        pList[i].rotate(c,rad);
}
Line LineSeg::lineExpr(){
    if(p1.x==p2.x)return Line(1.0,0.0,p1.x);
    if(p1.y==p2.y)return Line(0.0,1.0,p1.y);
    double k=(p1.y-p2.y)/(p1.x-p2.x);
    double b=p1.y-p1.x*k;
    return Line(0.0-k,1.0,0.0-b);
}
Point LineSeg::midpoint(){
    return Point((p1.x+p2.x)/2.0,(p1.y+p2.y)/2.0);
}
Line LineSeg::perpendicularBisector(){
    if(p1.x-p2.x == 0.0)return Line(0.0,1.0,0.0-(p1.y+p2.y)/2.0);
    if(p1.y-p2.y == 0.0)return Line(1.0,0.0,0.0-(p1.x+p2.x)/2.0);
    double k = (p1.x-p2.x)/(p1.y-p2.y);
    double b = midpoint().y + k*midpoint().x;
    return Line(k,1.0,0.0-b);
}
double LineSeg::length(){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
Point LineSeg::getPoint(int i,double dist){
    Circle c(pList[i],dist);
    vector<Point>v=LCSystem(lineExpr(),c).intersectionPoints();
    if(LineSeg(pList[1-i],v[0]).length()<LineSeg(pList[1-i],v[1]).length())return v[0];
    return v[1];
}
double Angle::measure(){
    double v1x = p1.x-p2.x;
    double v1y = p1.y-p2.y;
    double v2x = p3.x-p2.x;
    double v2y = p3.y-p2.y;
    return acos((v1x*v2x+v1y*v2y)/(sqrt((v1x*v1x+v1y*v1y)*(v2x*v2x+v2y*v2y))));
}
Line Angle::angleBisector(){
    LineSeg ls1(p2,p1);
    LineSeg ls2(p2,p3);
    ls1.getPoint(LINESEG_BEGINNING,5.0);
    ls2.getPoint(LINESEG_BEGINNING,5.0);
    return LineSeg(ls1.getPoint(LINESEG_BEGINNING,5.0),ls2.getPoint(LINESEG_BEGINNING,5.0)).perpendicularBisector();
}
Line Angle::supplementaryAngleBisector(){
    Line res = angleBisector();
    cout<<res<<endl;
    res.rotate(p2,pi()/2);
    cout<<res<<endl;
    return res;
}
Point Triangle::incenter(){
    Angle a1(p1,p2,p3);
    Angle a2(p2,p3,p1);
    return LLSystem(a1.angleBisector(),a2.angleBisector()).intersectionPoint();
}
Point Triangle::circumcenter(){
    return LLSystem(LineSeg(p1,p2).perpendicularBisector(),LineSeg(p2,p3).perpendicularBisector()).intersectionPoint();
}
Circle Triangle::excircle(int fp,int sp){
    int tp = 3-fp-sp;
    cout<<tp <<" : "<< pList.size()<<endl;
    Line l1 = Angle(pList[tp],pList[fp],pList[sp]).supplementaryAngleBisector();
    Line l2 = Angle(pList[tp],pList[sp],pList[fp]).supplementaryAngleBisector();
    Point c = LLSystem(l1,l2).intersectionPoint();
    double r = LPSystem(LineSeg(pList[fp],pList[sp]).lineExpr(),c).distance();
    return Circle(c,r);
}
Triangle Triangle::anticevianTriangle(){
    Line l1 = Angle(p1,p2,p3).supplementaryAngleBisector();
    Line l2 = Angle(p1,p3,p2).supplementaryAngleBisector();
    Line l3 = Angle(p2,p1,p3).supplementaryAngleBisector();
    Point pa = LLSystem(l1,l2).intersectionPoint();
    Point pb = LLSystem(l2,l3).intersectionPoint();
    Point pc = LLSystem(l1,l3).intersectionPoint();
    return Triangle(pa,pb,pc);
}
double PLSystem::distance(){
    LineSeg ls(p,orthogonalPoint());
    return ls.length();
}
Point PLSystem::orthogonalPoint(){
    LLSystem lls(perpendicularLine(),l);
    return lls.intersectionPoint();
}
Line PLSystem::perpendicularLine(){
    if(l.A == 0)return Line(1.0,0.0,0.0-p.x);
    if(l.B == 0)return Line(0.0,1.0,0.0-p.y);
    double k = l.B/l.A;
    double b = p.y-p.x*k;
    return Line(-k,1.0,0.0-b);
}
Line PLSystem::parallalLine(){
    return Line(l.A,l.B,0.0-(l.A*p.x+l.B*p.y));
}
Point LLSystem::intersectionPoint(){
    if(l1.A*l2.B==l2.A*l1.B)return Point(false);
    double f = 1/(l1.A*l2.B-l2.A*l1.B);
    return Point(f*(l1.B*l2.C-l2.B*l1.C),f*(l1.C*l2.A-l2.C*l1.A));
}
double LLSystem::distance(){
    if(intersectionPoint().exist)return -1.0;
    Line l(l1.A+1,l1.B,l1.C);
    return LPSystem(LLSystem(l,l1).intersectionPoint(),l2).distance();
}
double LCSystem::distance(){
    return PLSystem(c.c,l).distance();
}
vector<Point> LCSystem::intersectionPoints(){
    Point op=PLSystem(c.c,l).orthogonalPoint();
    vector<Point>res;
    if(distance()>c.r)return res;
    if(distance()==c.r){
        res.push_back(op);
        return res;
    }
    double d=sqrt(c.r*c.r-distance()*distance());
    if(l.A==0){//y=-c/b
        res.push_back(Point(op.x+d,-l.C/l.B));
        res.push_back(Point(op.x-d,-l.C/l.B));
        return res;
    }
    if(l.B==0){//x=-c/a
        res.push_back(Point(-l.C/l.A,op.y+d));
        res.push_back(Point(-l.C/l.A,op.y-d));
        return res;
    }
    double k=0.0-l.A/l.B;
    double x=sqrt(d*d/(1+k*k));
    res.push_back(Point(op.x-x,op.y-k*x));
    res.push_back(Point(op.x+x,op.y+k*x));
    return res;
}
Line PCSystem::tangentLine(){
    if(LineSeg(p,c.c).length()<c.r)return Line(false);
    LineSeg ls2(c.c,LineSeg(p,c.c).getPoint(LINESEG_BEGINNING,c.r*2));
    return ls2.perpendicularBisector();
}
double CCSystem::distance(){
    return LineSeg(c1.c,c2.c).length();
}
vector<Point>CCSystem::intersectionPoints(){
    Line l=LineSeg(c1.c,c2.c).perpendicularBisector();
    return LCSystem(l,c1).intersectionPoints();
}




#undef p1
#undef p2
#undef p3
