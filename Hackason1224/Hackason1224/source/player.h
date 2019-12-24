//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 高橋翔輝
//
//=============================================================================
#pragma once


// マクロ定義
#define PLAYER_TEXTURE					_T("data/TEXTURE/chara01.png")	// 画像
#define PLAYER_TEXTURE_SIZE_X			(40/2)		// テクスチャサイズ
#define PLAYER_TEXTURE_SIZE_Y			(40/2)		// 同上

#define PLAYER_TEXTURE_PATTERN_DIVIDE_X	(3)			// アニメパターンのテクスチャ内分割数（X)
#define PLAYER_TEXTURE_PATTERN_DIVIDE_Y	(1)			// アニメパターンのテクスチャ内分割数（Y)
#define PLAYER_ANIM_PATTERN_NUM			(PLAYER_TEXTURE_PATTERN_DIVIDE_X*PLAYER_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define PLAYER_TIME_ANIMATION			(4)			// アニメーションの切り替わるカウント

#define PLAYER_MAX						(1)			// プレイヤーの最大数

#define	PLAYER_JUMP_Y					(-80.0f)	// ジャンプの高さ
#define	PLAYER_JUMP_CNT_MAX				(30)		// 30フレームのジャンプ処理

#define	PLAYER_X_MAX                    (450)
#define	PLAYER_X_MINIMUM                (130)
#define	PLAYER_Y_MAX                    (340)
#define	PLAYER_Y_MINIMUM                (100)
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
	bool            key;                        //true;上↑ false;下↓

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	
	bool			jump;						// ジャンプ中フラグ
	float			jump_y;						// ジャンプの高さ
	int				jump_cnt_max;
	int				jump_cnt;
	int				cnt;					// カウント
	int				b_type;					// バレットタイプ
	int				muteki_cnt;				// 無敵時間
	D3DXVECTOR3		ofs;						// posに対するオフセット座標

	bool			hit;						// 当たり判定

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


