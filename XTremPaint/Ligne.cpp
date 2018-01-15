#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "BaseException.h"
#include "Point.h"
#include "Couleur.h"
#include "Forme.h"
#include "Ligne.h"



using namespace std;


Ligne::Ligne():Forme()
{
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Ligne" << endl;
	#endif
}


Ligne::Ligne(const char* i, Point p) : Forme()
{
	Ligne::setId(i);
	
	Forme::setPosition(p);
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 2 Ligne" << endl;
	#endif
}

Ligne::Ligne(const char* i, Point p, Point ex,const Couleur *c, int pr):Forme()
{
	Ligne::setId(i);
	
	Forme::setPosition(p);
	Forme::setCouleur(c);
	Forme::setProfondeur(pr);
	setExtremite(ex);
	
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 5 Ligne" << endl;
	#endif
}



Ligne::Ligne(const Ligne& arg):Forme(arg)
{
/*	Ligne::setId(arg.getId());
	
	Forme::setPosition(arg.getPosition());
	Forme::setCouleur(arg.getCouleur());
	Forme::setProfondeur(arg.getProfondeur());*/
	setExtremite(arg.getExtremite());
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Ligne" << endl;
	#endif
}



Ligne::~Ligne()
{
	
	if(info != NULL)
	{
		delete info;
	}
	
	#ifdef DEBUG
		cerr << "Fin Destructeur Ligne" << endl;
	#endif
	
}

void Ligne::setId(const char* arg)
{
	bool invalid = false;
	
	if(strlen(arg) > 1)
	{
		if(arg[0] == 'L')
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
			throw BaseException("L'identifiant doit commencer par la lettre L au début !");
		}
	
		if(invalid == false)
		{
			if(id != NULL)
				delete id;
			id = new char[strlen(arg) + 1];
			strcpy(id, arg);
		}
	}
	else
	{
		throw BaseException("L'identifiant doit posséder au moins deux caractères !");
	}
	
	
}

void Ligne::setExtremite(const Point arg)
{
	extremite = arg;
}

const Point Ligne::getExtremite() const
{
	return extremite;
}


Ligne& Ligne::operator=(const Ligne& arg)
{
	setId(arg.getId());
	info = NULL;
	setId(arg.getId());
	setProfondeur(arg.getProfondeur());
	setCouleur(arg.getCouleur());
	setPosition(arg.getPosition());
	setExtremite(arg.getExtremite());
	return *this;
}



ostream& operator<<(ostream& s, const Ligne& a)
{
	char temp[150];
	
	if(a.getCouleur() != NULL)
	{
		sprintf(temp, "[Ligne: Position(%d, %d), Extremite(%d, %d), Couleur(%d, %d, %d), Profondeur=%d]", a.getPosition().getX(), a.getPosition().getY(), a.getExtremite().getX(), a.getExtremite().getY(), a.getCouleur()->getRouge(), a.getCouleur()->getVert(), a.getCouleur()->getBleu(), a.getProfondeur());
	}
	else
	{
		sprintf(temp, "[Ligne: Position(%d, %d), Extremite(%d, %d), Couleur(NONE), Profondeur=%d]", a.getPosition().getX(), a.getPosition().getY(), a.getExtremite().getX(), a.getExtremite().getY(), a.getProfondeur());
	}
	
	//if(a.getInfos() != NULL)
		s << temp;

	return s;

}


void Ligne::Affiche() const
{
	Forme::Affiche();
	cout << "Extremite = " << extremite << endl;
}


const char* Ligne::getInfos() 
{
	char temp[100];
	
	if(getCouleur() != NULL)
	{
	sprintf(temp, "[Ligne: Position(%d, %d), Extremite(%d, %d), Couleur(%d, %d, %d), Profondeur=%d]", getPosition().getX(), getPosition().getY(), getExtremite().getX(), getExtremite().getY(), getCouleur()->getRouge(), getCouleur()->getVert(),getCouleur()->getBleu(), getProfondeur());
	}
	else
	{
		sprintf(temp, "[Ligne: Position(%d, %d), Extremite(%d, %d), Couleur(NONE), Profondeur=%d]", getPosition().getX(), getPosition().getY(), getExtremite().getX(), getExtremite().getY(),getProfondeur());
	}
	
	
	if(info != NULL)
		delete info;
	
	info = new char[strlen(temp) + 1];
	
	strcpy(info, temp);
	
	return info;
}

void Ligne::Dessine() const
{
	if(getCouleur() != NULL)
	{
		WindowSDL::drawLine(getCouleur()->getRouge(), getCouleur()->getVert(), getCouleur()->getBleu(), getPosition().getX(), getPosition().getY(), getExtremite().getX(), getExtremite().getY());
	}
	else
	{
		cerr << "Couleur non-définie !" << endl;
	}
}

void Ligne::Save(std::ofstream & fichier) const
{
	cerr << "Passé dans Ligne !";
	
	if(fichier.is_open())
	{
		Forme::Save(fichier);
		extremite.Save(fichier);
		
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Ligne::Load(std::ifstream & fichier)
{
	
	if(fichier.is_open())
	{
		
		if(!fichier.eof())
		{
			Forme::Load(fichier);
			
			extremite.Load(fichier);
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


