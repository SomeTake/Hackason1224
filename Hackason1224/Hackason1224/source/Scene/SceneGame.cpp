#include "SceneGame.h"
#include "../input.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	// �Ƃ肠�����X�y�[�X�L�[�������烊�U���g��
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		entity.ChangeState(State::Result);
	}

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
}
