#ifndef _SCORE_H_
#define _SCORE_H_

#include "../Core/Object.h"

class Score
{
public:
	Score();
	~Score();

	void Update();
	void Draw();

	void SetScore(float score);

private:
	Object* object[4];
	int score;
};

#endif
