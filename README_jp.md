![cpp](https://img.shields.io/badge/C%2B%2B-17-%23ff40d9.svg?style=flat)
![cmake](https://img.shields.io/badge/cmake-3.16-yellow)
![Game](https://img.shields.io/badge/Game-CS%3AGO-blue.svg?style=flat)
![License](http://img.shields.io/badge/license-MIT-yellowgreen.svg?style=flat)

[README in English](https://github.com/s3pt3mb3r/Dainsleif/blob/master/README.md)

![Banner](https://user-images.githubusercontent.com/33578715/90953346-22056a00-e49d-11ea-9b63-56f33187e667.png)
この絵は僕の親友である[@suzuharuR](https://twitter.com/suzuharuR)から頂いたものです。

# :zap: Dainsleif

まず初めに、もしこのプロジェクトが気に入ったら **:star: 星 :star:** をつけてくださると幸いです。

Dainsleifは _Counter-Strike: Global Offensive_ 用のチートプログラムです。
ただし、これはあくまでも僕の個人的な知識欲で作っているものであって実戦(マルチプレイヤーモード)で使うことは想定されていません。
明示的な対策を行っているわけではないのでBANされる可能性が多分にあります。 **このソフトウェアによって発生したいかなる問題に対しても、開発者一同は責任を負いかねます。** 注意してご使用ください。
ただ、ボット戦で使うことは可能ですし、実際のチートと同じ手法で作られていてとてもシンプルなためコードの参考にはなるかと思います。

もしこのプロジェクトについて質問等ありましたら気軽に [issue](https://github.com/s3pt3mb3r/Dainsleif/issues) ください！
暇なのですぐ答えます。

# :two_hearts: サポート
このプロジェクトにStarする、このアカウントをフォローする、プルリクエストを送るなどしていただけるととても励みになります。

# :pushpin: 目次

- [:syringe: ビルド方法](#syringe-ビルド方法)
- [:rotating_light: トラブルシューティング](#rotating_light-トラブルシューティング)
- [:scroll: ハックメニュー](#scroll-ハックメニュー)
- [:computer: ハック](#computer-ハック)
    - [エイムボット](#エイムボット)
    - [発光ハック](#発光ハック)
    - [ESPハック](#ESPハック)
    - [トリガーボット](#トリガーボット)
    - [アンチリコイル](#アンチリコイル)
- [:busts_in_silhouette: 共同開発者](#busts_in_silhouette-共同開発者)

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

# :rotating_light: トラブルシューティング

ハックがうまく動きませんか？ 大丈夫です、そんなときのために[Wiki](https://github.com/s3pt3mb3r/Dainsleif/wiki/Trouble-shooting)を用意してあります。

# :scroll: ハックメニュー

ハックメニューへは<kbd>INSERT</kbd>キーを押すことでアクセスできます。

各タブを押すことで各ハックのオン/オフや細かい調整ができます。
調整項目はこれから増やしていく予定です。

![Hack menu](https://user-images.githubusercontent.com/33578715/89070761-09c39300-d3a8-11ea-9aac-18cf2749b622.gif)

メニューバーからタブのオンオフを切り替えることができます。
いくつかのハックはデフォルトでオフになっています。
![menu visible](https://user-images.githubusercontent.com/33578715/91351549-0f7f8d80-e81b-11ea-9216-e7d77a0566d1.png)

# :computer: ハック

## エイムボット (Aimbot)

これが、現在のDainsleifの機能の中で一番完成度が高いです。(自負)

この機能をオンにすると、クロスヘアから一番近い敵の頭にエイムが吸い付きます。
Smoothnessという項目を変えると、吸い付きのゆるふわ度を変えることができます。
Rangeの項目を変えると、エイムボットが反応する範囲を変えることができます。

![aimbot](https://user-images.githubusercontent.com/33578715/89108283-b31e8d80-d469-11ea-8e55-e4e469d74576.gif)

## 発光ハック (Glow hack)

この機能をオンにすると、敵と味方の輪郭が光り壁を通して見れるようになります。簡単に言うとウォールハックですね。

敵と味方の光る色はハックメニューから自由にカスタマイズできます。

![Glow hack](https://user-images.githubusercontent.com/33578715/89087560-48b51100-d3c7-11ea-9ada-8ef04acfa52c.png)

## ESPハック (Esp)

これはESPハックです。味方や敵に対して長方形のオーバーレイを表示します。

また、自分から各プレイヤーに対して直線を引きます。

![esp](https://user-images.githubusercontent.com/33578715/92253522-30726d80-ef02-11ea-80d3-fdb7045851d0.png)

## トリガーボット(Trigger bot)

これは、クロスヘアが敵と重なった瞬間に自動的に発砲するようになるハックです。

一応エイムボットと併用して使うことを想定してデザインされています。今後単体でも十分使えるように改良していきます。

## アンチリコイル(Anti recoil)

これは、銃を発砲する際などに発生するリコイルを自動で制御してくれるハックです。

ただ、100%完全に集弾するわけではありません。

実際のスプレー結果↓

![Anti recoil](https://user-images.githubusercontent.com/33578715/89087634-769a5580-d3c7-11ea-83b1-dc31345e7424.png)

## 視野角調整(Field of view)

このハックでは、本来変更できないプレイヤーの視野角を60～120まで調整できるようにするものです。

## アンチ放置キック(Anti AFK)

このハックをオンにすると、50秒ごとにプレイヤーを自動で動かすことによって放置キックされないようなります。

# :busts_in_silhouette: 共同開発者

彼なしでは間違いなくここまで来れませんでした。感謝します。 ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/l1m0n3"><img src="https://avatars1.githubusercontent.com/u/13360351?v=4" width="100px;" alt=""/><br /><sub><b>L1m0n3</b></sub></a><br /><a href="https://github.com/s3pt3mb3r/Dainsleif/commits?author=l1m0n3" title="Code">💻</a> <a href="#maintenance-l1m0n3" title="Maintenance">🚧</a></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->
