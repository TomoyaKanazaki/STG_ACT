//==========================================
//
//  �����N���X(explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "explosion.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CExplosion::CExplosion(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CExplosion::~CExplosion()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CExplosion::Init(void)
{
	CObject3D_Anim::Init();
	CObject3D::SwitchBillboard();
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CExplosion::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CExplosion::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CExplosion::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D_Anim::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nPattern, int nInterval, bool bLoop, UVTYPE type)
{
	//�C���X�^���X����
	CExplosion *pExplosion = new CExplosion;

	if (pExplosion == NULL)
	{
		assert(false);
		return NULL;
	}

	//�e�����ݒ肷��
	pExplosion->m_pos = pos;
	pExplosion->m_size = size;
	pExplosion->m_rot = rot;

	//�A�j���[�V��������ݒ肷��
	pExplosion->SetAnim(nPattern, nInterval, bLoop, type);

	//������
	pExplosion->Init();

	//�e�N�X�`�������蓖�Ă�
	pExplosion->BindTexture(CManager::GetTexture()->GetAddress(CTexture::EXPLOSION));

	//�f�t�H���g�T�C�Y��ۑ�����
	pExplosion->m_size = size;

	//�|�C���^��Ԃ�
	return pExplosion;
}
