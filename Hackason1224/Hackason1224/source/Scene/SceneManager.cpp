//=============================================================================
//
// �V�[���}�l�[�W��[SceneManager.h]
// Author : GP12B332 19 ���J���u
//
//=============================================================================
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "../Title/TitleLogo.h"
#include "../Result/ResultLogo.h"
#include "../Resource/ResourceManager.h"
#include "../../gauge.h"
#include "../player.h"
#include "../station.h"
#include "../yajirushi.h"
#include "../Game/BackGround.h"
#include "../Game/Flag.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneManager::SceneManager()
{
	// �X�e�[�g�}�V���̍쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Title] = new SceneTitle();
	fsm[State::Game] = new SceneGame();
	fsm[State::Result] = new SceneResult();
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneManager::~SceneManager()
{
	// �X�e�[�g�}�V���̍폜
	for (auto&& p : fsm)
	{
		delete p;
		p = NULL;
	}
	fsm.clear();
}

void SceneManager::Init()
{
	// ���\�[�X�ǂݍ���
	LoadResource();

	titleLogo = new TitleLogo();
	resultLogo = new ResultLogo();
	backGround = new BackGround();
	flag = new Flag();

	InitGauge(0);
	//�v���C���[�̏�����
	InitPlayer(0);

	//���̏�����
	InitYajirushi(0);

	//�w�̏�����
	InitStation(0);

	// �����V�[����ݒ�
	ChangeState(State::Title);
}

void SceneManager::Uninit()
{
	SAFE_DELETE(titleLogo);
	SAFE_DELETE(resultLogo);
	SAFE_DELETE(backGround);
	SAFE_DELETE(flag);

	UninitGauge();
	//�v���C���[�̏I������
	UninitPlayer();

	//���̏I������
	UninitYajirushi();

	//�w�̏I������
	UninitStation();

}

void SceneManager::Update()
{
	// �X�e�[�g�}�V���̍X�V
	State next = fsm[currentState]->OnUpdate(*this);
}

void SceneManager::Draw()
{
	// �X�e�[�g�}�V���̕`��
	fsm[currentState]->OnDraw(*this);
}

void SceneManager::ChangeState(State next)
{
	prevState = currentState;

	currentState = next;

	if (fsm[currentState] != NULL)
	{
		fsm[currentState]->OnStart(*this);
	}
}

void SceneManager::LoadResource()
{
	ResourceManager::Instance()->LoadTexture("TitleLogo", "data/Texture/Title.png");
	ResourceManager::Instance()->LoadTexture("ResultLogo", "data/Texture/Result.png");
	ResourceManager::Instance()->LoadTexture("BackGround", "data/Texture/BackGround.png");
	ResourceManager::Instance()->LoadTexture("Flag", "data/Texture/Flag.png");
}
