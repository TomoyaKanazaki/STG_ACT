//==========================================
//
//  �G�l�~�[�N���X(enemy.h)
//  Author : Tomoay Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CMotion;

//==========================================
//  �G�l�~�[�N���X��`
//==========================================
class CEnemy : public CObject
{
public:

	//�񋓌^��`
	enum ENEMY_TYPE
	{
		NORMAL = 0, //�́[�܂�
		BLOCK, //����
		PUSH, //��������
		MAX
	};

	CEnemy(int nPriority = 4); //�R���X�g���N�^
	~CEnemy(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetLife(const int nDamage) { if (m_nLife > 0) m_nLife -= nDamage; }

	//�ÓI�����o�ϐ�
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, ENEMY_TYPE type);

protected:

	//�����o�֐�
	void AvertEnemy(void);
	void Chain(void);
	void Move(void);

	//���f�����
	CModel **m_ppModel; //���f�����
	CLayer::LAYERDATA *m_pLayer; //�K�w�\�����
	CMotion *m_pMotion;

	//�����o�ϐ�
	int m_nCntBullet;
	int m_nCombo;

private:

	//�����o�֐�
	int GetCombo() { return m_nCombo; } //�G�̃R���{���̎擾

	//�����o�ϐ�
	int m_nNumModel;
	int m_nLife;
	float m_fSpeed;
	bool m_bRand;

	//�ÓI�����o�ϐ�
	const static float mc_fSize; //�G���m�̓����蔻��͈̔�

};

#endif
