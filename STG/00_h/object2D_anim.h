//==========================================
//
//  �A�j���[�V�����I�u�W�F�N�g2D(object2D_anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_ANIM_H_
#define _OBJECT2D_ANIM_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �A�j���[�V�����I�u�W�F�N�g2D�N���X��`
//==========================================
class CObject2D_Anim : public CObject2D
{
public:
	CObject2D_Anim(); //�R���X�g���N�^
	~CObject2D_Anim(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nAnimPattern);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

	//�ÓI�����o�֐�
	static CObject2D_Anim *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nAnimPattern, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�ϐ�
	int m_nNumPattern; //�A�j���[�V�����p�^�[����
	int m_nCountAnim; //�A�j���[�V�����J�E���g
	int m_nPatternAnim; //���݂̃A�j���[�V�����p�^�[��

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
