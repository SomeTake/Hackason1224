#include "SceneTitle.h"
#include "../Title/TitleLogo.h"
#include "../input.h"
#include "../CircleSceneChanger.h"

void SceneManager::SceneTitle::OnStart(SceneManager & entity)
{

	//*********************************************************
	// シーンチェンジの終了
	CircleSceneChanger::Instance()->SetChanger(false);

}

SceneManager::State SceneManager::SceneTitle::OnUpdate(SceneManager & entity)
{
	entity.titleLogo->Update();

	// とりあえずスペースキー押したらゲームシーンへ
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
