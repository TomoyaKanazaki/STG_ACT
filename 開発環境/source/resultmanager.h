//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  �^�C�g���}�l�[�W���N���X��`
//==========================================
class CResultManager : public CScene
{
public:
	CResultManager(); //�R���X�g���N�^
	~CResultManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	int m_nCntScene;
	int m_nRank;

};

#endif
