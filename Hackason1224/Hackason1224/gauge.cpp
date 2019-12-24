//=============================================================================
//
// ���� [HP.cpp]
//
//=============================================================================
#include "../../main.h"
#include "gauge.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGauge(int no);
void SetTextureGauge(int no, int cntPattern);
void SetVertexGauge(int no);

HRESULT MakeVertexWaku(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureGauge = NULL;		// �e�N�X�`���ւ̃|���S��
static GAUGE					hp_meterWk[GAUGE_MAX];				// �\����

static LPDIRECT3DTEXTURE9		g_pD3DTextureWaku = NULL;			// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D				g_vertexWkWaku[NUM_VERTEX];		// ���_���i�[���[�N

static float g_Gauge;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitGauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAUGE,						// �t�@�C���̖��O
			&g_pD3DTextureGauge);				// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
			TEXTURE_WAKU,						// �t�@�C���̖��O
			&g_pD3DTextureWaku);				// �ǂݍ��ރ������[
	}


	for (int i = 0; i < GAUGE_MAX; i++)
	{
		hp_meterWk[i].use = true;										// �g�p
		hp_meterWk[i].pos = D3DXVECTOR3(WAKU_POS_X + WAKU_SIZE_X, WAKU_POS_Y, 0.0f);	// ���W�f�[�^��������
		hp_meterWk[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		hp_meterWk[i].CountAnim = 0;									// �A�j���J�E���g��������
		hp_meterWk[i].Texture = g_pD3DTextureGauge;

		g_Gauge = 0.0f;

		MakeVertexGauge(i);											// ���_���̍쐬
	}

	MakeVertexWaku();

	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void UninitGauge(void)
{
	if (g_pD3DTextureGauge != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureGauge->Release();
		g_pD3DTextureGauge = NULL;
	}

	if (g_pD3DTextureWaku != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureWaku->Release();
		g_pD3DTextureWaku = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGauge(void)
{
	for (int i = 0; i < GAUGE_MAX; i++)
	{
		if (hp_meterWk[i].use == true)					// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			hp_meterWk[i].CountAnim++;
			if ((hp_meterWk[i].CountAnim % GAUGE_TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				hp_meterWk[i].PatternAnim = (hp_meterWk[i].PatternAnim + 1) % GAUGE_ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTextureGauge(i, hp_meterWk[i].PatternAnim);
			}

			g_Gauge += 10;
			if (g_Gauge == 100)
			{
				g_Gauge = g_Gauge - 10;
			}
			else if (g_Gauge == 0)
			{
				g_Gauge = g_Gauge + 10;
			}

			//if (g_Gauge > GAUGE_MAX)
			//{
			//	g_Gauge = 100;
			//}

			//if (g_Gauge == 0)
			//{

			//}


			SetVertexGauge(i);						// �ړ���̍��W�Œ��_��ݒ�
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < GAUGE_MAX; i++)
	{
		if (hp_meterWk[i].use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, hp_meterWk[i].Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, hp_meterWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureWaku);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_pD3DTextureWaku, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexGauge(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexGauge(i);

	// rhw�̐ݒ�
	hp_meterWk[i].vertexWk[0].rhw =
	hp_meterWk[i].vertexWk[1].rhw =
	hp_meterWk[i].vertexWk[2].rhw =
	hp_meterWk[i].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	hp_meterWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hp_meterWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hp_meterWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hp_meterWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	hp_meterWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	hp_meterWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	hp_meterWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	hp_meterWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexWaku(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkWaku[0].vtx = D3DXVECTOR3(WAKU_POS_X, WAKU_POS_Y, 0.0f);
	g_vertexWkWaku[1].vtx = D3DXVECTOR3(WAKU_POS_X + WAKU_SIZE_X, WAKU_POS_Y, 0.0f);
	g_vertexWkWaku[2].vtx = D3DXVECTOR3(WAKU_POS_X, WAKU_POS_Y + WAKU_SIZE_Y, 0.0f);
	g_vertexWkWaku[3].vtx = D3DXVECTOR3(WAKU_POS_X + WAKU_SIZE_X, WAKU_POS_Y + WAKU_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkWaku[0].rhw =
	g_vertexWkWaku[1].rhw =
	g_vertexWkWaku[2].rhw =
	g_vertexWkWaku[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkWaku[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkWaku[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkWaku[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkWaku[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkWaku[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkWaku[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkWaku[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkWaku[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;

}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureGauge(int i, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % GAUGE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / GAUGE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / GAUGE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / GAUGE_TEXTURE_PATTERN_DIVIDE_Y;

	hp_meterWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	hp_meterWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	hp_meterWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	hp_meterWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexGauge(int i)
{
	// ���_���W�̐ݒ�
	hp_meterWk[i].vertexWk[0].vtx.x = hp_meterWk[i].pos.x - (g_Gauge / GAUGE_MAX) * GAUGE_TEXTURE_SIZE_X;
	hp_meterWk[i].vertexWk[0].vtx.y = hp_meterWk[i].pos.y;
	hp_meterWk[i].vertexWk[0].vtx.z = 0.0f;

	hp_meterWk[i].vertexWk[1].vtx.x = hp_meterWk[i].pos.x;
	hp_meterWk[i].vertexWk[1].vtx.y = hp_meterWk[i].pos.y;
	hp_meterWk[i].vertexWk[1].vtx.z = 0.0f;

	hp_meterWk[i].vertexWk[2].vtx.x = hp_meterWk[i].pos.x - (g_Gauge / GAUGE_MAX) * GAUGE_TEXTURE_SIZE_X;
	hp_meterWk[i].vertexWk[2].vtx.y = hp_meterWk[i].pos.y + GAUGE_TEXTURE_SIZE_Y;
	hp_meterWk[i].vertexWk[2].vtx.z = 0.0f;

	hp_meterWk[i].vertexWk[3].vtx.x = hp_meterWk[i].pos.x;
	hp_meterWk[i].vertexWk[3].vtx.y = hp_meterWk[i].pos.y + GAUGE_TEXTURE_SIZE_Y;
	hp_meterWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �擾�֐�
//=============================================================================
GAUGE *Get(void)
{
	return(&hp_meterWk[0]);
}

//=============================================================================
// �擾�֐�
//=============================================================================
float GetGauge(void)
{
	return g_Gauge;
}
