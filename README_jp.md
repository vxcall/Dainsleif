![cpp](https://img.shields.io/badge/C%2B%2B-17-%23ff40d9.svg?style=flat)
![cmake](https://img.shields.io/badge/cmake-3.16-yellow)
![Game](https://img.shields.io/badge/Game-CS%3AGO-blue.svg?style=flat)
![License](http://img.shields.io/badge/license-MIT-yellowgreen.svg?style=flat)

[英語版README](https://github.com/s3pt3mb3r/Dainsleif/blob/master/README.md)

# :zap: Dainsleif

まず初めに、もしこのプロジェクトが気に入ったらStarしてくれると嬉しいです！

Dainsleifは _Counter-Strike: Global Offensive_ 用のチートプログラムです。
ただし、これはあくまでも僕の個人的な知識欲で作っているものであって実戦(マルチプレイヤーモード)で使うことは想定されていません。
明示的な対策を行っているわけではないのでBANされる可能性が多分にあります。
ただ、ボット戦で使うことは可能ですし、実際のチートと同じ手法で作られていてとてもシンプルなためコードの参考にはなるかと思います。

もしこのプロジェクトについて質問等ありましたら気軽に [issue](https://github.com/s3pt3mb3r/Dainsleif/issues) ください！
暇なのですぐ答えます。

# :two_hearts: サポート
このプロジェクトにStarする、このアカウントをフォローする、プルリクエストを送るなどしていただけるととても励みになります。

# :pushpin: 目次

- [ビルド方法](#syringe-ビルド方法)
- [ハックメニュー](#scroll-ハックメニュー)
    - [注意事項](#rotating_light-注意事項)
- [ハック](#computer-ハック)
    - [エイムボット](#エイムボット)
    - [発光ハック](#発光ハック)
    - [トリガーボット](#トリガーボット)
    - [アンチリコイル](#アンチリコイル)
- [開発に貢献してくれた人](#開発に貢献してくれた人)

# :syringe: ビルド方法

必要なもの
- [DirectxSDK](https://www.microsoft.com/en-au/download/details.aspx?id=6812)

ビルド方法は二つあります。DirectxSDK以外の必要なものはあらかじめ含まれているため用意する必要はありません。

1. Cmakeを使ってビルドする

お好きなフォルダー内で以下のコマンドを実行してください。
```
$ git clone https://github.com/s3pt3mb3r/Dainsleif.git
$ cd Dainsleif
$ mkdir build && cd build
$ cmake ..
$ make
```

`/build` ディレクトリ内に `Dainsleif.dll`が生成されるはずです。

2. Visual Studio 2019でビルドする
もし「Visual Studioでビルドしたいけど、Cmakeは持ってるよ～」って方は、お好きなフォルダー内で以下のコマンドを実行してください。
(Cmakeがない人は少し下までスクロールしてね)
```
$ git clone https://github.com/s3pt3mb3r/Dainsleif.git
$ cd Dainsleif
$ mkdir build && cd build
$ cmake .. -A Win32
```
`/build` ディレクトリ内に `Dainsleif.sln`が生成されます。

これを使ってVisual Studioでプロジェクトとして開くことができるはずです。

Visual Studioで開いたら、メニューの`ビルド` → `ビルド Dainsleif`をクリックしてビルドしましょう。

すると`/build/Debug`ディレクトリ内に`Dainsleif.dll`が生成されます。

Cmakeを持ってない方は、[releases](https://github.com/s3pt3mb3r/Dainsleif/releases) の最新のリリースを確認してください。
Visual Studioユーザー用のフォルダを用意しています。(もし最新のリリース日から日にちが経過している場合はissueを作って僕に教えてください。なんとかしますw)

`Dainsleif.dll`を生成出来たら、あとは [GH injector](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/) などのお好きなDLL injectorを使ってインジェクトしてください。

# :scroll: ハックメニュー

ハックメニューへは<kbd>INSERT</kbd>キーを押すことでアクセスできます。

ただし、現段階では安全上の理由からメニューを開けるのはゲーム内だけとなっています。
メインメニューにいるときなどに<kbd>INSERT</kbd>を押しても反応しないのでご注意ください。

タブを押すことで各ハックのオン/オフや細かい調整ができます。
調整項目はこれから増やしていく予定です。

![Hack menu](https://user-images.githubusercontent.com/33578715/89070761-09c39300-d3a8-11ea-9aac-18cf2749b622.gif)

### :rotating_light: 注意事項

もし<kbd>INSERT</kbd>を押した際にハックメニューが表示されない、もしくはハックを起動した瞬間にクラッシュするようなことがあれば、おそらく原因は`Dainsleif/offset.h`ファイルにあります。

その場合は僕の`Dainsleif/offset.h`ファイルの中身をコピペしてあげてください。もし僕の`Dainsleif/offset.h`が数週間の間更新されていない場合は、[Hazedumper](https://github.com/frk1/hazedumper/blob/master/csgo.hpp)を使ってください。


# :computer: ハック

すでにいくつかのハックが開発済みですが、まだなんというか中途半端な部分もあります。

それぞれを単体で使う分には問題ないのですが、組み合わせて使うと想定外の動きになる可能性があります。

## エイムボット (Aimbot)

これが、現在のDainsleifの機能の中で一番完成度が高いです。(自負)

この機能をオンにすると、クロスヘアから一番近い敵の頭にエイムが吸い付きます。
Smoothnessという項目を変えると、吸い付きのゆるふわ度を変えることができます。

![aimbot](https://user-images.githubusercontent.com/33578715/89108283-b31e8d80-d469-11ea-8e55-e4e469d74576.gif)

## 発光ハック (Glow hack)

この機能をオンにすると、敵と味方の輪郭が光り壁を通して見れるようになります。簡単に言うとウォールハックですね。

敵と味方の光る色はハックメニューから自由にカスタマイズできます。

![Glow hack](https://user-images.githubusercontent.com/33578715/89087560-48b51100-d3c7-11ea-9ada-8ef04acfa52c.png)

## トリガーボット(Trigger bot)

これは、クロスヘアが敵と重なった瞬間に自動的に発砲するようになるハックです。

ただこの機能はまだ基礎を作ってからあまり改良していないため、低クオリティとなっています。

## アンチリコイル(Anti recoil)

これは、銃を発砲する際などに発生するリコイルを自動で制御してくれるハックです。

ただ、100%完全に集弾するわけではありません。

実際のスプレー結果↓

![Anti recoil](https://user-images.githubusercontent.com/33578715/89087634-769a5580-d3c7-11ea-83b1-dc31345e7424.png)

# 開発に貢献してくれた人
- [l1m0n3](https://github.com/l1m0n3)
