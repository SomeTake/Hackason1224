#include "SceneGame.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
}
