#ifndef LIGNE_H
#define LIGNE_H
#include "Forme.h"
#include "WindowSDL.h"

class Ligne : public Forme
{
	friend std::ostream& operator<<(std::ostream&, const Ligne&);
	private:
		Point extremite;
	public:
		// Constructeurs + Destructeur
		Ligne();
		Ligne(const char*, Point);
		Ligne(const char*, Point, Point,const Couleur*, int);
		
		Ligne(const Ligne&);
		~Ligne();
		
		void setId(const char*);
		void setExtremite(const Point);
		const Point getExtremite() const;
		
		Ligne& operator=(const Ligne&);
		
		void Affiche() const;
		
		const char* getInfos() ;
		
		void Dessine() const;
		
		void Save(std::ofstream &) const;
		
		int Load(std::ifstream&);
};

#endif
