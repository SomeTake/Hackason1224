//=============================================================================
//
// �o���b�g���� [yajirushi.cpp]
// Author : �����ċP
//
//=============================================================================
#include "../Main.h"
#include "yajirushi.h"
#include "player.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexYajirushi(void);
void SetVertexYajirushi(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureYajirushi = NULL;		// �e�N�X�`���ւ̃|���S��

static YAJIRUSHI					yajirushi;			// �o���b�g�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitYajirushi(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	PLAYER *player = GetPlayer();


	// �e�N�X�`���̓ǂݍ���
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			YAJIRUSHI_TEXTURE,						// �t�@�C���̖��O
			&g_pD3DTextureYajirushi);							// �ǂݍ��ރ������̃|�C���^
	}


	// �o���b�g�̏���������
	yajirushi.use = true;								// ���g�p�i���˂���Ă��Ȃ��e�j
	yajirushi.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���W�f�[�^��������
	yajirushi.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
	yajirushi.move = D3DXVECTOR3(YAJIRUSHI_SPEED, YAJIRUSHI_SPEED, 0.0f);	// �ړ��ʂ�������
	yajirushi.Texture = g_pD3DTextureYajirushi;

	D3DXVECTOR2 temp = D3DXVECTOR2(YAJIRUSHI_TEXTURE_SIZE_X, YAJIRUSHI_TEXTURE_SIZE_Y);
	yajirushi.Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
	yajirushi.BaseAngle = atan2f(YAJIRUSHI_TEXTURE_SIZE_Y, YAJIRUSHI_TEXTURE_SIZE_X);	// �G�l�~�[�̊p�x��������


	MakeVertexYajirushi();									// ���_���̍쐬


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitYajirushi(void)
{
	if (g_pD3DTextureYajirushi != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureYajirushi->Release();
		g_pD3DTextureYajirushi = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateYajirushi(void)
{
	PLAYER *player = GetPlayer();			// �v���C���[�̃|�C���^�[��������

	if (yajirushi.use == true)		// �g�p���Ă����ԂȂ�X�V����
	{
		yajirushi.key = player->key;
		//��L�[���͂��ꂽ��
		if (yajirushi.key == 1)
		{
			yajirushi.rot.z -= 0.05f;
		}
		//���L�[���͂��ꂽ��
		else if (yajirushi.key == 2)
		{
			yajirushi.rot.z += 0.05f;
		}

		if (yajirushi.rot.z >= 0.0f)
		{
			yajirushi.rot.z = 0.0f;
		}

		//if (yajirushi.rot.z <= -1.5f)
		//{
		//	yajirushi.rot.z = -1.5f;
		//}

		if (yajirushi.rot.z <= -D3DX_PI/2)
		{
			yajirushi.rot.z = -D3DX_PI/2;
		}

		yajirushi.pos = player->pos;
		yajirushi.pos.x += PLAYER_TEXTURE_SIZE_X;
		yajirushi.pos.y += PLAYER_TEXTURE_SIZE_Y;
	}

	// ��ʊO�܂Ői�񂾁H
	if (player->anim == true)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
	{
		yajirushi.use = false;
	}
	SetVertexYajirushi();				// �ړ���̍��W�Œ��_��ݒ�
			


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawYajirushi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (yajirushi.use == true)			// �g�p���Ă����ԂȂ�X�V����
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, yajirushi.Texture);

		//SetTextureYajirushi(yajirushi.PatternAnim);


		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, yajirushi.vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexYajirushi()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexYajirushi();

	// rhw�̐ݒ�
	yajirushi.vertexWk[0].rhw =
	yajirushi.vertexWk[1].rhw =
	yajirushi.vertexWk[2].rhw =
	yajirushi.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	yajirushi.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	yajirushi.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	yajirushi.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	yajirushi.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	yajirushi.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	yajirushi.vertexWk[1].tex = D3DXVECTOR2(1.0f / YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	yajirushi.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y);
	yajirushi.vertexWk[3].tex = D3DXVECTOR2( 1.0f/ YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X, 1.0f/YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y);


	return S_OK;
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexYajirushi(void)
{
	// ���_���W�̐ݒ�

	yajirushi.vertexWk[0].vtx.x = yajirushi.pos.x - cosf(yajirushi.BaseAngle + yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[0].vtx.y = yajirushi.pos.y - sinf(yajirushi.BaseAngle + yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[0].vtx.z = 0.0f;

	yajirushi.vertexWk[1].vtx.x = yajirushi.pos.x + cosf(yajirushi.BaseAngle - yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[1].vtx.y = yajirushi.pos.y - sinf(yajirushi.BaseAngle - yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[1].vtx.z = 0.0f;

	yajirushi.vertexWk[2].vtx.x = yajirushi.pos.x - cosf(yajirushi.BaseAngle - yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[2].vtx.y = yajirushi.pos.y + sinf(yajirushi.BaseAngle - yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[2].vtx.z = 0.0f;

	yajirushi.vertexWk[3].vtx.x = yajirushi.pos.x + cosf(yajirushi.BaseAngle + yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[3].vtx.y = yajirushi.pos.y + sinf(yajirushi.BaseAngle + yajirushi.rot.z) * yajirushi.Radius;
	yajirushi.vertexWk[3].vtx.z = 0.0f;

}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetYajirushi(D3DXVECTOR3 pos,int key)
{

	PLAYER *player = GetPlayer();

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )

	if (yajirushi.use == false)		// ���g�p��Ԃ̃o���b�g��������
	{
		yajirushi.use = true;			// �g�p��Ԃ֕ύX����
		yajirushi.pos = pos;			// ���W���Z�b�g
		yajirushi.key = key;           //true;�な false;����
		return;							// 1���Z�b�g�����̂ŏI������
	}
}



//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
YAJIRUSHI *GetYajirushi(void)
{
	return(&yajirushi);
}

