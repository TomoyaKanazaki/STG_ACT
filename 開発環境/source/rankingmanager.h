//==========================================
//
//  �����L���O�}�l�[�W��(rankingmanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  �^�C�g���}�l�[�W���N���X��`
//==========================================
class CRankingManager : public CScene
{
public:
	CRankingManager(); //�R���X�g���N�^
	~CRankingManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�����o�ϐ�
	int m_nCntScene;

};

#endif
