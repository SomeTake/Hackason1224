#include "ResultLogo.h"

ResultLogo::ResultLogo()
{
	object = new Object();
	object->LoadTexture("ResultLogo");
	object->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	object->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));
	object->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

ResultLogo::~ResultLogo()
{
	SAFE_DELETE(object);
}

void ResultLogo::Update()
{
}

void ResultLogo::Draw()
{
	object->Draw();
}
