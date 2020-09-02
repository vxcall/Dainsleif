![cpp](https://img.shields.io/badge/C%2B%2B-17-%23ff40d9.svg?style=flat)
![cmake](https://img.shields.io/badge/cmake-3.16-yellow)
![Game](https://img.shields.io/badge/Game-CS%3AGO-blue.svg?style=flat)
![License](http://img.shields.io/badge/license-MIT-yellowgreen.svg?style=flat)

<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-1-orange.svg?style=flat-square)](#busts_in_silhouette-Contributors)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

**[日本語版README](https://github.com/s3pt3mb3r/Dainsleif/blob/master/README_jp.md)**

[![Banner](https://user-images.githubusercontent.com/33578715/90916494-b9be7600-e413-11ea-8dee-ffea384afb2e.png)](https://github.com/s3pt3mb3r/Dainsleif)
Image's gifted by my big friend [@suzuharuR](https://twitter.com/suzuharuR)

# :zap: Dainsleif
First of all, if you are kind enough to motivate me, just **:star: star :star:** this project :) I would be very happy.

This is an internal cheat for **_Counter-Strike: Global Offensive_** I've been working on as my training of reverse engineering.

**Disclaimer**: Since I don't intend to make this a malicious software, this isn't considered to be performed in multi player mode. 
**We won't take any responsibility if a problem occurs because of this software.** Keep in that mind.

As of today, Dainsleif is a quite simple and tiny cheat, so you can use this as your reference if you want.

If you have any request or question, feel free to ask me through [issue](https://github.com/s3pt3mb3r/Dainsleif/issues).
Please understand that it may take a certain days because I'm doing this as completely my hobby without profit or reward, you know? 

### STILL WORKING: August 29, 2020

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
    - [Trigger bot](#trigger-bot)
    - [Anti recoil](#anti-recoil)
    - [Anti AFK](#anti-afk)
    - [FOV](#fov)
- [:busts_in_silhouette: Contributors](#busts_in_silhouette-Contributors)
- [:hammer_and_wrench: Features being developed](#hammer_and_wrench-features-being-developed)

# :syringe: How to build this hack

**requirement**
- [DirectxSDK](https://www.microsoft.com/en-au/download/details.aspx?id=6812)

You can select from two ways to build this hack.
I believe all you need in order to build this project except DirectxSDK is already included which is [MSDetour](https://github.com/microsoft/Detours), [ImGui](https://github.com/ocornut/imgui), and [toml11](https://github.com/ToruNiina/toml11).
They're in Dependencies directory.

**1. Build project using Cmake**

Run these commands below.

```
$ git clone https://github.com/s3pt3mb3r/Dainsleif.git
$ cd Dainsleif
$ mkdir build && cd build
$ cmake ..
$ make
```

Then your `Dainsleif.dll` should be in `/build` directory.

**2. Build project using Visual Studio 2019**

If you still have cmake, carry out following commands. (No? Then scroll down a bit)

```
$ git clone https://github.com/s3pt3mb3r/Dainsleif.git
$ cd Dainsleif
$ mkdir build && cd build
$ cmake .. -A Win32
```

You can find `Dainsleif.sln` in `/build` directory.

Once you load the project click `Build` -> `Build Dainsleif`.

Then your `Dainsleif.dll` should be in `/build/Debug` directory.

You reject to install cmake? Check [releases](https://github.com/s3pt3mb3r/Dainsleif/releases) and download relevant zip file.
(If latest release looks old, create an issue and ask me, I'll handle it.)

**Either way you get the `Dainsleif.dll`, you can now inject it to the game with any DLL injector such as [GH injector](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/) :)**

# :rotating_light: TROUBLE SHOOTING

**Something goes wrong? We've prepared [Wiki](https://github.com/s3pt3mb3r/Dainsleif/wiki/Trouble-shooting) for you :sunglasses:**

# :scroll: Menu

You're accessible to the hack menu by pressing <kbd>INSERT</kbd> key on your keyboard.

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

## Trigger bot

Once you turn this on, you no longer have to press left click when you engage them.
This feature will complete the job for you.

This is designed to use in conjunction with Aimbot.

## Anti recoil

This is basically a recoil control system.
It automatically calculate the in comming recoil and manipulate your angle to handle it.
But this doesn't guarantee the 100% accuracy.

![Anti recoil](https://user-images.githubusercontent.com/33578715/89087634-769a5580-d3c7-11ea-83b1-dc31345e7424.png)

## Anti AFK

This feature basically make you move randomly every 50 seconds so that you probably not gonna get kicked automatically I guess.

## FOV

You can change your field of view from 60 to 120 degrees.

# :busts_in_silhouette: Contributors

I couldn't have got this far without them ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

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

**Unintentional contributors:**
- [Osiris project](https://github.com/danielkrupinski/Osiris)
- [Hazedumper project](https://github.com/frk1/hazedumper)

# :hammer_and_wrench: Features being developed

**overall**
- [ ] Enemy's health indicator. <- postponed
- [ ] Chams feature. <- postponed

