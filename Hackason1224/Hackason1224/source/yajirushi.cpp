//=============================================================================
//
// バレット処理 [yajirushi.cpp]
// Author : 高橋翔輝
//
//=============================================================================
#include "../Main.h"
#include "yajirushi.h"
#include "player.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexYajirushi(void);
void SetVertexYajirushi(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureYajirushi = NULL;		// テクスチャへのポリゴン

static YAJIRUSHI					yajirushi;			// バレット構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitYajirushi(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	PLAYER *player = GetPlayer();


	// テクスチャの読み込み
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			YAJIRUSHI_TEXTURE,						// ファイルの名前
			&g_pD3DTextureYajirushi);							// 読み込むメモリのポインタ
	}


	// バレットの初期化処理
	yajirushi.use = true;								// 未使用（発射されていない弾）
	yajirushi.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 座標データを初期化
	yajirushi.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
	yajirushi.move = D3DXVECTOR3(YAJIRUSHI_SPEED, YAJIRUSHI_SPEED, 0.0f);	// 移動量を初期化
	yajirushi.Texture = g_pD3DTextureYajirushi;

	D3DXVECTOR2 temp = D3DXVECTOR2(YAJIRUSHI_TEXTURE_SIZE_X, YAJIRUSHI_TEXTURE_SIZE_Y);
	yajirushi.Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
	yajirushi.BaseAngle = atan2f(YAJIRUSHI_TEXTURE_SIZE_Y, YAJIRUSHI_TEXTURE_SIZE_X);	// エネミーの角度を初期化


	MakeVertexYajirushi();									// 頂点情報の作成


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitYajirushi(void)
{
	if (g_pD3DTextureYajirushi != NULL)
	{	// テクスチャの開放
		g_pD3DTextureYajirushi->Release();
		g_pD3DTextureYajirushi = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateYajirushi(void)
{
	PLAYER *player = GetPlayer();			// プレイヤーのポインターを初期化

	if (yajirushi.use == true)		// 使用している状態なら更新する
	{
		yajirushi.key = player->key;
		//上キー入力されたら
		if (yajirushi.key == 1)
		{
			yajirushi.rot.z -= 0.05f;
		}
		//下キー入力されたら
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

	// 画面外まで進んだ？
	if (player->anim == true)	// 自分の大きさを考慮して画面外か判定している
	{
		yajirushi.use = false;
	}
	SetVertexYajirushi();				// 移動後の座標で頂点を設定
			


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawYajirushi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (yajirushi.use == true)			// 使用している状態なら更新する
	{
		// テクスチャの設定
		pDevice->SetTexture(0, yajirushi.Texture);

		//SetTextureYajirushi(yajirushi.PatternAnim);


		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, yajirushi.vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexYajirushi()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexYajirushi();

	// rhwの設定
	yajirushi.vertexWk[0].rhw =
	yajirushi.vertexWk[1].rhw =
	yajirushi.vertexWk[2].rhw =
	yajirushi.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	yajirushi.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	yajirushi.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	yajirushi.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	yajirushi.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	yajirushi.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	yajirushi.vertexWk[1].tex = D3DXVECTOR2(1.0f / YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	yajirushi.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y);
	yajirushi.vertexWk[3].tex = D3DXVECTOR2( 1.0f/ YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X, 1.0f/YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y);


	return S_OK;
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexYajirushi(void)
{
	// 頂点座標の設定

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
// バレットの発射設定
//=============================================================================
void SetYajirushi(D3DXVECTOR3 pos,int key)
{

	PLAYER *player = GetPlayer();

	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )

	if (yajirushi.use == false)		// 未使用状態のバレットを見つける
	{
		yajirushi.use = true;			// 使用状態へ変更する
		yajirushi.pos = pos;			// 座標をセット
		yajirushi.key = key;           //true;上↑ false;下↓
		return;							// 1発セットしたので終了する
	}
}



//=============================================================================
// エネミー取得関数
//=============================================================================
YAJIRUSHI *GetYajirushi(void)
{
	return(&yajirushi);
}

