# Marci's ROM Hack - Changes Documentation

This document tracks all modifications made to the pokeemerald-expansion base for Marci's custom ROM hack.

## Version History

### v0.1 - Initial Modifications (2025-10-24)

#### Story Motivation Enhancement - Marci_Start Area
- **File**: `data/maps/Marci_Start/scripts.pory`
- **Enhancement**: Added story impetus to explore north toward Littleroot Town
- **Implementation**: 
  - Extended intro dialogue to mention hearing Pokemon in trouble from the north
  - Added `playmoncry(SPECIES_ZIGZAGOON, CRY_MODE_ENCOUNTER)` sound effect
  - `waitmoncry` ensures proper audio timing
- **Purpose**: Provides clear motivation for player to head north and discover Route 101 Birch scene
- **Effect**: Player now has narrative reason to explore and find their starter Pokemon

#### Atmospheric Music Change - Littleroot Town
- **File**: `data/maps/LittlerootTown/map.json`
- **Change**: Modified background music from `MUS_LITTLEROOT` to `MUS_RG_LAVENDER`
- **Effect**: Littleroot Town now plays Lavender Town's haunting melody
- **Purpose**: Creates mysterious, eerie atmosphere matching the ROM hack's otherworldly theme

#### Script Cleanup & Quality Improvements
- **File**: `data/maps/LittlerootTown/scripts.inc`
- **Changes**: Cleaned up scripts and fixed Unicode encoding issues
  - Removed test/debug code remnants
  - Converted Unicode characters to ASCII for GBA compatibility
  - Fixed dialogue formatting and character limits

#### New Starting Area - Marci_Start
- **Location**: South of Littleroot Town
- **Files Modified**:
  - `data/maps/Marci_Start/map.json` - Core map configuration
  - `data/maps/Marci_Start/scripts.pory` - Interactive elements and dialogue
  - `data/maps/map_groups.json` - Added to world map

**Map Features**:
- Connected to Littleroot Town via north exit
- Music: Cave of Origin theme (`MUS_CAVE_OF_ORIGIN`)
- Weather: Volcanic ash atmosphere (`WEATHER_VOLCANIC_ASH`)
- Region: Littleroot Town section (`MAPSEC_LITTLEROOT_TOWN`)
- Cycling, running allowed; escaping disabled

**Interactive Elements**:
1. **Hello World Sign** (7,2)
   - Script: `MarciStart_EventScript_HelloWorldSign`
   - Message: Welcome message introducing Marci's starting area
   
2. **Funny Sign** (Additional sign with humorous content)
   - Script: `MarciStart_EventScript_FunnySign`
   - Message: WiFi password joke and energy drink warning

**NPCs**:
- Brendan fishing sprite at (10,5) with look-around movement
- **Mysterious Girl** at (5,7) with wander movement
  - Graphics: `OBJ_EVENT_GFX_GIRL_3`
  - Script: `MarciStart_EventScript_MysteriousGirl`
  - Dialogue: Cryptic messages about time, change, and ancient energies
  - Movement: Wanders around a 1x1 area for natural exploration

#### Introductory Scene System
- **Files**: `data/maps/Marci_Start/scripts.pory`, `include/constants/vars.h`
- **Purpose**: Provide context and instructions when player first spawns

**Map Scripts Added**:
- `MAP_SCRIPT_ON_TRANSITION`: Sets up intro state
- `MAP_SCRIPT_ON_FRAME_TABLE`: Triggers intro dialogue on first visit

**Intro Sequence**:
1. **Player Thoughts**: "Where am I? This place looks unfamiliar... How did I get here?"
2. **Instructions**: Explains the mysterious area, suggests exploration, hints at needing Pokemon
3. **Variable**: `VAR_MARCI_START_INTRO` tracks intro completion

**Benefits**:
- Sets the mysterious/otherworldly tone
- Guides new players on what to do
- Explains why they need to find Pokemon
- Only triggers once per save file

#### Main Menu Visual Enhancement
- **File**: `src/main_menu.c`
- **Enhancement**: Animated gradient background system
  - Replaces static single-color background
  - 5-frame gradient animation (purple to blue transitions)
  - 10-frame animation speed for smooth color cycling
  - Palette file: `graphics/interface/main_menu_gradient.pal`

**Technical Implementation**:
- Added `Task_MainMenuGradientAnimation()` function
- Integrated with existing main menu task system
- Uses `LoadPalette()` for real-time color updates

#### Intro Scene Skip System & Starting Location
- **File**: `src/new_game.c` (lines 134-136, 204-224)
- **Purpose**: Skip opening truck, clock, TV scenes and Mom's forced tutorial; Start in Marci_Start area

**Starting Location Change**:
```c
// WarpToTruck() function modified to warp to Marci_Start instead
SetWarpDestination(MAP_GROUP(MAP_MARCI_START), MAP_NUM(MAP_MARCI_START), 
                   WARP_ID_NONE, 8, 7);  // Fixed spawn height to prevent floating
```

**Variables and Flags Set During New Game**:
```c
// Intro skip flags
VarSet(VAR_LITTLEROOT_INTRO_STATE, 7);  // Skip all intro sequences (>6)
VarSet(VAR_ROUTE101_STATE, 0);          // Allow Route 101 Birch rescue for starter
VarSet(VAR_OLDALE_RIVAL_STATE, 1);      // Skip Oldale Town blocking events
FlagSet(FLAG_SET_WALL_CLOCK);           // Skip clock setting
FlagSet(FLAG_SYS_CLOCK_SET);            // Mark clock as configured
FlagSet(FLAG_TV_EXPLAINED);             // Skip TV explanation
FlagSet(FLAG_SYS_TV_START);             // Initialize TV system
FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK);  // Hide trucks
FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK);
FlagSet(FLAG_RECEIVED_RUNNING_SHOES);   // Player has running shoes
FlagSet(FLAG_SYS_B_DASH);               // Enable running

// Hide blocking NPCs
FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN);      // Hide blocking NPC
FlagSet(FLAG_HIDE_ROUTE_101_BOY);                // Hide route 101 blocking boy
FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE);  // Hide mom outside
FlagSet(FLAG_HIDE_LITTLEROOT_TOWN_BIRCH);        // Hide Birch in town
FlagSet(FLAG_HIDE_ROUTE_103_BIRCH);              // Hide Birch on Route 103
// Note: Route 101 Birch scene preserved for starter Pokemon acquisition
```

**Intro State Progression (VAR_LITTLEROOT_INTRO_STATE)**:
- 1-2: Truck scenes (male/female)
- 3: Enter house moving in
- 4: Block stairs until clock is set
- 5: Go upstairs to set clock
- 6: Petalburg Gym report/TV scene
- 7+: All intro sequences completed

#### Complete Birch Speech Skip & Auto Character Setup
- **File**: `src/main_menu.c` (lines 1082-1091)
- **Purpose**: Completely bypass Birch intro speech and auto-configure player

**Implementation**:
```c
case ACTION_NEW_GAME:
    gPlttBufferUnfaded[0] = RGB_BLACK;
    gPlttBufferFaded[0] = RGB_BLACK;
    // Skip Birch speech, set name to Marci and gender to female
    gSaveBlock2Ptr->playerGender = FEMALE;
    StringCopy(gSaveBlock2Ptr->playerName, COMPOUND_STRING("MARCI"));
    SetMainCallback2(CB2_NewGame);
    DestroyTask(taskId);
    break;
```

**Auto-Configuration**:
- Player name: Automatically set to "MARCI"  
- Player gender: Automatically set to FEMALE
- Intro speech: Completely skipped, goes directly to CB2_NewGame

**Essential Game State Setup** (`src/new_game.c:223-229`):
```c
// Set essential game flags to prevent crashes and allow proper menu access
FlagSet(FLAG_SYS_POKEMON_GET);       // Enable Pokemon menu access
FlagSet(FLAG_RESCUED_BIRCH);         // Mark Birch as rescued (prevents various issues)
FlagSet(FLAG_ADVENTURE_STARTED);     // Mark adventure as started

// Give player a starter Pokemon to prevent crashes in systems that expect Pokemon
ScriptGiveMon(SPECIES_TREECKO, 5, ITEM_NONE);
```

**Benefits**:
- Zero interaction required from player for character setup
- Immediate access to gameplay after selecting "New Game"
- Eliminates all Birch speech dialogue trees
- Player starts with Treecko (level 5) to prevent system crashes
- All essential game flags set to enable proper menu and system access
- Streamlined for rapid testing and development

#### Custom Content Tracking
- **System**: `"romhack": true` fields added to custom content
- **Purpose**: Easy identification of custom additions vs. base game content
- **Files**: All custom map and event configurations

## Technical Standards Established

### Text and Dialogue Guidelines
- ASCII-only characters for GBA compatibility
- 35-40 character line limits for screen display
- Proper dialogue formatting: `\n` (newline), `\p` (page break), `$` (end)
- No Unicode characters (ellipsis, curly quotes, em dashes)

### Code Quality Standards
- Clean, well-commented code additions
- Preserve existing code conventions and style
- Use existing engine systems rather than creating new ones
- Maintain compatibility with build system

### Asset Management
- Custom graphics follow existing naming conventions
- Palette files backed up before modification (`.pal.backup`)
- All custom content marked with `romhack: true` tracking

## Build System
- **Command**: `make` (standard build)
- **Clean**: `make mostlyclean` (preserve tools directory)
- **Architecture**: DevkitARM toolchain with pokeemerald-expansion base

## File Structure Overview

```
pokeemerald-expansion/
├── data/maps/Marci_Start/           # Custom starting area
│   ├── map.json                     # Map configuration
│   ├── scripts.pory                 # Event scripts (source)
│   ├── scripts.inc                  # Generated event scripts
│   ├── events.inc                   # Generated events
│   └── header.inc                   # Generated header
├── graphics/interface/
│   └── main_menu_gradient.pal       # Animated gradient palette
├── src/
│   ├── main_menu.c                  # Enhanced with gradient animation
│   └── new_game.c                   # Modified for intro skip
└── CHANGES.md                       # This documentation
```

## Future Development Notes

### Planned Features
- Additional custom areas and maps
- Enhanced NPC interactions
- Custom battle mechanics
- Story modifications

### Development Guidelines
- Continue using Poryscript (.pory) for new event scripts
- Maintain ASCII text encoding standards
- Use existing engine capabilities where possible
- Document all changes in this file
- Test builds after each major modification

---

**Last Updated**: 2025-10-24
**Base Version**: pokeemerald-expansion (latest)
**Developer**: Claude Code assistance for Marci's ROM hack