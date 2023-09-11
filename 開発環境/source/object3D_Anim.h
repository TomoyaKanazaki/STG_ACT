//==========================================
//
//  �A�j���[�V����3D�N���X(object3D_Anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT3D_ANIM_H_
#define _OBJECT3D_ANIM_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �A�j���[�V����3D�N���X��`
//==========================================
class CObject3D_Anim : public CObject3D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_U, //�������̃A�j���[�V����
		TYPE_V //�c�����̃A�j���[�V����
	}UVTYPE;

	CObject3D_Anim(int nPriority = 3); //�R���X�g���N�^
	~CObject3D_Anim(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type);
	HRESULT SetTexPos(void);

	//�ÓI�����o�֐�
	static CObject3D_Anim *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nPattern, int nInterval, bool bLoop, UVTYPE type);

private:

	//�����o�ϐ�
	UVTYPE m_Type;
	int m_nNumPattern; //�p�^�[����
	int m_nAnimPattern; //���݂̃p�^�[��
	int m_nUpdateFrame; //�X�V�Ԋu
	int m_nAnimCounter; //�A�j���[�V�����J�E���^�[
	bool m_bLoop; //���[�v�̗L��

};

#endif
