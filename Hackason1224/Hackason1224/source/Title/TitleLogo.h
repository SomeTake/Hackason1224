#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "../Core/Object.h"

class TitleLogo
{
private:
	Object* object;

public:
	TitleLogo();
	~TitleLogo();

	void Update();
	void Draw();
};

#endif
