#include "SceneTitle.h"
#include "../Title/TitleLogo.h"
#include "../input.h"

void SceneManager::SceneTitle::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneTitle::OnUpdate(SceneManager & entity)
{
	entity.titleLogo->Update();

	// とりあえずスペースキー押したらゲームシーンへ
	if (GetKeyboardTrigger(DIK_SPACE)) 
	{
		entity.ChangeState(State::Game);
	}

	return State::Title;
}

void SceneManager::SceneTitle::OnDraw(SceneManager & entity)
{
	entity.titleLogo->Draw();
}
