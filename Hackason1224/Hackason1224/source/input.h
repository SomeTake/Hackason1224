//=============================================================================
//
// ���͏��� [input.h]
// Author : �����ċP
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "../Main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif