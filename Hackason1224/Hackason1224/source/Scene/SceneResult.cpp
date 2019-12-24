#include "SceneResult.h"
#include "../input.h"
#include "../Result/ResultLogo.h"
#include "../CircleSceneChanger.h"
#include "../../gauge.h"
#include "../player.h"
#include "../station.h"
#include "../yajirushi.h"
#include "../Game/BackGround.h"
#include "../Game/Flag.h"
#include "../Result/Score.h"

void SceneManager::SceneResult::OnStart(SceneManager & entity)
{
	// �����̌v�Z
	entity.CheckDistance();
	entity.score->SetScore(entity.ResultDistance);

	//*********************************************************
	// �V�[���`�F���W�̏I��
	CircleSceneChanger::Instance()->SetChanger(false);
}

SceneManager::State SceneManager::SceneResult::OnUpdate(SceneManager & entity)
{
	entity.resultLogo->Update();
	entity.score->Update();

	// �Ƃ肠�����X�y�[�X�L�[��������^�C�g����
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		CircleSceneChanger::Instance()->SetChanger(true, [&]()
		{
			entity.ChangeState(State::Title);
		});
	}

	return State::Result;
}

void SceneManager::SceneResult::OnDraw(SceneManager & entity)
{
	// �w�i�̕`��
	entity.backGround->Draw();

	DrawGauge();
	//�v���C���[�̕`�揈��
	DrawPlayer();

	//���̕`�揈��
	DrawYajirushi();

	//�w�̕`�揈��
	DrawStation();

	// �S�[���t���b�O
	entity.flag->Draw();

	entity.resultLogo->Draw();
	entity.score->Draw();
}
