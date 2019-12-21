//=============================================================================
//
// ステートマシン [BaseState.h]
// Author:GP12B332 19 染谷武志
//
//=============================================================================
#ifndef _BASESTATE_H_
#define _BASESTATE_H_

//****************************************************
// テンプレートクラス定義
//****************************************************
template <class T, class ENUM>
class BaseState
{
public:
	virtual void OnStart(T& entity) = 0;	// 入場
	virtual ENUM OnUpdate(T& entity) = 0;	// 更新
	virtual void OnDraw(T& entity) = 0;		// 描画
};

#endif
