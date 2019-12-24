//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �����ċP
//
//=============================================================================
#include "../Main.h"
#include "player.h"
#include "input.h"
#include "yajirushi.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern );
void SetVertexPlayer(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

static PLAYER					player;							// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			PLAYER_TEXTURE,					// �t�@�C���̖��O
			&g_pD3DTexturePlayer);			// �ǂݍ��ރ������̃|�C���^
	}

		player.pos = D3DXVECTOR3(220.0f, 700.0f, 0.0f);	// ���W�f�[�^��������
		player.move = D3DXVECTOR3(5.0f, 5.0f, 0.0f);	// ���W�f�[�^��������
		player.PatternAnim = 1;							// �A�j���p�^�[���ԍ��������_���ŏ�����
		player.CountAnim = 0;							// �A�j���J�E���g��������
		player.Texture = g_pD3DTexturePlayer;
		player.anim = false;
		MakeVertexPlayer();								// ���_���̍쐬

		//�e�N�X�`�����W��ݒ�
		SetTexturePlayer(player.PatternAnim);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	player.key = 0;

	if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S))
	{
		player.key = 2;

		player.cnt = 0;

	}
	else if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W))
	{
		player.key = 1;

		player.cnt = 0;

	}

	//�A�j���[�V����
	if (player.anim==true)
	{
		player.CountAnim++;

		if (player.PatternAnim == PLAYER_TEXTURE_PATTERN_DIVIDE_X -1)
		{
			return;
		}

		if ((player.CountAnim % PLAYER_TIME_ANIMATION) == 0)
		{
			//�p�^�[���̐؂�ւ�
			player.PatternAnim = (player.PatternAnim + 1) % PLAYER_ANIM_PATTERN_NUM;

			//�e�N�X�`�����W��ݒ�
			SetTexturePlayer(player.PatternAnim);
		}
	}

	 // ���ݒ�
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		player.anim = true;
	}


	SetVertexPlayer();	// �ړ���̍��W�Œ��_��ݒ�


}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, player.Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	player.vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	player.vertexWk[1].vtx = D3DXVECTOR3(100.0f+PLAYER_TEXTURE_SIZE_X, 100.0f, 0.0f);
	player.vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+PLAYER_TEXTURE_SIZE_Y, 0.0f);
	player.vertexWk[3].vtx = D3DXVECTOR3(100.0f+PLAYER_TEXTURE_SIZE_X, 100.0f+PLAYER_TEXTURE_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	player.vertexWk[0].rhw =
	player.vertexWk[1].rhw =
	player.vertexWk[2].rhw =
	player.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player.vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player.vertexWk[1].tex = D3DXVECTOR2( 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player.vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_Y );
	player.vertexWk[3].tex = D3DXVECTOR2( 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_X, 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_Y );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int cntPattern )
{

	float tw = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float ul = cntPattern * tw;
	float ur = (cntPattern + PLAYER_TEXTURE_PATTERN_DIVIDE_Y) *tw;

	player.vertexWk[0].tex = D3DXVECTOR2(ul, 0.0f);
	player.vertexWk[1].tex = D3DXVECTOR2(ur, 0.0f);
	player.vertexWk[2].tex = D3DXVECTOR2(ul, 1.0f);
	player.vertexWk[3].tex = D3DXVECTOR2(ur, 1.0f);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(void)
{
	// ���_���W�̐ݒ�
	D3DXVECTOR3 pos = player.pos + player.ofs;

	player.vertexWk[0].vtx.x = pos.x - PLAYER_TEXTURE_SIZE_X;
	player.vertexWk[0].vtx.y = pos.y - PLAYER_TEXTURE_SIZE_Y;
	player.vertexWk[0].vtx.z = 0.0f;

	player.vertexWk[1].vtx.x = pos.x + PLAYER_TEXTURE_SIZE_X;
	player.vertexWk[1].vtx.y = pos.y - PLAYER_TEXTURE_SIZE_Y;
	player.vertexWk[1].vtx.z = 0.0f;

	player.vertexWk[2].vtx.x = pos.x - PLAYER_TEXTURE_SIZE_X;
	player.vertexWk[2].vtx.y = pos.y + PLAYER_TEXTURE_SIZE_Y;
	player.vertexWk[2].vtx.z = 0.0f;

	player.vertexWk[3].vtx.x = pos.x + PLAYER_TEXTURE_SIZE_X;
	player.vertexWk[3].vtx.y = pos.y + PLAYER_TEXTURE_SIZE_Y;
	player.vertexWk[3].vtx.z = 0.0f;




}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(void)
{
	return(&player);
}



