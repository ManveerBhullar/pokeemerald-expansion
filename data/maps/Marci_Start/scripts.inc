Marci_Start_MapScripts::
# 2 "data//maps/Marci_Start/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, MarciStart_OnTransition
# 3 "data//maps/Marci_Start/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MarciStart_OnFrame
	.byte 0


MarciStart_OnTransition::
	return


MarciStart_OnFrame::
# 11 "data//maps/Marci_Start/scripts.pory"
	map_script_2 VAR_MARCI_START_INTRO, 0, MarciStart_EventScript_ShowIntro
	return


MarciStart_EventScript_ShowIntro::
# 15 "data//maps/Marci_Start/scripts.pory"
	lockall
# 16 "data//maps/Marci_Start/scripts.pory"
	msgbox MarciStart_Text_PlayerAwakeThought, MSGBOX_DEFAULT
# 17 "data//maps/Marci_Start/scripts.pory"
	setvar VAR_MARCI_START_INTRO, 1
# 18 "data//maps/Marci_Start/scripts.pory"
	releaseall
	return


MarciStart_Text_PlayerAwakeThought::
# 21 "data//maps/Marci_Start/scripts.pory"
	.string "Where am I?\p"
	.string "This place looks unfamiliar...\p"
	.string "How did I get here?$"
