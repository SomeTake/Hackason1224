//=============================================================================
//
// シーンマネージャ[SceneManager.h]
// Author : GP12B332 19 染谷武志
//
//=============================================================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <vector>
#include "../../Main.h"

//****************************************************
// インスタンス作成用クラスの前方宣言
//****************************************************
class TitleLogo;
class ResultLogo;
class BackGround;
class Flag;
//****************************************************
// クラス定義
//****************************************************
class SceneManager
{
public:
	// 状態
	enum State {
		Title,
		Game,
		Result,
		Max
	};

	SceneManager();
	~SceneManager();

	// 各種処理
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// 状態遷移処理
	void ChangeState(State next);

	// リソースの読み込み
	void LoadResource();

private:
	// 内部クラスの前方宣言
	class SceneTitle;
	class SceneGame;
	class SceneResult;

	State currentState, prevState;		// 現在、以前の状態
	using SceneState = BaseState<SceneManager, State>;
	std::vector<SceneState*> fsm;		// ステートマシン

	// 各種インスタンス
	TitleLogo* titleLogo;
	ResultLogo* resultLogo;
	BackGround* backGround;
	Flag* flag;
};
#endif
