#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Point.h"
#include "Couleur.h"
#include "Forme.h"



using namespace std;


Forme::Forme()
{
	couleur = NULL;
	id = NULL;
	info = NULL;
	profondeur = -999;
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Forme" << endl;
	#endif
}



Forme::Forme(const Forme& arg)
{
	id = NULL;
	info = NULL;
	setId(arg.getId());
	setProfondeur(arg.getProfondeur());
	setCouleur(arg.getCouleur());
	setPosition(arg.getPosition());
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Forme" << endl;
	#endif
}

Forme::Forme(const char* i, Point p)
{
	id = NULL;
	info = NULL;
	couleur = NULL;
	
	//setId(i);
	
	setPosition(p);
	
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 2 Forme" << endl;
	#endif
}

Forme::Forme(const char* i, Point p, const Couleur *c, int pr)
{
	id = NULL;
	info = NULL;
	
	setPosition(p);
	setCouleur(c); // ERROR
	setProfondeur(pr);
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 4 Forme" << endl;
	#endif
}

Forme::~Forme()
{
	
	if(id != NULL)
	{
		delete id;
	}
	
	compteur -=1;
	#ifdef DEBUG
		cerr << "Fin Destructeur Forme" << endl;
	#endif
}


void Forme::setId(const char* arg)
{
	
	if(id != NULL)
		delete id;
	id = new char[strlen(arg) + 1];
	strcpy(id, arg);
	
}

void Forme::setPosition(const Point arg)
{
	position.setX(arg.getX());
	position.setY(arg.getY());
}

void Forme::setCouleur(const Couleur *arg)
{
	//if(couleur == NULL)
	//	couleur = new Couleur;
	couleur = arg;
}



void Forme::setProfondeur(const int arg)
{
	profondeur = arg;
}


const char* Forme::getId() const
{
	return id;
}

const Point Forme::getPosition() const
{
	return position;
}

const Couleur* Forme::getCouleur() const
{
	return couleur;
}



const int Forme::getProfondeur() const
{
	return profondeur;
}

const int Forme :: getCompteur() 
{
	return compteur;
}

void Forme::Affiche() const
{
	
	cout << "Forme : ";
	if(getId() != NULL)
		cout << getId() << ";";
	
	
	if(getCouleur() != NULL) // ERROR
		if(getCouleur()->getNom() != NULL)
			cout << getCouleur()->getNom() << ";";

	cout << getProfondeur() << "; (" << getPosition().getX() << ";" <<getPosition().getY() << ")" << endl;
	
}

bool operator==(const Forme& a, const Forme& b)
{
	if(a.getProfondeur() == b.getProfondeur())
	{
		return 1;
	}
	
	return 0;
}

bool operator!=(const Forme& a, const Forme& b)
{
	if(a.getProfondeur() != b.getProfondeur())
	{
		return 1;
	}
	
	return 0;
}

bool operator<(const Forme& a, const Forme& b)
{
	if(a.getProfondeur() < b.getProfondeur())
	{
		return 1;
	}
	
	return 0;


}

bool operator>(const Forme& a, const Forme& b)
{
	if(!(a < b))
	{
		return 1;
	}
	
	return 0;


}

ostream& operator<<(ostream& s, const Forme& a)
{

	//s << "Forme : ";
	if(a.getId() != NULL)
		s << a.getId() << ";";
	
	
	if(a.getCouleur() != NULL) // ERROR
		if(a.getCouleur()->getNom() != NULL)
			s << a.getCouleur()->getNom() << ";";

	s << a.getProfondeur() << "; (" << a.getPosition().getX() << ";" <<a.getPosition().getY() << ")" << endl;

	return s;

}

Forme& Forme::operator=(const Forme& arg)
{
	//setId(arg.getId());
	info = NULL;
	setId(arg.getId());
	setProfondeur(arg.getProfondeur());
	setCouleur(arg.getCouleur());
	setPosition(arg.getPosition());
	return *this;
}

void Forme::Save(std::ofstream & fichier) const
{
	cerr << "Passé dans Forme !";
	
	if(fichier.is_open())
	{
		if(id != NULL)
		{
			int nb = strlen(id) + 1;
			fichier.write((char*)&nb, sizeof(int));
			fichier.write((char*)id, sizeof(char) * strlen(id) + 1);
			
		}
		else
		{
			int nb = 0;
			fichier.write((char*)&nb, sizeof(int));
		}
		
		fichier.write((char*)&profondeur, sizeof(int));
		position.Save(fichier);
		if(couleur != NULL)
		{
			int nb = 1;
			fichier.write((char*)&nb, sizeof(int));
			couleur->Save(fichier);
		}
		else
		{
			int nb = 0;
			fichier.write((char*)&nb, sizeof(int));
		}
		
		cerr << "Sauvé: " << id << "profondeur=" << profondeur << endl;
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Forme::Load(std::ifstream & fichier)
{
	//char *buff;
	int nb = 0;
	if(fichier.is_open())
	{
		if(!fichier.eof())
		{
			
			fichier.read((char*)&nb, sizeof(int));
			
			if(nb != 0)
			{
				
				char buff[nb];
				if(id != NULL)
					delete id;
				id = new char[sizeof(char) * nb];
				fichier.read((char*)buff, sizeof(char) * nb);
				
				strcpy(id, buff); // Pourquoi? Aucune idée.. Un des mystères du C++
				
				/*id = new char[sizeof(char) * nb]; 
				fichier.read((char*)&id, sizeof(char) * nb);*/ // Engendre un double free corruption
			}
			else
			{
				cerr << nb << endl;
				id = NULL;
			}
			fichier.read((char*)&profondeur, sizeof(int));
			position.Load(fichier);
			fichier.read((char*)&nb, sizeof(int));
			if(nb == 1)
			{
				Couleur *C = new Couleur();
				C->Load(fichier);
				couleur = C;
			}
			else
			{
				couleur = NULL;
			}
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

int Forme :: compteur = 0;


