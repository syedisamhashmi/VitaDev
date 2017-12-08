# **_VitaDev_**

## Read Please
#### I've seen that a couple of other people that aren't me have viewed this. That's great! Please, if you have **_any_** experience in developing for this target, **please** send me a message, I'm looking for advice and help and  I am open to suggestions. Thank you!
#### Also, the game being developed within is my attempt at a simple 2-D game remake, [Super Metroid](https://en.wikipedia.org/wiki/Super_Metroid).
#### Let it be noted that my graphics library does NOT have to be used in conjunction with the game files, the game files are an extenion upon the graphics library.
#### In addition, as can be seen, I am attempting to create my own graphics libraries from scratch. **_You can use Vita2D_**, but I have opted out of this, in order to further my learning experience. This includes rendering my own file format of rgba with a header, and my own functions to draw to the screen.

#### I am open to all advice.


## Compile Instructions
#### CMakeLists.txt file is attached.
#### Ensure that your vita is unlocked. For help with setting up a development environment, read more [here](https://vitasdk.org). For unlocking the vita, read more [here](https://henkaku.xyz). For the API, read [here](https://docs.vitasdk.org).
#### Run Cmake on the current directory with ```cmake .```.
#### You may then compile the program using ```make```.
#### Using an FTP client, transfer the _.vpk_ file over.

## Assets
#### The assets seen are taken from a sprite sheet containing all sprites from the original [Super Metroid](https://en.wikipedia.org/wiki/Super_Metroid) for the SNES. I do not claim ownership to any of the material.
#### The RGBA file format associated with this project is created using a PNG to RGBA converter, then the RGBA files are custom made by inserting three "words" (4 bytes) into the beginning of each file. The first word contains the height of the image, the second word contains the width, and the third word contains the total number of animation states present within the image. This RGBA file can then be preloaded into the system, loaded, or directly read from memory and then displayed using the functions in the filesystem and graphics namespaces.

## Documentation
### Please note that this documentation does not include or describe the packaged Vita2d calls that lie within the code. Those are there for testing purposes and their documentation and source can be found [here](https://github.com/xerpi/libvita2d/tree/master/libvita2d)
#### namespace (functions, members)
#### colors ([functions](#colorsF), members)
#### filesystem ([functions](#filesystemF), members)
#### font ([functions](#fontF), members)
#### game ([functions](#gameF), members)
#### graphics ([functions](#graphicsF), members)
#### io ([functions](#ioF), members)
#### preloaded ([functions](#preloadedF), members)
#### utils ([functions](#utilsF), members)

## Functions
### <a name="colorsF">colors</a>
##### ```uint32_t RGBA832(unsigned char r, unsigned char g, unsigned char b, unsigned char a)``` - Generates a 32 bit formatted RGBA color.
##### ```uint16_t RGB16(unsigned char r, unsigned char g, unsigned char b)``` - Generates a 16 bit formatted RGB color, no alpha.
### [filesystem](#filesystemF)
##### ```filesystem::Texture* loadFile(std::string filename)``` - Returns a Texture*. The pixels** of the Texture* contains all RGBA values of the texture loaded and the texture is formatted to width and height of the corresponding rgba file.
##### ```filesystem::Header* readHeader(SceUID file)``` - Returns a Header*. This reads the 3 word header of a custom made RGBA file, and returns it as an object that can be attributed to a Texture object.
##### [```filesystem::Texture* preload(filesystem::preloaded_animations animation)```](#preloadInstructions) - Returns a Texture*. This Texture* can be used in conjunction with the preload graphics display functions to draw a texture. In order to use this function, you must declare a filesystem::preloaded_animations type, you must create an entry for the preloaded texture within the preloaded.hpp file, and lastly you must add a condition case in ```graphics::draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` with the format ```if(texture->preloaded == filesystem::preloaded_animations) animation_to_draw = preloaded::animation;```.
### [font](#fontF)
##### No functions.
### [game](#gameF)
##### ```void drawPlayer()``` - Draws the player, applies friction, updates animation states, changes animation states.
##### ```void checkInput(SceCtrlData pad)``` - Reads input from the SceCtrlData structure passed in.
##### ```void applyFriction()``` - Applies a negative velocity force to ensure that the playeer will slow down if no force is given from the user, this is done automatically in drawPlayer.
##### ```void checkPlayerMaxSpeed()``` - Ensures that the player does not surpass the set value of  ```game::PLAYER_CURRENT_MAX_MOVE_SPEED```.
### [graphics](#graphicsF)
##### ```void setUp()``` - Turns off basic functionality from the PS Vita, such as the dimming and timeout of the display.
##### ```void initializeFramebuffers()``` - Initializes two framebuffers, these should be freed prior to ending the program.
##### ```void freeFramebuffers()``` - Frees the initialized frame buffers.
##### ```void swapFramebuffers()``` - Swaps the initialized frame buffers, should preferably be done upon a vertical blank from the system.
##### ```void clearScreen()``` - Sets the framebuffer's color (base member variable) completely to white.
##### ```void colorScreen(uint16_t color)``` - Sets the framebuffers's color (base member variable) completely to the supplied color. This color may be obtained from ```colors::RGB16(unsigned char r, unsigned char g, unsigned char b)``` or may be self-formatted. 
##### ```void draw_pixel(uint32_t x, uint32_t y, uint32_t color)``` - Sets a pixel at a given x and y coordinate in the current framebuffer to a supplied color. This color may be obtained from ```colors::RGBA832(unsigned char r, unsigned char g, unsigned char b, unsigned char a)``` or may be self-formatted.
##### ```void draw_texture_loaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` - Draws a loaded texture using the provided Texture* at a given position x and y.
##### ```void draw_texture_loaded_scale(filesystem::Texture* texture, unsigned int posX, unsigned int posY, double newHeightScale, double newWidthScale)``` - Draws a loaded texture using the provided Texture* at a given position x and y after scaling the texture with the provided scale proportions in the width and height directions.
##### ```void draw_texture_loaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)``` - Draws a portion of a loaded texture using the provided Texture* and the provided portion number at a given position x and y. Useful for animation.
##### ```void draw_texture_loaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)``` - Draws a portion loaded texture using the provided Texture* using the provided portion number at a given position x and y after scaling the texture with the provided scale proportions in the width and height directions. Useful for animation.
##### ```void draw_texture_file(std::string filename, unsigned int posX, unsigned int posY)``` - Draws a texture directly from a file at a given position x and y. (Note: This only works with formatted RGBA files)
##### ```void draw_texture_file_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)``` - Draws a portion of a texture using the portion number provided directly from a file at a given position x and y. Useful for animation. (Note: This only works with formatted RGBA files)
##### ```void draw_texture_file_scale_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)``` - Draws a portion of a texture using the portion number provided directly from a file at a given position x and y and scaled using the provided width and height scales. Useful for animation. (Note: This only works with formatted RGBA files)
##### ```void draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` - Draws a preloaded texture at a given coordinate x and y. (Note: This texture MUST be preloaded following the steps explained [here](#preloadInstructions)
##### ```void draw_texture_preloaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)``` - Draws a portion of a preloaded texture using the provided portion number at a given coordinate x and y. (Note: This texture MUST be preloaded following the steps explained [here](#preloadInstructions)
##### ```void draw_texture_preloaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)``` - Draws a portion of a preloaded texture using the provided portion number at a given coordinate x and y that will also be scaled using the provided new width and height scales. (Note: This texture MUST be preloaded following the steps explained [here](#preloadInstructions)
##### ```game::Position checkBounds(int posX, int posY, unsigned int x, unsigned int y)``` - Returns a ```game::Position``` object that represents bounds that are drawable to the screen. This bound is a position representing the coordinate (posX + x, posY + y). This stops segmentation faults in which a position out the bounds of the framebuffer is written to.
### [io](#ioF)
##### ```void getio()``` - Reads all data from buttons and touchscreen.
### [preloaded](#preloadedF)
##### No functions.
### [utils](#utilsF)
##### ```unsigned int align_mem(unsigned int addr, unsigned int align)``` - Alignes an address to an align offset.
##### ```int abs(int val)``` - Returns an integer representing the absolute value of the parameter val.
##### ```double abs(double val)``` - Returns a double representing the absolute value of the parameter val.
##### ```void printc(int x, int y, uint32_t color, char c)``` - Prints a character to a given x and y coordinate.
##### ```void prints(int x, int y, uint32_t color, const char *string)``` - Prints a string to a given x and y coordinate.
##### ```void printsf(int x, int y, uint32_t color, const char *s, ...)``` - Prints a formatted string to a given x and y coordinate.





