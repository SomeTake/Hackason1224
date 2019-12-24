#ifndef _RESULTLOGO_H_
#define _RESULTLOGO_H_

#include "../Core/Object.h"

class ResultLogo
{
private:
	Object* object;

public:
	ResultLogo();
	~ResultLogo();

	void Update();
	void Draw();

};

#endif
