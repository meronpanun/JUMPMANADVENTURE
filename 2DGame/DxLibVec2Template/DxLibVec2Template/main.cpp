#include "DxLib.h"
#include "game.h"
#include "Vec2.h"

namespace
{
	constexpr int kCenterX = Game::kScreenWidth / 2;
	constexpr int kCenterY = Game::kScreenHeigth / 2;

	constexpr int kCircleRadius = 160;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �t���X�N���[���ł͂Ȃ��A�E�C���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(1);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �p�x
	float angle = 20.0f;

	// ���S���W
	Vec2 center{ kCenterX,kCenterY };

	// �Q�[�����[�v
	while (ProcessMessage() == 0)	// Windows���s��������҂K�v������
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʑS�̂��N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		DrawLine(0, kCenterY, Game::kScreenWidth, kCenterY, GetColor(255, 255, 255));
		DrawLine(kCenterX, 0, kCenterX, Game::kScreenHeigth,  GetColor(255, 255, 255));

		DrawCircle(kCenterX, kCenterY, kCircleRadius, GetColor(255, 0, 0), false, 2);

		// ��ʒ�������angle�̕����ɐL�т���̕`��
		Vec2 start = center;  // ���̎n�_(��ʒ���)
		Vec2 end;             // ���̏I�_(�~���Ɍ������ĐL�т���)
		end.x = cosf(angle) * kCircleRadius;
		end.y = sinf(angle) * kCircleRadius;
		// ��ʒ�������ʒu�ɂȂ��Ă��Ȃ��̂Ŋ�ʒu�����炷
		end += start;

		DrawLine(start.x, start.y, end.x, end.y, GetColor(255, 255, 0), 2);

		// ��ʂ̐؂�ւ���҂K�v������
		ScreenFlip();	// 1/60�b�o�߂���܂ő҂�

		// FPS(Frame Per Second)60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}