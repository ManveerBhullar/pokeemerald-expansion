Marci_Start_MapScripts::
# 2 "data//maps/Marci_Start/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, MarciStart_OnTransition
	.byte 0


MarciStart_OnTransition::
	return


MarciStart_EventScript_ShowIntro::
# 10 "data//maps/Marci_Start/scripts.pory"
	lockall
# 11 "data//maps/Marci_Start/scripts.pory"
	msgbox MarciStart_Text_PlayerAwakeThought, MSGBOX_DEFAULT
# 12 "data//maps/Marci_Start/scripts.pory"
	delay 20
# 13 "data//maps/Marci_Start/scripts.pory"
	msgbox MarciStart_Text_PokemonCry, MSGBOX_DEFAULT
# 14 "data//maps/Marci_Start/scripts.pory"
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_ENCOUNTER
# 15 "data//maps/Marci_Start/scripts.pory"
	waitmoncry
# 16 "data//maps/Marci_Start/scripts.pory"
	delay 30
# 17 "data//maps/Marci_Start/scripts.pory"
	msgbox MarciStart_Text_UrgeToInvestigate, MSGBOX_DEFAULT
# 18 "data//maps/Marci_Start/scripts.pory"
	setvar VAR_MARCI_START_INTRO, 1
# 19 "data//maps/Marci_Start/scripts.pory"
	releaseall
	return


MarciStart_Text_PlayerAwakeThought::
# 22 "data//maps/Marci_Start/scripts.pory"
	.string "Where am I?\p"
	.string "This place looks unfamiliar...\p"
	.string "How did I get here?$"

MarciStart_Text_PokemonCry::
# 28 "data//maps/Marci_Start/scripts.pory"
	.string "Wait... I hear something from the\n"
	.string "north.$"

MarciStart_Text_UrgeToInvestigate::
# 33 "data//maps/Marci_Start/scripts.pory"
	.string "That sounded like a POKéMON in\n"
	.string "trouble!\p"
	.string "I should go check it out...$"
