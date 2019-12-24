#include "SceneTitle.h"
#include "../Title/TitleLogo.h"
#include "../input.h"
#include "../CircleSceneChanger.h"
#include "../station.h"
#include "../yajirushi.h"
#include "../player.h"
#include "../../gauge.h"

void SceneManager::SceneTitle::OnStart(SceneManager & entity)
{

	InitGauge(1);
	//プレイヤーの初期化
	InitPlayer(1);

	//矢印の初期化
	InitYajirushi(1);

	//駅の初期化
	InitStation(1);

	// 結果の初期化
	entity.ResultDistance = 0.0f;

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
