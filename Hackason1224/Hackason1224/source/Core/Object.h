#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../../Main.h"

class Object
{
private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^
	VERTEX_2D			vertexWk[NUM_VERTEX];		// ���_���i�[�\����
	D3DXVECTOR3			vtxPos[NUM_VERTEX];			// ���W
	D3DXVECTOR2			size;						// �T�C�Y
	int					PatternAnim;				// �A�j���[�V�����p�^�[��
	bool				use;						// �g�p�t���O
	LPDIRECT3DDEVICE9 pDevice;

	void SetVertex();

public:
	// �����o�֐�
	Object();
	virtual ~Object();

	void Draw();						// �`��

	void SetSize(float x, float y);
	void SetColor(D3DXCOLOR color);
	void SetUV(float left, float top, float width, float height);

	void LoadTexture(const char* tag);
	void SetPosition(D3DXVECTOR3 pos);
};

#endif
