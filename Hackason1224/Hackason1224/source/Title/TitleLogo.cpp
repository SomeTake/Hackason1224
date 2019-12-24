#include "TitleLogo.h"

TitleLogo::TitleLogo()
{
	object = new Object();
	object->LoadTexture("TitleLogo");
	object->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	object->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));
	object->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//object->SetUV();
}

TitleLogo::~TitleLogo()
{
	SAFE_DELETE(object);
}

void TitleLogo::Update()
{
}

void TitleLogo::Draw()
{
	object->Draw();
}
