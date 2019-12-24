//=============================================================================
//
// シーンマネージャ[SceneManager.h]
// Author : GP12B332 19 染谷武志
//
//=============================================================================
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "../Title/TitleLogo.h"
#include "../Result/ResultLogo.h"
#include "../Resource/ResourceManager.h"
#include "../../gauge.h"
#include "../player.h"
#include "../station.h"
#include "../yajirushi.h"
#include "../Game/BackGround.h"
#include "../Game/Flag.h"
#include "../CircleSceneChanger.h"
#include "../GameConfig.h"
#include "../Result/Score.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SceneManager::SceneManager()
{
	// ステートマシンの作成
	fsm.resize(State::Max, NULL);
	fsm[State::Title] = new SceneTitle();
	fsm[State::Game] = new SceneGame();
	fsm[State::Result] = new SceneResult();
}

//=============================================================================
// コンストラクタ
//=============================================================================
SceneManager::~SceneManager()
{
	// ステートマシンの削除
	for (auto&& p : fsm)
	{
		delete p;
		p = NULL;
	}
	fsm.clear();
}

void SceneManager::Init()
{
	// リソース読み込み
	LoadResource();

	titleLogo = new TitleLogo();
	resultLogo = new ResultLogo();
	backGround = new BackGround();
	flag = new Flag();
	score = new Score();

	InitGauge(0);
	//プレイヤーの初期化
	InitPlayer(0);

	//矢印の初期化
	InitYajirushi(0);

	//駅の初期化
	InitStation(0);

	// 初期シーンを設定
	ChangeState(State::Title);
}

void SceneManager::Uninit()
{
	SAFE_DELETE(titleLogo);
	SAFE_DELETE(resultLogo);
	SAFE_DELETE(backGround);
	SAFE_DELETE(flag);
	SAFE_DELETE(score);

	UninitGauge();
	//プレイヤーの終了処理
	UninitPlayer();

	//矢印の終了処理
	UninitYajirushi();

	//駅の終了処理
	UninitStation();

}

void SceneManager::Update()
{
	// ステートマシンの更新
	State next = fsm[currentState]->OnUpdate(*this);

	CircleSceneChanger::Instance()->Update();
}

void SceneManager::Draw()
{
	// ステンシルマスクの描画
	CircleSceneChanger::Instance()->DrawMask();

	// ステートマシンの描画
	fsm[currentState]->OnDraw(*this);

	// シーンチェンジャーの描画
	CircleSceneChanger::Instance()->DrawChanger();
}

void SceneManager::ChangeState(State next)
{
	prevState = currentState;

	currentState = next;

	if (fsm[currentState] != NULL)
	{
		fsm[currentState]->OnStart(*this);
	}
}

void SceneManager::LoadResource()
{
	ResourceManager::Instance()->LoadTexture("TitleLogo", "data/Texture/Title.png");
	ResourceManager::Instance()->LoadTexture("ResultLogo", "data/Texture/Result.png");
	ResourceManager::Instance()->LoadTexture("BackGround", "data/Texture/BackGround.png");
	ResourceManager::Instance()->LoadTexture("Flag", "data/Texture/Flag.png");
	ResourceManager::Instance()->LoadTexture("Digit", "data/Texture/Digit.png");

	ResourceManager::Instance()->LoadTexture("Mask", "data/Texture/Circle.png");
	ResourceManager::Instance()->LoadTexture("Changer", "data/Texture/Load.png");
	CircleSceneChanger::Instance()->LoadMaskTexture();
	CircleSceneChanger::Instance()->LoadChangeTexture();
}

// ゴールと現在の駅がある場所を測る
void SceneManager::CheckDistance()
{
	STATION* station = GetStation();

	D3DXVECTOR3 vec = station->pos - GameConfig::Const::GoalPosition; // 実際には落下した位置と比較する
	ResultDistance = D3DXVec3Length(&vec);
	ResultDistance = abs(ResultDistance);
}
