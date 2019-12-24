//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �����ċP
//
//=============================================================================
#pragma once


// �}�N����`
#define PLAYER_TEXTURE					_T("data/TEXTURE/chara01.png")	// �摜
#define PLAYER_TEXTURE_SIZE_X			(40/2)		// �e�N�X�`���T�C�Y
#define PLAYER_TEXTURE_SIZE_Y			(40/2)		// ����

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X	(3)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y	(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_ANIM_PATTERN_NUM			(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define PLAYER_TIME_ANIMATION			(4)			// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_MAX						(1)			// �v���C���[�̍ő吔

#define	PLAYER_JUMP_Y					(-80.0f)	// �W�����v�̍���
#define	PLAYER_JUMP_CNT_MAX				(30)		// 30�t���[���̃W�����v����

#define	PLAYER_X_MAX                    (450)
#define	PLAYER_X_MINIMUM                (130)
#define	PLAYER_Y_MAX                    (340)
#define	PLAYER_Y_MINIMUM                (100)
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
	bool            key;                        //true;�な false;����

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	
	bool			jump;						// �W�����v���t���O
	float			jump_y;						// �W�����v�̍���
	int				jump_cnt_max;
	int				jump_cnt;
	int				cnt;					// �J�E���g
	int				b_type;					// �o���b�g�^�C�v
	int				muteki_cnt;				// ���G����
	D3DXVECTOR3		ofs;						// pos�ɑ΂���I�t�Z�b�g���W

	bool			hit;						// �����蔻��

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


