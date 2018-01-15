#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Point.h"


using namespace std;


Point::Point()
{
	x = y = 0;
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Point" << endl;
	#endif
}



Point::Point(const Point& arg)
{
	setX(arg.getX());
	setY(arg.getY());
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Point" << endl;
	#endif
}

Point::Point(int abs, int ord)
{
	x = abs;
	y = ord;
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 2 Point" << endl;
	#endif
}

Point::~Point()
{
	
	compteur -=1;
	
	#ifdef DEBUG
		cerr << "Fin Destructeur Point" << endl;
	#endif
}


void Point::setX(const int arg)
{
	x = arg;
}

void Point::setY(const int arg)
{
	y = arg;
}


const int Point::getX() const
{
	return x;
}

const int Point::getY() const
{
	return y;
}

const int Point::getCompteur()
{
	return compteur;
}

ostream& operator<<(ostream& s, const Point& a)
{
	s << a.getX() << ";" << a.getY();

	return s;
}

void Point::Affiche() const
{
	cout << "Coordonnées : (" << getX() << ";" << getY() << ")" << endl;
}

void Point::Save(std::ofstream & fichier) const
{
	if(fichier.is_open())
	{
		//fichier.seekp(0,ios::end);
		fichier.write((char*)&x, sizeof(int));
		fichier.write((char*)&y, sizeof(int));
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Point::Load(std::ifstream & fichier)
{
	if(fichier.is_open())
	{
		if(!fichier.eof())
		{
			fichier.read((char*)&x, sizeof(int));
			fichier.read((char*)&y, sizeof(int));
			return 1;
		}
		else
			return 0;
	}
	else
	{
		cerr << "File Problem" << endl;
		return -1;
	}
}


int Point :: compteur = 0;
