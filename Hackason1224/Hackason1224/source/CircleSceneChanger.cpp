//=============================================================================
//
// �~�`�V�[���؂�ւ� [CircleSceneChanger.cpp]
// Author : HAL���� GP11B341 17 ���J���u
// 
//=============================================================================
#include "CircleSceneChanger.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHANGE_TIME	(30)

//=============================================================================
// �X�V
//=============================================================================
void CircleSceneChanger::Update()
{
	if (!useMask)
		return;

	cntFrame++;

	// �X�P�[��������������
	scl -= D3DXVECTOR3(1.0f / (float)CHANGE_TIME, 1.0f / (float)CHANGE_TIME, 0.0f);

	SetVertexMask();

	// �I���m�F
	if (cntFrame == CHANGE_TIME)
	{
		useMask = false;

		if (isChangerOut)
			useChanger = false;

		// �R�[���o�b�N�̌Ăяo��
		if (callback != NULL)
			callback();

		callback = NULL;
	}
}

//=============================================================================
// �J�n
//=============================================================================
void CircleSceneChanger::SetChanger(bool isStart, std::function<void(void)> func)
{
	// ���łɃ}�X�N���ł���ΊJ�n���Ȃ�
	if (useMask)
		return;

	// �����J�ڏ�Ԃ̏ꍇ�J�n���Ȃ�
	if (isStart == useChanger)
		return;

	// �p�����[�^������
	scl = isStart ? D3DXVECTOR3(1.0f, 1.0f, 0.0f) : D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;

	// �R�[���o�b�N�o�^
	callback = func;

	// �t���O������
	useMask = true;
	useChanger = true;
	isChangerOut = !isStart;
}
