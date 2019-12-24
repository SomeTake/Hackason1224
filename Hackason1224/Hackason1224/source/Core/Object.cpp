#include "Object.h"
#include "../Resource/ResourceManager.h"

#define POLYGON2D_DEFAULT_SIZE		(20.0f)

Object::Object() :
	D3DTexture(NULL)
{
	vtxPos[0] = D3DXVECTOR3(-POLYGON2D_DEFAULT_SIZE, -POLYGON2D_DEFAULT_SIZE, 0.0f);
	vtxPos[1] = D3DXVECTOR3(POLYGON2D_DEFAULT_SIZE, -POLYGON2D_DEFAULT_SIZE, 0.0f);
	vtxPos[2] = D3DXVECTOR3(-POLYGON2D_DEFAULT_SIZE, POLYGON2D_DEFAULT_SIZE, 0.0f);
	vtxPos[3] = D3DXVECTOR3(POLYGON2D_DEFAULT_SIZE, POLYGON2D_DEFAULT_SIZE, 0.0f);

	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	pDevice = GetDevice();

}

Object::~Object()
{
	SAFE_RELEASE(D3DTexture);
}

void Object::Draw()
{
	pDevice->SetTexture(0, D3DTexture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	SetVertex();

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));

}

void Object::SetVertex()
{
	vertexWk[0].vtx = vtxPos[0];
	vertexWk[1].vtx = vtxPos[1];
	vertexWk[2].vtx = vtxPos[2];
	vertexWk[3].vtx = vtxPos[3];
}

void Object::SetSize(float x, float y)
{
	size = D3DXVECTOR2(x / 2.0f, y / 2.0f);
}

void Object::SetColor(D3DXCOLOR color)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = color;
}

void Object::SetUV(float left, float top, float width, float height)
{
	vertexWk[0].tex = D3DXVECTOR2(left, top);
	vertexWk[1].tex = D3DXVECTOR2(left + width, top);
	vertexWk[2].tex = D3DXVECTOR2(left, top + height);
	vertexWk[3].tex = D3DXVECTOR2(left + width, top + height);
}

void Object::LoadTexture(const char * tag)
{
	SAFE_RELEASE(D3DTexture);

	ResourceManager::Instance()->GetTexture(tag, &D3DTexture);
}

void Object::SetPosition(D3DXVECTOR3 pos)
{
	vtxPos[0] = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	vtxPos[1] = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	vtxPos[2] = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	vtxPos[3] = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
}
