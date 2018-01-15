#ifndef POINT_H
#define POINT_H

class Point
{
	friend std::ostream& operator<<(std::ostream&, const Point&);
	private:
		int x;
		int y;
		static int compteur;
	public:
		// Constructeurs + Destructeur
		Point();
		Point(int, int);
		Point(const Point&);
		~Point();
		
		// Ascesseurs
		void setX(const int);
		void setY(const int);
		
		// Mutateurs
		const int getX() const;
		const int getY() const;
		static const int getCompteur();
		
		void Save(std::ofstream&) const;
		int Load(std::ifstream &);
		
		void Affiche() const;
};

#endif
