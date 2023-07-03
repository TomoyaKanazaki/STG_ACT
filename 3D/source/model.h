//==========================================
//
//  ���f���N���X(model.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "object.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_MODEL (32) //���f���̍ő吔

//==========================================
//  ���f���N���X��`
//==========================================
class CModel : public CObject
{
public:
	//���f���\���̒�`
	typedef struct
	{
		LPDIRECT3DTEXTURE9 *pTexture; //�}�e���A���Ɏg�p����e�N�X�`��
		LPD3DXMESH pMesh; //���_���
		LPD3DXBUFFER pBuffMat; //�}�e���A���o�b�t�@
		DWORD dwNumMat; //�}�e���A����
		D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	}MODEL;

	CModel(int nPriority = 7); //�R���X�g���N�^
	~CModel(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetTransform(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) { m_pos = pos; m_rot = rot; }
	static int GetNum(void) { return m_nNum; }

	//�ÓI�����o�֐�
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nModelID, CModel *m_pParent = NULL);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetLoadState(void) { return m_bLoad; }
	static int m_nNum;



private:

	//�����o�ϐ�
	MODEL m_Info;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	CModel *m_pParent; //�e���f���ւ̃|�C���^
	int m_nSelfID;

	//�ÓI�����o�ϐ�
	static int m_nNumAll; 
	static MODEL *m_pModel;
	static char m_sFilePass[MAX_MODEL][128];
	static bool m_bLoad;

};

#endif
