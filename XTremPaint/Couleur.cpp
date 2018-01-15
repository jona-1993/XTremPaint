#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "InvalidColorException.h"
#include "Couleur.h"


using namespace std;


Couleur::Couleur()
{
	rouge = vert = bleu = 0;
	
	nom = NULL;
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Couleur" << endl;
	#endif
}

Couleur::Couleur(int r, int v, int b, const char* n)
{
	bool ro = true, ve = true, bl = true;
		
	if(r > 255 || r < 0)
		ro = false;
	if(v > 255 || v < 0)
		ve = false;
	if(b > 255 || b < 0)
		bl = false;
	if(bl == false || ve == false || bl == false)
	{
		throw InvalidColorException("Couleur invalide", ro, ve, bl);
	}

	setRouge(r);
	setVert(v);
	setBleu(b);
	nom = NULL;
	setNom(n);
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 4 Couleur" << endl;
	#endif
}

Couleur::Couleur(const Couleur& arg)
{
	bool ro = true, ve = true, bl = true;
		
	if(arg.getRouge() > 255 || arg.getRouge() < 0)
		ro = false;
	if(arg.getVert() > 255 || arg.getVert() < 0)
		ve = false;
	if(arg.getBleu() > 255 || arg.getBleu() < 0)
		bl = false;
	if(bl == false || ve == false || bl == false)
	{
		throw InvalidColorException("Couleur invalide", ro, ve, bl);
	}

	setRouge(arg.getRouge());
	setVert(arg.getVert());
	setBleu(arg.getBleu());
	
	nom = NULL;
	
	if(arg.getNom() != NULL)
		setNom(arg.getNom());
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Couleur" << endl;
	#endif
}

Couleur::Couleur(int r, int v, int b)
{
	bool ro = true, ve = true, bl = true;
		
	if(r > 255 || r < 0)
		ro = false;
	if(v > 255 || v < 0)
		ve = false;
	if(b > 255 || b < 0)
		bl = false;
	if(bl == false || ve == false || bl == false)
	{
		throw InvalidColorException("Couleur invalide", ro, ve, bl);
	}
	
	setRouge(r);
	setVert(v);
	setBleu(b);
	
	nom = NULL;
	
	compteur +=1;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 3 Couleur" << endl;
	#endif
}

Couleur::~Couleur()
{
	if(nom != NULL)
		delete nom;
	
	compteur -=1;
	#ifdef DEBUG
		cerr << "Fin Destructeur Couleur" << endl;
	#endif
}


void Couleur::setRouge(const int arg)
{
	
	if(arg >= 0 && arg < 256)
	{
		rouge = arg;
	}
	else
	{
		throw InvalidColorException("Rouge invalide", false, true, true);
	}
}

void Couleur::setVert(const int arg)
{
	
	if(arg >= 0 && arg < 256)
	{
		vert = arg;
	}
	else
	{
		throw InvalidColorException("Vert invalide", true, false, true);
	}
}

void Couleur::setBleu(const int arg)
{
	
	if(arg >= 0 && arg < 256)
	{
		bleu = arg;
	}
	else
	{
		throw InvalidColorException("Bleu invalide", true, true, false);
	}
}

void Couleur::setNom(const char* arg)
{       
	if(nom != NULL)
		delete nom;
		
	nom = new char[strlen(arg)+1];

	strcpy(nom,arg);
}

const int Couleur::getRouge() const
{
	return rouge;
}

const int Couleur::getVert() const
{
	return vert;
}

const int Couleur::getBleu() const
{
	return bleu;
}

const char* Couleur::getNom() const
{
	return nom;
}

const int Couleur::getCompteur()
{
	return compteur;
}


const int Couleur::getLuminance() const
{
	return (getRouge() + getVert() + getBleu())/3;
}


void Couleur::Affiche() const
{
	cout << "RVB = " << getRouge() << ";" << getVert() << ";" << getBleu() << endl;
	if(getNom())
		cout << "Libellé: " << getNom() << endl;
}

Couleur& Couleur::operator=(const Couleur& arg)
{
	setRouge(arg.getRouge());
	setVert(arg.getVert());
	setBleu(arg.getBleu());
	if(arg.getNom() != NULL)
		setNom(arg.getNom());
	return *this;
}



Couleur operator+(const Couleur& a, int b)
{
	return b + a;
}

Couleur operator+(int a, const Couleur& b)
{
	Couleur temp(b);
	
	if((a + b.getRouge()) <= 255 && (a + b.getVert()) <= 255 && (a + b.getBleu()) <= 255)
	{
		temp.setRouge(a + b.getRouge());
		temp.setVert(a + b.getVert());
		temp.setBleu(a + b.getBleu());
		
		char tempNom[100];
		char templum[5];
		strcpy(tempNom, b.getNom());
	
		strcat(tempNom, " fonce(");
		sprintf(templum, "%d", a);
		strcat(tempNom, templum);
		
		strcat(tempNom, ")");
	
		temp.setNom(tempNom);
	}
	else
	{
		bool r = true, v = true, bl = true;
		
		if((a + b.getRouge()) > 255)
			r = false;
		if((a + b.getVert()) > 255)
			v = false;
		if((a + b.getBleu()) > 255)
			bl = false;
		throw InvalidColorException("Couleur invalide", r, v, bl);
	}

	return temp;


}

Couleur operator+(const Couleur& a, const Couleur& b)
{
	Couleur temp(a);
	
	if((a.getRouge() + b.getRouge()) <= 255 && (a.getVert() + b.getVert()) <= 255 && (a.getBleu() + b.getBleu()) <= 255)
	{
		temp.setRouge(a.getRouge() + b.getRouge());
		temp.setVert(a.getVert() + b.getVert());
		temp.setBleu(a.getBleu() + b.getBleu());
		
		if(a.getNom() != NULL && b.getNom() != NULL)
		{
			char tempNom[100];
			strcpy(tempNom, "Mélange de : ");
		
			strcat(tempNom, a.getNom());
		
			strcat(tempNom, " ");
		
			strcat(tempNom, b.getNom());
		
			temp.setNom(tempNom);
		}
	}
	else
	{
		bool r = true, v = true, bl = true;
		
		if((a.getRouge() + b.getRouge()) > 255)
			r = false;
		if((a.getVert() + b.getVert()) > 255)
			v = false;
		if((a.getBleu() + b.getBleu()) > 255)
			bl = false;
			
		throw InvalidColorException("Couleur invalide", r, v, bl);
	}
		
	return temp;
	
}

Couleur operator-(const Couleur& a, int b)
{
	Couleur temp(a);
	
	if((a.getRouge() - b) >= 0 && (a.getVert() - b) >= 0 && (a.getBleu() - b) >= 0)
	{
		temp.setRouge(a.getRouge() - b);
		temp.setVert(a.getVert() - b);
		temp.setBleu(a.getBleu() - b);
		
		char tempNom[100];
		char templum[5];
		strcpy(tempNom, a.getNom());
	
		strcat(tempNom, " clair(");
		sprintf(templum, "%d", b);
		strcat(tempNom, templum);
		
		strcat(tempNom, ")");
	
		temp.setNom(tempNom);
	}
	else
	{
		bool r = true, v = true, bl = true;
		
		if((a.getRouge() - b) < 0)
			r = false;
		if((a.getVert() - b) < 0)
			v = false;
		if((a.getBleu() - b) < 0)
			bl = false;
		throw InvalidColorException("Couleur invalide", r, v, bl);
	}

	return temp;
}

Couleur operator-(int a, const Couleur& b)
{
	Couleur temp(b);
	
	if((a - b.getRouge()) >= 0 && (a - b.getVert()) >= 0 && (a - b.getBleu()) >= 0)
	{
		temp.setRouge(a - b.getRouge());
		temp.setVert(a - b.getVert());
		temp.setBleu(a - b.getBleu());
		
		char tempNom[100];
		char templum[5];
		strcpy(tempNom, b.getNom());
	
		strcat(tempNom, " clair(");
		sprintf(templum, "%d", a);
		strcat(tempNom, templum);
		
		strcat(tempNom, ")");
	
		temp.setNom(tempNom);
	}
	else
	{
		bool r = true, v = true, bl = true;
		
		if((a - b.getRouge()) < 0)
			r = false;
		if((a - b.getVert()) < 0)
			v = false;
		if((a - b.getBleu()) < 0)
			bl = false;
		throw InvalidColorException("Couleur invalide", r, v, bl);
	}

	return temp;


}

Couleur operator-(const Couleur& a, const Couleur& b)
{
	Couleur temp(a);
	
	if((a.getRouge() - b.getRouge()) >= 0 && (a.getVert() - b.getVert()) >= 0 && (a.getBleu() - b.getBleu()) >= 0)
	{
		temp.setRouge(a.getRouge() - b.getRouge());
		temp.setVert(a.getVert() - b.getVert());
		temp.setBleu(a.getBleu() - b.getBleu());
	}
	else
	{
		bool r = true, v = true, bl = true;
		
		if((a.getRouge() - b.getRouge()) < 0)
			r = false;
		if((a.getVert() - b.getVert()) < 0)
			v = false;
		if((a.getBleu() - b.getBleu()) < 0)
			bl = false;
			
		throw InvalidColorException("Couleur invalide", r, v, bl);
	}
		
	return temp;
	
}

bool operator==(const Couleur& a, const Couleur& b)
{
	if(strcmp(a.getNom(), b.getNom()) == 0)
	{
		return 1;
	}
	/*if(a.getLuminance() == b.getLuminance())
	{
		return 1;
	}*/
	
	if(a.getRouge() == b.getRouge())
		if(a.getVert() == b.getVert())
			if(a.getBleu() == b.getBleu())
				return 1;
	
	return 0;
}

bool operator!=(const Couleur& a, const Couleur& b)
{
	if(strcmp(a.getNom(), b.getNom()) != 0)
	{
		return 1;
	}
	/*if(a.getLuminance() != b.getLuminance())
	{
		return 1;
	}*/
	if(a.getRouge() != b.getRouge())
		if(a.getVert() != b.getVert())
			if(a.getBleu() != b.getBleu())
				return 1;
	
	return 0;
}

bool operator<(const Couleur& a, const Couleur& b)
{
	if(a.getLuminance() < b.getLuminance())
	{
		return 1;
	}
	
	return 0;


}

bool operator>(const Couleur& a, const Couleur& b)
{
	if(!(a < b))
	{
		return 1;
	}
	
	return 0;


}

ostream& operator<<(ostream& s, const Couleur& a)
{

	s << a.getRouge() << " " << a.getVert() << " " << a.getBleu();
	if(a.getNom() != NULL)
		s << " " << a.getNom();

	return s;

}

istream& operator>>(istream& s, Couleur& a) // A rectifier --> 1 chaine de caractère
{
	int temp = 0;
	char temp1[100];
	char* save;
	char* vert;
	char* bleu;
	char* nom;
	
	s.getline(temp1, 256);
	
	for(int i = 0; temp1[i] != '\0'; i+=1)
		if(temp1[i] == ' ')
			temp1[i] = ';';
			
	strtok_r(temp1, ";", &save);
	
	
	temp = atoi(temp1);
	a.setRouge(temp);
	
	strtok_r(save, ";", &vert);
	
	temp = atoi(save);
	
	a.setVert(temp);
	
	strtok_r(vert, ";", &bleu);
	
	temp = atoi(vert);
	
	a.setBleu(temp);
	
	a.setNom(bleu);
	
	return s;
}


Couleur Couleur::operator++()
{
	
	(*this) = (*this) + 10;
	
	return *this;

}

Couleur Couleur::operator++(int)
{
	Couleur temp((*this) + 10);
	
	return temp;

}

Couleur Couleur::operator--()
{
	(*this) = (*this) - 10;
	
	return *this;

}

Couleur Couleur::operator--(int)
{
	Couleur temp((*this) - 10);
	
	return temp;

}

void Couleur::Save(std::ofstream & fichier) const
{
	if(fichier.is_open())
	{
		//fichier.seekp(0,ios::end);
		fichier.write((char*)&rouge, sizeof(int));
		fichier.write((char*)&vert, sizeof(int));
		fichier.write((char*)&bleu, sizeof(int));
		if(nom != NULL)
		{
			int len = strlen(nom) +1;
			fichier.write((char*)&len, sizeof(int));
			fichier.write(nom, sizeof(char)*len);
		}
		else
		{
			int len = 0;
			fichier.write((char*)&len, sizeof(int));
		}
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Couleur::Load(std::ifstream & fichier)
{
	if(fichier.is_open())
	{
		if(!fichier.eof())
		{
			fichier.read((char*)&rouge, sizeof(int));
			fichier.read((char*)&vert, sizeof(int));
			fichier.read((char*)&bleu, sizeof(int));
			
			int len = 0;
			fichier.read((char*)&len, sizeof(int));
			
			if(len != 0)
			{
				nom = new char[len];
				fichier.read(nom, sizeof(char)*len);
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



int Couleur :: compteur = 0;
Couleur Couleur::ROUGE(255, 0, 0, "Rouge");
Couleur Couleur::VERT(0, 255, 0, "Vert");
Couleur Couleur::BLEU(0, 0, 255, "Bleu");
