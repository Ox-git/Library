/*
This overwrites existing functions in the US ROM with new code hooks.
it needs to be placed in static ROM with no offset to the address
*/



//Change kwtexture2d to use loadtile
.org 0x463E0
.word 0x0C010F0A
//fix kwtexture2D_rgba32_bl
.org 0x0473F0
.word 0x0C011869
//add XLU to RGBA32
.org 0x047350
.word 0x273979E8
.org 0x0473C4
.word 0x273979E8





// fix for MKInit duplicate calls which are overwritten by our boot code.
// gamecode never needs to be reloaded.
.org 0x3314
NOP
.org 0x3354
NOP
.org 0x01CC64
NOP
.org 0x003334
NOP
.org 0x00335C
NOP
//
//
//


//Overwrite EEPROM load functions
.org 0xB51E0
jr RA
NOP
.org 0x0B5270
jr RA
NOP
.org 0x0B619C
jr RA
NOP
.org 0x0B6548
jr RA
NOP
.org 0x0B5610
jr RA
NOP

//end EEPROM funcs






//KT1 Tree Display Call
.org 0x10C7FC
JAL DisplayTree1Bypass

//Pakkun Display Call for PiranhaPlants
.org 0x10C990
JAL DisplayPiranhaBypass

//Pakkun Strategy Hook for PiranhaPlants
.org 0x10CC70
JAL PakkunStrategyOverride




/*   Disabled
//Load all object textures into RAM
.org 0x1079B8
NOP
.org 0x107A90
NOP
.org 0x107AAC
NOP
.org 0x107AC8
NOP
.org 0x107AF8
NOP
.org 0x107BE4
NOP
.org 0x107C14
NOP
.org 0x107D0C
NOP
.org 0x107D78
NOP
*/    //End



// Move FreeMemoryPointer loads to EOF using new funcs and rewrites


    // Rewrite for Segment 9 LoadData
    .org 0x113FD8
    JAL LoadDataBypass

    // Rewrite for Segment 6 LoadPressData
    .org 0x114004
    JAL LoadPressDataBypass

    // Rewrite for Segment 47 TransGFXData
    .org 0x114028
    JAL LoadDataBypass

    //Stop loading StaticMemoryPointer over LastMemoryPointer
    .org 0x36F8
    NOP
    
//



//AddGravityHooks
.org 0x2E00C
JAL AddGravityEdit
.org 0x2F2A4
JAL AddGravityEdit
.org 0x3997C
JAL AddGravityEdit


//InitSmokeHooks
.org 0x6D59C
JAL InitRndSmokeHook
.org 0x6D584
JAL InitRapidSmokeHook
.org 0x6D520
JAL InitSpinSmokeHook




//Display Custom Levels Hook
.org 0x0FF0BC
JAL DisplayKT1Hook

//Map Startup Hooks
.org 0x123B0C
JAL MapStartup
.org 0x0036F4
JAL MapStartup
.org 0x12506C
JAL MapStartup

//InitialMap Hook
.org 0x0036FC
JAL InitialMapCode

//InitialMapObject
.org 0x107DCC
JAL InitialMapObjectCode

//Litro Snow Code
.org 0x079290
J SnowHook
NOP


//Hook display after map.
.org 0x0FBA68
J DisplayMap2Hook
NOP


//Fix for MIO0 Decompression ; Return End Address
.org 0x040D64 
move v0, $t8

//Fix for gsSPCullDisplayList
//.org 0x122314
//.word 0x0000000E
//LOLJK FML AMIRITE


//CheckMapBG_ZX Hooks
.org 0x2EBE0
JAL CheckMapBG_ZX_Hook
.org 0x2FB10
JAL CheckMapBG_ZX_Hook
.org 0x30614
JAL CheckMapBG_ZX_Hook
.org 0x39CC0
JAL CheckMapBG_ZX_Hook

.org 0x2A74
JAL MiniMapDraw
//remove KWViewportCall for minimap drawing.
.org 0x059F40
NOP


//AirControlChange
.org 0x38A04
NOP
.org 0x38A10
JAL ProStickAngleHook
.org 0x38A4C
NOP

//Print Menu Hooks
.org 0x2B30
J PrintMenuHook
NOP


// fixes Alpha loading for level data vert color
.org 0x111D4C
LB t2, -1(v0)


//Staff Ghost routine
.org 0x5BA4
J    GhostHook
NOP



//Hook add new custom IBox code
//.org 0x1071E8
//JAL CreateCustomItemBox














//Kart Collision Wrappers
.org 0x02BF48 
JAL BombThrowRolloverWrap
.org 0x02BF6C
JAL RolloverWrap
.org 0x02BF90
JAL WheelspinWrap
.org 0x02C044
JAL BrokenWrap
.org 0x02C068
JAL ThunderWrap
.org 0x02C08C
JAL SpinWrap
.org 0x02C0B0
JAL BombRolloverWrap
.org 0x02C0D4
JAL BombThrowRolloverWrap
.org 0x02C184
JAL ProWheelSpinWrap
.org 0x02C1A4
JAL BombRolloverWrap





//PlayStarMusicHook
.org 0x90420
JAL PlayStarMusicHook

//StopStarMusicHook
.org 0x904B4
JAL StopStarMusicHook
.org 0x902D8
JAL StopStarMusicHook




//For handling lakitu respawns
.org 0x091890
JAL LakituSpawnBypass
.org 0x091920
JAL LakituSpawnBypass

//PlayFinalLapMusicHook
.org 0xF8954
JAL PlayFinalLapMusicHook

.org 0x11C890
JAL ExecuteItemHook


//original hook placement
.org 0x34BC //RAM address 0x800028BC
J GlobalCustomCode
NOP




.org 0x72094
JAL KWKumo_Alloc_Hook
.org 0x7209C
JAL KWKumo_Alloc_Hook
.org 0x72464
JAL KWKumo_Alloc_Hook
.org 0x7246C
JAL KWKumo_Alloc_Hook
.org 0x7266C
JAL KWKumo_Alloc_Hook
.org 0x72674
JAL KWKumo_Alloc_Hook


.org 0x5A9A4
JAL KWChart_Kumo_Hook
.org 0x5AA00
JAL KWChart_Kumo_Hook
.org 0x5AA10
JAL KWChart_Kumo_Hook
.org 0x5AA60
JAL KWChart_Kumo_Hook
.org 0x5AA98
JAL KWChart_Kumo_Hook
.org 0x5AAF0
JAL KWChart_Kumo_Hook
.org 0x5AB28
JAL KWChart_Kumo_Hook
.org 0x5AD00
JAL KWChart_Kumo_Hook

//EventDisplay Hooks
.org 0x058EB4
JAL EventDisplay
.org 0x058F7C
JAL EventDisplay
.org 0x059044
JAL EventDisplay
.org 0x059120
JAL EventDisplay
//EventDisplay_After Hooks
.org 0x0592E4
JAL EventDisplay_After
.org 0x05938C
JAL EventDisplay_After
.org 0x059434
JAL EventDisplay_After
.org 0x0594DC
JAL EventDisplay_After

//CommonGameEvent Hooks
.org 0x05AA18
JAL CommonGameEventChart
.org 0x05AAA8
JAL CommonGameEventChart
.org 0x05AB38
JAL CommonGameEventChart
.org 0x05AC50
JAL CommonGameEventChart
.org 0x05AD08
JAL CommonGameEventChart




//1p
.org 0x2214
J race1P
NOP
//2p
.org 0x269C
J race2P
NOP
.org 0x24F4
J race2PLR
NOP
//mp
.org 0x28F8
J raceMP
NOP



//title screen hook
.org 0x957D0 //RAM address 0x80094BD0
J CustomCodeTitleScreen
NOP




//3D Screen-Perspective Correct Draw 
.org 0x10CB44
J FreeDraw
NOP



//Push the level-data cache to EOF
.org 0x113FBA
.halfword 0x8080
.org 0x113FCE
.byte 0x00




//Code for auto-displaying custom crash screen
.org 0x0051E8
JAL DisplayCrashScreen
.org 0x5200
NOP
.org 0x5240
NOP

//Auto draw without button imprompt
.org 0xDD2FC
.halfword 0xFFFF
//




//Custom objects using the standard object array
//
.org 0x10C7E2
.halfword hi(DisplayHopTable)
.org 0x10C7EA
.halfword lo(DisplayHopTable)
.org 0x10C7D6
.halfword(100)
.org 0x109AAA
.halfword hi(CollisionHopTable)
.org 0x109AB2
.halfword lo(CollisionHopTable)
.org 0x109A92
.halfword(100)




//Disable the Goal Flag Gate / Starting Line Banner
//Ran manually from DrawPerScreen
.org 0x10C7A4
NOP
NOP

//Disable BackgroundFlag to control ourselves via gameCode
//Stops the sky from being drawn. 
.org 0x0F93D8
NOP
NOP
.org 0x0F8B64
NOP
NOP
.org 0x0F9214
NOP
NOP
.org 0x0F8278
NOP
NOP



//Custom triangle collision check
.org 0x11746C
JAL custom_check_triangle_zx
.org 0x1176BC
JAL custom_check_triangle_zx
.org 0x115950
JAL custom_check_triangle_zx
.org 0x115B78
JAL custom_check_triangle_zx

.org 0x1174B0
JAL custom_check_triangle_xy
.org 0x117758
JAL custom_check_triangle_xy
.org 0x1159A8
JAL custom_check_triangle_xy
.org 0x115CB8
JAL custom_check_triangle_xy

.org 0x1174EC
JAL custom_check_triangle_yz
.org 0x117710
JAL custom_check_triangle_yz
.org 0x1158FC
JAL custom_check_triangle_yz
.org 0x115C34
JAL custom_check_triangle_yz

.org 0x0922B0
JAL custom_check_bump
.org 0x00EB2C
JAL custom_check_bump
.org 0x0890DC
JAL custom_check_bump
.org 0x00DC3C
JAL custom_check_bump
.org 0x00DAA0
JAL custom_check_bump
.org 0x01F558
JAL custom_check_bump

.org 0x030584
JAL custom_check_bump_2
.org 0x039BE0
JAL custom_check_bump_2
.org 0x02F77C
JAL custom_check_bump_2
.org 0x02E818
JAL custom_check_bump_2

.org 0x117014
JAL custom_check_triangle_zx_v
.org 0x11729C
JAL custom_check_triangle_zx_v
.org 0x119208
JAL custom_check_triangle_zx_v
.org 0x119514
JAL custom_check_triangle_zx_v

.org 0x117070
JAL custom_check_triangle_xy_v
.org 0x117358
JAL custom_check_triangle_xy_v
.org 0x1192C4
JAL custom_check_triangle_xy_v
.org 0x119718
JAL custom_check_triangle_xy_v

.org 0x1170BC
JAL custom_check_triangle_yz_v
.org 0x117300
JAL custom_check_triangle_yz_v
.org 0x11914C
JAL custom_check_triangle_yz_v
.org 0x119628
JAL custom_check_triangle_yz_v

//Custom Spin Kart
.org 0x029788
JAL custom_SpinKart
.org 0x0298FC
JAL custom_SpinKart
.org 0x029A38
JAL custom_SpinKart

//Custom Run Kart
.org 0x029798
JAL custom_RunKart
.org 0x0297FC
JAL custom_RunKart
.org 0x02990C
JAL custom_RunKart
.org 0x029A48
JAL custom_RunKart

.ifndef CFLG_LapCounter

//Disable the LapCounter (LAP 1/3)


.org 0x04F38C
jr RA
NOP
.endif
