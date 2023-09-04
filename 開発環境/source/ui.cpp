//==========================================
//
//  UI�N���X(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "gamemanager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
char CUi::m_sPass[256] = {};

//==========================================
//  �R���X�g���N�^
//==========================================
CUi::CUi()
{
	m_hWnd = NULL;
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_EnemyData[nCnt].CreateData.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_EnemyData[nCnt].CreateData.fase = 0;
		m_EnemyData[nCnt].CreateData.type = 0;
		m_EnemyData[nCnt].CreateData.nCount = 0;
		m_EnemyData[nCnt].CreateData.nInterval = 0;
		m_EnemyData[nCnt].bUse = false;
	}
	m_nID = 0;
	m_state = CGameManager::NONE;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CUi::~CUi()
{

}

//==========================================
//  ����������
//==========================================
void CUi::Init(HWND hWnd)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_hWnd = hWnd;

	//ImGui���̐ݒ�
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//�g�p����t�H���g
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//�t�H���g�T�C�Y
	const float FontSize = 15.0f;

	//�����̐ݒ�
	ImGuiIO &io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGui�X�^�C���̐ݒ�
	ImGui::StyleColorsLight();

	//�v���b�g�t�H�[��/�����_���[�ƃo�b�N�G���h�̐ݒ�
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
}

//==========================================
//  �I������
//==========================================
void CUi::Uninit(void)
{
	//ImGui���I��
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  �X�V����
//==========================================
void CUi::Update(void)
{
	//ImGui�̎��s
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//�E�B���h�E�̐���
	ImGui::Begin(u8"EnemyManager");

	//�\������G�̔ԍ������߂�
	if (ImGui::ArrowButton("##0", 0))
	{
		if (m_nID > 0)
		{
			m_nID--;
		}
	} ImGui::SameLine();
	ImGui::Text(u8"�G���ԍ� : %d", m_nID); ImGui::SameLine();
	if (ImGui::ArrowButton("##1", 1))
	{
		if (m_nID < 255)
		{
			m_nID++;
		}
	}

	//���C��
	ImGui::NewLine();

	//�G���̎g�p��Ԃ�ݒ�
	ImGui::Checkbox(u8"�g�p���", &m_EnemyData[m_nID].bUse);

	//�G���̃p�����[�^�ݒ�
	if (m_EnemyData[m_nID].bUse)
	{
		//�G�^�C�v�̐ݒ�
		ImGui::SliderInt (u8"�G�^�C�v", &m_EnemyData[m_nID].CreateData.type, 0, CEnemy::TYPE_MAX - 1);

		//�����ʒu�̐ݒ�
		ImGui::DragFloat3(u8"�����ʒu", m_EnemyData[m_nID].CreateData.pos);

		//���������t�F�[�Y�̐ݒ�
		ImGui::SliderInt(u8"�����t�F�[�Y", &m_EnemyData[m_nID].CreateData.fase, 0, CGameManager::FAZE_MAX - 1);

		//�����񐔂̐ݒ�
		ImGui::Text(u8"[ -1 ]�Ŗ�������");
		ImGui::DragInt(u8"������", &m_EnemyData[m_nID].CreateData.nCount, 0.05f, -1);

		//�����Ԋu�̐ݒ�
		ImGui::DragInt(u8"�����Ԋu", &m_EnemyData[m_nID].CreateData.nInterval, 0.05f, 0);
	}

	//���C��
	ImGui::NewLine();

	//�t�F�[�Y�ݒ�
	ImGui::Text(u8"���݂̃t�F�[�Y : %d", CGameManager::GetState());
	if (ImGui::ArrowButton("##2", 0))
	{
		if (m_state > 0)
		{
			m_state = (CGameManager::STATE)((int)m_state - 1);
		}
	} ImGui::SameLine();
	ImGui::Text(u8"�t�F�[�Y : %d", m_state); ImGui::SameLine();
	if (ImGui::ArrowButton("##3", 1))
	{
		if (m_state < CGameManager::FAZE_MAX - 1)
		{
			m_state = (CGameManager::STATE)((int)m_state + 1);
		}
	} ImGui::SameLine();
	if (ImGui::Button(u8"�Đݒ�"))
	{
		ReLoad();
		CGameManager::SetState(m_state);
		CEnemyManager::ResetDeth();
	}

	//���o��
	Save(); ImGui::SameLine(); Load();

	//�E�B���h�E�̏I��
	ImGui::End();

	//�X�V�̏I��
	ImGui::EndFrame();

}

//==========================================
//  �`�揈��
//==========================================
void CUi::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`����e
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	//���C�e�B���O���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CUi *CUi::Create(HWND hWnd)
{
	//�C���X�^���X����
	CUi *pUI = NULL;

	//NULL�`�F�b�N
	if (pUI == NULL)
	{
		//���������m��
		pUI = new CUi;
	}

	//������
	if (pUI != NULL)
	{
		pUI->Init(hWnd);
	}

	//�|�C���^��Ԃ�
	return pUI;
}

//==========================================
//  �����o������
//==========================================
void CUi::Save(void)
{
	if (ImGui::Button(u8"�Z�[�u"))
	{
		OPENFILENAMEA filename = {};

		// �t�@�C���I���_�C�A���O�̐ݒ�
		filename.lStructSize = sizeof(OPENFILENAMEA);
		filename.hwndOwner = NULL;
		filename.lpstrFilter = 
			"�o�C�i���t�@�C��\0*.bin\0";
		filename.lpstrFile = m_sPass;
		filename.nMaxFile = MAX_PATH;
		filename.Flags = OFN_FILEMUSTEXIST;

		// �t�@�C���I���_�C�A���O��\��
		if (GetOpenFileNameA(&filename))
		{
			// �I�����ꂽ�t�@�C���̃p�X��\��
			printf("Selected file: %s\n", m_sPass);
		}

		//�Z�[�u
		if (strcmp(&m_sPass[0], "") != 0)
		{
			//���[�J���ϐ��錾
			FILE *pFile; //�t�@�C����
		
			//�t�@�C�����������ݐ�p�ŊJ��
			pFile = fopen(m_sPass, "wb");
		
			if (pFile != NULL)
			{
				//�ۑ�����Ă���f�[�^�����擾����
				int nNumData = 0;
				for (int nCnt = 0; nCnt < 256; nCnt++)
				{
					if (m_EnemyData[nCnt].bUse)
					{
						nNumData++;
					}
				}
		
				//�f�[�^����ۑ�����
				fwrite(&nNumData, sizeof(int), 1, pFile);
		
				//�g�p���Ă���f�[�^��ۑ�����
				for (int nCnt = 0; nCnt < 256; nCnt++)
				{
					if (m_EnemyData[nCnt].bUse)
					{
						//0����h�~
						if (m_EnemyData[nCnt].CreateData.nInterval <= 0)
						{
							m_EnemyData[nCnt].CreateData.nInterval = 1;
						}

						//�����o��
						fwrite(&m_EnemyData[nCnt].CreateData, sizeof(CEnemyManager::CreateData), 1, pFile);
					}
				}
		
				//�t�@�C�������
				fclose(pFile);
			}
		}
		else
		{
			MessageBox(m_hWnd, "Failed to save", "Failed to save", MB_OK);
		}
	}
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CUi::Load(void)
{
	if (ImGui::Button(u8"���[�h"))
	{
		OPENFILENAMEA filename = {};

		// �t�@�C���I���_�C�A���O�̐ݒ�
		filename.lStructSize = sizeof(OPENFILENAMEA);
		filename.hwndOwner = NULL;
		filename.lpstrFilter =
			"�o�C�i���t�@�C��\0*.bin\0";
		filename.lpstrFile = m_sPass;
		filename.nMaxFile = MAX_PATH;
		filename.Flags = OFN_FILEMUSTEXIST;

		// �t�@�C���I���_�C�A���O��\��
		if (GetOpenFileNameA(&filename))
		{
			// �I�����ꂽ�t�@�C���̃p�X��\��
			printf("Selected file: %s\n", m_sPass);
		}

		//�Z�[�u
		if (strcmp(&m_sPass[0], "") != 0)
		{
			//���[�J���ϐ��錾
			FILE *pFile; //�t�@�C����

			//�t�@�C�����������ݐ�p�ŊJ��
			pFile = fopen(m_sPass, "rb");

			if (pFile != NULL)
			{
				//�ۑ�����Ă���f�[�^�����擾����
				int nNumData = 0;
				fread(&nNumData, sizeof(int), 1, pFile);

				//�ۑ�����Ă���f�[�^��S�ēǂݍ���
				for (int nCnt = 0; nCnt < nNumData; nCnt++)
				{
					fread(&m_EnemyData[nCnt].CreateData, sizeof(CEnemyManager::CreateData), 1, pFile);
					m_EnemyData[nCnt].bUse = true;
				}

				//�t�@�C�������
				fclose(pFile);

				//�G�l�~�[�}�l�[�W���ɕۑ����ꂽ�f�[�^���X�V
				CEnemyManager::Unload();
				CEnemyManager::Load(&m_sPass[0]);
			}
		}
		else
		{
			MessageBox(m_hWnd, "Failed to load", "Failed to load", MB_OK);
		}
	}
}

//==========================================
//  �ēǂݍ���
//==========================================
void CUi::ReLoad(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����

	//�t�@�C�����������ݐ�p�ŊJ��
	pFile = fopen(m_sPass, "rb");

	if (pFile != NULL)
	{
		//�ۑ�����Ă���f�[�^�����擾����
		int nNumData = 0;
		fread(&nNumData, sizeof(int), 1, pFile);

		//�ۑ�����Ă���f�[�^��S�ēǂݍ���
		for (int nCnt = 0; nCnt < nNumData; nCnt++)
		{
			fread(&m_EnemyData[nCnt].CreateData, sizeof(CEnemyManager::CreateData), 1, pFile);
			m_EnemyData[nCnt].bUse = true;
		}

		//�G�l�~�[�}�l�[�W���̍X�V
		CEnemyManager::Unload();
		CEnemyManager::Load(&m_sPass[0]);

		//�t�@�C�������
		fclose(pFile);
	}
}
