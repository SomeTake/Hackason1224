//=============================================================================
//
// 円形シーン切り替え [CircleSceneChanger.h]
// Author : HAL東京 GP11B341 17 染谷武志
// 
//=============================================================================
#ifndef _CIRCLESCENECHANGER_H_
#define _CIRCLESCENECHANGER_H_

#include "SceneChanger.h"
#include "Resource/BaseSingleton.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CircleSceneChanger :
	public SceneChanger,
	public BaseSingleton<CircleSceneChanger>
{
	friend class BaseSingleton<CircleSceneChanger>;

private:
	int cntFrame;			// シーンチェンジにかける時間

public:
	CircleSceneChanger() { cntFrame = 0; }
	void Update()override;
	void SetChanger(bool isStart, std::function<void(void)> func = NULL);
};

#endif
