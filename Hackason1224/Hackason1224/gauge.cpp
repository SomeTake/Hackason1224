//=============================================================================
//
// 処理 [HP.cpp]
//
//=============================================================================
#include "../../main.h"
#include "gauge.h"
#include "source/input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGauge(int no);
void SetTextureGauge(int no, int cntPattern);
void SetVertexGauge(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureGauge = NULL;		// テクスチャへのポリゴン
static GAUGE					g_GaugeWk[GAUGE_MAX];				// 構造体

static float g_Gauge;
static float g_Power;			// 0.0～1.0の値
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAUGE,						// ファイルの名前
			&g_pD3DTextureGauge);				// 読み込むメモリのポインタ
	}


	for (int i = 0; i < GAUGE_MAX; i++)
	{
		g_GaugeWk[i].use = true;										// 使用
		g_GaugeWk[i].pos = D3DXVECTOR3(GAUGE_POS_X , GAUGE_POS_Y, 0.0f);	// 座標データを初期化
		g_GaugeWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		g_GaugeWk[i].CountAnim = 0;									// アニメカウントを初期化
		g_GaugeWk[i].Texture = g_pD3DTextureGauge;

		g_GaugeWk[i].count = 0;
		g_GaugeWk[i].Isfinished = false;


		g_Gauge = 0.0f;

		MakeVertexGauge(i);											// 頂点情報の作成
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGauge(void)
{
	if (g_pD3DTextureGauge != NULL)
	{	// テクスチャの開放
		g_pD3DTextureGauge->Release();
		g_pD3DTextureGauge = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGauge(void)
{
	for (int i = 0; i < GAUGE_MAX; i++)
	{
		if (g_GaugeWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			g_GaugeWk[i].CountAnim++;
			if ((g_GaugeWk[i].CountAnim % GAUGE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				g_GaugeWk[i].PatternAnim = (g_GaugeWk[i].PatternAnim + 1) % GAUGE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
				SetTextureGauge(i, g_GaugeWk[i].PatternAnim);
			}

			if (g_GaugeWk[i].Isfinished == false)
			{
				g_GaugeWk[i].count++;
				if (g_GaugeWk[i].count == LOOP_COUNT)
				{
					g_GaugeWk[i].count = 0;
				}

				if (g_GaugeWk[i].count < 30)
				{
					g_Gauge += 100 / 30;
				}
				else
				{
					g_Gauge -= 100 / 30;
				}
			}

			if (GetKeyboardTrigger(DIK_RETURN))
			{
				g_GaugeWk[i].Isfinished = true;

				g_Power = g_Gauge / GAUGE_METER_MAX;
			}

			SetVertexGauge(i);						// 移動後の座標で頂点を設定
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < GAUGE_MAX; i++)
	{
		if (g_GaugeWk[i].use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_GaugeWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_GaugeWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexGauge(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexGauge(i);

	// rhwの設定
	g_GaugeWk[i].vertexWk[0].rhw =
	g_GaugeWk[i].vertexWk[1].rhw =
	g_GaugeWk[i].vertexWk[2].rhw =
	g_GaugeWk[i].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_GaugeWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_GaugeWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_GaugeWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_GaugeWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_GaugeWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_GaugeWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_GaugeWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_GaugeWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureGauge(int i, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % GAUGE_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / GAUGE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / GAUGE_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / GAUGE_TEXTURE_PATTERN_DIVIDE_Y;

	g_GaugeWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_GaugeWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_GaugeWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_GaugeWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexGauge(int i)
{
	// 頂点座標の設定
	g_GaugeWk[i].vertexWk[0].vtx.x = g_GaugeWk[i].pos.x;
	g_GaugeWk[i].vertexWk[0].vtx.y = g_GaugeWk[i].pos.y;
	g_GaugeWk[i].vertexWk[0].vtx.z = 0.0f;

	g_GaugeWk[i].vertexWk[1].vtx.x = g_GaugeWk[i].pos.x + (g_Gauge / GAUGE_METER_MAX) * GAUGE_TEXTURE_SIZE_X;
	g_GaugeWk[i].vertexWk[1].vtx.y = g_GaugeWk[i].pos.y;
	g_GaugeWk[i].vertexWk[1].vtx.z = 0.0f;

	g_GaugeWk[i].vertexWk[2].vtx.x = g_GaugeWk[i].pos.x;
	g_GaugeWk[i].vertexWk[2].vtx.y = g_GaugeWk[i].pos.y + GAUGE_TEXTURE_SIZE_Y;
	g_GaugeWk[i].vertexWk[2].vtx.z = 0.0f;

	g_GaugeWk[i].vertexWk[3].vtx.x = g_GaugeWk[i].pos.x + (g_Gauge / GAUGE_METER_MAX) * GAUGE_TEXTURE_SIZE_X;;
	g_GaugeWk[i].vertexWk[3].vtx.y = g_GaugeWk[i].pos.y + GAUGE_TEXTURE_SIZE_Y;
	g_GaugeWk[i].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// 取得関数
//=============================================================================
GAUGE *Get(void)
{
	return(&g_GaugeWk[0]);
}

//=============================================================================
// 取得関数
//=============================================================================
float GetGauge(void)
{
	return g_Gauge;
}

//=============================================================================
// 取得関数
//=============================================================================
float GetPower(void)
{
	return g_Power;
}
