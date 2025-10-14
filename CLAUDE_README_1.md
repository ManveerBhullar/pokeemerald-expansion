# CLAUDE_README_1.md

This document contains community standards, best practices, and technical limitations for Pokémon ROM hacking, specifically for the pokeemerald-expansion project.

## Text and Dialogue Standards

### Character Limits (Critical!)
- **34 characters per line maximum** (guideline)
- **35 characters per line** in practice for message boxes
- **2 lines per textbox maximum**
- Variable name lengths to consider:
  - Player/Rival names: **7 characters max**
  - Pokémon names: **10 characters max**

### Text Formatting Commands
- `\n` - Line break (use only once per box)
- `\p` - Page break (new textbox)
- `\l` - Line continuation (avoid when possible)

### Dialogue Best Practices
- **One complete thought per two-line textbox**
- Place line breaks at natural pauses
- Test all dialogue in-game
- Maximize character usage without exceeding margins
- Avoid using text adjusters - manually format for better flow

## Graphics and Visual Standards

### Sprite Constraints
- **16x16 pixel tiles** (fundamental constraint)
- Default tileset: **14×33 tiles = 462 tiles max**
- **6 palettes reserved** for main tileset
- **16 different colors per palette** (no duplicates)

### Graphics Limitations
- Use only existing palette IDs from vanilla ROM
- New palettes require overwriting existing ones
- 8×8 blocks with bottom & top layers
- Background color should distinguish elements clearly

### Animation Guidelines
- **150 animation paths available** (most use only up to path 52)
- Consider disabling animations to reduce workload
- Palette corruption causes instability and crashes

## Audio Standards

### Track Limitations
- **Fire Red/Emerald: 12 tracks maximum** (0xC in hex)
- **Ruby/Sapphire: 7 tracks maximum**
- Default Fire Red: 10 simultaneous tracks
- Can be expanded to 16 tracks with RAM repointing

### Engine Specifications (m4a/mp2k/Sappy)
- Default reverb value: 0
- Reverb: ON
- **5 simultaneous DirectSound channels**
- Master volume: 12
- Engine frequency: **13379Hz**
- 8-bit DAC

### Audio File Requirements
- Custom samples: **5+ seconds minimum**
- Format: **.aiff files, mono channels only**
- Manual looping required
- Use `mid2agb` for .mid to .s conversion

### Memory Safety
- **Safe free space starts at 0xE3CF64**
- Instrument data starts at **0x6B46BB** (do not modify)
- Expand ROM to **32MB** and fill with FF bytes
- Avoid 00, 01, 02 bytes in instrument range

## Community Standards

### Legal Guidelines
- ROM hacking is legal if you own the original ROM
- **Distribution**: Share patches only, never full ROMs
- **Attribution**: Always credit original creators
- **Commercial use**: Selling ROM hacks is illegal

### Development Categories
- **Story Enhancement**: Complete overhauls with new regions/plots
- **Difficulty Hacks**: Modified stats, typing, trainer battles
- **Quality Polish**: High attention to detail and creativity

### Technical Standards
- Use **English 1.0 versions** of base games only
- Proper save configuration: "Flash 128K" + Real-Time Clock
- Version control and compatibility checking essential

### Tools (Standard Community Tools)
- **AdvanceMap**: Map creation
- **XSE**: Scripting NPCs and events  
- **Advance Text**: Text editing (legacy)
- **Pokemon Text Editor**: Modern text editing alternative
- **mid2agb**: Audio conversion

## File Structure Best Practices

### Configuration Files
- Keep feature toggles in `include/config/` organized
- Test all config combinations before release
- Document feature dependencies

### Build Process
- Always run `make clean` before major builds
- Test on multiple emulators
- Verify save compatibility

### Documentation
- Document custom features for future developers
- Maintain changelog for version tracking
- Include installation instructions

## Common Mistakes to Avoid

### Text Issues
- Don't rely on automatic text adjusters
- Avoid run-on sentences across multiple textboxes
- Test dialogue with maximum-length variable names

### Graphics Problems
- Don't exceed palette limits
- Avoid corrupting existing graphics data
- Test all graphics changes in-game

### Audio Corruption
- Never modify instrument data ranges
- Don't use incorrect free space areas
- Always backup before audio modifications

### General Development
- Don't use "Download ZIP" from GitHub (missing commit history)
- Don't modify copyrighted content for distribution
- Don't skip testing on real hardware/accurate emulators

## Resource Management

### Memory Constraints
- Emerald free space: Limited after 0xE3CF64
- Graphics memory: Shared with existing game data
- Audio samples: Balance quality vs. file size

### Performance Considerations
- Minimize simultaneous audio tracks
- Optimize graphics loading
- Test frame rate with custom animations

---

**Note**: This document reflects 2024 community standards and should be updated as tools and practices evolve.