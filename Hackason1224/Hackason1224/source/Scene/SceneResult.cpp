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

void SceneManager::SceneResult::OnStart(SceneManager & entity)
{
	// 距離の計算
	entity.CheckDistance();

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
	// 背景の描画
	entity.backGround->Draw();

	DrawGauge();
	//プレイヤーの描画処理
	DrawPlayer();

	//矢印の描画処理
	DrawYajirushi();

	//駅の描画処理
	DrawStation();

	// ゴールフラッグ
	entity.flag->Draw();


	entity.resultLogo->Draw();
}
