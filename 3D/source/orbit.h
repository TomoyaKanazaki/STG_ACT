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
	static COrbit *Create(CModel *pParent, D3DXCOLOR col, D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, int nLife);

private:

	struct OFFSET
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
		D3DXMATRIX mtxWorld;
	};

	//�����o�ϐ�
	CModel *m_parent; //�Ǐ]���郂�f��
	OFFSET m_offset[2]; //�I�t�Z�b�g���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@
	D3DXCOLOR m_colDef; //�����J���[
	int m_nLife; //���ݎ���
	int m_nNumVtx; //���_��
	D3DXMATRIX m_mtxWorld; //�O�Ֆ{�̂̃}�g���b�N�X

};

#endif
