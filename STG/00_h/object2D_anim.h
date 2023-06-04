//==========================================
//
//  �A�j���[�V����2D�N���X(object2D_Anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_ANIM_H_
#define _OBJECT2D_ANIM_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �A�j���[�V����2D�N���X��`
//==========================================
class CObject2D_Anim : public CObject2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_U, //�������̃A�j���[�V����
		TYPE_V //�c�����̃A�j���[�V����
	}UVTYPE;

	CObject2D_Anim(); //�R���X�g���N�^
	~CObject2D_Anim(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type);

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
