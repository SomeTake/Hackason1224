#include "Flag.h"
#include "../GameConfig.h"

Flag::Flag()
{
	object = new Object();
	object->LoadTexture("Flag");
	object->SetSize(128.0f, 256.0f);
	object->SetPosition(D3DXVECTOR3(GameConfig::Const::GoalPosition.x, GameConfig::Const::GoalPosition.y, 0.0f));
	object->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

Flag::~Flag()
{
	SAFE_DELETE(object);
}

void Flag::Update()
{
}

void Flag::Draw()
{
	object->Draw();
}
