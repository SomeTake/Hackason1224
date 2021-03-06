//=============================================================================
//
// 入力処理 [input.h]
// Author : 高橋翔輝
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "../Main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif