//==========================================
//
//  UI�N���X(ui.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
#include "enemy_manager.h"
#include "gamemanager.h"

//==========================================
//  �N���X��`
//==========================================
class CUi
{
public:
	CUi(); //�R���X�g���N�^
	~CUi(); //�f�X�g���N�^

	//�����o�֐�
	void Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CUi *Create(HWND hWnd);

private:

	//�G�l�~�[�}�l�[�W���̊Ǘ��p
	struct EnemyData
	{
		CEnemyManager::CreateData CreateData;
		bool bUse;
	};

	//�����o�֐�
	void Save(void);
	void Load(void);
	void ReLoad(void);

	//�����o�ϐ�
	HWND m_hWnd; //�E�B���h�E�n���h��
	EnemyData m_EnemyData[256]; //�������
	int m_nID; //�������̃C���f�b�N�X
	char m_aPass[256]; //���O�ɓǂݍ��܂ꂽ�p�X

	//�ÓI�����o�ϐ�
	static char m_sPass[256];

};

#endif
