//=============================================================================
//
// 処理 [gauge.h]
// Author : Takeaki Sakamaki
//
//=============================================================================
#pragma once

// マクロ定義

/*　メーター　*/
#define TEXTURE_GAUGE			_T("data/TEXTURE/gauge.png")			// サンプル用画像

#define GAUGE_TEXTURE_SIZE_X	(1000)									// テクスチャサイズ
#define GAUGE_TEXTURE_SIZE_Y	(100)									// 同上

#define GAUGE_POS_X		(30)
#define GAUGE_POS_Y		(30)

#define GAUGE_TEXTURE_PATTERN_DIVIDE_X	(1)								// アニメパターンのテクスチャ内分割数（X)
#define GAUGE_TEXTURE_PATTERN_DIVIDE_Y	(1)								// アニメパターンのテクスチャ内分割数（Y)
#define GAUGE_ANIM_PATTERN_NUM			(GAUGE_TEXTURE_PATTERN_DIVIDE_X*GAUGE_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define GAUGE_TIME_ANIMATION			(1)								// アニメーションの切り替わるカウント

#define GAUGE_MAX						(1)								// 最大個数

#define GAUGE_METER_MAX	(100)											// ゲージ最大数


#define LOOP_COUNT		(60)

/*　枠　*/
#define TEXTURE_WAKU			_T("data/TEXTURE/waku.png")				// サンプル用画像

#define WAKU_TEXTURE_SIZE_X	(1000)										// テクスチャサイズ
#define WAKU_TEXTURE_SIZE_Y	(100)										// 同上
		
#define WAKU_POS_X		(30)
#define WAKU_POS_Y		(30)


typedef struct	// 構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	int	count;

	bool	Isfinished;
	bool	reverse;
} GAUGE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGauge(int type);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);

float GetGauge(void);
float GetPower(void);
