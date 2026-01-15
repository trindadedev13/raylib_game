# raylib_game
 - Me and @ThDev-Only Studies with Raylib

# Building and Running
## Desktop
  To build it for desktop, make sure you has gcc/clang snd raylib installed, also make.  
  ```shellscript
  make
  make run # to run
  ```
## Android
  To build for android, you need have installed android-sdk, android-ndk and openjdk (17)  
  if you have it all installed, so you just need do adjust those [VARS](https://github.com/trindadedev13/raylib_game/blob/main/Makefile.Android#L58) at Makefile.Android  
  ```shellscript
  make -f Makefile.Android
  ```
  if everything goes well, you'll notice a raylib_game.apk.
