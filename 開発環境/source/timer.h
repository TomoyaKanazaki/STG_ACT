//==========================================
//
//  �^�C�}�[�N���X(time.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CNumber;

//==========================================
//  �N���X��`
//==========================================
class CTime : public CObject
{
public:

	//�^�C�}�[�`���̗񋓌^��`
	enum Time
	{
		ADD = 0, //���Z
		SAB, //���Z
		MAX
	};

	//�����o�֐�
	CTime(int nPriority = 6);
	~CTime();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//�ÓI�����o�֐�
	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int max, Time kind);

protected:

	//�����o�ϐ�
	int m_nCurrent;
	int m_nMax;

private:

#define TIMER_DIGIT (3) //�X�R�A�̌���

	//�����o�ϐ�
	CNumber *m_apNumber[TIMER_DIGIT];
	int m_aTime[TIMER_DIGIT]; //�\������l

	//�����o�֐�
	void CalcScore(void);
	D3DXVECTOR3 CalcPos(int nCnt);


};

#endif
