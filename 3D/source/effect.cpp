//==========================================
//
//  �G�t�F�N�g�N���X(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEffect::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEffect::CEffect(int nPriority) : CObject3D(nPriority)
{
	m_vecDeffSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fLifeRatio = 0;
	m_nNum++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEffect::~CEffect()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CEffect::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject3D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�r���{�[�h�ɐݒ肷��
	SwitchBillboard();

	//�^�C�v�̐ݒ�
	SetType(TYPE_EFFECT);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEffect::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEffect::Update(void)
{
	//���������炷
	m_nLife--;

	//�������Ȃ��Ȃ�����폜����
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//�T�C�Y������������
	m_size.x -= m_vecDeffSize.x * m_fLifeRatio;
	m_size.z -= m_vecDeffSize.z * m_fLifeRatio;

	//�ړ��ʂ����Z����
	m_pos += m_move;

	//�X�V
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CEffect *CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXCOLOR col, int nLife)
{
	//�C���X�^���X����
	CEffect *pEffect = NULL;

	//NULL�`�F�b�N
	if (pEffect == NULL)
	{
		//���������m��
		pEffect = new CEffect;
	}

	if (pEffect == NULL)
	{
		return NULL;
	}

	//������
	pEffect->Init(pos, size, rot);

	//�e�N�X�`�������蓖�Ă�
	pEffect->BindTexture(CManager::GetTexture()->GetAddress(0));

	//�f�t�H���g�T�C�Y��ۑ�����
	pEffect->m_vecDeffSize = size;

	//������ݒ肷��
	pEffect->m_nLife = nLife;
	pEffect->m_fLifeRatio = 1.0f / nLife;

	//�F��ݒ肷��
	pEffect->SetCol(col);

	//�|�C���^��Ԃ�
	return pEffect;
}

//==========================================
//  ��������
//==========================================
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	//�C���X�^���X����
	CEffect *pEffect = Create(pos, size, rot, col, nLife);

	//�ړ��ʂ�ݒ�
	pEffect->m_move = move;

	//�|�C���^��Ԃ�
	return pEffect;
}
