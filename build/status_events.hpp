#pragma once

constexpr uint32_t StatusEvent_None                      { 0x00000000 };
constexpr uint32_t StatusEvent_SelCodeChange             { 0x00000001 };
constexpr uint32_t StatusEvent_PlayQueueChange           { 0x00000002 };
constexpr uint32_t StatusEvent_NowPlayingChange          { 0x00000004 };
constexpr uint32_t StatusEvent_TimerChange               { 0x00000008 };
constexpr uint32_t StatusEvent_CreditsChange             { 0x00000010 };
constexpr uint32_t StatusEvent_SongStart                 { 0x00000020 };
constexpr uint32_t StatusEvent_SongStop                  { 0x00000040 };
constexpr uint32_t StatusEvent_AttractModeModeChange     { 0x00000080 };
constexpr uint32_t StatusEvent_LoopModeChange            { 0x00000100 };
constexpr uint32_t StatusEvent_FreeplayModeChange        { 0x00000200 };
constexpr uint32_t StatusEvent_VolumeChange              { 0x00000400 };
constexpr uint32_t StatusEvent_ButtonChange              { 0x00000800 };
constexpr uint32_t StatusEvent_TitleStripMoveChange      { 0x00001000 };
// constexpr uint32_t StatusEvent_TitleStripMoveRightInit   { 0x00002000 };
constexpr uint32_t StatusEvent_OneSecondChange           { 0x00004000 };
constexpr uint32_t StatusEvent_SongLoad                  { 0x00008000 };
constexpr uint32_t StatusEvent_SongUnload                { 0x00010000 };
constexpr uint32_t StatusEvent_MuteChange                { 0x00020000 };
constexpr uint32_t StatusEvent_NewArtwork                { 0x00040000 };
constexpr uint32_t StatusEvent_SongPauseChange           { 0x00080000 };
constexpr uint32_t StatusEvent_ChooseSong                { 0x00100000 };
constexpr uint32_t StatusEvent_SongVideoShow             { 0x00200000 };
constexpr uint32_t StatusEvent_SongVideoStart            { 0x00400000 };
constexpr uint32_t StatusEvent_SongVideoStop             { 0x00800000 };
constexpr uint32_t StatusEvent_FlagChange                { 0x01000000 };
constexpr uint32_t StatusEvent_AudioBandsChange          { 0x02000000 };
constexpr uint32_t StatusEvent_ScrollText                { 0x04000000 };
constexpr uint32_t StatusEvent_StartAttractModeTimer     { 0x08000000 };
constexpr uint32_t StatusEvent_StopAttractModeTimer      { 0x10000000 };
constexpr uint32_t StatusEvent_ICYDataReady              { 0x20000000 };
constexpr uint32_t StatusEvent_NewDatabaseSearch         { 0x40000000 };
constexpr uint32_t StatusEvent_InitEmpty                 { 0x80000000 };

constexpr uint32_t StatusEvent_status {
  StatusEvent_InitEmpty
};

constexpr uint32_t StatusEvent_joystick {
  StatusEvent_None
};

constexpr uint32_t StatusEvent_TouchSong {
  StatusEvent_None
};

constexpr uint32_t StatusEvent_bitmap {
  StatusEvent_None
};

constexpr uint32_t StatusEvent_titleStrips {
  StatusEvent_TitleStripMoveChange
};

constexpr uint32_t StatusEvent_spectrum_analyser {
  StatusEvent_AudioBandsChange
};

constexpr uint32_t StatusEvent_init {
  StatusEvent_InitEmpty |
  StatusEvent_OneSecondChange |
  StatusEvent_SelCodeChange |
  StatusEvent_PlayQueueChange |
  StatusEvent_TimerChange |
  StatusEvent_CreditsChange |
  StatusEvent_SongStop |
  StatusEvent_AttractModeModeChange |
  StatusEvent_LoopModeChange |
  StatusEvent_FreeplayModeChange |
  StatusEvent_VolumeChange |
  StatusEvent_ButtonChange
};

