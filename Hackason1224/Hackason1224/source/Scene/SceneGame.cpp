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
	// シーンチェンジの終了
	CircleSceneChanger::Instance()->SetChanger(false);
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	// とりあえずスペースキー押したらリザルトへ
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		CircleSceneChanger::Instance()->SetChanger(true, [&]()
		{
			entity.ChangeState(State::Result);
		});
	}

	UpdateGauge();
	//プレイヤーの更新処理
	UpdatePlayer();

	//矢印の更新処理
	UpdateYajirushi();

	// ゴールフラッグ
	entity.flag->Update();

	// 背景
	entity.backGround->Update();

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
	// 背景の描画
	entity.backGround->Draw();

	DrawGauge();
	//プレイヤーの描画処理
	DrawPlayer();

	//矢印の描画処理
	DrawYajirushi();

	// ゴールフラッグ
	entity.flag->Draw();
}
