#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "InvalidColorException.h"
#include "Forme.h"
#include "Rectangle.h"
#include "Pixel.h"
#include "Ligne.h"
#include "Dessin.h"
#include "SmartPointer.h"
#include "Iterateur.h"


Dessin::Dessin()
{
	largeur = hauteur = 0;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur par défaut Dessin" << endl;
	#endif
}

Dessin::Dessin(int l, int h, const Couleur& b)
{
	largeur = l;
	hauteur = h;
	fond = b;
	
	#ifdef DEBUG
		cerr << "Fin Constructeur d'init 3 Dessin" << endl;
	#endif
}

Dessin::Dessin(const Dessin& arg)
{
	largeur = arg.getLargeur();
	hauteur = arg.getHauteur();
	setBackground(arg.getBackground());
	setPalette(arg.getPalette());
	setFormes(arg.getFormes());
	
	#ifdef DEBUG
		cerr << "Fin Constructeur Copie Dessin" << endl;
	#endif
}

Dessin::~Dessin()
{
	
	#ifdef DEBUG
		cerr << "Fin Destructeur Dessin" << endl;
	#endif
}

void Dessin::setLargeur(const int arg)
{
	largeur = arg;
}

void Dessin::setHauteur(const int arg)
{
	hauteur = arg;
}

void Dessin::setBackground(const Couleur arg)
{
	fond = arg;
}

void Dessin::setPalette(const Liste<Couleur> arg)
{       
	palette.Purge();
	palette = arg; // ??
}

void Dessin::addPalette(const Liste<Couleur> arg)
{       
	palette = arg; // ??
}

void Dessin::setFormes(const ListeTriee<SmartPointer<Forme> > arg)
{       
	formes.Purge();
	formes = arg; // ??
}

void Dessin::addFormes(const ListeTriee<SmartPointer<Forme> > arg)
{       
	formes = arg; // ??
}

const int Dessin::getLargeur() const
{
	return largeur;
}

const int Dessin::getHauteur() const
{
	return hauteur;
}

const Couleur Dessin::getBackground() const
{
	return fond;
}

Liste<Couleur> Dessin::getPalette() const
{
	return palette;
}

Couleur* Dessin::getCouleurPalette(const char* name) const
{
	Couleur *temp = NULL;
	
	for(int i = 0; i < palette.getNombreElements(); i+=1)
	{
		if(strcmp(name, palette.getElement(i)->valeur.getNom()) == 0)
		{
			temp = &palette.getElement(i)->valeur;
			goto end;
		}
	}
	end:;
	return temp;
}

int Dessin::ReplaceCouleurPalette(const char* name, const Couleur coul)
{
	for(int i = 0; i < palette.getNombreElements(); i+=1)
	{
		if(strcmp(name, palette.getElement(i)->valeur.getNom()) == 0)
		{
			palette.getElement(i)->valeur = coul;
			goto end;
		}
	}
	return 0;
	end:;
	return 1;
}

ListeTriee<SmartPointer<Forme> > Dessin::getFormes() const
{
	return formes;
}

void Dessin::AjouteCouleur(const Couleur& c)
{
	Couleur* search = &palette.Recherche(c)->valeur;
	
	if(search == NULL)
	{
		palette.insere(c);
	}
}

void Dessin::AjouteForme(Forme *pf,const char* nomCouleur)
{
	cerr << "Nombre de couleurs dans la palette: " << palette.getNombreElements() << endl;
	for(int i = 0; i < palette.getNombreElements(); i+=1)
	{
		if((palette.getElement(i)->valeur).getNom() != NULL)
		{
			
			cerr << nomCouleur << " vs " << (palette.getElement(i)->valeur).getNom() << endl;
			if(strcmp(nomCouleur, (palette.getElement(i)->valeur).getNom()) == 0)
			{
				
				pf->setCouleur((&palette.getElement(i)->valeur));
				formes.insere(pf);
			}
		}
		
	}
}
		
Dessin& Dessin::operator=(const Dessin& arg)
{
	setLargeur(arg.getLargeur());
	setHauteur(arg.getHauteur());
	setBackground(arg.getBackground());
	setPalette(arg.getPalette());
	setFormes(arg.getFormes());
	return *this;
}


ostream& operator<<(ostream& s, const Dessin& a)
{

	s << a.getLargeur() << " " << a.getHauteur();

	return s;

}

istream& operator>>(istream& s, Dessin& a)
{
	int temp = 0;
	char temp1[100];
	char* save;
	
	s.getline(temp1, 256);
	
	for(int i = 0; temp1[i] != '\0'; i+=1)
		if(temp1[i] == ' ')
			temp1[i] = ';';
			
	strtok_r(temp1, ";", &save);
	
	
	temp = atoi(temp1);
	a.setLargeur(temp);
	
	//strtok_r(save, ";", &a.getHauteur()); // Reviens quand tu sera moins crevé..
	
	//temp = atoi(save);
	
	//a.setHauteur(temp);
	
	return s;
}



void Dessin::Save(std::ofstream & fichier) const
{
	int nb = 0;
	
	if(fichier.is_open())
	{
		//fichier.seekp(0,ios::end);
		fichier.write((char*)&largeur, sizeof(int));
		fichier.write((char*)&hauteur, sizeof(int));
		fond.Save(fichier);
		nb = palette.getNombreElements();
		fichier.write((char*)&nb, sizeof(int));
		for(int i = 0; i < nb; i+=1)
		{
			palette.getElement(i)->valeur.Save(fichier);
		}
		nb = formes.getNombreElements();
		fichier.write((char*)&nb, sizeof(int));
		/*for(int i = 0; i < nb; i+=1)
		{
			fichier.write((char*)&(formes.getElement(i)->valeur)->getId()[0], sizeof(char));
			
			
			formes.getElement(i)->valeur->Save(fichier);
		}*/
		
		ListeTriee<SmartPointer<Forme> > des(getFormes());
		Iterateur<SmartPointer<Forme> > itcoul(des);
		itcoul.reset();
		//while(!itcoul.end())
		for(int i = 0; i < nb; i+=1) // Impossible d'accéder aux variables membres dans le Save..
		{
			fichier.write((char*)&(*(&itcoul))->getId()[0], sizeof(char));
			cerr << "ID: " << (*(&itcoul))->getId()[0] << endl;
			
			switch((*(&itcoul))->getId()[0])
			{
				case 'P': ((Pixel*)&itcoul)->Save(fichier);
					break;
				case 'L': ((Ligne*)&itcoul)->Save(fichier);
					break;
				case 'R': ((Rectangle*)&itcoul)->Save(fichier);
					break;
			}
			
			
			itcoul++;
		}
		if(!itcoul.end())
		{
			cout << "Supprimé avec succès !" << endl;
			itcoul.remove();
		}
	}
	else
	{
		cerr << "File Problem" << endl;
	}
}

int Dessin::Load(std::ifstream & fichier)
{
	int nb = 0;
	char identifier;
	Forme *import;
	Couleur col;
	
	if(fichier.is_open())
	{
		if(!fichier.eof())
		{
			
			fichier.read((char*)&largeur, sizeof(int));
			fichier.read((char*)&hauteur, sizeof(int));
			fond.Load(fichier);
			fichier.read((char*)&nb, sizeof(int));
			
			
			for(int i = 0; i < nb; i+=1)
			{
				col.Load(fichier);
				palette.insere(col);
			}
			fichier.read((char*)&nb, sizeof(int));
			
			cerr << "Nombre de Formes à charger: " << nb << " forme(s)";
			for(int i = 0; i < nb; i+=1)
			{
				
				fichier.read((char*)&identifier, sizeof(char)); // identifiant pas bon?
				cerr << largeur << " x " << hauteur << " fond: " << fond.getNom() << " NB= " << nb << " Identifier= " << identifier << endl;
				palette.Affiche();
				switch(identifier)
				{
					case 'P': import = new Pixel();
						  ((Pixel*)import)->Load(fichier);
						break;
					case 'L': import = new Ligne();
						  ((Ligne*)import)->Load(fichier);
						  
						break;
					case 'R': import = new Rectangle();
						  ((Rectangle*)import)->Load(fichier);
						break;
					default: import = NULL;
				}
				
				if(import != NULL)
				{
					import->Affiche();
					
					formes.insere(*import);
					
					delete(import);
				}
				else
				{
					cerr << "Erreur d'importation.." << endl;
				}
				
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


int Dessin::importCouleurs(const char* filename)
{
	ifstream fichier(filename, ios::in);
	char* t1, *t2, *t3, *t4;
	int r, v, b;
	Couleur temp;
	
	if(fichier)
	{
		char buffer[200];
		fichier.getline(buffer, 200);
		//while(!fichier.eof())
		while(fichier.getline(buffer, 200))
		{
			//fichier.getline(buffer, 200);
			
			strtok_r(buffer, ";", &t1);
			
			strtok_r(t1, ";", &t2);
			
			strtok_r(t2, ";", &t3);
			
			strtok_r(t3, ";", &t4);
			
			r = atoi(buffer);
			v = atoi(t1);
			b = atoi(t2);
			
			cerr << buffer << " " << t1 << " " << t2 << " " << t3 << endl;
			
			try
			{
				temp.setRouge(r);
				temp.setVert(v);
				temp.setBleu(b);
				if(t3 != NULL)
				{
					temp.setNom(t3);
					if(strcmp(t3, "") != 0) // Sinon Comment je peux l'identifier??'
						AjouteCouleur(temp);
				}
				
				
			}
			catch(InvalidColorException ex)
			{
				cerr << ex.getMessage() << endl;
			}
		}
		
		
		fichier.close();
		
	}
	
	return 1;
	
}

int Dessin::importPixels(const char* filename)
{
	ifstream fichier(filename, ios::in);
	char* t1, *t2, *t3, *t4, *t5;
	int px, py, p;
	Pixel *pix;
	Point point;
	
	if(fichier)
	{
		char buffer[200];
		fichier.getline(buffer, 200);
		//while(!fichier.eof())
		while(fichier.getline(buffer, 200))
		{
			//fichier.getline(buffer, 200);
			strtok_r(buffer, ";", &t1);
			
			strtok_r(t1, ";", &t2);
			
			strtok_r(t2, ";", &t3);
			
			strtok_r(t3, ";", &t4);
			
			px = atoi(buffer);
			py = atoi(t1);
			p = atoi(t2);
			
			
			try
			{
				pix = new Pixel();
				point.setX(px);
				point.setY(py);
				pix->setPosition(point);
				pix->setProfondeur(p);
				pix->setCouleur(getCouleurPalette(t3));
				char buff[20] = "P";
				char buffer2[20];
				sprintf(buffer2, "%d", pix->getCompteur());
				strcat(buff, buffer2);
				pix->setId(buff);
				cerr << "ID: " << pix->getId() << endl;
				
				formes.insere(pix);
			}
			catch(InvalidColorException ex)
			{
				cerr << ex.getMessage() << endl;
			}
		}
		
		fichier.close();
		
	}
	
	return 1;
	
}

int Dessin::importLignes(const char* filename)
{
	ifstream fichier(filename, ios::in);
	char* t1, *t2, *t3, *t4, *t5, *t6, *t7;
	int px, py, ex, ey, p;
	Ligne *line;
	Point point, extremite;
	
	if(fichier)
	{
		char buffer[200];
		fichier.getline(buffer, 200);
		//while(!fichier.eof())
		while(fichier.getline(buffer, 200))
		{
			//fichier.getline(buffer, 200);
			strtok_r(buffer, ";", &t1);
			
			strtok_r(t1, ";", &t2);
			
			strtok_r(t2, ";", &t3);
			
			strtok_r(t3, ";", &t4);
			
			strtok_r(t4, ";", &t5);
			
			strtok_r(t5, ";", &t6);
			
			px = atoi(buffer);
			py = atoi(t1);
			ex = atoi(t2);
			ey = atoi(t3);
			p = atoi(t4);
			
			
			try
			{
				line = new Ligne();
				point.setX(px);
				point.setY(py);
				extremite.setX(ex);
				extremite.setX(ey);
				line->setPosition(point);
				line->setExtremite(extremite);
				line->setProfondeur(p);
				line->setCouleur(getCouleurPalette(t5));
				char buff[20] = "L";
				char buffer2[20];
				sprintf(buffer2, "%d", line->getCompteur());
				strcat(buff, buffer2);
				line->setId(buff);
				cerr << "ID: " << line->getId() << endl;
				
				formes.insere(line);
			}
			catch(InvalidColorException ex)
			{
				cerr << ex.getMessage() << endl;
			}
		}
		
		fichier.close();
		
	}
	
	return 1;
	
}

int Dessin::importRectangles(const char* filename)
{
	ifstream fichier(filename, ios::in);
	char* t1, *t2, *t3, *t4, *t5, *t6, *t7;
	int px, py, dx, dy, r, p;
	Rectangle *rect;
	Point point;
	
	if(fichier)
	{
		char buffer[200];
		fichier.getline(buffer, 200);
		//while(!fichier.eof())
		while(fichier.getline(buffer, 200))
		{
			//fichier.getline(buffer, 200);
			strtok_r(buffer, ";", &t1);
			
			strtok_r(t1, ";", &t2);
			
			strtok_r(t2, ";", &t3);
			
			strtok_r(t3, ";", &t4);
			
			strtok_r(t4, ";", &t5);
			
			strtok_r(t5, ";", &t6);
			
			strtok_r(t6, ";", &t7);
			
			px = atoi(buffer);
			py = atoi(t1);
			dx = atoi(t2);
			dy = atoi(t3);
			r = atoi(t4);
			p = atoi(t5);
			
			
			try
			{
				rect = new Rectangle();
				point.setX(px);
				point.setY(py);
				rect->setPosition(point);
				rect->setDimX(dx);
				rect->setDimY(dy);
				rect->setProfondeur(p);
				rect->setRempli(r);
				rect->setCouleur(getCouleurPalette(t6));
				char buff[20] = "R";
				char buffer2[20];
				sprintf(buffer2, "%d", rect->getCompteur());
				strcat(buff, buffer2);
				rect->setId(buff);
				cerr << "ID: " << rect->getId() << endl;
				
				formes.insere(rect);
			}
			catch(InvalidColorException ex)
			{
				cerr << ex.getMessage() << endl;
			}
		}
		
		fichier.close();
		
	}
	
	return 1;
	
}

