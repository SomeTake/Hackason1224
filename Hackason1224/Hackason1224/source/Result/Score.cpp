#include "Score.h"

Score::Score() :
	score(0)
{
	for (int i = 0; i < 4; i++)
	{
		object[i] = new Object();
		object[i]->LoadTexture("Digit");
		object[i]->SetSize(100.0f, 200.0f);
		object[i]->SetPosition(D3DXVECTOR3(960.0f + i * 100.0f, 550.0f, 0.0f));
		object[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		object[i]->SetUV(0.0f, 0.0f, 0.1f, 1.0f);
	}
}

Score::~Score()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(object[i])
	}
}

void Score::Update()
{
}

void Score::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		object[i]->Draw();
	}
}

void Score::SetScore(float score)
{
	this->score = (int)score;

	int digit[4];
	digit[0] = this->score / 1000;
	digit[1] = (this->score / 100) % 10;
	digit[2] = (this->score / 10) % 10;
	digit[3] = this->score % 10;

	for (int i = 0; i < 4; i++)
	{
		float left = (float)digit[i] * 0.1f;
		object[i]->SetUV(left, 0.0f, 0.1f, 1.0f);
	}
}
