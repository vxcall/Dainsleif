![cpp](https://img.shields.io/badge/C%2B%2B-17-%23ff40d9.svg?style=flat)
![cmake](https://img.shields.io/badge/cmake-3.16-yellow)
![Game](https://img.shields.io/badge/Game-CS%3AGO-blue.svg?style=flat)
![License](http://img.shields.io/badge/license-MIT-yellowgreen.svg?style=flat)

<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-2-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

**[日本語版README](https://github.com/s3pt3mb3r/Dainsleif/blob/master/README_jp.md)**

[![Banner](https://user-images.githubusercontent.com/33578715/90916494-b9be7600-e413-11ea-8dee-ffea384afb2e.png)](https://github.com/s3pt3mb3r/Dainsleif)
Image's gifted by my big friend [@suzuharuR](https://twitter.com/suzuharuR)

# :zap: Dainsleif
**Please :star:star this project, it'll be a huge help for me =)**

This is an internal cheat for **_Counter-Strike: Global Offensive_** I've been working on as my training of reverse engineering.

**Disclaimer**: Since I don't intend to make this a malicious software, this isn't considered to be performed in multi player mode. 
**We won't take any responsibility if a problem occurs because of this software.** Keep that in mind.

As of today, Dainsleif is a quite simple and tiny cheat, so you can use this as your reference if you want.

If you have any request or question, feel free to ask me through [issue](https://github.com/s3pt3mb3r/Dainsleif/issues).
Please understand that it may take a certain days because I'm doing this as completely my hobby without profit or reward, you know? 

# :two_hearts: Support me
Any supports will be greatly appreciated. 
You can easily support/motivate me by either **starring my project**, **following me on github** or **sending PR to me**.

# :pushpin: Table of contents

- [:syringe: How to build this hack](#syringe-how-to-build-this-hack)
- [:rotating_light: TROUBLE SHOOTING](#rotating_light-trouble-shooting)
- [:scroll: Menu](#scroll-menu)
- [:computer: Hacks](#computer-hacks)
    - [Aimbot](#aimbot)
    - [Glow hack](#glow-hack)
    - [ESP hack](#esp-hack)
    - [Trigger bot](#trigger-bot)
    - [Anti recoil](#anti-recoil)
    - [Minimap hack](#minimap-hack)
    - [Anti AFK](#anti-afk)
    - [FOV](#fov)
- [:put_litter_in_its_place: Uninstall](#put_litter_in_its_place-uninstall)
- [:busts_in_silhouette: Contributors](#busts_in_silhouette-contributors)
- [:hammer_and_wrench: Features being developed](#hammer_and_wrench-features-being-developed)

# :syringe: How to build this hack

**requirement**
- [DirectxSDK](https://www.microsoft.com/en-au/download/details.aspx?id=6812)

You can select from two ways to build this hack.
I believe all you need in order to build this project except DirectxSDK is already included which is [MSDetour](https://github.com/microsoft/Detours), [ImGui](https://github.com/ocornut/imgui), and [toml11](https://github.com/ToruNiina/toml11).
They're in Dependencies directory.

**1. Build project using Visual Studio 2019**

If you have Visual Studio 2019, you must installed `Developer Command Prompt for Visual Studio` at the same time.
Launch it and go to any directory you wanna clone Dainsleif in, and run following commands.

```Shell
$ git clone https://github.com/s3pt3mb3r/Dainsleif.git
$ cd Dainsleif
$ mkdir build && cd build
$ cmake .. -A Win32
$ cmake --build .
```

After finished compiling, `Dainsleif.dll` will be in debug folder.

**Once you get the `Dainsleif.dll`, you can now inject it to the game with any DLL injector such as [GH injector](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/) :)**

# :rotating_light: TROUBLE SHOOTING

**Something goes wrong? We've prepared [Wiki](https://github.com/s3pt3mb3r/Dainsleif/wiki/Trouble-shooting) for you :sunglasses:**

# :scroll: Menu

You're accessible to the hack menu by pressing <kbd>INSERT</kbd> key on your keyboard. (While the menu is open, input to CSGO will be locked)

You can toggle on/off and tweak parameters in the tabs with the name of each hack.

![Hack menu](https://user-images.githubusercontent.com/33578715/91472649-5aa4a980-e8ca-11ea-8352-21b6400a494b.gif)

You can choose what hacks to be visible with the menu bar.
Several hacks're set to invisible by default.
![menu visible](https://user-images.githubusercontent.com/33578715/91351549-0f7f8d80-e81b-11ea-9216-e7d77a0566d1.png)

# :computer: Hacks

## Aimbot

This is the feature I can guarantee the highest quality in the hacks I offer here.

Turning this function on automatically lets you aim at enemy's head with 100% precision.
It select the closest enemy from where your crosshair is as a target.

Tweaking Smoothness bar affects the smoothness of sticking aim.
By changing the value of the Range bar, you can change the range in which the aimbot will react

![aimbot](https://user-images.githubusercontent.com/33578715/89108283-b31e8d80-d469-11ea-8e55-e4e469d74576.gif)

## Glow hack

This feature allows you to see both opponents and teammate's outline through walls.

![Glow hack](https://user-images.githubusercontent.com/33578715/89087560-48b51100-d3c7-11ea-9ada-8ef04acfa52c.png)

## ESP hack

With this hack turned on:
- Red and green lines from player's foot position towards every enemies and allies are displayed.
- Outline rectangles are drawn on the players

![esp](https://user-images.githubusercontent.com/33578715/92253522-30726d80-ef02-11ea-80d3-fdb7045851d0.png)

## Trigger bot

Once you turn this on, you no longer have to press left click when you engage them.
This feature will complete the job for you.

This is designed to use in conjunction with Aimbot.

## Anti recoil

This is basically a recoil control system.
It automatically calculate the in comming recoil and manipulate your angle to handle it.
But this doesn't guarantee the 100% accuracy.

![Anti recoil](https://user-images.githubusercontent.com/33578715/89087634-769a5580-d3c7-11ea-83b1-dc31345e7424.png)

## Minimap hack

Minimap hack will show you all enemy positions on the mini map as a red dot even if they're not in your sight which would be super cool.

![Minimap hack](https://user-images.githubusercontent.com/33578715/96349413-0c4da300-10e2-11eb-8ba9-b1965b1a7dfb.png)

## Anti AFK

This feature basically make you move randomly every 50 seconds so that you probably not gonna get kicked automatically I guess.

## FOV

You can change your field of view from 60 to 120 degrees.

# :put_litter_in_its_place: Uninstall

Since this cheat creates some setting files, u have to follow this to clear things up.

All setting files are located at `C:\Users\Public\Documents\Dainsleif`, so delete this folder and you're good.
Of course don't forget to delete exe file itself.

# :busts_in_silhouette: Contributors

I couldn't have got this far without them ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/l1m0n3"><img src="https://avatars1.githubusercontent.com/u/13360351?v=4" width="100px;" alt=""/><br /><sub><b>L1m0n3</b></sub></a><br /><a href="https://github.com/s3pt3mb3r/Dainsleif/commits?author=l1m0n3" title="Code">💻</a> <a href="#maintenance-l1m0n3" title="Maintenance">🚧</a></td>
    <td align="center"><a href="https://github.com/tomsa000"><img src="https://avatars2.githubusercontent.com/u/45645938?v=4" width="100px;" alt=""/><br /><sub><b>tomsa</b></sub></a><br /><a href="https://github.com/s3pt3mb3r/Dainsleif/commits?author=tomsa000" title="Code">💻</a> <a href="https://github.com/s3pt3mb3r/Dainsleif/issues?q=author%3Atomsa000" title="Bug reports">🐛</a> <a href="#ideas-tomsa000" title="Ideas, Planning, & Feedback">🤔</a></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

**Unintentional contributors:**

- [Osiris project](https://github.com/danielkrupinski/Osiris)
- [Hazedumper project](https://github.com/frk1/hazedumper)
- [Guided Hacking](https://guidedhacking.com)

# :hammer_and_wrench: Features being developed

**overall**
- [ ] Enemy's health indicator.
- [ ] 3D rectangle ESP.
- [ ] Chams feature. <- postponed

