//=============================================================================
//
// バレット処理 [yajirushi.h]
// Author : 高橋翔輝
//
//=============================================================================
#pragma once


// マクロ定義
#define YAJIRUSHI_TEXTURE			_T("data/TEXTURE/斬撃2.png")	// 画像
#define YAJIRUSHI_TEXTURE_SIZE_X	(60)		// テクスチャサイズ
#define YAJIRUSHI_TEXTURE_SIZE_Y	(60)		// 同上

#define YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define YAJIRUSHI_ANIM_PATTERN_NUM			(YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_X*YAJIRUSHI_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define YAJIRUSHI_TIME_ANIMATION			(4)	// アニメーションの切り替わるカウント

#define YAJIRUSHI_MAX						(300)	// バレットの最大数
#define YAJIRUSHI_DAMAGE					(10)	// バレットの最大数


#define YAJIRUSHI_SPEED			(14.0f)		// バレットの移動スピード


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// バレット構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		move;						// 移動量
	
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// 半径
	float			BaseAngle;					// 角度

} YAJIRUSHI;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitYajirushi(int type);
void UninitYajirushi(void);
void UpdateYajirushi(void);
void DrawYajirushi(void);
void SetYajirushi(D3DXVECTOR3 pos);
YAJIRUSHI *GetYajirushi(void);


