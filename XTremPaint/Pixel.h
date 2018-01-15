#ifndef PIXEL_H
#define PIXEL_H
//#include "Forme.h"
#include "WindowSDL.h"

class Pixel : public Forme
{
	friend std::ostream& operator<<(std::ostream&, const Pixel&);
	public:
		// Constructeurs + Destructeur
		Pixel();
		Pixel(const char*, Point);
		Pixel(const char*, Point, const Couleur*, int);
		
		Pixel(const Pixel&);
		~Pixel();
		
		void setId(const char*);
		
		Pixel& operator=(const Pixel&);
		
		const char* getInfos() ;
		
		void Save(std::ofstream&) const;
		
		int Load(std::ifstream&);
		
		void Dessine() const;
};

#endif
