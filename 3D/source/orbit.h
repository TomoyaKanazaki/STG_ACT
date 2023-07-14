//==========================================
//
//  �O�ՃN���X(orbit.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "main.h"
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CModel;

//==========================================
//  �O�ՃN���X��`
//==========================================
class COrbit : public CObject
{
public:
	COrbit(); //�R���X�g���N�^
	~COrbit(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static COrbit *Create(CModel *pParent, D3DXCOLOR col, float fLength, int nLife);

private:

	//�����o�ϐ�
	CModel *m_parent; //�Ǐ]���郂�f��
	D3DXVECTOR3 m_Pos; //�ʒu
	D3DXVECTOR3 m_VtxPos; //���_�ʒu
	D3DXCOLOR m_Col; //�F
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	float m_fLength; //�O�Ղ̒���
	int m_nLife; //���ݎ���
	int m_nNumVtx; //���_��

};

#endif
