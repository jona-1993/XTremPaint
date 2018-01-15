#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

class BaseException
{
	protected:
		char* message;
	public:
		BaseException();
		
		BaseException(const char*);
		
		const char* getMessage();

};

#endif
