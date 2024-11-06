#include "DxLib.h"
#include "game.h"
#include "Vec2.h"

namespace
{
	constexpr int kCenterX = Game::kScreenWidth / 2;
	constexpr int kCenterY = Game::kScreenHeigth / 2;

	constexpr int kCircleRadius = 160;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// フルスクリーンではなく、ウインドウモードで開くようにする
	ChangeWindowMode(1);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 角度
	float angle = 20.0f;

	// 中心座標
	Vec2 center{ kCenterX,kCenterY };

	// ゲームループ
	while (ProcessMessage() == 0)	// Windowsが行う処理を待つ必要がある
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		// ここにゲームの処理を書く
		DrawLine(0, kCenterY, Game::kScreenWidth, kCenterY, GetColor(255, 255, 255));
		DrawLine(kCenterX, 0, kCenterX, Game::kScreenHeigth,  GetColor(255, 255, 255));

		DrawCircle(kCenterX, kCenterY, kCircleRadius, GetColor(255, 0, 0), false, 2);

		// 画面中央からangleの方向に伸びる線の描画
		Vec2 start = center;  // 線の始点(画面中央)
		Vec2 end;             // 線の終点(円周に向かって伸びた先)
		end.x = cosf(angle) * kCircleRadius;
		end.y = sinf(angle) * kCircleRadius;
		// 画面中央が基準位置になっていないので基準位置をずらす
		end += start;

		DrawLine(start.x, start.y, end.x, end.y, GetColor(255, 255, 0), 2);

		// 画面の切り替わりを待つ必要がある
		ScreenFlip();	// 1/60秒経過するまで待つ

		// FPS(Frame Per Second)60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}