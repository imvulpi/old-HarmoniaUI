⚠ PLEASE READ BEFORE PROCEEDING ⚠

This library is in early development, and hasn't been thoroughly checked on all platforms.
<br>I suggest downloading the library and testing it for yourself on a seperate project, it might be something you would want to follow, or contribute to 😁

You should join the [discord server](https://discord.com/invite/rgsGFsGQsg) for more updates 🤗

❗ You should download the most recent branch to get the latest version. 

## How to get it working:

Requirements:
- You should have a Godot project created with version above 4.0 preferably [version 4.3](https://godotengine.org/download/archive/4.3-stable/) (this is the version it was tested on so far)
- You should have [SConstruct installed](https://scons.org/doc/latest/HTML/scons-user/ch01s02.html)
- You need to have some kind of a C++ compiler like Microsoft Visual C++ compiler, G++ mingw etc, be aware that some compilers only work on a specific platform.

Tutorial:
1. Clone the repository, for now to get the newest features clone the most [recently updated branch.](https://github.com/imvulpi/HarmoniaUI/branches)<br>
👉 use the command `git clone -b {branch name} --recurse-submodules https://github.com/imvulpi/HarmoniaUI` <br> it will also clone the submodules allowing you to simply compile it without needing to clone the godot extern.
2. Go inside the cloned directory root (there should be a SConstruct file there) and simply execute `scons` in that location, you can also use parameters like `platform=linux`, but it should autodetect for you.
3. It will take some time mostly because godot stuff has to compile as well (when developing/making changes after the 1st compilation the next ones will be a lot faster, because godot stuff is already compiled)
4. After compilation the library files will be inside the export directory `export/bin` there will be a file `export/harmoniaui.gdextension` as well.
5. Copy or move both the `/bin` directory and `harmoniaui.gdextension` file inside your godot project (The project must be closed, later when the files are already there you can open/close your project without any issues unless you want to move the files, which then you have to close or just reopen the project after moving)
6. At this point the project can be opened and the library should be working.

At this moment there is only one container called `ContainerBox` inside the godot control node. There will be more containers added but you need to wait for that.

**For now there is no website documentation**, but you can look inside the header files to check what methods do what.

I recommend joining the [discord server](https://discord.com/invite/rgsGFsGQsg) to get more info or for help if you are stuck at something. You can also just talk about the library, godot, ui and other. 😊

### Releases

When a stable version gets released I will include the binaries for all the platforms so you don't need to compile it all. 😉

An issue might be with Apple products, because 
1. I don't own Apple electronics.
2. I'm not exactly sure how compiling for Apple stuff really works 😅

So I might need to ask someone to compile for those platforms or borrow apple stuff.

# HarmoniaUI
HarmoniaUI is a library for Godot engine designed to simplify UI creation and extend the UI possibilities.

Our library tries to implement well known and liked aspects of different UI libraries, styling languages like CSS or web engines.
It mainly uses Godot C++ GDExtension to make the UI and to steer it, obviously with its own implementation. 

The UI works with basic Godot control nodes and if some kind of migration is needed then control nodes can be converted to containers.

Join our [Discord](https://discord.com/invite/rgsGFsGQsg) to be a member in our community 😎

## Plans for the future:

- Containers:
  - ResolutionContainer (Picks a container based on the device resolution)
  - ContainerBox
  - Holder Containers:
    - GridBox
    - ListBox 
    - FlexBox
- Buttons:
  - Button [PLAY]
  - CheckButton [X][O]
  - ToogleButton [ O -text-  ]
  - SelectButton [ -text- \\/ ]
- Input
- Text

FUNCTIONALITIES

CONTAINERS:
Containers (ALL)
- Scroll options and scroll in general
- Width (auto, %, px, vh, vw) OK
- Min/Max width
- Height (auto, %, px, vh, vw) OK
- Min/Max height
- Margin (auto, %, px, vh, vw)
- Padding (auto, %, px, vh, vw)
- Font family (to discuss)
- Font size (to discuss)
- Text align (to discuss)
- Color (to discuss) (color in all texts)
- Background color
- Position
- Border (line at the borders)
- Overflow (visible/hidden/scroll/auto)
- Rounded corners

- GridBox:
  - Template/Layout
    - auto-placement[space] (block per how many)
    - column-placement [amount, space]
    - [size][(1][-]\(size)[..] (template)
      "[size]" (size of the block in grid blocks) "\(size)" (new row)
    - flipping, changing order in general
- ListBox:
  - Changing order Vertical, Vertical-Flip (No horizontal)
  - Gap (%, px) gap between elements
  - Alignment-x (Left, right, top, down, center, stretch?, space-around, space-between)
  - Alignment-y (Left, right, top, down, center, stretch?, space-around, space-between)
- FlexBox:
  - Changing order Vertical, Horizontal, Vertical-Flip, Horizontal-Flip ...
  - Gap (%, px) gap between elements
  - Alignment-x (Left, right, top, down, center, stretch?, space-around, space-between)
  - Alignment-y (Left, right, top, down, center, stretch?, space-around, space-between)

BUTTONS
(These would actually be a type of container with specific events and other functionalities)

Buttons(all):
  - Disabled (Y/N)

Buttons:
  Button:
     - Text
  CheckInput:
     - "Check" image
     - Text
  Toggle:
     - "Toggle" image
     - Text
  SelectButton:
     - "Dropdown" image
     - List Order (flip)
     - List elements container attributes
     - Possiblity of making the list a ListBox instead.
   
Input:
  - Scroll (from container - to discuss)
  - Type (number, text, date, (regex - to discuss))
  - Multiline (Y/N)
  - Placeholder text
  - Text
  - Disabled (Y/N)
  - Context menu (to discuss)
  - Shortcut keys enabled (Y/N)
  - Selecting enabled
  - Virtual keyboard (Y/N)
  - Autowrap modes (to discuss)
  - Caret (type, blink, blink interval)

Text:
  - Scroll (from container - to discuss)
  - Multiline (Y/N)
  - Selecting enabled
  - Autowrap modes (to discuss)


Besides these an API for each of them would be there for interacting with the object and objects inside them, you can create your own containers and stuff.
Definely events like press, input, hover etc.

\* There is definely a lot missing from the plans for future, I didn't write all of the functionalities that are desired.
\** Not sure if ListBox will be created, because of flexbox being very similiar and extending the listbox possibilities.

### Hope you are interested!

If you are interested in this project join our [Discord](https://discord.com/invite/rgsGFsGQsg) 😁
You can discuss different ideas, contribute, show projects and other stuff related to this library~!
