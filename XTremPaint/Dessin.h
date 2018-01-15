#ifndef DESSIN_H
#define DESSIN_H

#include "Couleur.h"
#include "Forme.h"
#include "SmartPointer.h"
#include "Liste.h"
#include "ListeTriee.h"

class Dessin
{
	friend std::ostream& operator<<(std::ostream&, const Dessin&);
	friend std::istream& operator>>(std::istream&, Dessin&);
	
	private :
		int largeur;
		int hauteur;
		Couleur fond;
		Liste<Couleur> palette;
		ListeTriee<SmartPointer<Forme> > formes;
	public :
		Dessin();
		Dessin(int,int,const Couleur&);
		Dessin(const Dessin&);
		~Dessin();
		
		void setLargeur(const int);
		void setHauteur(const int);
		void setBackground(const Couleur);
		void setPalette(const Liste<Couleur>);
		void addPalette(const Liste<Couleur>);
		void setFormes(const ListeTriee<SmartPointer<Forme> >);
		void addFormes(const ListeTriee<SmartPointer<Forme> >);
		
		const int getLargeur() const;
		const int getHauteur() const;
		const Couleur getBackground() const;
		Liste<Couleur> getPalette() const;
		Couleur* getCouleurPalette(const char*) const;
		int ReplaceCouleurPalette(const char*, const Couleur);
		ListeTriee<SmartPointer<Forme> > getFormes() const;
		
		
		
		void AjouteCouleur(const Couleur&);
		void AjouteForme(Forme*,const char*);
		
		void Save(std::ofstream&) const; // IDEM, ça sent le caca
		int Load(std::ifstream&);
		
		int importCouleurs(const char* filename);
		int importRectangles(const char* filename); //!\\ MEFIANCE: Source possible de crasses dans les imports
		int importPixels(const char* filename);
		int importLignes(const char* filename);
		
		Dessin& operator=(const Dessin&);
		
} ;

#endif
