#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../../Main.h"

class Object
{
private:
	// メンバ変数
	LPDIRECT3DTEXTURE9	D3DTexture;					// テクスチャのポインタ
	VERTEX_2D			vertexWk[NUM_VERTEX];		// 頂点情報格納構造体
	D3DXVECTOR3			vtxPos[NUM_VERTEX];			// 座標
	D3DXVECTOR2			size;						// サイズ
	int					PatternAnim;				// アニメーションパターン
	bool				use;						// 使用フラグ
	LPDIRECT3DDEVICE9 pDevice;

	void SetVertex();

public:
	// メンバ関数
	Object();
	virtual ~Object();

	void Draw();						// 描画

	void SetSize(float x, float y);
	void SetColor(D3DXCOLOR color);
	void SetUV(float left, float top, float width, float height);

	void LoadTexture(const char* tag);
	void SetPosition(D3DXVECTOR3 pos);
};

#endif
