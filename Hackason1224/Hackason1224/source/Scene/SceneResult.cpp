#include "SceneResult.h"

void SceneManager::SceneResult::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneResult::OnUpdate(SceneManager & entity)
{
	return State::Result;
}

void SceneManager::SceneResult::OnDraw(SceneManager & entity)
{
}
