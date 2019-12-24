#include "SceneTitle.h"
#include "../Title/TitleLogo.h"
#include "../input.h"
#include "../CircleSceneChanger.h"

void SceneManager::SceneTitle::OnStart(SceneManager & entity)
{

	//*********************************************************
	// �V�[���`�F���W�̏I��
	CircleSceneChanger::Instance()->SetChanger(false);

}

SceneManager::State SceneManager::SceneTitle::OnUpdate(SceneManager & entity)
{
	entity.titleLogo->Update();

	// �Ƃ肠�����X�y�[�X�L�[��������Q�[���V�[����
	if (GetKeyboardTrigger(DIK_SPACE)) 
	{
		CircleSceneChanger::Instance()->SetChanger(true, [&]()
		{
			entity.ChangeState(State::Game);
		});
	}

	return State::Title;
}

void SceneManager::SceneTitle::OnDraw(SceneManager & entity)
{
	entity.titleLogo->Draw();
}
