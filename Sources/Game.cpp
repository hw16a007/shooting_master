#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C) //HW15A213 山本 裕生
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)  //hw16a007変更
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G) HW15A062 菊地 龍大
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H) HW15A062 菊地 龍大


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 cannonInitPos;  //!< 砲台の初期位置の追加 HW15A213 山本 裕生
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    // HW15A153 野間涼司 (A)
    cannonPos = Vector2(-Screen::size().x/2 + 20, -150);
    cannonInitPos = cannonPos;// 砲台の初期位置を取得 HW15A213 山本 裕生
    targetRect = Rect(Screen::size().x/2 - 50, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
    PlayBGM("bgm_maoudamashii_8bit07.mp3");// BGMの再生処理を追加 実装：HW15A062 菊地 龍大
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_explosion03.mp3");// SEの再生処理を追加 実装：HW15A062 菊地 龍大
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 60 * Time::deltaTime;    //hw16a007弾の速さ変更

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 1;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion06.mp3");// SEの再生処理を追加 実装：HW15A062 菊地 龍大
        }
        if(bulletPos.x >= Screen::size().x / 2){    //hw16a007変更
            bulletPos.x = -999;                     //hw16a007変更
        }
        
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonInitPos.x-10, -140, 20, 100), Color::blue);// 描画位置を砲台の初期位置に HW15A213 山本 裕生
    cannonPos.y = -160 + 100 * Mathf::PingPong(Time::time, 1.0f);// 砲台を自動的に上下移動させる HW15A213 山本 裕生
    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 60.0f);
    DrawText(FormatString("%05d", score*100), Vector2(-319, 189), Color::black);　　//hw16a096 白永　滉　スコアを100点ずつ加算するようにし、5桁の表示に変えました
    DrawText(FormatString("%05d", score*100), Vector2(-320, 190), Color::white);

}

