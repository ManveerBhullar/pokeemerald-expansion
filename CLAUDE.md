# CLAUDE.md

Always refer to this file.

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Latest Updates (2025-10-24)

### Marci's ROM Hack - Complete Intro Skip System
- **Ultra-Fast New Game**: Complete Birch speech bypass with auto character setup
- **Custom Starting Area**: `MAP_MARCI_START` - mysterious starting location south of Littleroot Town
- **Auto Configuration**: Player name set to "MARCI" (female), starts with level 5 Treecko
- **Essential Flags**: All game systems properly initialized (`FLAG_SYS_POKEMON_GET`, `FLAG_RESCUED_BIRCH`, `FLAG_ADVENTURE_STARTED`)
- **Build Optimizations**: M1 Max specific optimizations added to Makefile for faster compilation
- **Documentation**: Comprehensive `CHANGES.md` tracking all modifications

### Key Implementation Files
- `src/main_menu.c:1082-1091` - New game flow bypass
- `src/new_game.c:223-230` - Essential game state setup
- `data/maps/Marci_Start/` - Custom starting area with intro sequence
- `include/constants/vars.h:98` - Custom variable `VAR_MARCI_START_INTRO`

## Project Overview
This is pokeemerald-expansion, a comprehensive ROM hack base for creating Pokémon Emerald ROM hacks. It's built on top of pret's pokeemerald decompilation project and includes hundreds of modern Pokémon features, battle mechanics, and quality-of-life improvements.

**Current State**: Active ROM hack development with custom starting area and streamlined intro experience.

## Build Commands

### Basic Build
```bash
make                    # Build the ROM (creates pokeemerald.gba)
```

**M1 Mac Optimizations**: Build system includes performance optimizations for M1 Max chips with faster compilation flags in tool Makefiles.

### Testing and Analysis used less often
```bash
make check             # Run test suite using mgba-rom-test
make debug             # Build with debug symbols and optimization
make ANALYZE=1         # Build with C analyzer for undefined behavior detection
make COMPARE=1         # Compare ROM against original checksum
```

### Cleaning
```bash
make clean             # Full clean including tools and generated files, use mostlyclean instead
make tidy              # Clean build artifacts only
make clean-assets      # Clean generated graphics and audio assets
```

### Alternative Targets
```bash
make pokeemerald-test.elf      # Build test ROM
make UNUSED_ERROR=1            # Treat unused warnings as errors (RH-Hideout style)
make LTO=1                     # Enable link-time optimization
make mostlyclean               # Clean build artifacts while preserving tools directory
```

### Git Workflow Commands
```bash
git remote add <name> <repo>   # Add repository as remote (e.g., for pulling features)
git pull <remote> <branch>     # Pull changes from another repository/branch
git log -n 1 -S <function>     # Find last commit containing specific function
```

## Architecture Overview

### Core Directories
- `src/` - Main C source files (350+ files)
  - Battle engine components (`battle_*.c`)
  - AI systems (`battle_ai_*.c`) 
  - Game systems (menus, overworld, Pokemon data)
  - `src/strings.c` - Predefined game strings
  - `src/data/trainers.h` - Trainer data configuration
  - `src/data/trainer_parties.h` - Trainer Pokémon team details
  - `src/data/script_menu.h` - Multichoice list definitions
  - `src/main_menu.c` - Game start and intro handling
  - `src/starter_choose.c` - Starter Pokémon selection
- `include/` - Header files (280+ files)
  - `include/config/` - Feature configuration toggles
  - `include/constants/` - Game constants and enums
    - `include/constants/flags.h` - Game flags definitions
    - `include/constants/vars.h` - Game variables definitions
    - `include/constants/map_scripts.h` - Map script function reference
    - `include/constants/opponents.h` - Trainer definitions for battles
    - `include/constants/follower_npc.h` - Follower NPC behavior flags
    - `include/constants/battle_partner.h` - Battle partner definitions
- `data/` - Game data files (maps, graphics metadata, text)
  - `data/maps/` - Map-specific scripts and configurations
  - `data/scripts/new_game.inc` - Game state reset scripts
- `graphics/` - Image assets and tilesets
- `sound/` - Audio files and music
- `test/` - Comprehensive test suite with 100+ test files
- `tools/` - Build tools and data processors
- `asm/macros/event.inc` - Scripting macros for custom script development

### Key Configuration System
The project uses extensive configuration files in `include/config/` to toggle features:
- `battle.h` - Battle mechanics toggles
- `general.h` - General game features  
- `pokemon.h` - Pokémon-related features
- `ai.h` - AI behavior configuration
- `debug.h` - Debug and development tools
- `overworld.h` - Overworld features including follower NPC settings

### Testing Framework
Uses mgba-rom-test for automated testing with comprehensive battle mechanics tests organized by:
- Abilities (`test/battle/ability/`)
- Moves (`test/battle/move/`) 
- Items (`test/battle/item/`)
- Status effects and other mechanics

### Build System
- Custom Makefile with extensive rules for graphics, maps, and data processing
- Separate build directories for different configurations (modern, test, debug)
- Automated asset generation from source graphics and data files
- DevkitARM toolchain required for compilation

## Development Notes

### Feature Additions
- Most features can be toggled via config files rather than code changes
- New battle mechanics should include corresponding test cases
- Graphics follow specific naming conventions for automated processing

### Code Organization  
- Battle mechanics organized by type (abilities, moves, items)
- AI code separated from core battle logic
- Extensive use of constants and enums for maintainability

### Text and Scripting Guidelines
- **CRITICAL**: Use only ASCII characters in .inc script files
- **Unicode Replacement Guide**:
  - Replace ellipsis (…) with three periods (...)
  - Replace curly quotes ('') with straight quotes ('')
  - Replace em dashes (—) with double hyphens (--)
  - Replace en dashes (–) with single hyphens (-)
- **Character Limits**: Keep dialogue lines to 35-40 characters for GBA screen compatibility
- **Dialogue Format**: Use `\n` (new line), `\p` (page break), `$` (string end)
- Avoid Unicode asterisks (*) - use plain text descriptions instead
- Replace action descriptions like "*blushes*" with dialogue like "My cheeks are turning red!"
- File encoding must be UTF-8 without BOM or plain ASCII
- **Testing**: Always build after text changes to catch encoding issues early

### Graphics Pipeline
- Source images automatically converted to GBA formats
- Sprite sheets and palettes generated from source files
- Map graphics processed through specialized tools

### Visual Theme Implementation
- **Consistent Color Scheme** - Use faded pink palette across all UI elements for brand recognition
- **Palette Coordination** - Standard menu, main menu, and interface palettes use harmonious color values
- **Professional Aesthetic** 
- **Theme Files** - Always backup original `.pal` files before modifications (`.pal.backup` format)
- **Build Integration** - Palette changes automatically processed by `tools/gbagfx/gbagfx` during compilation

### Build Guidelines
- **Avoid `make clean`** unless absolutely necessary - normal `make` handles incremental builds efficiently

### Code Documentation Standards
- Add technical comments explaining purpose and rationale of changes
- Focus on WHY rather than WHAT when commenting
- Keep comments concise and relevant to future maintainers
- Document complex state flows and coordinate systems
- Avoid verbose comments for self-explanatory code

### ROM Hack Development Patterns

#### New Game Flow Customization
- **Main Menu Bypass**: Modify `src/main_menu.c` `ACTION_NEW_GAME` case to skip intro sequences
- **Auto Character Setup**: Use `COMPOUND_STRING()` for names, set `gSaveBlock2Ptr->playerGender`
- **Direct Game Start**: Call `SetMainCallback2(CB2_NewGame)` and `DestroyTask(taskId)` for immediate gameplay
- **Essential Flags**: Always set `FLAG_SYS_POKEMON_GET`, `FLAG_RESCUED_BIRCH`, `FLAG_ADVENTURE_STARTED`

#### Custom Starting Areas
- **Map Creation**: Add new map group in `data/maps/map_groups.json`
- **Map Definition**: Define in `include/constants/map_groups.h` with format `(0 | (GROUP_ID << 8))`
- **Spawn Location**: Modify `WarpToTruck()` in `src/new_game.c` to set custom coordinates
- **Intro Sequences**: Use map scripts with custom variables for one-time dialogue
- **Connection Setup**: Bidirectional connections in map JSON for seamless transitions

#### Game State Management
- **Starter Pokemon**: Use `ScriptGiveMon(SPECIES, level, ITEM_NONE)` to prevent crashes
- **Flag Management**: Strategically hide blocking NPCs while preserving important sequences
- **Variable Tracking**: Define custom variables in `include/constants/vars.h` for state management
- **Custom Content Tracking**: Add `"romhack": true` field to JSON files for easy identification
- **Documentation**: Maintain `CHANGES.md` with technical implementation details and version history

### Event Scripting Guidelines

**IMPORTANT**: Use Poryscript (.pory files) for all new script development. See `PORYSCRIPT_REFERENCE.md` for complete syntax guide.

#### Basic Battle Setup (Poryscript Syntax)
- Use `setwildbattle(SPECIES_NAME, level)` to create wild battles
- Use `seteventmon(SPECIES_NAME, level)` for legendary encounters (preferred)
- Use `givemon()` with parameters for custom pokemon gifts:
  - `givemon(SPECIES_NAME, level, shinyMode=SHINY_MODE_ALWAYS)` for shiny
  - Include item, ball, nature, abilities, IVs, EVs, moves as needed
- Use `special(BattleSetup_StartLegendaryBattle)` for legendary battles

#### Audio/Visual Polish for Legendary Encounters
- Use `playmoncry(SPECIES_NAME, CRY_MODE_ENCOUNTER)` for dramatic effect
- Use `special(LoopWingFlapSE)` for flying legendary pokemon
- Camera control: `special(SpawnCameraObject)` + movement + `special(RemoveCameraObject)`
- Screen effects: `special(ShakeCamera)` with VAR_0x8004 (intensity), VAR_0x8005 (duration)
- Weather integration: `setweather(WEATHER_TYPE)` + `doweather()` for atmosphere

#### Wild Encounter Customization
- Toggle different wild encounter tables using `VAR_ENCOUNTER_TABLE` in `include/constants/vars.h`
- In `src/wild_encounter.c`, modify `GetCurrentMapWildMonHeaderId` by adding: `i += VarGet(VAR_ENCOUNTER_TABLE);`
- Default value 0 uses first table, value 1 uses second table, etc.
- Ensure variable value doesn't exceed number of encounter tables for the map

#### Map Preview Screens
- Configure map previews in `include/map_preview_screen.h` and `src/map_preview_screen.c`
- Preview types: `MPS_TYPE_BASIC` (fade to black), `MPS_TYPE_FADE_IN` (fade to map), `MPS_TYPE_CAVE` (cave entry)
- Use `mappreview` and `mappopup` script macros
- Configure duration, fade speed, and flag-based behavior

### Map Event Structure
- **Object Events**: NPCs, Pokemon, and interactive objects in `map.json`
- **Coord Events**: Triggered by stepping on specific coordinates
- **Script Events**: Define behavior in `scripts.inc` files
- **Movement Patterns**: Defined with step commands like `walk_fast_up`, `step_end`
- **Flags**: Control object visibility and story progression

### NPC Implementation Patterns
- **LOCALID Constants** - Define NPC identifiers in `include/constants/map_event_ids.h`
  - Format: `#define LOCALID_MAPNAME_NPCNAME ID_NUMBER`
  - Example: `#define LOCALID_LITTLEROOT_TWIN 1`
- **Movement Types** - Use appropriate movement for NPC behavior
  - `MOVEMENT_TYPE_WANDER_AROUND` - Natural exploration with movement range
  - `MOVEMENT_TYPE_FACE_DOWN` - Static NPCs facing specific directions
- **Gender-Specific Dialogue** - Use `checkplayergender` and conditional scripts
- **Flag Management** - Coordinate visibility and interaction states
  - Hide flags: `FLAG_HIDE_MAPNAME_NPCNAME`
  - Quest completion: `FLAG_DEFEATED_TRAINERNAME` or `FLAG_COMPLETED_QUESTNAME`

### Special Trainer Implementation
- **Trainer Data** - Define in `src/data/trainers.party` with custom Pokemon
- **Opponent Constants** - Add to `include/constants/opponents.h` and increment `TRAINERS_COUNT`
- **Shiny Pokemon** - Use `Shiny: Yes` format in trainer party files
- **Move Restrictions** - List moves with `- MOVE_NAME` format for specific movesets
- **Reward Items** - Use `giveitem ITEM_NAME, quantity` after trainer defeat

### Advanced Features

#### Follower NPCs
- Use `setfollowernpc` macro with object ID and follower flags
- Configure behavior flags in `include/constants/follower_npc.h` (e.g., `FNPC_SURF`, `FNPC_RUNNING`)
- Set battle partners in `src/data/battle_partners.party`
- Additional commands: `changefollowerbattler`, `facefollowernpc`, `checkfollowernpc`, `hidefollowernpc`, `destroyfollowernpc`
- Configure automatic healing and participation rules in `include/config/overworld.h`

#### Title Screen Customization
- Customize color fading using `UpdateLegendaryMarkingColor` function
- Define colors with `RGB2GBA(r, g, b)` macro in `sFadeColors` array
- Support for multiple simultaneous color transitions
- Configure starting color, ending color, and palette index for each fade effect

## External Resources

### Official Community Guides
For additional tutorials and guides, refer to the [decomps-resources wiki](https://github.com/Bivurnum/decomps-resources/wiki):
- [Useful Commands](https://github.com/Bivurnum/decomps-resources/wiki/Useful-Commands) - Development workflow and Git commands
- [Commonly Used Files](https://github.com/Bivurnum/decomps-resources/wiki/Commonly-Used-Files) - Key files for ROM development
- [Wild Encounter Toggling](https://github.com/Bivurnum/decomps-resources/wiki/Easily-Toggle-Different-Wild-Encounters) - Dynamic encounter system
- [Title Screen Customization](https://github.com/Bivurnum/decomps-resources/wiki/Title-Screen-Easy-Fade-Colors) - Color fading effects
- [Map Previews](https://github.com/Bivurnum/decomps-resources/wiki/FRLG-Map-Previews) - FireRed-style map preview screens
- [Follower NPCs](https://github.com/Bivurnum/decomps-resources/wiki/Follower-NPCs-for-pokeemerald%E2%80%90expansion) - Companion system implementation

## Current ROM Hack State

### Active Development: Marci's ROM Hack
The project currently implements a complete intro skip system with custom starting area:

**Key Files to Reference**:
- `CHANGES.md` - Comprehensive technical documentation of all modifications
- `data/maps/Marci_Start/` - Custom starting area implementation
- `src/main_menu.c:1082-1091` - New game flow bypass implementation
- `src/new_game.c:223-230` - Essential game state initialization

**Gameplay Flow**:
1. Main Menu → "New Game" → Instant character creation (MARCI, female)
2. Spawn in `MAP_MARCI_START` with level 5 Treecko
3. Brief intro dialogue: "Where am I? This place looks unfamiliar... How did I get here?"
4. Full access to menus, items, Pokemon systems
5. Route 101 Birch scene preserved for additional starter acquisition

**Development Standards Established**:
- ASCII-only text for GBA compatibility
- Custom content marked with `"romhack": true`
- Comprehensive change documentation in `CHANGES.md`
- Build system optimized for M1 Mac development