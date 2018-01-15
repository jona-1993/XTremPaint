#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

template<class T> 
class SmartPointer
{	
	private:
		T* val;
	public:
		SmartPointer();
		
		SmartPointer(T*);
		
		SmartPointer(T&);
		
		~SmartPointer();
		
		void Delete();
		
		T* getVal() const;
		
		T& operator=(const T&);
		
		SmartPointer<T>& operator=(const SmartPointer<T>&);
		
		T* operator->() const;
		
		T& operator*();
		
};

template<class T>	bool operator==(const SmartPointer<T>&, const SmartPointer<T>&);
template<class T>	bool operator!=(const SmartPointer<T>&, const SmartPointer<T>&);
template<class T>	bool operator<(const SmartPointer<T>&, const SmartPointer<T>&);
template<class T>	bool operator>(const SmartPointer<T>&, const SmartPointer<T>&);
template<class T>	std::ostream& operator<<(std::ostream&, const SmartPointer<T>&);

#endif
