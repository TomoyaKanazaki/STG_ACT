//==========================================
//
//  ���b�V���I�u�W�F�N�g�N���X(object_mesh.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_MESH_H_
#define _OBJECT_MESH_H_
#include "main.h"
#include "object.h"

//==========================================
//  ���b�V���I�u�W�F�N�g�N���X��`
//==========================================
class CObject_Mesh : public CObject
{
public:
	typedef struct
	{
		int nNumMesh; //��������(�v���~�e�B�u��)
		int nNumMesh_U; //���̕�����
		int nNumMesh_V; //�c�̕�����
		int nNumVtx; //�����_��
		int nNumVtx_U; //���̒��_��
		int nNumVtx_V; //�c�̒��_��
		int nNumIdx; //���C���f�b�N�X��
	}MeshData; //���_���n�̍\����

	CObject_Mesh(int nPriority = 3); //�R���X�g���N�^
	~CObject_Mesh(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool OnMesh(const D3DXVECTOR3 pos);
	bool OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos);
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	//�ÓI�����o�֐�
	static CObject_Mesh *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv);

private:

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //�C���f�b�N�X�o�b�t�@
	MeshData m_Mesh; //���b�V�����
	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`�����
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	D3DXCOLOR m_Color;

	//�����o�֐�
	void SetVtx(void);
	void SetIdx(void);
	void CalcData(void);
	bool CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const;

};

#endif
