//=============================================================================
//
// バレット処理 [station.cpp]
// Author : 
//
//=============================================================================
#include "../main.h"
#include "station.h"
#include "yajirushi.h"
#include "input.h"
#include "../gauge.h"
#include "GameConfig.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexStation(void);
void SetVertexStation(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureStation = NULL;		// テクスチャへのポリゴン

static STATION					station;			// バレット構造体

bool enter = false;
bool use = false;
float gravity = 0.0f;
D3DXVECTOR3 old;
static int cnt = 1;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStation(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャの読み込み
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			STATION_TEXTURE,						// ファイルの名前
			&g_pD3DTextureStation);							// 読み込むメモリのポインタ
	}

	enter = false;
	use = false;
	gravity = 0.0f;
	cnt = 1;

	// バレットの初期化処理
	station.pos = D3DXVECTOR3(300.0f, 900.0f, 0.0f);		// 座標データを初期化
	station.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
	station.move= D3DXVECTOR3(1800.0f, 0.0f, 0.0f);	// 移動量を初期化
	station.Texture = g_pD3DTextureStation;

	D3DXVECTOR2 temp = D3DXVECTOR2(STATION_TEXTURE_SIZE_X, STATION_TEXTURE_SIZE_Y);
	station.Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
	station.BaseAngle = atan2f(STATION_TEXTURE_SIZE_Y, STATION_TEXTURE_SIZE_X);	// エネミーの角度を初期化

	MakeVertexStation();									// 頂点情報の作成


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStation(void)
{
	if (g_pD3DTextureStation != NULL)
	{	// テクスチャの開放
		g_pD3DTextureStation->Release();
		g_pD3DTextureStation = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStation(void)
{
	YAJIRUSHI *yajirushi = GetYajirushi();

	old.x = station.pos.x;

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		enter = true;
		use = true;
	}
	static D3DXVECTOR3 destination = D3DXVECTOR3(0.0f,0.0f,0.0f);
	static float distance;

	if (enter == true)
	{
		//ゲージ*移動量=目的地
		distance = GetPower()*station.move.x;

		destination.x = distance * cosf(yajirushi->rot.z) / 30.0f;
		destination.y = distance * sinf(yajirushi->rot.z) / 30.0f;

		enter = false;
	}


	//if (station.pos.y <= STATION_TEXTURE_SIZE_Y / 2)
	//{// 着地した
	//	station.pos.y = station.STATION_TEXTURE_SIZE_Y / 2;      //地面の位置に移動
	//	station.move.y = station.move.y * -0.75f;//マイナスにマイナスをかけて上にいかせる
	//}


	if (cnt % 120 == 0)
	{
		use = false;
	}
	if (use==true)
	{
		gravity +=1.5f;
		station.pos.y += gravity;
		station.pos +=  destination;

		cnt++;
	}
	if (station.pos.y > GameConfig::Const::GoalPosition.y)
	{
		station.pos.y = GameConfig::Const::GoalPosition.y;
		station.pos.x = old.x;
	}

	
			
	SetVertexStation();				// 移動後の座標で頂点を設定
		

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStation(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, station.Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, station.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexStation(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexStation();

	// rhwの設定
	station.vertexWk[0].rhw =
	station.vertexWk[1].rhw =
	station.vertexWk[2].rhw =
	station.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	station.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	station.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	station.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	station.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
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
// 頂点座標の設定
//=============================================================================
void SetVertexStation(void)
{

	// 頂点座標の設定
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
// バレットの発射設定
//=============================================================================
void SetStation(D3DXVECTOR3 pos)
{
	station.pos = pos;			// 座標をセット


	station.move = D3DXVECTOR3(STATION_SPEED, -STATION_SPEED, 0.0f);	// 移動量を初期化
	station.rot.z = D3DX_PI / 4;									// 右斜め４５度向き
			
	return;							// 1発セットしたので終了する
}

//=============================================================================
// エネミー取得関数
//=============================================================================
STATION *GetStation(void)
{
	return(&station);
}

