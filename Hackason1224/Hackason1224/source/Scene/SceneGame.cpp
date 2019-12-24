#include "SceneGame.h"
#include "../input.h"
#include "../../gauge.h"
#include "../player.h"
#include "../yajirushi.h"
#include "../Game/BackGround.h"

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

	UpdateGauge();
	//�v���C���[�̍X�V����
	UpdatePlayer();

	//���̍X�V����
	UpdateYajirushi();

	// �w�i
	entity.backGround->Update();

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
	DrawGauge();
	//�v���C���[�̕`�揈��
	DrawPlayer();

	//���̕`�揈��
	DrawYajirushi();

	// �w�i�̕`��
	entity.backGround->Draw();
}
