#include "SceneGame.h"
#include "../player.h"
#include "../yajirushi.h"

void SceneManager::SceneGame::OnStart(SceneManager & entity)
{
}

SceneManager::State SceneManager::SceneGame::OnUpdate(SceneManager & entity)
{
	//プレイヤーの更新処理
	UpdatePlayer();

	//矢印の更新処理
	UpdateYajirushi();

	return State::Game;
}

void SceneManager::SceneGame::OnDraw(SceneManager & entity)
{
	//プレイヤーの描画処理
	DrawPlayer();

	//矢印の描画処理
	DrawYajirushi();

}
