//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �����ċP
//
//=============================================================================
#pragma once


// �}�N����`
#define PLAYER_TEXTURE					_T("data/TEXTURE/player.png")	// �摜
#define PLAYER_TEXTURE_SIZE_X			(500/2)		// �e�N�X�`���T�C�Y
#define PLAYER_TEXTURE_SIZE_Y			(500/2)		// ����

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X	(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y	(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ANIM_PATTERN_NUM			(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_TIME_ANIMATION			(4)			// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_MAX						(1)			// �v���C���[�̍ő吔
//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	bool			anim;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̍��W
	D3DXVECTOR3		move;						// �|���S���̍��W
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g
	int             key;                        //0;�L�[���͂Ȃ�1;�な 2;����

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	
	int				cnt;						// �J�E���g
	D3DXVECTOR3		ofs;						// pos�ɑ΂���I�t�Z�b�g���W

} PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void UpdatePlayerLineOver(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);


