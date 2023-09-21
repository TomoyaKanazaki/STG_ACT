//==========================================
//
//  �^�C�g���}�l�[�W��(titlemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  �O���錾
//==========================================
class CCamera;
class CLight;

//==========================================
//  �^�C�g���}�l�[�W���N���X��`
//==========================================
class CTitleManager : public CScene
{
public:
	CTitleManager(); //�R���X�g���N�^
	~CTitleManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//�ÓI�����o�ϐ�
	static CCamera *m_pCamera;
	static CLight *m_pLight;

};

#endif
