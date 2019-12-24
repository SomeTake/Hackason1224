#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../Core/Object.h"

class BackGround
{
private:
	Object* object;

public:
	BackGround();
	~BackGround();

	void Update();
	void Draw();
};


#endif
