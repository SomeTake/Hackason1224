//=============================================================================
//
// バレット処理 [station.h]
// Author : 
//
//=============================================================================
#pragma once


// マクロ定義
#define STATION_TEXTURE			_T("data/TEXTURE/station.png")	// 画像
#define STATION_TEXTURE_SIZE_X	(150)		// テクスチャサイズ
#define STATION_TEXTURE_SIZE_Y	(100)		// 同上

#define STATION_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define STATION_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)


#define STATION_SPEED			(4.0f)		// バレットの移動スピード


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量

	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// 半径
	float			BaseAngle;					// 角度

} STATION;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStation(int type);
void UninitStation(void);
void UpdateStation(void);
void DrawStation(void);
void SetStation(D3DXVECTOR3 pos);
STATION *GetStation(void);


