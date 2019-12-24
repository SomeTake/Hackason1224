#include "SceneGame.h"
#include "../../gauge.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{

	UpdateGauge();
	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
	DrawGauge();
}
