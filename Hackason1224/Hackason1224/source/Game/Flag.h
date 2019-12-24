#ifndef _FLAG_H_
#define _FLAG_H_

#include "../Core/Object.h"

class Flag
{
private:
	Object* object;

public:
	Flag();
	~Flag();

	void Update();
	void Draw();
};

#endif