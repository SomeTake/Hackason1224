//=============================================================================
//
// �V�[���}�l�[�W��[SceneManager.h]
// Author : GP12B332 19 ���J���u
//
//=============================================================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <vector>
#include "../../Main.h"

//****************************************************
// �C���X�^���X�쐬�p�N���X�̑O���錾
//****************************************************
class TitleLogo;
class ResultLogo;
class BackGround;
class Flag;
//****************************************************
// �N���X��`
//****************************************************
class SceneManager
{
public:
	// ���
	enum State {
		Title,
		Game,
		Result,
		Max
	};

	SceneManager();
	~SceneManager();

	// �e�폈��
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// ��ԑJ�ڏ���
	void ChangeState(State next);

	// ���\�[�X�̓ǂݍ���
	void LoadResource();

private:
	// �����N���X�̑O���錾
	class SceneTitle;
	class SceneGame;
	class SceneResult;

	State currentState, prevState;		// ���݁A�ȑO�̏��
	using SceneState = BaseState<SceneManager, State>;
	std::vector<SceneState*> fsm;		// �X�e�[�g�}�V��

	// �e��C���X�^���X
	TitleLogo* titleLogo;
	ResultLogo* resultLogo;
	BackGround* backGround;
	Flag* flag;
};
#endif
