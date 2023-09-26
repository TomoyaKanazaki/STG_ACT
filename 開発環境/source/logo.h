//==========================================
//
//  ���S�̃N���X(logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_H_
#define _LOGO_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CLogo : public CObject2D
{
public:

	//���
	enum TYPE
	{
		TITLE = 0, //�^�C�g��
		RESULT, //���U���g
		RANKING, //�����L���O
		ENTER, //�G���^�[
		RANK, //����̏���
		SCORE, //�X�R�A
		MAX
	};

	CLogo(int nPriority = 7); //�R���X�g���N�^
	~CLogo(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);

private:

	//�����o�ϐ�
	TYPE m_type;
	float m_fCounter;

};

#endif
