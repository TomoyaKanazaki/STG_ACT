//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "main.h"
#include "scene.h"

//==========================================
//  �O���錾
//==========================================
class CObject_Fan;
class CPlayer;
class CCamera;
class CLight;

//==========================================
//  �Q�[���}�l�[�W���N���X��`
//==========================================
class CGameManager : public CScene
{
public:
	typedef enum
	{
		NONE = 0, //�Ȃ�
		MOVIE, //���[�r�[���
		MAX
	}STATE;

	CGameManager(); //�R���X�g���N�^
	~CGameManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static STATE GetState(void) { return m_State; }
	static void SetState(STATE state) { m_State = state; }
	static CObject_Fan *GetFan(void) { return m_pFan; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }

private:

	//�����o�ϐ�

	//�ÓI�����o�ϐ�
	static STATE m_State; //�Q�[���̏��
	static CObject_Fan *m_pFan;
	static CPlayer *m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;

};

#endif
