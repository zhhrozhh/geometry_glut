glut:	gdemo
geo:	demo
gdemo:	glut_demo.o	geo2d.o RealFunction.o
	g++ -std=c++11 -o demo glut_demo.o geo2d.o RealFunction.o -framework OpenGL -framework GLUT
glut_demo.o:	glut_demo.cpp
	g++ -std=c++11 -c glut_demo.cpp -framework OpenGL -framework GLUT
demo:	demo.o geo2d.o
	g++ -std=c++11 -o gdemo demo.o geo2d.o
demo.o:	demo.cpp
	g++ -std=c++11 -c demo.cpp
geo2d.o:	geo2d.cpp
	g++ -std=c++11 -c geo2d.cpp
RealFunction.o:	RealFunction.cpp
	g++ -std=c++11 -c RealFunction.cpp
