//=============================================================================
//
// �o���b�g���� [station.cpp]
// Author : 
//
//=============================================================================
#include "../main.h"
#include "station.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexStation(void);
void SetVertexStation(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureStation = NULL;		// �e�N�X�`���ւ̃|���S��

static STATION					station;			// �o���b�g�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStation(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			STATION_TEXTURE,						// �t�@�C���̖��O
			&g_pD3DTextureStation);							// �ǂݍ��ރ������̃|�C���^
	}


	// �o���b�g�̏���������
	station.pos = D3DXVECTOR3(300.0f, 900.0f, 0.0f);		// ���W�f�[�^��������
	station.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
	station.move= D3DXVECTOR3(10.0f, 0.0f, 0.0f);	// �ړ��ʂ�������
	station.Texture = g_pD3DTextureStation;

	D3DXVECTOR2 temp = D3DXVECTOR2(STATION_TEXTURE_SIZE_X, STATION_TEXTURE_SIZE_Y);
	station.Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
	station.BaseAngle = atan2f(STATION_TEXTURE_SIZE_Y, STATION_TEXTURE_SIZE_X);	// �G�l�~�[�̊p�x��������

	MakeVertexStation();									// ���_���̍쐬


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStation(void)
{
	if (g_pD3DTextureStation != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureStation->Release();
		g_pD3DTextureStation = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStation(void)
{
	float distance;
	float destination;
	int cnt=0;
	bool use=true;
	//�Q�[�W*�ړ���=�ړI�n
	destination =1.0f*station.move.x*150;
	//if (cnt % 120 == 0)
	//{
		// �w�̈ړ�����
		if (station.pos.x >= destination)
		{
			use = false;
		}
		if (use==true)
		{

			station.pos += station.move;
			cnt = 0;
		}
	//}
	//cnt++;
			
	SetVertexStation();				// �ړ���̍��W�Œ��_��ݒ�
		

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStation(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, station.Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, station.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexStation(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexStation();

	// rhw�̐ݒ�
	station.vertexWk[0].rhw =
	station.vertexWk[1].rhw =
	station.vertexWk[2].rhw =
	station.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	station.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	station.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	station.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	station.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	station.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	station.vertexWk[1].tex = D3DXVECTOR2(1.0f / STATION_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	station.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / STATION_TEXTURE_PATTERN_DIVIDE_Y);
	station.vertexWk[3].tex = D3DXVECTOR2( 1.0f/ STATION_TEXTURE_PATTERN_DIVIDE_X, 1.0f/STATION_TEXTURE_PATTERN_DIVIDE_Y);

	//station.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//station.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//station.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//station.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexStation(void)
{

	// ���_���W�̐ݒ�
	station.vertexWk[0].vtx.x = station.pos.x - cosf(station.BaseAngle + station.rot.z) * station.Radius;
	station.vertexWk[0].vtx.y = station.pos.y - sinf(station.BaseAngle + station.rot.z) * station.Radius;
	station.vertexWk[0].vtx.z = 0.0f;

	station.vertexWk[1].vtx.x = station.pos.x + cosf(station.BaseAngle - station.rot.z) * station.Radius;
	station.vertexWk[1].vtx.y = station.pos.y - sinf(station.BaseAngle - station.rot.z) * station.Radius;
	station.vertexWk[1].vtx.z = 0.0f;

	station.vertexWk[2].vtx.x = station.pos.x - cosf(station.BaseAngle - station.rot.z) * station.Radius;
	station.vertexWk[2].vtx.y = station.pos.y + sinf(station.BaseAngle - station.rot.z) * station.Radius;
	station.vertexWk[2].vtx.z = 0.0f;

	station.vertexWk[3].vtx.x = station.pos.x + cosf(station.BaseAngle + station.rot.z) * station.Radius;
	station.vertexWk[3].vtx.y = station.pos.y + sinf(station.BaseAngle + station.rot.z) * station.Radius;
	station.vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetStation(D3DXVECTOR3 pos)
{
	station.pos = pos;			// ���W���Z�b�g


	station.move = D3DXVECTOR3(STATION_SPEED, -STATION_SPEED, 0.0f);	// �ړ��ʂ�������
	station.rot.z = D3DX_PI / 4;									// �E�΂߂S�T�x����
			
	return;							// 1���Z�b�g�����̂ŏI������
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
STATION *GetStation(void)
{
	return(&station);
}
