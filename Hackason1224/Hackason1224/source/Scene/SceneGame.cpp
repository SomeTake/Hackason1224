#include "SceneGame.h"
#include "../player.h"
#include "../yajirushi.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	//�v���C���[�̍X�V����
	UpdatePlayer();

	//���̍X�V����
	UpdateYajirushi();

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
	//�v���C���[�̕`�揈��
	DrawPlayer();

	//���̕`�揈��
	DrawYajirushi();

}
