#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "BaseException.h"
#include "Point.h"
#include "Couleur.h"
#include "Forme.h"
#include "Rectangle.h"



using namespace std;


Rectangle::Rectangle()
{
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Rectangle" << endl;
	#endif
}


Rectangle::Rectangle(const char* i, Point p)
{
	Rectangle::setId(i);
	
	Forme::setPosition(p);
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 2 Rectangle" << endl;
	#endif
}

Rectangle::Rectangle(const char* i, Point p, int dx, int dy, bool r, const Couleur *c, int pr)
{
	Rectangle::setId(i);
	
	Forme::setPosition(p);
	Forme::setCouleur(c); // ERROR
	Forme::setProfondeur(pr);
	setDimX(dx);
	setDimY(dy);
	setRempli(r);
	
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 7 Rectangle" << endl;
	#endif
}



Rectangle::Rectangle(const Rectangle& arg)
{
	Rectangle::setId(arg.getId());
	
	Forme::setPosition(arg.getPosition());
	Forme::setCouleur(arg.getCouleur());
	Forme::setProfondeur(arg.getProfondeur());
	setDimX(arg.getDimX());
	setDimY(arg.getDimY());
	setRempli(arg.isRempli());
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Rectangle" << endl;
	#endif
}



Rectangle::~Rectangle()
{
	if(info != NULL)
	{
		delete info;
	}
	
	#ifdef DEBUG
		cerr << "Fin Destructeur Rectangle" << endl;
	#endif
}

void Rectangle::setId(const char* arg)
{
	bool invalid = false;
	
	if(strlen(arg) > 1)
	{
		if(arg[0] == 'R')
		{
			for(int i = 1; arg[i] != '\0'; i+=1)
				if(!isdigit(arg[i]))
				{
					throw BaseException("L'identifiant ne peut comporter que d'une lettre au début !");
					invalid = true;
				}
		}
		else
		{
			throw BaseException("L'identifiant doit commencer par la lettre R au début !");
		}
	
		if(invalid == false)
		{
			if(id != NULL)
				delete id;
			id = new char(strlen(arg) + 1);
			strcpy(id, arg);
		}
	}
	else
	{
		throw BaseException("L'identifiant doit posséder au moins deux caractères !");
	}
	
	
}

void Rectangle::setDimX(const int arg)
{
	dimX = arg;
}

void Rectangle::setDimY(const int arg)
{
	dimY = arg;
}

void Rectangle::setRempli(const bool arg)
{
	rempli = arg;
}

const int Rectangle::getDimX() const
{
	return dimX;
}

const int Rectangle::getDimY() const
{
	return dimY;
}

const bool Rectangle::isRempli() const
{
	return rempli;
}


Rectangle& Rectangle::operator=(const Rectangle& arg)
{
	setId(arg.getId());
	info = NULL;
	setId(arg.getId());
	setProfondeur(arg.getProfondeur());
	setCouleur(arg.getCouleur());
	setPosition(arg.getPosition());
	setDimX(arg.getDimX());
	setDimY(arg.getDimY());
	setRempli(arg.isRempli());
	return *this;
}

ostream& operator<<(ostream& s, const Rectangle& a)
{
	char temp[150];
	
	if(a.getCouleur() != NULL)
	{
		sprintf(temp, "[Rectangle: Position(%d, %d), DimX=%d, DimY=%d, Rempli=%d, Couleur(%d, %d, %d), Profondeur=%d]", a.getPosition().getX(), a.getPosition().getY(), a.getDimX(), a.getDimY(), a.isRempli(), a.getCouleur()->getRouge(), a.getCouleur()->getVert(),a.getCouleur()->getBleu(), a.getProfondeur());
	}
	else
	{
		sprintf(temp, "[Rectangle: Position(%d, %d), DimX=%d, DimY=%d, Rempli=%d, Couleur(NONE), Profondeur=%d]", a.getPosition().getX(), a.getPosition().getY(), a.getDimX(), a.getDimY(), a.isRempli(),a.getProfondeur());
	}
	
	//if(a.getInfos() != NULL)
		s << temp;

	return s;

}

void Rectangle::Affiche() const
{
	Forme::Affiche();
	cout << "Dimension: (" << getDimX() << ";" << getDimY() << ")" << "Rempli = " << isRempli() << endl;
}

const char* Rectangle::getInfos()
{
	char temp[100];
	
	if(getCouleur() != NULL)
	{
	sprintf(temp, "[Rectangle: Position(%d, %d), DimX=%d, DimY=%d, Rempli=%d, Couleur(%d, %d, %d), Profondeur=%d]", getPosition().getX(), getPosition().getY(), getDimX(), getDimY(), isRempli(), getCouleur()->getRouge(), getCouleur()->getVert(),getCouleur()->getBleu(), getProfondeur());
	}
	else
	{
		sprintf(temp, "[Rectangle: Position(%d, %d), DimX=%d, DimY=%d, Rempli=%d, Couleur(NONE), Profondeur=%d]", getPosition().getX(), getPosition().getY(), getDimX(), getDimY(), isRempli(), getProfondeur());
	}
	
	
	if(info != NULL)
		delete info;
	
	info = new char[strlen(temp) + 1];
	
	strcpy(info, temp);
	
	return info;
}

void Rectangle::Save(std::ofstream & fichier) const
{
	cerr << "Passé dans Rectangle !";
	if(fichier.is_open())
	{
		Forme::Save(fichier);
		
		fichier.write((char*)&dimX, sizeof(int));
		fichier.write((char*)&dimY, sizeof(int));
		fichier.write((char*)&rempli, sizeof(bool));
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Rectangle::Load(std::ifstream & fichier)
{
	
	if(fichier.is_open())
	{
		
		if(!fichier.eof())
		{
			Forme::Load(fichier);
			
			fichier.read((char*)&dimX, sizeof(int));
			fichier.read((char*)&dimY, sizeof(int));
			fichier.read((char*)&rempli, sizeof(bool));
			
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

void Rectangle::Dessine() const
{
	if(getCouleur() != NULL)
	{
		if(isRempli())
			WindowSDL::fillRectangle(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getDimX() - getPosition().getX(), getDimY() - getPosition().getY()); 
		else
			WindowSDL::drawRectangle(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getDimX() - getPosition().getX(), getDimY() - getPosition().getY()); 
	}
	else
	{
		cerr << "Couleur non-définie !" << endl;
	}
}

