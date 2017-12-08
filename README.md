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
#### Run Cmake on the current directory with ```cpp cmake .```.
#### You may then compile the program using ```cpp make```.
#### Using an FTP client, transfer the _.vpk_ file over.

## Assets
#### The assets seen are taken from a sprite sheet containing all sprites from the original [Super Metroid](https://en.wikipedia.org/wiki/Super_Metroid) for the SNES. I do not claim ownership to any of the material.
#### The RGBA file format associated with this project is created using a PNG to RGBA converter, then the RGBA files are custom made by inserting three "words" (4 bytes) into the beginning of each file. The first word contains the height of the image, the second word contains the width, and the third word contains the total number of animation states present within the image. This RGBA file can then be preloaded into the system, loaded, or directly read from memory and then displayed using the functions in the filesystem and graphics namespaces.

## Documentation
### Please note that this documentation does not include or describe the packaged Vita2d calls that lie within the code. Those are there for testing purposes and their documentation and source can be found [here](https://github.com/xerpi/libvita2d/tree/master/libvita2d)
#### namespace (functions, members)
#### colors ([functions](#colorsF), [members](#colorsM))
#### filesystem ([functions](#filesystemF), [members](#filesystemM))
#### font ([functions](#fontF), [members](#fontM))
#### game ([functions](#gameF), [members](#gameM))
#### graphics ([functions](#graphicsF), [members](#graphicsM))
#### io ([functions](#ioF), [members](#ioM))
#### preloaded ([functions](#preloadedF), [members](#preloadedM))
#### utils ([functions](#utilsF), [members](#utilsM))

## Functions
### <a name="colorsF">colors</a>
##### ```cpp uint32_t RGBA832(unsigned char r, unsigned char g, unsigned char b, unsigned char a)``` - Generates a 32 bit formatted RGBA color.
##### ```cpp uint16_t RGB16(unsigned char r, unsigned char g, unsigned char b)``` - Generates a 16 bit formatted RGB color, no alpha.
### <a name="filesystemF">filesystem</a>
##### ```cpp filesystem::Texture* loadFile(std::string filename)``` - Returns a Texture*. The pixels** of the Texture* contains all RGBA values of the texture loaded and the texture is formatted to width and height of the corresponding rgba file.
##### ```cpp filesystem::Header* readHeader(SceUID file)``` - Returns a Header*. This reads the 3 word header of a custom made RGBA file, and returns it as an object that can be attributed to a Texture object.
##### <a name="preloadInstructions">```filesystem::Texture* preload(filesystem::preloaded_animations animation)```</a> - Returns a Texture*. This Texture* can be used in conjunction with the preload graphics display functions to draw a texture. In order to use this function, you must declare a filesystem::preloaded_animations type, you must create an entry for the preloaded texture within the preloaded.hpp file, and lastly you must add a condition case in ```cpp graphics::draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` with the format ```cpp if(texture->preloaded == filesystem::preloaded_animations) animation_to_draw = preloaded::animation;```.
### <a name="fontF">font</a>
##### No functions.
### <a name="gameF">game</a>
##### ```cpp void drawPlayer()``` - Draws the player, applies friction, updates animation states, changes animation states.
##### ```cpp void checkInput(SceCtrlData pad)``` - Reads input from the SceCtrlData structure passed in.
##### ```cpp void applyFriction()``` - Applies a negative velocity force to ensure that the playeer will slow down if no force is given from the user, this is done automatically in drawPlayer.
##### ```cpp void checkPlayerMaxSpeed()``` - Ensures that the player does not surpass the set value of  ```game::PLAYER_CURRENT_MAX_MOVE_SPEED```.
### <a name="graphicsF">graphics</a>
##### ```cpp void setUp()``` - Turns off basic functionality from the PS Vita, such as the dimming and timeout of the display.
##### ```cpp void initializeFramebuffers()``` - Initializes two framebuffers, these should be freed prior to ending the program.
##### ```cpp void freeFramebuffers()``` - Frees the initialized frame buffers.
##### ```cpp void swapFramebuffers()``` - Swaps the initialized frame buffers, should preferably be done upon a vertical blank from the system.
##### ```cpp void clearScreen()``` - Sets the framebuffer's color (base member variable) completely to white.
##### ```cpp void colorScreen(uint16_t color)``` - Sets the framebuffers's color (base member variable) completely to the supplied color. This color may be obtained from ```colors::RGB16(unsigned char r, unsigned char g, unsigned char b)``` or may be self-formatted. 
##### ```cpp void draw_pixel(uint32_t x, uint32_t y, uint32_t color)``` - Sets a pixel at a given x and y coordinate in the current framebuffer to a supplied color. This color may be obtained from ```cpp colors::RGBA832(unsigned char r, unsigned char g, unsigned char b, unsigned char a)``` or may be self-formatted.
##### ```cpp void draw_texture_loaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` - Draws a loaded texture using the provided Texture* at a given position x and y.
##### ```cpp void draw_texture_loaded_scale(filesystem::Texture* texture, unsigned int posX, unsigned int posY, double newHeightScale, double newWidthScale)``` - Draws a loaded texture using the provided Texture* at a given position x and y after scaling the texture with the provided scale proportions in the width and height directions.
##### ```cpp void draw_texture_loaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)``` - Draws a portion of a loaded texture using the provided Texture* and the provided portion number at a given position x and y. Useful for animation.
##### ```cpp void draw_texture_loaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)``` - Draws a portion loaded texture using the provided Texture* using the provided portion number at a given position x and y after scaling the texture with the provided scale proportions in the width and height directions. Useful for animation.
##### ```cpp void draw_texture_file(std::string filename, unsigned int posX, unsigned int posY)``` - Draws a texture directly from a file at a given position x and y. (Note: This only works with formatted RGBA files)
##### ```cpp void draw_texture_file_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)``` - Draws a portion of a texture using the portion number provided directly from a file at a given position x and y. Useful for animation. (Note: This only works with formatted RGBA files)
##### ```cpp void draw_texture_file_scale_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)``` - Draws a portion of a texture using the portion number provided directly from a file at a given position x and y and scaled using the provided width and height scales. Useful for animation. (Note: This only works with formatted RGBA files)
##### ```cpp void draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` - Draws a preloaded texture at a given coordinate x and y. (Note: This texture MUST be preloaded following the steps explained [here](#preloadInstructions)
##### ```cpp void draw_texture_preloaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)``` - Draws a portion of a preloaded texture using the provided portion number at a given coordinate x and y. (Note: This texture MUST be preloaded following the steps explained [here](#preloadInstructions)
##### ```cpp void draw_texture_preloaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)``` - Draws a portion of a preloaded texture using the provided portion number at a given coordinate x and y that will also be scaled using the provided new width and height scales. (Note: This texture MUST be preloaded following the steps explained [here](#preloadInstructions)
##### ```cpp game::Position checkBounds(int posX, int posY, unsigned int x, unsigned int y)``` - Returns a ```game::Position``` object that represents bounds that are drawable to the screen. This bound is a position representing the coordinate (posX + x, posY + y). This stops segmentation faults in which a position out the bounds of the framebuffer is written to.
### <a name="ioF">io</a>
##### ```void getio()``` - Reads all data from buttons and touchscreen.
### <a name="preloadedF">preloaded</a>
##### No functions.
### <a name="utilsF">utils</a>
##### ```cpp unsigned int align_mem(unsigned int addr, unsigned int align)``` - Alignes an address to an align offset.
##### ```cpp int abs(int val)``` - Returns an integer representing the absolute value of the parameter val.
##### ```cpp double abs(double val)``` - Returns a double representing the absolute value of the parameter val.
##### ```cpp void printc(int x, int y, uint32_t color, char c)``` - Prints a character to a given x and y coordinate.
##### ```cpp void prints(int x, int y, uint32_t color, const char *string)``` - Prints a string to a given x and y coordinate.
##### ```cpp void printsf(int x, int y, uint32_t color, const char *s, ...)``` - Prints a formatted string to a given x and y coordinate.

## Members
### <a name="colorsM">colors</a>
##### ```cpp uint32_t RED32``` - An unsigned 32 bit integer representing the RGBA value of red.
##### ```cpp uint32_t GREEN32``` - An unsigned 32 bit integer representing the RGBA value of green.
##### ```cpp uint32_t BLUE32``` - An unsigned 32 bit integer representing the RGBA value of blue.
##### ```cpp uint32_t CYAN32``` - An unsigned 32 bit integer representing the RGBA value of cyan.
##### ```cpp uint32_t LIME32``` - An unsigned 32 bit integer representing the RGBA value of lime.
##### ```cpp uint32_t PURPLE32``` - An unsigned 32 bit integer representing the RGBA value of purple.
##### ```cpp uint32_t WHITE32``` - An unsigned 32 bit integer representing the RGBA value of white.
##### ```cpp uint32_t BLACK32``` - An unsigned 32 bit integer representing the RGBA value of black.
##### ```cpp uint16_t RED16```  - An unsigned 16 bit integer representing the RGB value of red.
##### ```cpp uint16_t GREEN16```  - An unsigned 16 bit integer representing the RGB value of green.
##### ```cpp uint16_t BLUE16```  - An unsigned 16 bit integer representing the RGB value of blue.
##### ```cpp uint16_t CYAN16```  - An unsigned 16 bit integer representing the RGB value of cyan.
##### ```cpp uint16_t LIME16```  - An unsigned 16 bit integer representing the RGB value of lime.
##### ```cpp uint16_t PURPLE16```  - An unsigned 16 bit integer representing the RGB value of purple.
##### ```cpp uint16_t WHITE16```  - An unsigned 16 bit integer representing the RGB value of white.
##### ```cpp uint16_t BLACK16```  - An unsigned 16 bit integer representing the RGB value of black.
### <a name="filesystemM">filesystem</a>
##### ```cpp preloaded_animations``` - Enumerated type representing all types of preloaded animations. Values are currently 
##### > * ```cpp NOT_PRELOADED``` - Represents a texture type that is not currently preloaded.
##### > * ```cpp IDLE_ANIMATION``` - Represents the idle animation texture.
##### > * ```cpp RIGHT_RUN_ANIMATION``` - Represents the right run animation texture.
##### > * ```cpp LEFT_RUN_ANIMATION``` - Represents the left run animation texture.
### <a name="fontM">font</a>
##### ```cpp unsigned char msx_font``` - An MSX stylized font set.
##### ```cpp unsigned char bitmapFont``` - Not interactable with current project. May be used in Vita2d, though.
### <a name="gameM">game</a>
##### ```cpp unsigned int PLAYER_HEIGHT``` - Represents the height of the player in the game, typically a constant.
##### ```cpp unsigned int PLAYER_WIDTH``` - Represents the height of the player in the game, typically a constant.
##### ```cpp double PLAYER_BASE_MOVE_SPEED``` - Represents the base movement speed of the player in the game.
##### ```cpp double PLAYER_MAX_MOVE_SPEED``` - Represents the maximum allowed movement speed of the player in the game.
##### ```cpp double PLAYER_CURRENT_MAX_MOVE_SPEED``` - Represents the current maximum allowed movement speed of the player in the game. As this may change during the game, power-ups, etc..
##### ```cpp double SPEED_MODIFIER``` - Represents a modifier that may affect the speed of a player (different terrain, etc.).
##### ```cpp double FRICTION``` - Represents a modifier for friction that affects the speed of a player.
##### ```cpp int MAX_AXIS_VALUE``` - Represents the maximum value that the joysticks may reach.
##### ```cpp gamestate``` - Enumerated type representing the possible states of the game. Values are currently 
##### > * ```cpp PAUSED``` - Represents a gamestate in which the game is currently paused.
##### > * ```cpp UNPAUSED``` - Represents a gamestate in which the game is currently unpaused.
##### ```movestate``` - Enumerated type representing the possible movestates of the player. Values are currently 
> * ```cpp IDLE``` - Represents a movestate in which the player is not moving.
> * ```cpp MOVING_RIGHT``` - Represents a gamestate in which the player is moving to the right.
> * ```cpp MOVING_LEFT``` - Represents a gamestate in which the player is moving to the left.
##### ```cpp gamestate state``` - Represents the current state of the game.
##### ```cpp filesystem::Texture* rightrun``` - Preloaded texture for the rightrun animation.
##### ```cpp filesystem::Texture* leftrun``` - Preloaded texture for the leftrun animation.
##### ```cpp filesystem::Texture* idle``` - Preloaded texture for the idle animation.
##### ```cpp signed char lx``` - Signed character representing the left analog X value.
##### ```cpp signed char ly``` - Signed character representing the left analog Y value.
##### ```cpp signed char rx``` - Signed character representing the right analog X value.
##### ```cpp signed char ry``` - Signed character representing the right analog Y value.
### <a name="graphicsM">graphics</a>
##### ```cpp int SCREEN_W``` - Value representing the width of the PS Vita screen in pixels.
##### ```cpp int SCREEN_H``` - Value representing the height of the PS Vita screen in pixels.
##### ```cpp int DISPLAY_STRIDE_IN_PIXELS``` - Value representing the stride of the display of the PS Vita screen in pixels.
##### ```cpp SceDisplayFrameBuf fb``` - Array (size two) that will be containing the frame buffers.
##### ```cpp SceUID fb_memuid``` - Array (size two) that will be containing the UID's for the frame buffers in order to release them later.
##### ```cpp int cur_fb``` - Integer representing the current framebuffer being displayed.
### <a name="ioM">io</a>
##### ```cpp SceCtrlData pad``` - Structure containing all the controls and their current states (pressed/unpressed).
##### ```cpp SceTouchData touch``` - Structure containing the touchscreen and current screen touch information.
### <a name="preloadedM">preloaded</a>
##### ```cpp unsigned char idle``` - Array containing all RGBA values for the preloaded idle image.
##### ```cpp unsigned char rightrun``` - Array containing all RGBA values for the preloaded rightrun image.
##### ```cpp unsigned char leftrun``` - Array containing all RGBA values for the preloaded leftrun image.
### <a name="utilsM">utils</a>
##### ```cpp unsigned char* fontStyle``` - The current fontStyle to be used in the project. (note: automatically set in utils.cpp)


