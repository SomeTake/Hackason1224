//=============================================================================
//
// ゲームシーン [SceneGame.h]
// Author : GP12B332 19
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "SceneManager.h"

//****************************************************
// クラス定義
//****************************************************
class SceneManager::SceneGame :
	public SceneManager::SceneState
{
public:
	void OnStart(SceneManager& entity)override;		// 入場
	State OnUpdate(SceneManager& entity)override;	// 更新
	void OnDraw(SceneManager& entity)override;		// 描画
};

#endif
