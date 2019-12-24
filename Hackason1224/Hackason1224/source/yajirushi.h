//=============================================================================
//
// �o���b�g���� [yajirushi.h]
// Author : �����ċP
//
//=============================================================================
#pragma once


// �}�N����`
#define YAJIRUSHI_TEXTURE			_T("data/TEXTURE/�a��2.png")	// �摜
#define YAJIRUSHI_TEXTURE_SIZE_X	(60)		// �e�N�X�`���T�C�Y
#define YAJIRUSHI_TEXTURE_SIZE_Y	(60)		// ����

#define YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define YAJIRUSHI_ANIM_PATTERN_NUM			(YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X*YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define YAJIRUSHI_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define YAJIRUSHI_MAX						(300)	// �o���b�g�̍ő吔
#define YAJIRUSHI_DAMAGE					(10)	// �o���b�g�̍ő吔


#define YAJIRUSHI_SPEED			(14.0f)		// �o���b�g�̈ړ��X�s�[�h


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���
	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// ���a
	float			BaseAngle;					// �p�x

} YAJIRUSHI;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitYajirushi(int type);
void UninitYajirushi(void);
void UpdateYajirushi(void);
void DrawYajirushi(void);
void SetYajirushi(D3DXVECTOR3 pos);
YAJIRUSHI *GetYajirushi(void);


