//==========================================
//
//  �v���C���[�N���X(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CShadow;

//==========================================
//  �v���C���[�N���X�̒�`
//==========================================
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4); //�R���X�g���N�^
	~CPlayer(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }

	//�ÓI�����o�ϐ�
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�֐�
	void Move(void);
	void Rotate(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_oldPos;
	int m_nLife;
	int m_nNumModel;
	int m_nDeadCounter;
	float m_fSpeed;
	float m_fAngle;
	bool m_bRand;
	bool m_bDead;

	//���f�����
	CModel *m_apModel[5]; //���f�����
	CLayer::LAYERDATA *m_pLayer; //�K�w�\�����
	CShadow *m_pShadow; //�e�̏��

};

#endif
