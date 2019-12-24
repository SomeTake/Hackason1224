//=============================================================================
//
// ���� [gauge.h]
// Author : Takeaki Sakamaki
//
//=============================================================================
#pragma once

// �}�N����`

/*�@���[�^�[�@*/
#define TEXTURE_GAUGE			_T("data/TEXTURE/gauge.png")			// �T���v���p�摜

#define GAUGE_TEXTURE_SIZE_X	(1000)									// �e�N�X�`���T�C�Y
#define GAUGE_TEXTURE_SIZE_Y	(100)									// ����

#define GAUGE_POS_X		(30)
#define GAUGE_POS_Y		(30)

#define GAUGE_TEXTURE_PATTERN_DIVIDE_X	(1)								// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define GAUGE_TEXTURE_PATTERN_DIVIDE_Y	(1)								// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define GAUGE_ANIM_PATTERN_NUM			(GAUGE_TEXTURE_PATTERN_DIVIDE_X*GAUGE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define GAUGE_TIME_ANIMATION			(1)								// �A�j���[�V�����̐؂�ւ��J�E���g

#define GAUGE_MAX						(1)								// �ő��

#define GAUGE_METER_MAX	(100)											// �Q�[�W�ő吔


#define LOOP_COUNT		(60)

/*�@�g�@*/
#define TEXTURE_WAKU			_T("data/TEXTURE/waku.png")				// �T���v���p�摜

#define WAKU_TEXTURE_SIZE_X	(1000)										// �e�N�X�`���T�C�Y
#define WAKU_TEXTURE_SIZE_Y	(100)										// ����
		
#define WAKU_POS_X		(30)
#define WAKU_POS_Y		(30)


typedef struct	// �\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	int	count;

	bool	Isfinished;
	bool	reverse;
} GAUGE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGauge(int type);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);

float GetGauge(void);
float GetPower(void);
