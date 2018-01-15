#ifndef COULEUR_H
#define COULEUR_H

class Couleur
{
	friend Couleur operator+(const Couleur&, int);
	friend Couleur operator+(int, const Couleur&);
	friend Couleur operator+(const Couleur&, const Couleur&); 
	friend Couleur operator-(const Couleur&, int);
	friend Couleur operator-(int, const Couleur&);
	friend Couleur operator-(const Couleur&, const Couleur&); 
	friend bool operator==(const Couleur&, const Couleur&);
	friend bool operator!=(const Couleur&, const Couleur&);
	friend bool operator<(const Couleur&, const Couleur&);
	friend bool operator>(const Couleur&, const Couleur&);
	friend std::ostream& operator<<(std::ostream&, const Couleur&);
	friend std::istream& operator>>(std::istream&, Couleur&);
	private:
		int rouge;
		int vert;
		int bleu;
		char* nom;
		static int compteur;
		
	public:
		// Constructeurs + Destructeur
		Couleur();
		Couleur(int, int, int, const char*);
		Couleur(int, int, int);
		Couleur(const Couleur&);
		~Couleur();
		
		// setters
		
		void setRouge(const int);
		void setVert(const int);
		void setBleu(const int);
		void setNom(const char*);
		
		// getters
		const int getRouge() const;
		const int getVert() const;
		const int getBleu() const;
		const char* getNom() const;
		static const int getCompteur();
		
		const int getLuminance() const;
		
		void Affiche() const;
		
		Couleur& operator=(const Couleur&);
		Couleur operator++();
		Couleur operator++(int);
		Couleur operator--();
		Couleur operator--(int);
		
		void Save(std::ofstream & fichier) const;
		int Load(std::ifstream & fichier);
		
		
		
		static Couleur ROUGE;
		static Couleur VERT;
		static Couleur BLEU;
};

#endif
