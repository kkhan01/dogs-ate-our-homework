# dogs-ate-our-homework

Jeffrey Weng - Kyle Lin - Khinshan Khan

Period 10

---

### Description

A tetris game built using C and SDL. The goal is to get the most points you can before time runs out or you reach the top of the map.

---

### How to run

1. Install all libraries
2. Navigate to `./sdl_tests/sdlUbuntu/`
3. run `make`
4. run `./game`
5. Left/Right arrow key for movement. J/K for rotation.

---


### SDL Installation + Libraries

#### Ubuntu
 - *Pre-Installation*
   - Check to see if you have SDL:
     - `dpkg -l | grep sd` 
   - To find the current SDL version to install:
     - `apt-cache search libsdl2`
   - To find the current SDL_image version to install:
     - `apt-cache search libsdl2-image`
   - To find the current SDL_ttf version to install:
     - `apt-cache search libsdl2-ttf`
 - *Installation*
   - Install SDL2:
     - `apt-get install libsdl2-dev`
   - Install Image Library for PNG files:
     - `apt-get install libsdl2-image-dev`
   - Install SDL_ttf:
     - `apt-get install libsdl2-ttf-dev`
#### Mac OS-X (On Xcode)
  - *Installation*
    - Download the .dmg for SDL2 on the webpage: [SDL2 WebPage](https://www.libsdl.org/download-2.0.php#source)
    - Download the .dmg for SDL2 image on the webpage: [SDL2 Image Webpage](https://www.libsdl.org/projects/SDL_image/)
    - Download the .dmg for SDL2 ttf on the webpage: [SDL2 TTF Webpage](https://www.libsdl.org/projects/SDL_ttf/)
    - Open the .dmg file and drag the **SDL2.framework**, **SDL2_image.framework**, **SDL2_ttf.framework** into your **/Library/Frameworks** folder.
    - Open a new Xcode Project
      - Select SDL Project
      - Build Phases
      - Link Binary with Libraries
      - Press + and **command+shift+g** to find your SDL2.framework, SDL2_image.framework, and SDL2_ttf.framework
      - Add them.
  - *Post-Installation*
    - In your Xcode Window
      - Press Product
      	- Scheme
      - Edit Scheme...
        - Set custom working directory to your current working directory
    
---

### Bugs

1. Gravity works uniform on all pieces of the tetrimo rather than on the tetrimo
2. Sometimes the last row clearing gets disabled (re-enabled after clearing more rows)
3. Blocks can sort of phase throught the bottom if you move them alot on the last row (left and right)
4. Rotating fast enough might cause temporary suspension (gravity will work as soon as you fail to be at that speed)

---

### How to use log.sh

1. Open the terminal
2. Navigate to the root folder containing log.sh
3. Run `./log.sh "<lastF>" "<devmsg>"`

---

    
