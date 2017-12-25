**_VitaDev_**
=============

## Read Please
#### I've seen that a couple of other people that aren't me have viewed this. That's great! Please, if you have **_any_** experience in developing for this target, **please** send me a message, I'm looking for advice and help and  I am open to suggestions. Thank you!
#### Also, the game being developed within is my attempt at a simple 2-D game remake, [Super Metroid](https://en.wikipedia.org/wiki/Super_Metroid).
#### Let it be noted that my graphics library does NOT have to be used in conjunction with the game files, the game files are an extenion upon the graphics library.
#### In addition, as can be seen, I am attempting to create my own graphics libraries from scratch. **_You can use Vita2D_**, but I have opted out of this, in order to further my learning experience. This includes rendering my own file format of rgba with a header, and my own functions to draw to the screen.

#### I am open to all advice.


Compile Instructions
====================
#### CMakeLists.txt file is attached.
#### Ensure that your vita is unlocked. For help with setting up a development environment, read more [here](https://vitasdk.org). For unlocking the vita, read more [here](https://henkaku.xyz). For the API, read [here](https://docs.vitasdk.org).
#### Run Cmake on the current directory with ``` cmake .```.
#### You may then compile the program using ``` make```.
#### Using an FTP client, transfer the _.vpk_ file over.

Assets
======
#### The assets seen are taken from a sprite sheet containing all sprites from the original [Super Metroid](https://en.wikipedia.org/wiki/Super_Metroid) for the SNES. I do not claim ownership to any of the material.
#### The RGBA file format associated with this project is created using a PNG to RGBA converter, then the RGBA files are custom made by inserting three "words" (4 bytes) into the beginning of each file. The first word contains the height of the image, the second word contains the width, and the third word contains the total number of animation states present within the image. This RGBA file can then be preloaded into the system, loaded, or directly read from memory and then displayed using the functions in the filesystem and graphics namespaces.

Documentation
==============
### Please note that this documentation does not include or describe the packaged Vita2d calls that lie within the code. Those are there for testing purposes and their documentation and source can be found [here](https://github.com/xerpi/libvita2d/tree/master/libvita2d)

|namespace |        functions           |         members         |           classes          |
|:--------:|:--------------------------:|:-----------------------:|:--------------------------:|
|colors|[functions](#colorsF)|[members](#colorsM)|[classes](#colorsC)|
|filesystem|[functions](#filesystemF)|[members](#filesystemM) |[classes](#filesystemC)|
|font|[functions](#fontF)|[members](#fontM)|[classes](#fontC)|
|game|[functions](#gameF)|[members](#gameM)|[classes](#gameC)|
|graphics|[functions](#graphicsF)|[members](#graphicsM)|[classes](#graphicsC)|
|io|[functions](#ioF)|[members](#ioM)| [classes](#ioC)|
|preloaded|[functions](#preloadedF)|[members](#preloadedM)|[classes](#preloadedC)|
|utils|[functions](#utilsF)|[members](#utilsM)|[classes](#utilsC)|

---
---
## Functions
### <a name="colorsF">colors</a>
##### ``` uint32_t RGBA832(unsigned char r, unsigned char g, unsigned char b, unsigned char a)``` - Generates a 32 bit formatted RGBA color.
##### ```uint16_t RGB16(unsigned char r, unsigned char g, unsigned char b)``` - Generates a 16 bit formatted RGB color, no alpha.
##### ```uint32_t pixelToRGBA832(filesystem::pixel p)``` - Generates a 32 bit formatted RGBA color from a provided [```filesystem::pixel```](#pixelC).
### <a name="filesystemF">filesystem</a>
##### ```filesystem::Texture* loadFile(std::string filename)``` - Returns a Texture*. The pixels** of the Texture* contains all RGBA values of the texture loaded and the texture is formatted to width and height of the corresponding rgba file.
##### ```filesystem::Header* readHeader(SceUID file)``` - Returns a Header*. This reads the 3 word header of a custom made RGBA file, and returns it as an object that can be attributed to a Texture object.
##### <a name="preloadInstructions">```filesystem::Texture* preload(filesystem::preloaded_animations animation)```</a> - Returns a Texture*. This Texture* can be used in conjunction with the preload graphics display functions to draw a texture. In order to use this function, you must declare a filesystem::preloaded_animations type, you must create an entry for the preloaded texture within the preloaded.hpp file, and lastly you must add a condition case in ```graphics::draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)``` with the format ```if(texture->preloaded == filesystem::preloaded_animations) animation_to_draw = preloaded::animation;```.
##### ```filesystem::Header* readHeader(SceUID file)``` - Returns a Header*. This reads the 3 word header of a custom made RGBA file, and returns it as an object that can be attributed to a Texture object.
##### <a name="preloadTilesF">```void preloadTiles()```</a> - This function will assign the [```tiles```](#gameTilesM) member of the game namespace to a static pointer of an array containing [```Texture*```](#textureClassObject).


### <a name="fontF">font</a>
##### No functions.
### <a name="gameF">game</a>
##### ```void drawPlayer()``` - Draws the player, applies friction, updates animation states, changes animation states.
##### ```void checkInput(SceCtrlData pad)``` - Reads input from the SceCtrlData structure passed in.
##### ```void applyFriction()``` - Applies a negative velocity force to ensure that the playeer will slow down if no force is given from the user, this is done automatically in drawPlayer.
##### ```void checkPlayerMaxSpeed()``` - Ensures that the player does not surpass the set value of  ```game::PLAYER_CURRENT_MAX_MOVE_SPEED```.
### <a name="graphicsF">graphics</a>
##### ```void setUp()``` - Turns off basic functionality from the PS Vita, such as the dimming and timeout of the display.
##### ```void initializeFramebuffers()``` - Initializes two framebuffers, these should be freed prior to ending the program.
##### ```void freeFramebuffers()``` - Frees the initialized frame buffers.
##### ```void swapFramebuffers()``` - Swaps the initialized frame buffers, should preferably be done upon a vertical blank from the system.
##### ```void clearScreen()``` - Sets the framebuffer's color (base member variable) completely to white.
##### ```void colorScreen(uint16_t color)``` - Sets the framebuffers's color (base member variable) completely to the supplied color. This color may be obtained from ```colors::RGB16(unsigned char r, unsigned char g, unsigned char b)``` or may be self-formatted.
##### ```void draw_pixel(uint32_t x, uint32_t y, uint32_t color)``` - Sets a pixel at a given x and y coordinate in the current framebuffer to a supplied color. This color may be obtained from ```colors::RGBA832(unsigned char r, unsigned char g, unsigned char b, unsigned char a)``` or may be self-formatted.
##### ```uint32_t getPixel(uint32_t x, uint32_t y)``` - Gets a unsigned thirty-two bit color at a given x and y coordinate in the current framebuffer.
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
##### ```void draw_tile(unsigned int tileNum, unsigned int x, unsigned int y)``` - Draws the specified tile number from [tiles](#tilesM) to the screen at the specified x and y position.
##### ```game::Position checkBounds(int posX, int posY, unsigned int x, unsigned int y)``` - Returns a ```game::Position``` object that represents bounds that are drawable to the screen. This bound is a position representing the coordinate (posX + x, posY + y). This stops segmentation faults in which a position out the bounds of the framebuffer is written to.
### <a name="ioF">io</a>
##### ```void getio()``` - Reads all data from buttons and touchscreen.
### <a name="preloadedF">preloaded</a>
##### No functions.
### <a name="utilsF">utils</a>
##### ```unsigned int align_mem(unsigned int addr, unsigned int align)``` - Alignes an address to an align offset.
##### ```int abs(int val)``` - Returns an integer representing the absolute value of the parameter val.
##### ```double abs(double val)``` - Returns a double representing the absolute value of the parameter val.
##### ```void printc(int x, int y, uint32_t color, char c)``` - Prints a character to a given x and y coordinate.
##### ```void prints(int x, int y, uint32_t color, const char *string)``` - Prints a string to a given x and y coordinate.
##### ```void printsf(int x, int y, uint32_t color, const char *s, ...)``` - Prints a formatted string to a given x and y coordinate.
---
## Members
### <a name="colorsM">colors</a>
##### ```uint32_t RED32``` - An unsigned 32 bit integer representing the RGBA value of red.
##### ```uint32_t GREEN32``` - An unsigned 32 bit integer representing the RGBA value of green.
##### ```uint32_t BLUE32``` - An unsigned 32 bit integer representing the RGBA value of blue.
##### ```uint32_t CYAN32``` - An unsigned 32 bit integer representing the RGBA value of cyan.
##### ```uint32_t LIME32``` - An unsigned 32 bit integer representing the RGBA value of lime.
##### ```uint32_t PURPLE32``` - An unsigned 32 bit integer representing the RGBA value of purple.
##### ```uint32_t WHITE32``` - An unsigned 32 bit integer representing the RGBA value of white.
##### ```uint32_t BLACK32``` - An unsigned 32 bit integer representing the RGBA value of black.
##### ```uint32_t CLEAR32``` - An unsigned 32 bit integer representing the RGBA value of clear.
##### ```uint16_t RED16```  - An unsigned 16 bit integer representing the RGB value of red.
##### ```uint16_t GREEN16```  - An unsigned 16 bit integer representing the RGB value of green.
##### ```uint16_t BLUE16```  - An unsigned 16 bit integer representing the RGB value of blue.
##### ```uint16_t CYAN16```  - An unsigned 16 bit integer representing the RGB value of cyan.
##### ```uint16_t LIME16```  - An unsigned 16 bit integer representing the RGB value of lime.
##### ```uint16_t PURPLE16```  - An unsigned 16 bit integer representing the RGB value of purple.
##### ```uint16_t WHITE16```  - An unsigned 16 bit integer representing the RGB value of white.
##### ```uint16_t BLACK16```  - An unsigned 16 bit integer representing the RGB value of black.
 
### <a name="filesystemM">filesystem</a>
##### ```preloaded_animations``` - Enumerated type representing all types of preloaded animations. Values are currently
> * ```NOT_PRELOADED``` - Represents a texture type that is not currently preloaded.
> * ```IDLE_ANIMATION``` - Represents the idle animation texture.
> * ```RIGHT_RUN_ANIMATION``` - Represents the right run animation texture.
> * ```LEFT_RUN_ANIMATION``` - Represents the left run animation texture.

### <a name="fontM">font</a>
##### ```unsigned char msx_font``` - An MSX stylized font set.
##### ```unsigned char bitmapFont``` - Not interactable with current project. May be used in Vita2d, though.
### <a name="gameM">game</a>
##### ```unsigned int tileSize``` - Unsigned integer representing the size of every tile.
##### ```unsigned int PLAYER_HEIGHT``` - Represents the height of the player in the game, typically a constant.
##### ```unsigned int PLAYER_WIDTH``` - Represents the height of the player in the game, typically a constant.
##### ```double PLAYER_BASE_MOVE_SPEED``` - Represents the base movement speed of the player in the game.
##### ```double PLAYER_MAX_MOVE_SPEED``` - Represents the maximum allowed movement speed of the player in the game.
##### ```double PLAYER_CURRENT_MAX_MOVE_SPEED``` - Represents the current maximum allowed movement speed of the player in the game. As this may change diuring the game, power-ups, etc..
##### ```double SPEED_MODIFIER``` - Represents a modifier that may affect the speed of a player (different terrain, etc.).
##### ```double FRICTION``` - Represents a modifier for friction that affects the speed of a player.
##### ```int MAX_AXIS_VALUE``` - Represents the maximum value that the joysticks may reach.
##### ```gamestate``` - Enumerated type representing the possible states of the game. Values are currently
> * ```PAUSED``` - Represents a gamestate in which the game is currently paused.
> * ```UNPAUSED``` - Represents a gamestate in which the game is currently unpaused.

##### ```movestate``` - Enumerated type representing the possible movestates of the player. Values are currently 
> * ```IDLE``` - Represents a movestate in which the player is not moving.
> * ```MOVING_RIGHT``` - Represents a gamestate in which the player is moving to the right.
> * ```MOVING_LEFT``` - Represents a gamestate in which the player is moving to the left.

##### ```tileVals``` - Enumerated type representing the values pertinent to tiles. Values are currently 
> * ```tileCount``` - Represents the total amount of tiles in the [tile member of the preloaded namespace](#tilesM).

##### ```gamestate state``` - Represents the current state of the game.
##### ```filesystem::Texture* rightrun``` - Preloaded texture for the rightrun animation.
##### ```filesystem::Texture* leftrun``` - Preloaded texture for the leftrun animation.
##### ```filesystem::Texture* idle``` - Preloaded texture for the idle animation.
##### <a name = "gameTilesM">```filesystem::Texture** tiles``` </a> - [Texture](#textureClassObject)** containing an array of [Texture](#textureClassObject]* containing all preloaded tiles. Must [preload tiles](#preloadTilesF) first.
##### ```signed char lx``` - Signed character representing the left analog X value.
##### ```signed char ly``` - Signed character representing the left analog Y value.
##### ```signed char rx``` - Signed character representing the right analog X value.
##### ```signed char ry``` - Signed character representing the right analog Y value.
### <a name="graphicsM">graphics</a>
##### ```int SCREEN_W``` - Value representing the width of the PS Vita screen in pixels.
##### ```int SCREEN_H``` - Value representing the height of the PS Vita screen in pixels.
##### ```int DISPLAY_STRIDE_IN_PIXELS``` - Value representing the stride of the display of the PS Vita screen in pixels.
##### ```SceDisplayFrameBuf fb``` - Array (size two) that will be containing the frame buffers.
##### ```SceUID fb_memuid``` - Array (size two) that will be containing the UID's for the frame buffers in order to release them later.
##### ```int cur_fb``` - Integer representing the current framebuffer being displayed.
### <a name="ioM">io</a>
##### ```SceCtrlData pad``` - Structure containing all the controls and their current states (pressed/unpressed).
##### ```SceTouchData touch``` - Structure containing the touchscreen and current screen touch information.
### <a name="preloadedM">preloaded</a>

##### ```unsigned int maps[][100][100]``` - A three dimensional array of tiles and their positioning in a map. The first dimension is the map number, the second dimension is the X position of the tile, and the third dimension is the Y position of a tile. The value is the [tile number](#tilesM) to be rendered at that position.
##### ```unsigned char idle``` - Array containing all RGBA values for the preloaded idle image.
##### ```unsigned char rightrun``` - Array containing all RGBA values for the preloaded rightrun image.
##### ```unsigned char leftrun``` - Array containing all RGBA values for the preloaded leftrun image.
##### <a name = "tilesM">```unsigned char tile``` </a> - Two dimensional array containing all RGBA values for all preloaded tiles.
### <a name="utilsM">utils</a>
##### ```unsigned char* fontStyle``` - The current fontStyle to be used in the project. (note: automatically set in utils.cpp)
---
## Classes
### <a name="colorsC">colors</a>
##### No classes.
### <a name="filesystemC">filesystem</a>
##### <a name="headerClassObject">```Header```</a> - Class containing the header of a RGBA file for use in a [Texture](#textureClassObject) object
> * ```Header(unsigned int height, unsigned int width, unsigned int states)``` - Constructor to create new Header with specified height, width, and states.
> * ```Header()``` - Constructor to create new Header with height, width, and states set to zero.
> * ```unsigned int height``` - Represents the height in pixels for the Texture in which the header will reside in.
> * ```unsigned int width``` - Represents the width in pixels for the Texture in which the header will reside in.
> * ```unsigned int states``` - Represents the states for the Texture in which the header will reside in.

##### <a name="pixelC">```pixel```</a> - Class containing all the necessary information of a pixel.
> * ```pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)``` - Constructor to create a pixel with the specified red, green, blue, and alpha.
> * ```pixel()``` - Constructor to create a pixel with the red, green, blue, and alpha set to zero.
> * ```unsigned char red``` - Represents the red value of the pixel.
> * ```unsigned char green``` - Represents the green value of the pixel.
> * ```unsigned char blue``` - Represents the blue value of the pixel.
> * ```unsigned char alpha``` - Represents the alpha value of the pixel.

##### <a name="textureClassObject">```Texture```</a> - Class containing all the necessary information of a pixel.
> * ```filesystem::preloaded_animations preloaded``` - If the texture is preloaded, this will contain the filesystem::preloaded_animations value which it represents.
> * ```filesystem::Header header``` - The [header](#headerClassObject) of the texture.
> * ```pixel** pixels``` - Pointer to a two-dimensional array of size [height][width] that contains all pixel data for the texture.
> * ```void format(unsigned int height, unsigned int width, unsigned int states)``` - Formats the header to represent the specified height, width, and states. Format also resizes the pixel body for the texture to the new specified height and width.
> * ```Texture(unsigned int height, unsigned int width, unsigned int states)``` - Crates a new texture and formats the header and pixel body to represent the specified height, width, and states. 

### <a name="fontC">font</a>
##### No classes.

### <a name="gameC">game</a>
##### ```Velocity``` - Class containing information pertinent to velocity.
> * ```double x``` - The current velocity in the x direction.
> * ```double y``` - The current velocity in the y direction.
> * ```Velocity(double x, double y)``` - Constructor to create a Velocity object with the given x and y velocity.
> * ``` Velocity()``` - Constructor to create a Velocity object with the x and y velocity equal to zero.

##### ```Position``` - Class containing information regarding positioning.
> * ```int x``` - The current position on the x axis.
> * ```int y``` - The current position on the y axis.
> * ```Position(int x, int y)``` - Constructor to create a Position object with the given x and y coordinates.
> * ``` Position()``` - Constructor to create a Velocity object with the x and y position set to the center of the screen.

##### <a name="entityClassObject">```Entity```</a> - Class containing information for an Entity.
> * ```Position position``` - The current position of the entity.
> * ```int y``` - The current position on the y axis.
> * ```Entity(int x, int y)``` - Constructor to create a Entity object with the given x and y coordinates.
> * ``` Entity()``` - Constructor to create an Entity object with the x and y position set to the center of the screen.

##### <a name="playerClassObject">```Player```</a> - Class containing information for the Player. Player extends [Entity](#entityClassObject)
> * ```Position lastPosition``` - The previous position of the player.
> * ```Movestate movestate``` - The movestate of the player.
> * ```Movestate previousMovestate``` - The previous movestate of the player.
> * ```double animationFrame``` - The current animation frame to use when drawing the player to the screen.
> * ```unsigned int health``` - The current amount of health the player has.
> * ```unsigned int missiles``` - The current amount of missiles the player has.
> * ```Velocity velocity``` - The current velocity of the player.
> * ```Player()``` - Creates a new Player object that has an IDLE movestate and a previous movestate of IDLE as well.
> * ```Player(int x, int y)``` - Creates a new Player object that has an IDLE movestate and a previous movestate of IDLE as well at the specified x and y position.

##### ```Camera``` - Class containing information for the camera.
> * ```Position positon``` - The position of the camera.
> * ```Camera()``` - Creates a new Camera object that has an x and y coordinate of center screen.
> * ```Camera(int x, int y)``` - Creates a new Camera object at the specified x and y coordinates.

### <a name="graphicsC">graphics</a>
##### No classes.

### <a name="ioC">io</a>
##### No classes.

### <a name="preloadedC">preloaded</a>
##### No classes.

### <a name="utilsC">utils</a>
##### No classes.
---
