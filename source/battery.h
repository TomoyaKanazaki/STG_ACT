//==========================================
//
//  �o�b�e���[�N���X(battery.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BATTERY_H_
#define _BATTERY_H_
#include "main.h"
#include "object2D.h"

//===========================================
//  �N���X��`
//==========================================
class CBattery : public CObject2D
{
public:
	CBattery(int nPriority = 7); //�R���X�g���N�^
	~CBattery(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Add(const float fAdd);
	void Sab(const float fSab);

	//�ÓI�����o�֐�
	static CBattery *Create();

private:

	//�����o�ϐ�
	float m_fBattery; //���݂̃o�b�e���[��

	//�ÓI�����o�ϐ�
	static const float mc_fMax; //�Q�[�W�̍ő�l
	static const float mc_fTime; //�������Ȃ������ꍇ�̐�������
	static const float mc_fSab; //1f�Ō�������l

};

#endif
