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

	//�����o�ϐ�
	HWND m_hWnd;
	EnemyData m_EnemyData[256];

	//�ÓI�����o�ϐ�
	static char m_sPass[256];

};

#endif
