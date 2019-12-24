#include "SceneResult.h"
#include "../input.h"
#include "../Result/ResultLogo.h"
#include "../CircleSceneChanger.h"

void SceneManager::SceneResult::OnStart(SceneManager & entity)
{

	//*********************************************************
	// �V�[���`�F���W�̏I��
	CircleSceneChanger::Instance()->SetChanger(false);
}

SceneManager::State SceneManager::SceneResult::OnUpdate(SceneManager & entity)
{
	entity.resultLogo->Update();

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
	entity.resultLogo->Draw();
}
