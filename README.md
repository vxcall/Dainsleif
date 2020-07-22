# HACK4CSGO
Internal trainer for CSGO I've been working on as my training of reverse engineering and not completed yet.
Since I don't intend to make this a malicious software, this isn't considered to be performed in multiplayer mode. Keep in that mind plz.

#### STILL WORKING: July 23, 2020

# How to build this project

I really wonder is there anyone who wanna build use this shit, but anyway i have to mention this topic just in case.

I believe all you need in order to build this project is already included which is [MSDetour](https://github.com/microsoft/Detours) and [ImGui](https://github.com/ocornut/imgui).
They're in Dependencies directory.

In the project root, run these commands below.
```
$ mkdir build && cd build
$ cmake ..
$ make
```

Then you will have HACK4CSGO.dll in the build directory. Just play it with DLL injector:)

# Menu

**You're accessible to the hack menu by pressing INSERT key on your keyboard.**
This menu feature is one of the most unstable thing in this project now. You can use it yet any error or unexpected behavior can be occurred.

# Aimbot

If you turn it on, it will automatically lock aim at a closest enemy unless you step really away from him.
When you are away enough from enemies you get the control of angle back.

- [x] Check if bDormant is true
- [x] Aiming smoother rather than instantly stick crosshair to the target
- [ ] Require more humanistic way to aim
- [ ] Aim at closest enemy based on the position of crosshair not physical distance so that user can move their angle most of the time

# Glow hack

This feature allows you to see both opponents and teammate's outline through walls.

- [x] want it to be capable of setting specific color of outline.

# Trigger bot

Once you turn this on, you no longer have to press left click when you engage them.
This feature will complete the job for you.

# Neutralize recoil

This is basically a recoil control system.
It automatically calculate the in comming recoil and manipulate your angle to handle it.
But this doesn't guarantee the 100% accuracy.

# Features being developed

- [x] Aim bot
- [x] Glow hack
- [x] Trigger bot
- [x] Neutralize recoil
- [ ] GUI menu for more better user experience (by hooking Directx9 endScene function)
- [ ] Enemy's health indicator
- [ ] ESP (drow line by myself)
- [ ] teleport hack (not sure if it's possible without getting detected)