//==========================================
//
//  �I�u�W�F�N�g�t�@���N���X(object_fan.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_FAN_H_
#define _OBJECT_FAN_H_
#include "main.h"
#include "object.h"

//==========================================
//  �I�u�W�F�N�g�t�@���N���X��`
//==========================================
class CObject_Fan : public CObject
{
public:
	CObject_Fan(int nPriority = 1); //�R���X�g���N�^
	~CObject_Fan(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool OnMesh(const D3DXVECTOR3 pos);
	bool OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos);

	//�ÓI�����o�֐�
	static CObject_Fan *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumPrimitive, float fRadius);

private:

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`�����
	D3DXCOLOR m_Color; //���_�J���[
	float m_fRadius; //���S���W����e���_�ւ̋���
	int m_nNumPrimitive; //�v���~�e�B�u��
	int m_nNumVtx; //���_��

	//�����o�֐�
	void SetVtx(void);
	bool CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const;

};

#endif
