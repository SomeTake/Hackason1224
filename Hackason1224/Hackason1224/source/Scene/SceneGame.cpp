#include "SceneGame.h"
#include "../input.h"
#include "../../gauge.h"
#include "../player.h"
#include "../yajirushi.h"
#include "../Game/BackGround.h"
#include "../Game/Flag.h"
#include "../CircleSceneChanger.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{

	//*********************************************************
	// �V�[���`�F���W�̏I��
	CircleSceneChanger::Instance()->SetChanger(false);
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	// �Ƃ肠�����X�y�[�X�L�[�������烊�U���g��
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		CircleSceneChanger::Instance()->SetChanger(true, [&]()
		{
			entity.ChangeState(State::Result);
		});
	}

	UpdateGauge();
	//�v���C���[�̍X�V����
	UpdatePlayer();

	//���̍X�V����
	UpdateYajirushi();

	// �S�[���t���b�O
	entity.flag->Update();

	// �w�i
	entity.backGround->Update();

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
	// �w�i�̕`��
	entity.backGround->Draw();

	DrawGauge();
	//�v���C���[�̕`�揈��
	DrawPlayer();

	//���̕`�揈��
	DrawYajirushi();

	// �S�[���t���b�O
	entity.flag->Draw();
}
