#include "SceneResult.h"
#include "../input.h"
#include "../Result/ResultLogo.h"

void SceneManager::SceneResult::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneResult::OnUpdate(SceneManager & entity)
{
	entity.resultLogo->Update();

	// とりあえずスペースキー押したらタイトルへ
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		entity.ChangeState(State::Title);
	}

	return State::Result;
}

void SceneManager::SceneResult::OnDraw(SceneManager & entity)
{
	entity.resultLogo->Draw();
}
