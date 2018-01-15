#ifndef RECTANGLE_H
#define RECTANGLE_H

//#include "Forme.h"
#include "WindowSDL.h"

class Rectangle : public Forme
{
	friend std::ostream& operator<<(std::ostream&, const Rectangle&);
	
	private:
		int dimX;
		int dimY;
		bool rempli;
	public:
		// Constructeurs + Destructeur
		Rectangle();
		Rectangle(const char*, Point);
		Rectangle(const char*, Point, int, int, bool, const Couleur*, int);
		
		Rectangle(const Rectangle&);
		~Rectangle();
		
		void setId(const char* arg);
		void setDimX(const int);
		void setDimY(const int);
		void setRempli(const bool);
		const int getDimX() const;
		const int getDimY() const;
		const bool isRempli() const;
		
		
		Rectangle& operator=(const Rectangle&);
		
		void Affiche() const;
		
		const char* getInfos() ;
		
		void Save(std::ofstream&) const;
		
		int Load(std::ifstream&);
		
		void Dessine() const;
};

#endif
