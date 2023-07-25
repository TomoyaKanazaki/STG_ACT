//==========================================
//
//  �t�F�[�h�N���X(fade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �t�F�[�h�N���X��`
//==========================================
class CFade : public CObject2D
{
public:
	enum MODE
	{
		MODE_NONE = 0,
		MODE_IN, //�t�F�[�h�C��
		MODE_OUT, //�t�F�[�h�A�E�g
		MODE_MAX
	};

	CFade(int nPriority = 7); //�R���X�g���N�^
	~CFade(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool GetState(void) { return m_bFinish; }
	MODE GetMode(void) { return m_Mode; }

	//�ÓI�����o�֐�
	static CFade *Create(int nTime, MODE mode);

private:

	//�����o�ϐ�
	bool m_bFinish; //�t�F�[�h�I���t���O
	int m_nTime; //�t�F�[�h�ɂ����鎞��
	int m_nCounter; //�t�F�[�h�J�E���^�[
	float m_fAlpha; //�s�����x�̊���
	MODE m_Mode; //�t�F�[�h���[�h

};

#endif
