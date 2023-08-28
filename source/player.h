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
class CMotion;
class COrbit;

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
	void SetDead(const bool bDead) { m_bDead = bDead; }

	//�ÓI�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�֐�
	void Move(void);
	void Slop(void);
	void Shot(void);
	void Explosion(void);
	void Swing(void);
	void Aiming(void);

	//�����o�ϐ�
	int m_nLife;
	int m_nNumModel;
	int m_nDeadCounter;
	int m_nBladeLife;
	float m_fSpeed;
	float m_fAngle;
	float m_fSwing;
	bool m_bRand;
	bool m_bDead;
	D3DXMATERIAL *m_pDefMat;

	//�ÓI�����o�ϐ�
	const static float mc_fExplosion; //�r�Ŕ͈�

	//���f�����
	CModel **m_ppModel; //���f�����
	CLayer::LAYERDATA *m_pLayer; //�K�w�\�����
	CShadow *m_pShadow; //�e�̏��
	CMotion *m_pMotion;
	COrbit *m_orbit;

};

#endif
