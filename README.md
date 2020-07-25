# HACK4CSGO :zap:
Internal trainer for CSGO I've been working on as my training of reverse engineering.
Since I don't intend to make this a malicious software, **this isn't considered to be performed in multiplayer mode**. Keep in that mind plz.

If you are enough kind to motivate me, just **star** this project :) I would be very happy.

If you have any question about this project, feel free to ask me through [issue](https://github.com/s3pt3mb3r/HACK4CSGO/issues).
### STILL WORKING: July 26, 2020

#Table of contents

- [How to use this hack](#how-to-use-this-hack-key)
    - [Download DLL itself from release](#1-download-dll-itself-from-release)
    - [Build DLL from source code](#2-build-dll-from-source-code)
- [Menu](#menu-green_book)
- [Hakcs](#hacks)
    - [Aimbot](#aimbot)
    - [Glow hack](#glow-hack)
    - [Trigger bot](#trigger-bot)
    - [Neutralize recoil](#neutralize-recoil)
- [Features being developed](#features-being-developed)
- [Contributors](#contributors)


# How to use this hack :key:

### 1. Download DLL itself from [release](https://github.com/s3pt3mb3r/HACK4CSGO/releases)

### 2. Build DLL from source code

I believe all you need in order to build this project is already included which is [MSDetour](https://github.com/microsoft/Detours), [ImGui](https://github.com/ocornut/imgui), and [toml11](https://github.com/ToruNiina/toml11).
They're in Dependencies directory.

In the project root, run these commands below.
```
$ mkdir build && cd build
$ cmake ..
$ make
```

### Either way you get the HACK4CSGO.dll, you can now inject it to the game with any DLL injector such as [GH injector](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/) :)


# Menu :green_book:

You're accessible to the hack menu by pressing **INSERT** key on your keyboard.
**But you may only access it in game. Even though you press INSERT when you are in main menu, nothing happens**

![Hack menu](https://user-images.githubusercontent.com/33578715/88310005-c03ccd80-cd41-11ea-980e-a7f1fa639597.png)

# Hacks

## Aimbot

If you turn it on, it will automatically lock aim at a closest enemy unless you step really away from him.
When you are away enough from enemies you get the control of angle back.

- [x] Check if bDormant is true
- [x] Aiming smoother rather than instantly stick crosshair to the target
- [ ] Require more humanistic way to aim
- [ ] Aim at closest enemy based on the position of crosshair not physical distance so that user can move their angle most of the time

## Glow hack

This feature allows you to see both opponents and teammate's outline through walls.

- [x] want it to be capable of setting specific color of outline.

## Trigger bot

Once you turn this on, you no longer have to press left click when you engage them.
This feature will complete the job for you.

## Neutralize recoil

This is basically a recoil control system.
It automatically calculate the in comming recoil and manipulate your angle to handle it.
But this doesn't guarantee the 100% accuracy.

# Features being developed

- [x] Aim bot
- [x] Glow hack
- [x] Trigger bot
- [x] Neutralize recoil
- [x] GUI menu for more better user experience (by hooking Directx9 endScene function)
- [x] Close GUI menu whenever user gets outta in game and goes back to main menu
- [x] Save setting automatically that user inputs to toml file
- [x] Add a "reset setting" button
- [ ] Display alert when dll is successfully injected
- [ ] Place quit button on menu bar.
- [ ] Enemy's health indicator
- [ ] ESP (draw line by myself)
- [ ] teleportation hack (not sure if it's possible without getting detected)

#Contributors
- [l1m0n3](https://github.com/l1m0n3)