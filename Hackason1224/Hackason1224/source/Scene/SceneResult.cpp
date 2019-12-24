#include "SceneResult.h"
#include "../input.h"
#include "../Result/ResultLogo.h"
#include "../CircleSceneChanger.h"

void SceneManager::SceneResult::OnStart(SceneManager & entity)
{

	//*********************************************************
	// シーンチェンジの終了
	CircleSceneChanger::Instance()->SetChanger(false);
}

SceneManager::State SceneManager::SceneResult::OnUpdate(SceneManager & entity)
{
	entity.resultLogo->Update();

	// とりあえずスペースキー押したらタイトルへ
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
