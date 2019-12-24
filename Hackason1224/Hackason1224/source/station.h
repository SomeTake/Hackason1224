//=============================================================================
//
// �o���b�g���� [station.h]
// Author : 
//
//=============================================================================
#pragma once


// �}�N����`
#define STATION_TEXTURE			_T("data/TEXTURE/station.png")	// �摜
#define STATION_TEXTURE_SIZE_X	(150)		// �e�N�X�`���T�C�Y
#define STATION_TEXTURE_SIZE_Y	(100)		// ����

#define STATION_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define STATION_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)


#define STATION_SPEED			(4.0f)		// �o���b�g�̈ړ��X�s�[�h


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���b�g�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		move;						// �ړ���

	
	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// ���a
	float			BaseAngle;					// �p�x

} STATION;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStation(int type);
void UninitStation(void);
void UpdateStation(void);
void DrawStation(void);
void SetStation(D3DXVECTOR3 pos);
STATION *GetStation(void);


