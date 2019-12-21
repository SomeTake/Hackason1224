#include "SceneTitle.h"

void SceneManager::SceneTitle::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneTitle::OnUpdate(SceneManager & entity)
{
	return State::Title;
}

void SceneManager::SceneTitle::OnDraw(SceneManager & entity)
{
}
