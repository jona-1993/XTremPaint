#ifndef LISTEBASE_H
#define LISTEBASE_H


template <class T> class Iterateur;

template <class T> struct Cellule
{
	T valeur;
	
	Cellule<T> *suivant;

};

template <class T> class ListeBase
{
	protected:
		Cellule<T> *ptete;
	
	public:
		ListeBase();
		
		ListeBase(const ListeBase&);
		
		~ListeBase();
		
		ListeBase<T>& operator=(const ListeBase&);
		
		bool estVide();
		
		void Affiche();
		
		Cellule<T>* getElement(int) const;
		
		int getNombreElements() const;
		
		void Purge();
		
		virtual T* insere(const T&) = 0;
		
		friend class Iterateur<T>;
		
};



#endif
