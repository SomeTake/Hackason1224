//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 高橋翔輝
//
//=============================================================================
#include "../Main.h"
#include "player.h"
#include "input.h"
#include "yajirushi.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern );
void SetVertexPlayer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// テクスチャへのポリゴン

static PLAYER					player;			// プレイヤー構造体

//static LPDIRECTSOUNDBUFFER8		g_pSE;							// SE用バッファ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャの読み込み
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			PLAYER_TEXTURE,					// ファイルの名前
			&g_pD3DTexturePlayer);			// 読み込むメモリのポインタ
	}

		player.pos = D3DXVECTOR3(220.0f, 700.0f, 0.0f);	// 座標データを初期化
		player.move = D3DXVECTOR3(5.0f, 5.0f, 0.0f);	// 座標データを初期化
		player.PatternAnim = 1;		// アニメパターン番号をランダムで初期化
		player.CountAnim = 0;										// アニメカウントを初期化
		player.Texture = g_pD3DTexturePlayer;
		player.key = 0;

		player.cnt = 0;//カウント
		player.b_type = 0;//カウント
		player.muteki_cnt = 0;

		player.ofs = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// オフセット座標を初期化

		MakeVertexPlayer();											// 頂点情報の作成

							//テクスチャ座標を設定
		SetTexturePlayer( player.PatternAnim);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{	// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{

	player.anim = false;

	player.key = 0;

	if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S)/*|| IsButtonPressed(0, BUTTON_DOWN)*/)
	{
		player.key = 2;
		player.anim = true;

		player.cnt = 0;

		//player.CountAnim++;
	}
	else if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W) /*|| IsButtonPressed(0, BUTTON_UP)*/)
	{
		player.key = 1;
		player.anim = true;

		player.cnt = 0;

		//player.CountAnim++;
	}
	//key = player.key;

	//SetYajirushi(pos, key);


	//アニメーション
	if (player.anim==true)
	{

		if ((player.CountAnim % PLAYER_TIME_ANIMATION) == 0)
		{
			//パターンの切り替え
			player.PatternAnim = (player.PatternAnim + 1) % PLAYER_ANIM_PATTERN_NUM;

			//テクスチャ座標を設定
			SetTexturePlayer(player.PatternAnim);
		}
	}

	// 矢印設定
	//if (GetKeyboardTrigger(DIK_P))
	//{
	//}


	SetVertexPlayer();	// 移動後の座標で頂点を設定


}


//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, player.Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	player.vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	player.vertexWk[1].vtx = D3DXVECTOR3(100.0f+PLAYER_TEXTURE_SIZE_X, 100.0f, 0.0f);
	player.vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+PLAYER_TEXTURE_SIZE_Y, 0.0f);
	player.vertexWk[3].vtx = D3DXVECTOR3(100.0f+PLAYER_TEXTURE_SIZE_X, 100.0f+PLAYER_TEXTURE_SIZE_Y, 0.0f);

	// rhwの設定
	player.vertexWk[0].rhw =
	player.vertexWk[1].rhw =
	player.vertexWk[2].rhw =
	player.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	player.vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player.vertexWk[1].tex = D3DXVECTOR2( 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player.vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_Y );
	player.vertexWk[3].tex = D3DXVECTOR2( 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_X, 1.0f/PLAYER_TEXTURE_PATTERN_DIVIDE_Y );

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer( int cntPattern )
{

	float tw = 1.0f / PLAYER_TEXTURE_PATTERN_DIVIDE_X;
	float ul = cntPattern * tw;
	float ur = (cntPattern + PLAYER_TEXTURE_PATTERN_DIVIDE_Y) *tw;

	//if (player.direction == 0)
	//{
	//	player.vertexWk[0].tex = D3DXVECTOR2(ul, 0.0f);
	//	player.vertexWk[1].tex = D3DXVECTOR2(ur, 0.0f);
	//	player.vertexWk[2].tex = D3DXVECTOR2(ul, 0.25f);
	//	player.vertexWk[3].tex = D3DXVECTOR2(ur, 0.25f);
	//}

	//
	//if (player.direction == 1)
	//{
	//	player.vertexWk[0].tex = D3DXVECTOR2(ul, 0.5f);
	//	player.vertexWk[1].tex = D3DXVECTOR2(ur, 0.5f);
	//	player.vertexWk[2].tex = D3DXVECTOR2(ul, 0.75f);
	//	player.vertexWk[3].tex = D3DXVECTOR2(ur, 0.75f);
	//}
	//else if (player.direction == 2)
	//{
	//	player.vertexWk[0].tex = D3DXVECTOR2(ul, 0.25f);
	//	player.vertexWk[1].tex = D3DXVECTOR2(ur, 0.25f);
	//	player.vertexWk[2].tex = D3DXVECTOR2(ul, 0.5f);
	//	player.vertexWk[3].tex = D3DXVECTOR2(ur, 0.5f);
	//}

	//if (player.direction == 3)
	//{
	//	player.vertexWk[0].tex = D3DXVECTOR2(ul, 0.75f);
	//	player.vertexWk[1].tex = D3DXVECTOR2(ur, 0.75f);
	//	player.vertexWk[2].tex = D3DXVECTOR2(ul, 1.0f);
	//	player.vertexWk[3].tex = D3DXVECTOR2(ur, 1.0f);
	//}

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(void)
{
	// 頂点座標の設定
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
// プレイヤー取得関数
//=============================================================================
PLAYER *GetPlayer(void)
{
	return(&player);
}



