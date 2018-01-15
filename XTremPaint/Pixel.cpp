#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctype.h>

#include "BaseException.h"
#include "Point.h"
#include "Couleur.h"
#include "Forme.h"
#include "Pixel.h"



using namespace std;


Pixel::Pixel()
{
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Pixel" << endl;
	#endif
}


Pixel::Pixel(const char* i, Point p)
{
	Pixel::setId(i);
	
	Forme::setPosition(p);
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 2 Pixel" << endl;
	#endif
}

Pixel::Pixel(const char* i, Point p, const Couleur *c, int pr)
{
	Pixel::setId(i);
	
	Forme::setPosition(p);
	Forme::setCouleur(c); // ERROR
	Forme::setProfondeur(pr);
	
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 4 Pixel" << endl;
	#endif
}



Pixel::Pixel(const Pixel& arg):Forme(arg)
{/*
	Forme::setId(arg.getId());
	
	Forme::setPosition(arg.getPosition());
	Forme::setCouleur(arg.getCouleur());
	Forme::setProfondeur(arg.getProfondeur());
*/
info = NULL;	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Pixel" << endl;
	#endif
}



Pixel::~Pixel()
{
	if(info != NULL)
	{
		delete info;
	}
	
	#ifdef DEBUG
		cerr << "Fin Destructeur Pixel" << endl;
	#endif
}

void Pixel::setId(const char* arg)
{
	bool invalid = false;
	
	if(strlen(arg) > 1)
	{
		if(arg[0] == 'P')
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
			throw BaseException("L'identifiant doit commencer par la lettre P au début !");
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

Pixel& Pixel::operator=(const Pixel& arg)
{
	Pixel::setId(arg.getId());
	info = NULL;
	setId(arg.getId());
	setProfondeur(arg.getProfondeur());
	setCouleur(arg.getCouleur());
	setPosition(arg.getPosition());
	return *this;
}


ostream& operator<<(ostream& s, const Pixel& a)
{
	char temp[150];
	
	if(a.getCouleur() != NULL)
	{
		sprintf(temp, "[PIXEL: Position(%d, %d) Couleur(%d, %d, %d), Profondeur=%d]", a.getPosition().getX(), a.getPosition().getY(), a.getCouleur()->getRouge(), a.getCouleur()->getVert(),a.getCouleur()->getBleu(), a.getProfondeur());
	}
	else
	{
		sprintf(temp, "[PIXEL: Position(%d, %d) Couleur(NONE), Profondeur=%d]", a.getPosition().getX(), a.getPosition().getY(),a.getProfondeur());
	}
	
	//if(a.getInfos() != NULL)
		s << temp;

	return s;

}



const char* Pixel::getInfos() 
{
	char temp[100];
	
	if(getCouleur() != NULL)
	{
	sprintf(temp, "[PIXEL: Position(%d, %d) Couleur(%d, %d, %d), Profondeur=%d]", getPosition().getX(), getPosition().getY(), getCouleur()->getRouge(), getCouleur()->getVert(),getCouleur()->getBleu(), getProfondeur());
	}
	else
	{
		sprintf(temp, "[Pixel: Position(%d, %d) Couleur(NONE), Profondeur=%d]", getPosition().getX(), getPosition().getY(),getProfondeur());
	}
	
	
	if(info != NULL)
		delete info;
	
	info = new char[strlen(temp) + 1];

	strcpy(info, temp);
	
	return info;
}

void Pixel::Save(std::ofstream & fichier) const
{
	cerr << "Passé dans Pixel !";
	if(fichier.is_open())
	{
		Forme::Save(fichier);
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Pixel::Load(std::ifstream & fichier)
{
	
	if(fichier.is_open())
	{
		
		if(!fichier.eof())
		{
			Forme::Load(fichier);
			
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

void Pixel::Dessine() const
{
	if(getCouleur() != NULL)
	{
		WindowSDL::setPixel(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY()); 
	}
	else
	{
		cerr << "Couleur non-définie !" << endl;
	}
}


