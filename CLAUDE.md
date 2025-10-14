# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is pokeemerald-expansion, a comprehensive ROM hack base for creating Pokémon Emerald ROM hacks. It's built on top of pret's pokeemerald decompilation project and includes hundreds of modern Pokémon features, battle mechanics, and quality-of-life improvements.

## Build Commands

### Basic Build
```bash
make                    # Build the ROM (creates pokeemerald.gba)
make -j$(nproc)        # Parallel build (faster, use nproc output for job count)
```

### Testing and Analysis
```bash
make check             # Run test suite using mgba-rom-test
make debug             # Build with debug symbols and optimization
make ANALYZE=1         # Build with C analyzer for undefined behavior detection
make COMPARE=1         # Compare ROM against original checksum
```

### Cleaning
```bash
make clean             # Full clean including tools and generated files
make tidy              # Clean build artifacts only
make clean-assets      # Clean generated graphics and audio assets
```

### Alternative Targets
```bash
make pokeemerald-test.elf      # Build test ROM
make UNUSED_ERROR=1            # Treat unused warnings as errors (RH-Hideout style)
make LTO=1                     # Enable link-time optimization
```

## Architecture Overview

### Core Directories
- `src/` - Main C source files (350+ files)
  - Battle engine components (`battle_*.c`)
  - AI systems (`battle_ai_*.c`) 
  - Game systems (menus, overworld, Pokemon data)
- `include/` - Header files (280+ files)
  - `include/config/` - Feature configuration toggles
  - `include/constants/` - Game constants and enums
- `data/` - Game data files (maps, graphics metadata, text)
- `graphics/` - Image assets and tilesets
- `sound/` - Audio files and music
- `test/` - Comprehensive test suite with 100+ test files
- `tools/` - Build tools and data processors

### Key Configuration System
The project uses extensive configuration files in `include/config/` to toggle features:
- `battle.h` - Battle mechanics toggles
- `general.h` - General game features  
- `pokemon.h` - Pokémon-related features
- `ai.h` - AI behavior configuration
- `debug.h` - Debug and development tools

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

### Graphics Pipeline
- Source images automatically converted to GBA formats
- Sprite sheets and palettes generated from source files
- Map graphics processed through specialized tools