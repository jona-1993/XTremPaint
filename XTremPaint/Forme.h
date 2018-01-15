#ifndef FORME_H
#define FORME_H

#include "WindowSDL.h"
#include "Couleur.h"
#include "Point.h"


class Forme
{
	friend bool operator==(const Forme&, const Forme&);
	friend bool operator!=(const Forme&, const Forme&);
	friend bool operator<(const Forme&, const Forme&);
	friend bool operator>(const Forme&, const Forme&);
	friend std::ostream& operator<<(std::ostream&, const Forme&);
	
	protected: 
		char* info;
		char* id;
	private:
		
		Point position;
		const Couleur *couleur;
		int profondeur;
		static int compteur;
	public:
		// Constructeurs + Destructeur
		Forme();
		Forme(const char*, Point);
		Forme(const char*, Point, const Couleur*, int);
		Forme(const Forme&);
		virtual ~Forme();
		
		// setters
		virtual void setId(const char*);
		void setPosition(const Point);
		void setCouleur(const Couleur*);
		void setProfondeur(const int);
		
		// getters
		const char* getId() const;
		const Point getPosition() const;
		const Couleur* getCouleur() const;
		const int getProfondeur() const;
		static const int getCompteur();
		
		void Affiche() const;
		
		Forme& operator=(const Forme&);
		
		void Save(std::ofstream&) const; // Crash avec virtual?
		
		int Load(std::ifstream&);
		
		virtual const char* getInfos() = 0;
		
		virtual void Dessine() const = 0;
};

#endif
