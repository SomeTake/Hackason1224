//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 高橋翔輝
//
//=============================================================================
#pragma once


// マクロ定義
#define PLAYER_TEXTURE					_T("data/TEXTURE/player.png")	// 画像
#define PLAYER_TEXTURE_SIZE_X			(500/2)		// テクスチャサイズ
#define PLAYER_TEXTURE_SIZE_Y			(500/2)		// 同上

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X	(5)			// アニメパターンのテクスチャ内分割数（X)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y	(1)			// アニメパターンのテクスチャ内分割数（Y)
#define PLAYER_ANIM_PATTERN_NUM			(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define PLAYER_TIME_ANIMATION			(4)			// アニメーションの切り替わるカウント

#define PLAYER_MAX						(1)			// プレイヤーの最大数
//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			anim;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの座標
	D3DXVECTOR3		move;						// ポリゴンの座標
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	int             key;                        //0;キー入力なし1;上↑ 2;下↓

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	
	int				cnt;						// カウント
	D3DXVECTOR3		ofs;						// posに対するオフセット座標

} PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void UpdatePlayerLineOver(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);


