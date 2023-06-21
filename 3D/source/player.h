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
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetMove(void) { return m_move; }

	//�ÓI�����o�ϐ�
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�֐�
	void Move(void);
	void Rotate(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	float m_fSpeed;
	float m_fAngle;
	bool m_bJunp;

	//���f�����
	CModel *m_apModel[2];
	CShadow *m_pShadow;

};

#endif
