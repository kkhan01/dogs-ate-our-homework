# dogs-ate-our-homework

---

### How to use log.sh

1. Open the terminal
2. Navigate to the root folder containing log.sh
3. Run `./log.sh "<lastF>" "<devmsg>"`

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
    


    
