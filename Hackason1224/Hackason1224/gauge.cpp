//=============================================================================
//
// 処理 [HP.cpp]
//
//=============================================================================
#include "../../main.h"
#include "gauge.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGauge(int no);
void SetTextureGauge(int no, int cntPattern);
void SetVertexGauge(int no);

HRESULT MakeVertexWaku(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureGauge = NULL;		// テクスチャへのポリゴン
static GAUGE					hp_meterWk[GAUGE_MAX];				// 構造体

static LPDIRECT3DTEXTURE9		g_pD3DTextureWaku = NULL;			// テクスチャへのポインタ
static VERTEX_2D				g_vertexWkWaku[NUM_VERTEX];		// 頂点情報格納ワーク

static float g_Gauge;
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

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_WAKU,						// ファイルの名前
			&g_pD3DTextureWaku);				// 読み込むメモリー
	}


	for (int i = 0; i < GAUGE_MAX; i++)
	{
		hp_meterWk[i].use = true;										// 使用
		hp_meterWk[i].pos = D3DXVECTOR3(WAKU_POS_X + WAKU_SIZE_X, WAKU_POS_Y, 0.0f);	// 座標データを初期化
		hp_meterWk[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		hp_meterWk[i].CountAnim = 0;									// アニメカウントを初期化
		hp_meterWk[i].Texture = g_pD3DTextureGauge;

		g_Gauge = 0.0f;

		MakeVertexGauge(i);											// 頂点情報の作成
	}

	MakeVertexWaku();

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

	if (g_pD3DTextureWaku != NULL)
	{	// テクスチャの開放
		g_pD3DTextureWaku->Release();
		g_pD3DTextureWaku = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGauge(void)
{
	for (int i = 0; i < GAUGE_MAX; i++)
	{
		if (hp_meterWk[i].use == true)					// 使用している状態なら更新する
		{
			// アニメーション
			hp_meterWk[i].CountAnim++;
			if ((hp_meterWk[i].CountAnim % GAUGE_TIME_ANIMATION) == 0)
			{
				// パターンの切り替え
				hp_meterWk[i].PatternAnim = (hp_meterWk[i].PatternAnim + 1) % GAUGE_ANIM_PATTERN_NUM;

				// テクスチャ座標を設定
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
		if (hp_meterWk[i].use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, hp_meterWk[i].Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, hp_meterWk[i].vertexWk, sizeof(VERTEX_2D));
		}
	}

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureWaku);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_pD3DTextureWaku, sizeof(VERTEX_2D));

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
	hp_meterWk[i].vertexWk[0].rhw =
	hp_meterWk[i].vertexWk[1].rhw =
	hp_meterWk[i].vertexWk[2].rhw =
	hp_meterWk[i].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	hp_meterWk[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hp_meterWk[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hp_meterWk[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hp_meterWk[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	hp_meterWk[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	hp_meterWk[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	hp_meterWk[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	hp_meterWk[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexWaku(void)
{
	// 頂点座標の設定
	g_vertexWkWaku[0].vtx = D3DXVECTOR3(WAKU_POS_X, WAKU_POS_Y, 0.0f);
	g_vertexWkWaku[1].vtx = D3DXVECTOR3(WAKU_POS_X + WAKU_SIZE_X, WAKU_POS_Y, 0.0f);
	g_vertexWkWaku[2].vtx = D3DXVECTOR3(WAKU_POS_X, WAKU_POS_Y + WAKU_SIZE_Y, 0.0f);
	g_vertexWkWaku[3].vtx = D3DXVECTOR3(WAKU_POS_X + WAKU_SIZE_X, WAKU_POS_Y + WAKU_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkWaku[0].rhw =
	g_vertexWkWaku[1].rhw =
	g_vertexWkWaku[2].rhw =
	g_vertexWkWaku[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkWaku[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkWaku[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkWaku[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkWaku[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkWaku[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkWaku[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkWaku[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkWaku[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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

	hp_meterWk[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	hp_meterWk[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	hp_meterWk[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	hp_meterWk[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexGauge(int i)
{
	// 頂点座標の設定
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
// 取得関数
//=============================================================================
GAUGE *Get(void)
{
	return(&hp_meterWk[0]);
}

//=============================================================================
// 取得関数
//=============================================================================
float GetGauge(void)
{
	return g_Gauge;
}
