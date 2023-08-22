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
class CScore;
class CTimer;
class CObject_Fan;
class CPlayer;
class CCamera;
class CLight;
class CEnergy;
class CBattery;

//==========================================
//  �Q�[���}�l�[�W���N���X��`
//==========================================
class CGameManager : public CScene
{
public:
	typedef enum
	{
		NONE = 0, //�Ȃ�
		SHOT, //�ˌ����[�h
		BLADE, //�a�����[�h
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
	static CScore *GetScore(void) { return m_pScore; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CObject_Fan *GetFan(void) { return m_pFan; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CEnergy *GetEnergy(void) { return m_pEnergy; }
	static CBattery *GetBattery(void) { return m_pBattery; }

private:

	//�����o�ϐ�

	//�ÓI�����o�ϐ�
	static STATE m_State; //�Q�[���̏��
	static CScore *m_pScore;
	static CTimer *m_pTimer;
	static CObject_Fan *m_pFan;
	static CPlayer *m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CEnergy *m_pEnergy;
	static CBattery *m_pBattery;

};

#endif
