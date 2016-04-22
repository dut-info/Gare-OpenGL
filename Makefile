#Makefile Linux
EXEC = projet
COMPILO = g++

GLUT_INC=
GLUT_LIBS=-lglut
GL_INC=
GL_LIBS= -lGL -lGLU

#Chemin d'acces des includes
CXXINCS =  $(GLUT_INC) $(GL_INC)

#Parametres de compilation
CXXFLAGS = $(CXXINCS) -std=c++11 -Wall

#Chemin d'acces des librairies
LIBS = $(GL_LIBS) $(GLUT_LIBS)

#Chemin d'acces des .h et .cpp (qui pourraient etre ailleurs que dans le répertoire principal)
PATH_INC=.
PATH_SRC=.

#Cree l'executable sous Linux
all: $(EXEC)

$(EXEC): TestObject.o Object.o Point.o Parallelepiped.o RailDroit.o BezierCurve.o Train.o Locomotive.o Wagon.o Roue.o Tube.o Chemine.o Sol.o Toure.o TourePetite.o
	$(COMPILO) -o $@ $^ $(LIBS)

TestObject.o:  $(PATH_SRC)/TestObject.cpp
	$(COMPILO) -o $@ -c $< $(CXXFLAGS)

#Efface les fichiers .o
clean:
	rm -rf *.o
