.SILENT:

#COMPILATEUR = clang++ -m64 -std=c++14
COMPILATEUR = g++ -m64
FILE = XTremPaint
OBJ = WindowSDL.o WindowSDLexception.o WindowSDLclick.o Couleur.o Point.o Forme.o Pixel.o Ligne.o Rectangle.o BaseException.o InvalidColorException.o SmartPointer.o ListeBase.o Liste.o ListeTriee.o Iterateur.o Dessin.o
DEBUG=

all: TestWindowSDL $(FILE)

TestWindowSDL:	TestWindowSDL.cpp $(OBJ)
		echo Creation de TestWindowSDL...
		$(COMPILATEUR) TestWindowSDL.cpp -o TestWindowSDL $(OBJ) -lpthread -lSDL

$(FILE):	$(FILE).cpp $(OBJ)
		$(COMPILATEUR) $(FILE).cpp $(OBJ) -o $(FILE) -lpthread -lSDL
		echo Compile executable $(FILE)

Couleur.o:	Couleur.cpp Couleur.h
		$(COMPILATEUR) -c Couleur.cpp $(DEBUG)
		echo Compile Couleur.o

Point.o:	Point.cpp Point.h
		$(COMPILATEUR) -c Point.cpp $(DEBUG)
		echo Compile Point.o
		
Forme.o:	Forme.cpp Forme.h
		$(COMPILATEUR) -c Forme.cpp $(DEBUG)
		echo Compile Forme.o

Pixel.o:	Pixel.cpp Pixel.h
		$(COMPILATEUR) -c Pixel.cpp $(DEBUG)
		echo Compile Pixel.o

Ligne.o:	Ligne.cpp Ligne.h
		$(COMPILATEUR) -c Ligne.cpp $(DEBUG)
		echo Compile Ligne.o
		
Rectangle.o:	Rectangle.cpp Rectangle.h
		$(COMPILATEUR) -c Rectangle.cpp $(DEBUG)
		echo Compile Rectangle.o
		
BaseException.o:	BaseException.cpp BaseException.h
		$(COMPILATEUR) -c BaseException.cpp $(DEBUG)
		echo Compile BaseException.o

InvalidColorException.o:	InvalidColorException.cpp InvalidColorException.h
		$(COMPILATEUR) -c InvalidColorException.cpp $(DEBUG)
		echo Compile InvalidColorException.o

ListeBase.o:	ListeBase.cpp ListeBase.h
		$(COMPILATEUR) -c ListeBase.cpp $(DEBUG)
		echo Compile ListeBase.o

Liste.o:	Liste.cpp Liste.h
		$(COMPILATEUR) -c Liste.cpp $(DEBUG)
		echo Compile Liste.o

ListeTriee.o:	ListeTriee.cpp ListeTriee.h
		$(COMPILATEUR) -c ListeTriee.cpp $(DEBUG)
		echo Compile ListeTriee.o

Iterateur.o:	Iterateur.cpp Iterateur.h
		$(COMPILATEUR) -c Iterateur.cpp $(DEBUG)
		echo Compile Iterateur.o

SmartPointer.o:	SmartPointer.cpp SmartPointer.h
		$(COMPILATEUR) -c SmartPointer.cpp $(DEBUG)
		echo Compile SmartPointer.o

Dessin.o:	Dessin.cpp Dessin.h
		$(COMPILATEUR) -c Dessin.cpp $(DEBUG)
		echo Compile Dessin.o
		
WindowSDL.o:	WindowSDL.cpp WindowSDL.h
		echo Creation de WindowSDL.o ...
		$(COMPILATEUR) -c WindowSDL.cpp

WindowSDLexception.o:	WindowSDLexception.cpp WindowSDLexception.h
			echo Creation de WindowSDLexception.o ...
			$(COMPILATEUR) -c WindowSDLexception.cpp

WindowSDLclick.o:	WindowSDLclick.cpp WindowSDLclick.h
			echo Creation de WindowSDLclick.o ...
			$(COMPILATEUR) -c WindowSDLclick.cpp
		
clobber:	clean
		rm -f ./$(FILE) ./TestWindowSDL
		echo Projet nettoyé
clean:
		rm -f ./core ./*.o		
		echo Nettoyage fichiers objets + core

