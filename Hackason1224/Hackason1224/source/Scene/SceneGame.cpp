#include "SceneGame.h"
#include "../input.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	// とりあえずスペースキー押したらリザルトへ
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		entity.ChangeState(State::Result);
	}

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
}
