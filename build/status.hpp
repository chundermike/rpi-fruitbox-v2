#pragma once

#include "fruitbox.hpp"

#define STATUS_VAR_START                            255
#define STATUS_CODE_PARAM_NONE                      254
#define STATUS_IF_SKIP_UNDEFINED                    254
#define STATUS_VAR_OFFSET                           1  /* prevents null (0) character as STATUS_VAR code) */

#define STATUS_VAR_NOW_PLAYING_TITLE                (STATUS_VAR_OFFSET + 0)
#define STATUS_VAR_NOW_PLAYING_STREAM_TITLE         (STATUS_VAR_OFFSET + 1)
#define STATUS_VAR_NOW_PLAYING_STREAM_URL           (STATUS_VAR_OFFSET + 2)
#define STATUS_VAR_NOW_PLAYING_ARTIST               (STATUS_VAR_OFFSET + 3)
#define STATUS_VAR_NOW_PLAYING_ALBUM                (STATUS_VAR_OFFSET + 4)
#define STATUS_VAR_NOW_PLAYING_ALBUM_ARTIST         (STATUS_VAR_OFFSET + 5)
#define STATUS_VAR_NOW_PLAYING_TRACK_NUMBER         (STATUS_VAR_OFFSET + 6)
#define STATUS_VAR_NOW_PLAYING_YEAR                 (STATUS_VAR_OFFSET + 7)
#define STATUS_VAR_NOW_PLAYING_GENRE                (STATUS_VAR_OFFSET + 8)
#define STATUS_VAR_NOW_PLAYING_PUBLISHER            (STATUS_VAR_OFFSET + 9)
#define STATUS_VAR_NOW_PLAYING_ISRC                 (STATUS_VAR_OFFSET + 10)
#define STATUS_VAR_NOW_PLAYING_CUSTOM_TAG           (STATUS_VAR_OFFSET + 11)
#define STATUS_VAR_NOW_PLAYING_LENGTH               (STATUS_VAR_OFFSET + 12)
#define STATUS_VAR_NOW_PLAYING_ELAPSED_TIME         (STATUS_VAR_OFFSET + 13)
#define STATUS_VAR_NOW_PLAYING_TIME_REMAINING       (STATUS_VAR_OFFSET + 14)
#define STATUS_VAR_NOW_PLAYING_ARTWORK              (STATUS_VAR_OFFSET + 15)
#define STATUS_VAR_COMING_UP_NUM_SONGS              (STATUS_VAR_OFFSET + 16)
#define STATUS_VAR_COMING_UP_TOTAL_TIME             (STATUS_VAR_OFFSET + 17)
#define STATUS_VAR_COMING_UP_TITLE                  (STATUS_VAR_OFFSET + 18)
#define STATUS_VAR_COMING_UP_ARTIST                 (STATUS_VAR_OFFSET + 19)
#define STATUS_VAR_COMING_UP_ALBUM                  (STATUS_VAR_OFFSET + 20)
#define STATUS_VAR_COMING_UP_ALBUM_ARTIST           (STATUS_VAR_OFFSET + 21)
#define STATUS_VAR_COMING_UP_TRACK_NUMBER           (STATUS_VAR_OFFSET + 22)
#define STATUS_VAR_COMING_UP_YEAR                   (STATUS_VAR_OFFSET + 23)
#define STATUS_VAR_COMING_UP_GENRE                  (STATUS_VAR_OFFSET + 24)
#define STATUS_VAR_COMING_UP_PUBLISHER              (STATUS_VAR_OFFSET + 25)
#define STATUS_VAR_COMING_UP_ISRC                   (STATUS_VAR_OFFSET + 26)
#define STATUS_VAR_COMING_UP_CUSTOM_TAG             (STATUS_VAR_OFFSET + 27)
#define STATUS_VAR_COMING_UP_LENGTH                 (STATUS_VAR_OFFSET + 28)
#define STATUS_VAR_LAST_PLAYED_TITLE                (STATUS_VAR_OFFSET + 29)
#define STATUS_VAR_LAST_PLAYED_ARTIST               (STATUS_VAR_OFFSET + 30)
#define STATUS_VAR_LAST_PLAYED_ALBUM                (STATUS_VAR_OFFSET + 31)
#define STATUS_VAR_LAST_PLAYED_ALBUM_ARTIST         (STATUS_VAR_OFFSET + 32)
#define STATUS_VAR_LAST_PLAYED_TRACK_NUMBER         (STATUS_VAR_OFFSET + 33)
#define STATUS_VAR_LAST_PLAYED_YEAR                 (STATUS_VAR_OFFSET + 34)
#define STATUS_VAR_LAST_PLAYED_GENRE                (STATUS_VAR_OFFSET + 35)
#define STATUS_VAR_LAST_PLAYED_PUBLISHER            (STATUS_VAR_OFFSET + 36)
#define STATUS_VAR_LAST_PLAYED_ISRC                 (STATUS_VAR_OFFSET + 37)
#define STATUS_VAR_LAST_PLAYED_CUSTOM_TAG           (STATUS_VAR_OFFSET + 38)
#define STATUS_VAR_LAST_PLAYED_LENGTH               (STATUS_VAR_OFFSET + 39)
#define STATUS_VAR_CREDITS                          (STATUS_VAR_OFFSET + 40)
#define STATUS_VAR_SONGS_CREDITED                   (STATUS_VAR_OFFSET + 41)
#define STATUS_VAR_ATTRACT_MODE_GENRE               (STATUS_VAR_OFFSET + 42)
#define STATUS_VAR_CREDITS_PER_COIN1                (STATUS_VAR_OFFSET + 43)
#define STATUS_VAR_CREDITS_PER_COIN2                (STATUS_VAR_OFFSET + 44)
#define STATUS_VAR_CREDITS_PER_COIN3                (STATUS_VAR_OFFSET + 45)
#define STATUS_VAR_CREDITS_PER_COIN4                (STATUS_VAR_OFFSET + 46)
#define STATUS_VAR_CREDITS_PER_COIN5                (STATUS_VAR_OFFSET + 47)
#define STATUS_VAR_CREDITS_PER_COIN6                (STATUS_VAR_OFFSET + 48)
#define STATUS_VAR_CREDITS_PER_SONG                 (STATUS_VAR_OFFSET + 49)
#define STATUS_VAR_VOLUME                           (STATUS_VAR_OFFSET + 50)
#define STATUS_VAR_SELECT_CODE                      (STATUS_VAR_OFFSET + 51)
#define STATUS_VAR_NUM_SONGS                        (STATUS_VAR_OFFSET + 52)
#define STATUS_VAR_NUM_SEARCH_SONGS                 (STATUS_VAR_OFFSET + 53)
#define STATUS_VAR_PLAYQUEUE_SPACE                  (STATUS_VAR_OFFSET + 54)
#define STATUS_VAR_NUM_TITLE_STRIPS                 (STATUS_VAR_OFFSET + 55)
#define STATUS_VAR_FIRST_VISIBLE_TITLE_STRIP        (STATUS_VAR_OFFSET + 56)
#define STATUS_VAR_LAST_VISIBLE_TITLE_STRIP         (STATUS_VAR_OFFSET + 57)
#define STATUS_VAR_TOTAL_SONGS_PLAYED               (STATUS_VAR_OFFSET + 58)
#define STATUS_VAR_TOTAL_SONGS_TIME                 (STATUS_VAR_OFFSET + 59)
#define STATUS_VAR_SET_GPIO_00_HI                   (STATUS_VAR_OFFSET + 60)
#define STATUS_VAR_SET_GPIO_00_LO                   (STATUS_VAR_OFFSET + 61)
#define STATUS_VAR_SET_GPIO_01_HI                   (STATUS_VAR_OFFSET + 62)
#define STATUS_VAR_SET_GPIO_01_LO                   (STATUS_VAR_OFFSET + 63)
#define STATUS_VAR_SET_GPIO_02_HI                   (STATUS_VAR_OFFSET + 64)
#define STATUS_VAR_SET_GPIO_02_LO                   (STATUS_VAR_OFFSET + 65)
#define STATUS_VAR_SET_GPIO_03_HI                   (STATUS_VAR_OFFSET + 66)
#define STATUS_VAR_SET_GPIO_03_LO                   (STATUS_VAR_OFFSET + 67)
#define STATUS_VAR_SET_GPIO_04_HI                   (STATUS_VAR_OFFSET + 68)
#define STATUS_VAR_SET_GPIO_04_LO                   (STATUS_VAR_OFFSET + 69)
#define STATUS_VAR_SET_GPIO_05_HI                   (STATUS_VAR_OFFSET + 70)
#define STATUS_VAR_SET_GPIO_05_LO                   (STATUS_VAR_OFFSET + 71)
#define STATUS_VAR_SET_GPIO_06_HI                   (STATUS_VAR_OFFSET + 72)
#define STATUS_VAR_SET_GPIO_06_LO                   (STATUS_VAR_OFFSET + 73)
#define STATUS_VAR_SET_GPIO_07_HI                   (STATUS_VAR_OFFSET + 74)
#define STATUS_VAR_SET_GPIO_07_LO                   (STATUS_VAR_OFFSET + 75)
#define STATUS_VAR_SET_GPIO_08_HI                   (STATUS_VAR_OFFSET + 76)
#define STATUS_VAR_SET_GPIO_08_LO                   (STATUS_VAR_OFFSET + 77)
#define STATUS_VAR_SET_GPIO_09_HI                   (STATUS_VAR_OFFSET + 78)
#define STATUS_VAR_SET_GPIO_09_LO                   (STATUS_VAR_OFFSET + 79)
#define STATUS_VAR_SET_GPIO_10_HI                   (STATUS_VAR_OFFSET + 80)
#define STATUS_VAR_SET_GPIO_10_LO                   (STATUS_VAR_OFFSET + 81)
#define STATUS_VAR_SET_GPIO_11_HI                   (STATUS_VAR_OFFSET + 82)
#define STATUS_VAR_SET_GPIO_11_LO                   (STATUS_VAR_OFFSET + 83)
#define STATUS_VAR_SET_GPIO_12_HI                   (STATUS_VAR_OFFSET + 84)
#define STATUS_VAR_SET_GPIO_12_LO                   (STATUS_VAR_OFFSET + 85)
#define STATUS_VAR_SET_GPIO_13_HI                   (STATUS_VAR_OFFSET + 86)
#define STATUS_VAR_SET_GPIO_13_LO                   (STATUS_VAR_OFFSET + 87)
#define STATUS_VAR_SET_GPIO_14_HI                   (STATUS_VAR_OFFSET + 88)
#define STATUS_VAR_SET_GPIO_14_LO                   (STATUS_VAR_OFFSET + 89)
#define STATUS_VAR_SET_GPIO_15_HI                   (STATUS_VAR_OFFSET + 90)
#define STATUS_VAR_SET_GPIO_15_LO                   (STATUS_VAR_OFFSET + 91)
#define STATUS_VAR_SET_GPIO_16_HI                   (STATUS_VAR_OFFSET + 92)
#define STATUS_VAR_SET_GPIO_16_LO                   (STATUS_VAR_OFFSET + 93)
#define STATUS_VAR_SET_GPIO_17_HI                   (STATUS_VAR_OFFSET + 94)
#define STATUS_VAR_SET_GPIO_17_LO                   (STATUS_VAR_OFFSET + 95)
#define STATUS_VAR_SET_GPIO_18_HI                   (STATUS_VAR_OFFSET + 96)
#define STATUS_VAR_SET_GPIO_18_LO                   (STATUS_VAR_OFFSET + 97)
#define STATUS_VAR_SET_GPIO_19_HI                   (STATUS_VAR_OFFSET + 98)
#define STATUS_VAR_SET_GPIO_19_LO                   (STATUS_VAR_OFFSET + 99)
#define STATUS_VAR_SET_GPIO_20_HI                   (STATUS_VAR_OFFSET + 100)
#define STATUS_VAR_SET_GPIO_20_LO                   (STATUS_VAR_OFFSET + 101)
#define STATUS_VAR_SET_GPIO_21_HI                   (STATUS_VAR_OFFSET + 102)
#define STATUS_VAR_SET_GPIO_21_LO                   (STATUS_VAR_OFFSET + 103)
#define STATUS_VAR_SET_GPIO_22_HI                   (STATUS_VAR_OFFSET + 104)
#define STATUS_VAR_SET_GPIO_22_LO                   (STATUS_VAR_OFFSET + 105)
#define STATUS_VAR_SET_GPIO_23_HI                   (STATUS_VAR_OFFSET + 106)
#define STATUS_VAR_SET_GPIO_23_LO                   (STATUS_VAR_OFFSET + 107)
#define STATUS_VAR_SET_GPIO_24_HI                   (STATUS_VAR_OFFSET + 108)
#define STATUS_VAR_SET_GPIO_24_LO                   (STATUS_VAR_OFFSET + 109)
#define STATUS_VAR_SET_GPIO_25_HI                   (STATUS_VAR_OFFSET + 110)
#define STATUS_VAR_SET_GPIO_25_LO                   (STATUS_VAR_OFFSET + 111)
#define STATUS_VAR_SET_GPIO_26_HI                   (STATUS_VAR_OFFSET + 112)
#define STATUS_VAR_SET_GPIO_26_LO                   (STATUS_VAR_OFFSET + 113)
#define STATUS_VAR_SET_GPIO_27_HI                   (STATUS_VAR_OFFSET + 114)
#define STATUS_VAR_SET_GPIO_27_LO                   (STATUS_VAR_OFFSET + 115)
#define STATUS_VAR_SET_FLAG_1_HI                    (STATUS_VAR_OFFSET + 116)
#define STATUS_VAR_SET_FLAG_1_LO                    (STATUS_VAR_OFFSET + 117)
#define STATUS_VAR_SET_FLAG_2_HI                    (STATUS_VAR_OFFSET + 118)
#define STATUS_VAR_SET_FLAG_2_LO                    (STATUS_VAR_OFFSET + 119)
#define STATUS_VAR_SET_FLAG_3_HI                    (STATUS_VAR_OFFSET + 120)
#define STATUS_VAR_SET_FLAG_3_LO                    (STATUS_VAR_OFFSET + 121)
#define STATUS_VAR_SET_FLAG_4_HI                    (STATUS_VAR_OFFSET + 122)
#define STATUS_VAR_SET_FLAG_4_LO                    (STATUS_VAR_OFFSET + 123)
#define STATUS_VAR_NO_DRAW                          (STATUS_VAR_OFFSET + 124)
#define STATUS_VAR_SET_VISIBLE                      (STATUS_VAR_OFFSET + 125)
#define STATUS_VAR_SET_NOT_VISIBLE                  (STATUS_VAR_OFFSET + 126)
#define STATUS_VAR_DRAW_BITMAP                      (STATUS_VAR_OFFSET + 127)
#define STATUS_VAR_DRAW_RANDOM_BITMAP               (STATUS_VAR_OFFSET + 128)
#define STATUS_VAR_UNDRAW_BITMAP                    (STATUS_VAR_OFFSET + 129)
#define STATUS_VAR_DRAW_VIDEO                       (STATUS_VAR_OFFSET + 130)
#define STATUS_VAR_UNDRAW_VIDEO                     (STATUS_VAR_OFFSET + 131)
#define STATUS_VAR_START_VIDEO                      (STATUS_VAR_OFFSET + 132)
#define STATUS_VAR_STOP_VIDEO                       (STATUS_VAR_OFFSET + 133)
#define STATUS_VAR_PAUSE_VIDEO                      (STATUS_VAR_OFFSET + 134)
#define STATUS_VAR_UNPAUSE_VIDEO                    (STATUS_VAR_OFFSET + 135)
#define STATUS_VAR_STOP_TIMER                       (STATUS_VAR_OFFSET + 136)
#define STATUS_VAR_START_TIMER                      (STATUS_VAR_OFFSET + 137)
#define STATUS_VAR_RESET_TIMER                      (STATUS_VAR_OFFSET + 138)
#define STATUS_VAR_PLAY_SOUND                       (STATUS_VAR_OFFSET + 139)
#define STATUS_VAR_STOP_SOUND                       (STATUS_VAR_OFFSET + 140)
#define STATUS_VAR_IF_FREEPLAY                      (STATUS_VAR_OFFSET + 141)
#define STATUS_VAR_IF_NOT_FREEPLAY                  (STATUS_VAR_OFFSET + 142)
#define STATUS_VAR_IF_NO_CREDITS                    (STATUS_VAR_OFFSET + 143)
#define STATUS_VAR_IF_ANY_CREDITS                   (STATUS_VAR_OFFSET + 144)
#define STATUS_VAR_IF_SONG_PLAYING                  (STATUS_VAR_OFFSET + 145)
#define STATUS_VAR_IF_NOT_SONG_PLAYING              (STATUS_VAR_OFFSET + 146)
#define STATUS_VAR_IF_ATTRACT_PLAYING               (STATUS_VAR_OFFSET + 147)
#define STATUS_VAR_IF_NOT_ATTRACT_PLAYING           (STATUS_VAR_OFFSET + 148)
#define STATUS_VAR_IF_FILE_PLAYING                  (STATUS_VAR_OFFSET + 149)
#define STATUS_VAR_IF_NOT_FILE_PLAYING              (STATUS_VAR_OFFSET + 150)
#define STATUS_VAR_IF_VIDEO_PLAYING                 (STATUS_VAR_OFFSET + 151)
#define STATUS_VAR_IF_NOT_VIDEO_PLAYING             (STATUS_VAR_OFFSET + 152)
#define STATUS_VAR_IF_STREAM_PLAYING                (STATUS_VAR_OFFSET + 153)
#define STATUS_VAR_IF_NOT_STREAM_PLAYING            (STATUS_VAR_OFFSET + 154)
#define STATUS_VAR_IF_SONG_LOADING                  (STATUS_VAR_OFFSET + 155)
#define STATUS_VAR_IF_NOT_SONG_LOADING              (STATUS_VAR_OFFSET + 156)
#define STATUS_VAR_IF_SONG_UNLOADING                (STATUS_VAR_OFFSET + 157)
#define STATUS_VAR_IF_NOT_SONG_UNLOADING            (STATUS_VAR_OFFSET + 158)
#define STATUS_VAR_IF_ANY_COMING_UP                 (STATUS_VAR_OFFSET + 159)
#define STATUS_VAR_IF_NONE_COMING_UP                (STATUS_VAR_OFFSET + 160)
#define STATUS_VAR_IF_SONG_COMING_UP                (STATUS_VAR_OFFSET + 161)
#define STATUS_VAR_IF_ATTRACT_MODE                  (STATUS_VAR_OFFSET + 162)
#define STATUS_VAR_IF_NOT_ATTRACT_MODE              (STATUS_VAR_OFFSET + 163)
#define STATUS_VAR_IF_LOOPQUEUE_MODE                (STATUS_VAR_OFFSET + 164)
#define STATUS_VAR_IF_NOT_LOOPQUEUE_MODE            (STATUS_VAR_OFFSET + 165)
#define STATUS_VAR_IF_TIMER_HI                      (STATUS_VAR_OFFSET + 166)
#define STATUS_VAR_IF_TIMER_LO                      (STATUS_VAR_OFFSET + 167)
#define STATUS_VAR_IF_TIMER_TICK                    (STATUS_VAR_OFFSET + 168)
#define STATUS_VAR_IF_MUTE                          (STATUS_VAR_OFFSET + 169)
#define STATUS_VAR_IF_NOT_MUTE                      (STATUS_VAR_OFFSET + 170)
#define STATUS_VAR_IF_TITLE_STRIP_MOVING            (STATUS_VAR_OFFSET + 171)
#define STATUS_VAR_IF_NOT_TITLE_STRIP_MOVING        (STATUS_VAR_OFFSET + 172)
#define STATUS_VAR_IF_PLAYQUEUE_EMPTY               (STATUS_VAR_OFFSET + 173)
#define STATUS_VAR_IF_NOT_PLAYQUEUE_EMPTY           (STATUS_VAR_OFFSET + 174)
#define STATUS_VAR_IF_PLAYQUEUE_FULL                (STATUS_VAR_OFFSET + 175)
#define STATUS_VAR_IF_NOT_PLAYQUEUE_FULL            (STATUS_VAR_OFFSET + 176)
#define STATUS_VAR_IF_STEREO                        (STATUS_VAR_OFFSET + 177)
#define STATUS_VAR_IF_NOT_STEREO                    (STATUS_VAR_OFFSET + 178)
#define STATUS_VAR_IF_PAUSED                        (STATUS_VAR_OFFSET + 179)
#define STATUS_VAR_IF_NOT_PAUSED                    (STATUS_VAR_OFFSET + 180)
#define STATUS_VAR_IF_INSTANT_PLAY                  (STATUS_VAR_OFFSET + 181)
#define STATUS_VAR_IF_NOT_INSTANT_PLAY              (STATUS_VAR_OFFSET + 182)
#define STATUS_VAR_IF_INVALID_CHOICE                (STATUS_VAR_OFFSET + 183)
#define STATUS_VAR_IF_NOT_INVALID_CHOICE            (STATUS_VAR_OFFSET + 184)
#define STATUS_VAR_IF_DUPLICATE_CHOICE              (STATUS_VAR_OFFSET + 185)
#define STATUS_VAR_IF_NOT_DUPLICATE_CHOICE          (STATUS_VAR_OFFSET + 186)
#define STATUS_VAR_IF_VISIBLE                       (STATUS_VAR_OFFSET + 187)
#define STATUS_VAR_IF_NOT_VISIBLE                   (STATUS_VAR_OFFSET + 188)
#define STATUS_VAR_IF_FLAG_HI                       (STATUS_VAR_OFFSET + 189)
#define STATUS_VAR_IF_FLAG_LO                       (STATUS_VAR_OFFSET + 190)
//                                                                       191 // placemarkers for FLAGS 2..4
//                                                                       192
//                                                                       193
//                                                                       194
//                                                                       195
//                                                                       196
#define STATUS_VAR_END_IF                           (STATUS_VAR_OFFSET + 197)
#define STATUS_VAR_ELSE                             (STATUS_VAR_OFFSET + 198)

// IF_BUTTON and IF_NOT_BUTTON entries must be the last here (so nothing after them except STATUS_VAR_NULL) ...

#define STATUS_VAR_IF_BUTTON_PRESSED                (STATUS_VAR_OFFSET + 199)
#define STATUS_VAR_IF_NOT_BUTTON_PRESSED            (STATUS_VAR_OFFSET + 200)

#define STATUS_VAR_NULL                             (STATUS_VAR_OFFSET + 201)


const char STAT_DESC_NULL[] = {""};
const char STAT_DESC_NPTI[] = {"The name of the song which is currently playing"};
const char STAT_DESC_NPST[] = {"The StreamTitle of the currently playing radio program"};
const char STAT_DESC_NPSU[] = {"The StreamUrl of the currently playing radio program"};
const char STAT_DESC_NPAR[] = {"The name of the artist of the song which is currently playing"};
const char STAT_DESC_NPAL[] = {"The name of the album of the song which is currently playing"};
const char STAT_DESC_NPAA[] = {"The name of the album artist of the song which is currently playing"};
const char STAT_DESC_NPTN[] = {"The track number of the song which is currently playing"};
const char STAT_DESC_NPYR[] = {"The year of the song which is currently playing"};
const char STAT_DESC_NPGN[] = {"The genre of the song which is currently playing"};
const char STAT_DESC_NPPU[] = {"The publisher of the song which is currently playing"};
const char STAT_DESC_NPIS[] = {"The ISRC of the song which is currently playing"};
const char STAT_DESC_NPCT[] = {"The custom MP3 tag of the song which is currently playing"};
const char STAT_DESC_NPLE[] = {"The length in mm:ss of the currently playing song"};
const char STAT_DESC_NPET[] = {"The elapsed time in mm:ss of the currently playing song"};
const char STAT_DESC_NPRT[] = {"The remaining time in mm:ss of the currently playing song"};
const char STAT_DESC_NPAT[] = {"The cover artwork of the currently playing song.  "
                              "The artwork will occupy the entire status box, and is drawn before any text.  " \
                              "The actual artwork displayed will depend upon the value of the [general] 'ArtworkMode' configuration setting."};
const char STAT_DESC_CUNS[] = {"The number of songs coming up in the play queue"};
const char STAT_DESC_CUTT[] = {"The total play time in hh:mm:ss of the songs in the play queue"};
const char STAT_DESC_CUTI[] = {"The title of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUAL[] = {"The album name of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUAR[] = {"The artist name of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUAA[] = {"The album artist name of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUTN[] = {"The track number of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUYR[] = {"The year of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUGN[] = {"The genre of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUPU[] = {"The publisher of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUIS[] = {"The ISRC of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CUCT[] = {"The custom MP3 tag of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};
const char STAT_DESC_CULE[] = {"The length in mm:ss of a song in the play queue.  Each time this reserved word is used, it refers to the next song after the last one referenced"};

const char STAT_DESC_LPTI[] = {"The name of the song which was last played"};
const char STAT_DESC_LPAR[] = {"The name of the artist of the song which was last played"};
const char STAT_DESC_LPAL[] = {"The name of the album of the song which was last played"};
const char STAT_DESC_LPAA[] = {"The name of the album artist of the song which was last played"};
const char STAT_DESC_LPTN[] = {"The track number of the song which was last played"};
const char STAT_DESC_LPYR[] = {"The year of the song which was last played"};
const char STAT_DESC_LPGN[] = {"The genre of the song which was last played"};
const char STAT_DESC_LPPU[] = {"The publisher of the song which was last played"};
const char STAT_DESC_LPIS[] = {"The ISRC of the song which was last played"};
const char STAT_DESC_LPCT[] = {"The custom MP3 tag of the song which was last played"};
const char STAT_DESC_LPLE[] = {"The length in mm:ss of the song which was last played"};

const char STAT_DESC_CRED[] = {"The number of credits"};
const char STAT_DESC_SCRE[] = {"The number of songs available from inserted credits"};
const char STAT_DESC_ATMG[] = {"The name of the current AttractModeGenre that Attract mode will select a random song from"};
const char STAT_DESC_PPCR[] = {"The number of credits added when a coin is inserted"};
const char STAT_DESC_SPCR[] = {"The number of credits used per song play"};
const char STAT_DESC_VOLU[] = {"The song volume"};
const char STAT_DESC_SELC[] = {"The select code"};
const char STAT_DESC_NSON[] = {"The total number of songs in the database"};
const char STAT_DESC_NSFS[] = {"The number of songs from the search"};
const char STAT_DESC_PQSP[] = {"The number of empty spaces in the playqueue"};
const char STAT_DESC_NPAG[] = {"The total number of title strips in the jukebox"};
const char STAT_DESC_FVPA[] = {"The number of the first title strip visible on the display"};
const char STAT_DESC_LVPA[] = {"The number of the last title strip visible on the display"};
const char STAT_DESC_TSPL[] = {"The number of songs played"};
const char STAT_DESC_TSTI[] = {"The total time in hh:mm:ss for the number of songs played"};
const char STAT_DESC_GPHI[] = {"Sets the specified GPIO output high"};
const char STAT_DESC_GPLO[] = {"Sets the specified GPIO output low"};
const char STAT_DESC_FGHI[] = {"Sets the specified status flag high"};
const char STAT_DESC_FGLO[] = {"Sets the specified status flag low"};
const char STAT_DESC_BMPX[] = {"Draw user defined bitmaps, as specified by the Bitmap parameter.  " \
                               "The bitmap will occupy the entire status box, and is drawn after any text.  " \
                               "If multiple bitmaps are defined, they will be drawn in turn, each time the " \
                               "${DRAW_BITMAP} keyword is executed.  Bitmaps remain visible until " \
                               "a ${UNDRAW_BITMAP} command is executed."};
const char STAT_DESC_BMPR[] = {"Draw a random user defined bitmap, chosen from the specified Bitmap parameters."};
const char STAT_DESC_BMPU[] = {"Undraw the bitmap"};
const char STAT_DESC_VIDX[] = {"Draw the video"};
const char STAT_DESC_VIDU[] = {"Undraw the video"};
const char STAT_DESC_STRV[] = {"Start video playing"};
const char STAT_DESC_STPV[] = {"Stop video playing"};
const char STAT_DESC_PAUV[] = {"Pause video playing"};
const char STAT_DESC_UNPV[] = {"Un-pause video playing"};
const char STAT_DESC_STOT[] = {"Stop the status TimerTick timer"};
const char STAT_DESC_STAT[] = {"Start the status TimerTick timer"};
const char STAT_DESC_REST[] = {"Reset the status TimerTick timer"};
const char STAT_DESC_PSND[] = {"Play the sound as defined by the Sound parameter"};
const char STAT_DESC_SSND[] = {"Stop the sound as defined by the Sound parameter"};
const char STAT_DESC_IFSM[] = {"Activates the text following it if the secret menu enabled"};
const char STAT_DESC_INSM[] = {"Activates the text following it if the secret menu disabled"};
const char STAT_DESC_IFFP[] = {"Activates the text following it if Free Play mode is enabled"};
const char STAT_DESC_INFP[] = {"Activates the text following it if Free Play mode is disabled"};
const char STAT_DESC_IFNC[] = {"Activates the text following it if no credits are available"};
const char STAT_DESC_IFCA[] = {"Activates the text following it if credits are available"};
const char STAT_DESC_IFPL[] = {"Activates the text following it if a song is currently playing"};
const char STAT_DESC_IFNP[] = {"Activates the text following it if no song is currently playing"};
const char STAT_DESC_IFAP[] = {"Activates the text following it if a song is currently playing via attract"};
const char STAT_DESC_IFNA[] = {"Activates the text following it if no song is currently playing via attract"};
const char STAT_DESC_IFSF[] = {"Activates the text following it if the song is currently playing is a local mp3 file"};
const char STAT_DESC_IFNF[] = {"Activates the text following it if the song is currently playing is not a local mp3 file"};
const char STAT_DESC_IFSV[] = {"Activates the text following it if the song is currently playing is a video"};
const char STAT_DESC_IFNV[] = {"Activates the text following it if the song is currently playing is not a video"};
const char STAT_DESC_IFSR[] = {"Activates the text following it if the song is currently playing is a streaming (internet radio) song"};
const char STAT_DESC_IFNR[] = {"Activates the text following it if the song is currently playing is not a streaming (internet radio) song"};
const char STAT_DESC_IFLO[] = {"Activates the text following it if a song is currently loading"};
const char STAT_DESC_IFNL[] = {"Activates the text following it if no song is currently loading"};
const char STAT_DESC_IFUL[] = {"Activates the text following it if a song is currently unloading"};
const char STAT_DESC_IFNU[] = {"Activates the text following it if no song is currently unloading"};
const char STAT_DESC_IFAC[] = {"Activates the text following it if any songs are coming up"};
const char STAT_DESC_INCU[] = {"Activates the text following it if no songs are coming up"};
const char STAT_DESC_ISCU[] = {"Activates the text following it if there is another song in the play queue.  This is different to the ${IF_ANY_COMING_UP} " \
                               "keyword because it refers to the next coming up entry rather than the complete play queue"};
const char STAT_DESC_IFRM[] = {"Activates the text following it if Attract mode is enabled"};
const char STAT_DESC_INRM[] = {"Activates the text following it if Attract mode is disabled"};
const char STAT_DESC_IFLM[] = {"Activates the text following it if Loop mode is enabled"};
const char STAT_DESC_INLM[] = {"Activates the text following it if Loop mode is disabled"};
const char STAT_DESC_IFTY[] = {"Activates the text following it if the status timer is high.  " \
                               "The value of 'TimerTickPeriod' for the status object in the configuration file determines the rate at which the timer toggles between high and low.  " \
                               "i.e. TimerTickPeriod = 30 means the timer will be high for 30 video frames, then low for 30 video frames, repeating indefinitely"};
const char STAT_DESC_IFTN[] = {"Activates the text following it if the status timer is low"};
const char STAT_DESC_IFTT[] = {"Activates the text following it when the status timer ticks (each tick occurs every TimerTickPeriod video frames"};
const char STAT_DESC_IFPM[] = {"Activates the text following it when the song title_strips are moving"};
const char STAT_DESC_IFPN[] = {"Activates the text following it when the song title_strips are not moving"};
const char STAT_DESC_IFPE[] = {"Activates the text following it if the play queue is empty\n (includes currently playing song)"};
const char STAT_DESC_INPE[] = {"Activates the text following it if the play queue is not empty\n (includes currently playing song)"};
const char STAT_DESC_IFPF[] = {"Activates the text following it if the play queue is full\n (includes currently playing song)"};
const char STAT_DESC_INPF[] = {"Activates the text following it if the play queue is not full\n (includes currently playing song)"};
const char STAT_DESC_IFST[] = {"Activates the text following it if the current song is stereo"};
const char STAT_DESC_INST[] = {"Activates the text following it if the current song is not stereo"};
const char STAT_DESC_IFPA[] = {"Activates the text following it if the current song is paused"};
const char STAT_DESC_INPA[] = {"Activates the text following it if the current song is not paused"};
const char STAT_DESC_IFIP[] = {"Activates the text following it if Instant Play mode is set"};
const char STAT_DESC_INIP[] = {"Activates the text following it if Instant Play mode is not set"};
const char STAT_DESC_IFIC[] = {"Activates the text following it if the last song selection was invalid"};
const char STAT_DESC_INIC[] = {"Activates the text following it if the last song selection was not invalid"};
const char STAT_DESC_IFDC[] = {"Activates the text following it if the last song selection was a duplicate choice"};
const char STAT_DESC_INDC[] = {"Activates the text following it if the last song selection was not a duplicate choice"};
const char STAT_DESC_IFVI[] = {"Activates the text following it if the status object is visible"};
const char STAT_DESC_INVI[] = {"Activates the text following it if the status object is invisible"};
const char STAT_DESC_IFFH[] = {"Activates the text following it if the specified status flag is high"};
const char STAT_DESC_IFFL[] = {"Activates the text following it if the specified status flag is low"};
const char STAT_DESC_IFMU[] = {"Activates the text following it when the song volume is muted"};
const char STAT_DESC_IFNM[] = {"Activates the text following it when the song volume is not muted"};
const char STAT_DESC_ENIF[] = {"Marks the end of a text section playing by the preceding $IF_"};
const char STAT_DESC_ELSE[] = {"Complement to previous $IF condition"};
const char STAT_DESC_ENND[] = {"Supresses drawing of the status object"};
const char STAT_DESC_SVIS[] = {"Makes the status object visible"};
const char STAT_DESC_SNVI[] = {"Makes the status object invisible"};
const char STAT_DESC_IFBP[] = {"Activates the text following it if the specified button is pressed"};
const char STAT_DESC_INBP[] = {"Activates the text following it if the specified button is not pressed"};
const char STAT_DESC_IFAB[] = {"Activates the text following it if any button is pressed"};
const char STAT_DESC_INAB[] = {"Activates the text following it if any button is not pressed"};


class StatusDisplayClass : public DisplayBaseClass
{
public:

  StatusDisplayClass() { supports_dynamics = true; }
  
  void init(const dynamics2_t sze, const uint32_t emsk);

  bool update(const uint32_t event) override;

  void cfgRead(string line) {
    string str {};
    bitmap_t bm {};
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_Contents,        desc_name)) return;
    if (GetParam(line, cfgKeyword_Output,          output_filename)) return;
    if (GetParam(line, cfgKeyword_Text,            text)) return;
    if (GetParam(line, cfgKeyword_LineSpacing,     line_spacing)) return;
    if (GetParam(line, cfgKeyword_LoopVideo,       loop_video)) return;
    if (GetParam(line, cfgKeyword_TimerTickPeriod, timer_tick_period)) return;
    if (GetParam(line, cfgKeyword_TimerOneShot,    timer_oneshot)) return;
    if (GetParam(line, cfgKeyword_TimerEnable,     timer_enable)) return;
    if (GetParam(line, cfgKeyword_BitmapDirectory, bitmap_directory)) return;
    if (GetParam(line, cfgKeyword_Sound,           sound))
    {
      num_sound_channels++;
      return;
    }
    if (GetParam(line, cfgKeyword_Bitmap, bm)) {
      bitmap_list.push_back(bm.handle);
      return;
    }
    if (GetParam(line, cfgKeyword_Video, video))
    {
      num_sound_channels++;
      return;
    }
    return;
  }

  void DescribeParams(ofstream &strm, const char *indent) {
    DisplayBaseClass::DescribeParams(strm, indent);
    DescribeParam(strm, indent, cfgKeyword_Contents        , cfgKeywordDesc_Contents          , false);
    DescribeParam(strm, indent, cfgKeyword_Output          , cfgKeywordDesc_Output            , false);
    DescribeParam(strm, indent, cfgKeyword_Text            , cfgKeywordDesc_Text              , false);
    DescribeParam(strm, indent, cfgKeyword_LineSpacing     , cfgKeywordDesc_StatusLineSpacing , false);
    DescribeParam(strm, indent, cfgKeyword_LoopVideo       , cfgKeywordDesc_LoopVideo         , false);
    DescribeParam(strm, indent, cfgKeyword_TimerTickPeriod , cfgKeywordDesc_TimerTickPeriod   , false);
    DescribeParam(strm, indent, cfgKeyword_TimerOneShot    , cfgKeywordDesc_TimerOneShot      , false);
    DescribeParam(strm, indent, cfgKeyword_TimerEnable     , cfgKeywordDesc_TimerEnable       , false);
    DescribeParam(strm, indent, cfgKeyword_BitmapDirectory , cfgKeywordDesc_BitmapDirectory   , false);
    DescribeParam(strm, indent, cfgKeyword_Bitmap          , cfgKeywordDesc_Bitmap            , true);
    DescribeParam(strm, indent, cfgKeyword_Video           , cfgKeywordDesc_Video             , false);
    DescribeParam(strm, indent, cfgKeyword_Sound           , cfgKeywordDesc_Sound             , false);
  }

  StatusDisplayClass* clone() const { return new StatusDisplayClass(*this); }

  void draw(void);

  void renew(void) {
    // ensure no parameters from a previous status object are inherited to the next status objects
    desc_name.clear();
    event_mask = 0;
    output_filename.clear();
    loop_video = false;
    timer_tick_period = TimeUnitOneTick;
    timer_oneshot = false;
    timer_enable = true;
    bitmap_list.clear();
    video.handle = nullptr;
    bitmap_directory.clear();
    DisplayBaseClass::renew(); // ResetBaseParams();
  };

  static int BitmapSearch(const char *path, const struct stat *sptr, int type);

  static int32_t if_song_coming_ups;
  static int32_t coming_up_song_title;
  static int32_t coming_up_song_artist;
  static int32_t coming_up_song_album;
  static int32_t coming_up_song_album_artist;
  static int32_t coming_up_song_track_number;
  static int32_t coming_up_song_year;
  static int32_t coming_up_song_genre;
  static int32_t coming_up_song_publisher;
  static int32_t coming_up_song_isrc;
  static int32_t coming_up_song_custom_tag;
  static int32_t coming_up_song_length;
  static uint32_t num_sound_channels;

  static bool funcNowPlayingTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingStreamTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingStreamUrl(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingAlbum(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingAlbumArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingTrackNumber(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingYear(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingPublisher(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingISRC(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingCustomTag(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayinglength(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingElapsedTime(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingTimeRemaining(StatusDisplayClass *s, unsigned char param);
  static bool funcNowPlayingArtwork(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpNumSongs(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpTotalTime(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpAlbum(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpAlbumArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpTrackNumber(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpYear(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpPublisher(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpISRC(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpCustomTag(StatusDisplayClass *s, unsigned char param);
  static bool funcComingUpLength(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedTitle(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedAlbum(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedAlbumArtist(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedTrackNumber(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedYear(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedPublisher(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedISRC(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedCustomTag(StatusDisplayClass *s, unsigned char param);
  static bool funcLastPlayedlength(StatusDisplayClass *s, unsigned char param);
  static bool funcCredits(StatusDisplayClass *s, unsigned char param);
  static bool funcSongsCredited(StatusDisplayClass *s, unsigned char param);
  static bool funcAttractModeGenre(StatusDisplayClass *s, unsigned char param);
  static bool funcCreditsPerCoin(StatusDisplayClass *s, unsigned char param);
  static bool funcCreditsPerSong(StatusDisplayClass *s, unsigned char param);
  static bool funcVolume(StatusDisplayClass *s, unsigned char param);
  static bool funcSelectCode(StatusDisplayClass *s, unsigned char param);
  static bool funcNumSongs(StatusDisplayClass *s, unsigned char param);
  static bool funcNumSearchSongs(StatusDisplayClass *s, unsigned char param);
  static bool funcPlayQueueRemainingSpace(StatusDisplayClass *s, unsigned char param);
  static bool funcNumTitleStrips(StatusDisplayClass *s, unsigned char param);
  static bool funcFirstVisibleTitleStrip(StatusDisplayClass *s, unsigned char param);
  static bool funcLastVisibleTitleStrip(StatusDisplayClass *s, unsigned char param);
  static bool funcTotalPlayedSongs(StatusDisplayClass *s, unsigned char param);
  static bool funcTotalPlayedTime(StatusDisplayClass *s, unsigned char param);
  static bool funcGPIOSetPinHigh(StatusDisplayClass *s, unsigned char param);
  static bool funcGPIOSetPinLow(StatusDisplayClass *s, unsigned char param);
  static bool funcSetFlagLow(StatusDisplayClass *s, unsigned char param);
  static bool funcSetFlagHigh(StatusDisplayClass *s, unsigned char param);
  static bool funcDrawBitmap(StatusDisplayClass *s, unsigned char param);
  static bool funcDrawRandomBitmap(StatusDisplayClass *s, unsigned char param);
  static bool funcUndrawBitmap(StatusDisplayClass *s, unsigned char param);
  static bool funcDrawVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcUndrawVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcStartVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcStopVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcPauseVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcUnPauseVideo(StatusDisplayClass *s, unsigned char param);
  static bool funcStopTimer(StatusDisplayClass *s, unsigned char param);
  static bool funcStartTimer(StatusDisplayClass *s, unsigned char param);
  static bool funcResetTimer(StatusDisplayClass *s, unsigned char param);
  static bool funcPlaySound(StatusDisplayClass *s, unsigned char param);
  static bool funcStopSound(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFreeplay(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotFreeplay(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNoCredits(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAnyCredits(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotSongPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAttractPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotAttractPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFilePlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotFilePlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfVideoPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotVideoPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfStreamPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotStreamPlaying(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongLoading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotSongLoading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongUnloading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotSongUnloading(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAnyComingUp(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNoneComingUp(StatusDisplayClass *s, unsigned char param);
  static bool funcIfSongComingUp(StatusDisplayClass *s, unsigned char param);
  static bool funcIfAttractModeMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotAttractModeMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfLoopMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotLoopMode(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTimerHi(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTimerLo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTimerTick(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTitleStripMoving(StatusDisplayClass *s, unsigned char param);
  static bool funcIfTitleStripNotMoving(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPlayQueueEmpty(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotPlayQueueEmpty(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPlayQueueFull(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotPlayQueueFull(StatusDisplayClass *s, unsigned char param);
  static bool funcIfStereo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotStereo(StatusDisplayClass *s, unsigned char param);
  static bool funcIfPaused(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotPaused(StatusDisplayClass *s, unsigned char param);
  static bool funcIfInstantPlay(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotInstantPlay(StatusDisplayClass *s, unsigned char param);
  static bool funcIfInvalidChoice(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotInvalidChoice(StatusDisplayClass *s, unsigned char param);
  static bool funcIfDuplicateChoice(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotDuplicateChoice(StatusDisplayClass *s, unsigned char param);
  static bool funcIfVisible(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotVisible(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFlagHigh(StatusDisplayClass *s, unsigned char param);
  static bool funcIfFlagLow(StatusDisplayClass *s, unsigned char param);
  static bool funcIfMute(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotMute(StatusDisplayClass *s, unsigned char param);
  static bool funcIfButtonPressed(StatusDisplayClass *s, unsigned char param);
  static bool funcIfNotButtonPressed(StatusDisplayClass *s, unsigned char param);
  static bool funcEndIf(StatusDisplayClass *s, unsigned char param);
  static bool funcNoDraw(StatusDisplayClass *s, unsigned char param);
  static bool funcSetVisible(StatusDisplayClass *s, unsigned char param);
  static bool funcSetNotVisible(StatusDisplayClass *s, unsigned char param);

  string *var_str {};
  bitmap_t artwork_bitmap {};

  string coming_up_song_length_str {};
  vector<ALLEGRO_BITMAP*> bitmap_list {};
  int32_t bitmap_idx {};
  sound_t sound {};

  private:
  void CalculateIfSkips(void);
  // ALLEGRO_BITMAP *status_bitmap {};
  // uints2_t status_bitmap_size {};
  bool draw_bitmap { false };
  bool draw_video { false };
  bool loop_video { false };
  string output_filename {};
  string desc_name {};
  text_t text {};
  uint32_t scroll_offset {};
  uint32_t line_spacing {};
  time_unit_t timer_tick_period { TimeUnitOneTick };
  bool timer_hi { false };
  uint32_t timer_count {};
  bool timer_tick { false };
  bool timer_enable { true };
  bool timer_oneshot { false };
  string bitmap_directory {};
  static vector<string> static_bitmap_name;
  vector<string> bitmap_name;
  vector<status_line_t> lines {};

  string *line {};
  uint32_t line_pos {};
  string dst {};
  video_t video {};
};

struct status_vars_t {
  const string name;
  const string desc;
  unsigned char code;
  unsigned char else_code;
  unsigned char code_param;
  bool is_if;
  bool (*func)(StatusDisplayClass *s, unsigned char param);
  int32_t event_bit;
};



///////////////////////////////////////////////////////////////////////////////

const vector <status_vars_t> (status_vars) {
  {"${NOW_PLAYING_TITLE}",                  STAT_DESC_NPTI, STATUS_VAR_NOW_PLAYING_TITLE,                STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingTitle,         StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_STREAM_TITLE}",           STAT_DESC_NPST, STATUS_VAR_NOW_PLAYING_STREAM_TITLE,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingStreamTitle,   StatusEvent_ICYDataReady},
  {"${NOW_PLAYING_STREAM_URL}",             STAT_DESC_NPSU, STATUS_VAR_NOW_PLAYING_STREAM_URL,           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingStreamUrl,     StatusEvent_ICYDataReady},
  {"${NOW_PLAYING_ARTIST}",                 STAT_DESC_NPAR, STATUS_VAR_NOW_PLAYING_ARTIST,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingArtist,        StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_ALBUM}",                  STAT_DESC_NPAL, STATUS_VAR_NOW_PLAYING_ALBUM,                STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingAlbum,         StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_ALB_ARTIST}",             STAT_DESC_NPAA, STATUS_VAR_NOW_PLAYING_ALBUM_ARTIST,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingAlbumArtist,   StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_TRACK_NUMBER}",           STAT_DESC_NPTN, STATUS_VAR_NOW_PLAYING_TRACK_NUMBER,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingTrackNumber,   StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_YEAR}",                   STAT_DESC_NPYR, STATUS_VAR_NOW_PLAYING_YEAR,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingYear,          StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_GENRE}",                  STAT_DESC_NPGN, STATUS_VAR_NOW_PLAYING_GENRE,                STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingGenre,         StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_PUBLISHER}",              STAT_DESC_NPPU, STATUS_VAR_NOW_PLAYING_PUBLISHER,            STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingPublisher,     StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_ISRC}",                   STAT_DESC_NPIS, STATUS_VAR_NOW_PLAYING_ISRC,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingISRC,          StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_CUSTOM_TAG}",             STAT_DESC_NPCT, STATUS_VAR_NOW_PLAYING_CUSTOM_TAG,           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingCustomTag,     StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_LENGTH}",                 STAT_DESC_NPLE, STATUS_VAR_NOW_PLAYING_LENGTH,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayinglength,        StatusEvent_SongStart | StatusEvent_SongStop},
  {"${NOW_PLAYING_ELAPSED_TIME}",           STAT_DESC_NPET, STATUS_VAR_NOW_PLAYING_ELAPSED_TIME,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingElapsedTime,   StatusEvent_OneSecondChange},
  {"${NOW_PLAYING_TIME_REMAINING}",         STAT_DESC_NPRT, STATUS_VAR_NOW_PLAYING_TIME_REMAINING,       STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingTimeRemaining, StatusEvent_OneSecondChange},
  {"${NOW_PLAYING_ARTWORK}",                STAT_DESC_NPAT, STATUS_VAR_NOW_PLAYING_ARTWORK,              STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNowPlayingArtwork,       StatusEvent_NewArtwork | StatusEvent_PlayQueueChange},
  {"${COMING_UP_NUM_SONGS}",                STAT_DESC_CUNS, STATUS_VAR_COMING_UP_NUM_SONGS,              STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpNumSongs,        StatusEvent_PlayQueueChange},
  {"${COMING_UP_TOTAL_TIME}",               STAT_DESC_CUTT, STATUS_VAR_COMING_UP_TOTAL_TIME,             STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpTotalTime,       StatusEvent_PlayQueueChange},
  {"${COMING_UP_TITLE}",                    STAT_DESC_CUTI, STATUS_VAR_COMING_UP_TITLE,                  STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpTitle,           StatusEvent_PlayQueueChange},
  {"${COMING_UP_ARTIST}",                   STAT_DESC_CUAR, STATUS_VAR_COMING_UP_ARTIST,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpArtist,          StatusEvent_PlayQueueChange},
  {"${COMING_UP_ALBUM}",                    STAT_DESC_CUAL, STATUS_VAR_COMING_UP_ALBUM,                  STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpAlbum,           StatusEvent_PlayQueueChange},
  {"${COMING_UP_ALB_ARTIST}",               STAT_DESC_CUAA, STATUS_VAR_COMING_UP_ALBUM_ARTIST,           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpAlbumArtist,     StatusEvent_PlayQueueChange},
  {"${COMING_UP_TRACK_NUMBER}",             STAT_DESC_CUTN, STATUS_VAR_COMING_UP_TRACK_NUMBER,           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpTrackNumber,     StatusEvent_PlayQueueChange},
  {"${COMING_UP_YEAR}",                     STAT_DESC_CUYR, STATUS_VAR_COMING_UP_YEAR,                   STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpYear,            StatusEvent_PlayQueueChange},
  {"${COMING_UP_GENRE}",                    STAT_DESC_CUGN, STATUS_VAR_COMING_UP_GENRE,                  STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpGenre,           StatusEvent_PlayQueueChange},
  {"${COMING_UP_PUBLISHER}",                STAT_DESC_CUPU, STATUS_VAR_COMING_UP_PUBLISHER,              STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpPublisher,       StatusEvent_PlayQueueChange},
  {"${COMING_UP_ISRC}",                     STAT_DESC_CUIS, STATUS_VAR_COMING_UP_ISRC,                   STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpISRC,            StatusEvent_PlayQueueChange},
  {"${COMING_UP_CUSTOM_TAG}",               STAT_DESC_CUCT, STATUS_VAR_COMING_UP_CUSTOM_TAG,             STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpCustomTag,       StatusEvent_PlayQueueChange},
  {"${COMING_UP_LENGTH}",                   STAT_DESC_CULE, STATUS_VAR_COMING_UP_LENGTH,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcComingUpLength,          StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_TITLE}",                  STAT_DESC_LPTI, STATUS_VAR_LAST_PLAYED_TITLE,                STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedTitle,         StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_ARTIST}",                 STAT_DESC_LPAR, STATUS_VAR_LAST_PLAYED_ARTIST,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedArtist,        StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_ALBUM}",                  STAT_DESC_LPAL, STATUS_VAR_LAST_PLAYED_ALBUM,                STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedAlbum,         StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_ALB_ARTIST}",             STAT_DESC_LPAA, STATUS_VAR_LAST_PLAYED_ALBUM_ARTIST,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedAlbumArtist,   StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_TRACK_NUMBER}",           STAT_DESC_LPTN, STATUS_VAR_LAST_PLAYED_TRACK_NUMBER,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedTrackNumber,   StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_YEAR}",                   STAT_DESC_LPYR, STATUS_VAR_LAST_PLAYED_YEAR,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedYear,          StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_GENRE}",                  STAT_DESC_LPGN, STATUS_VAR_LAST_PLAYED_GENRE,                STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedGenre,         StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_PUBLISHER}",              STAT_DESC_LPPU, STATUS_VAR_LAST_PLAYED_PUBLISHER,            STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedPublisher,     StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_ISRC}",                   STAT_DESC_LPIS, STATUS_VAR_LAST_PLAYED_ISRC,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedISRC,          StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_CUSTOM_TAG}",             STAT_DESC_LPCT, STATUS_VAR_LAST_PLAYED_CUSTOM_TAG,           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedCustomTag,     StatusEvent_PlayQueueChange},
  {"${LAST_PLAYED_LENGTH}",                 STAT_DESC_LPLE, STATUS_VAR_LAST_PLAYED_LENGTH,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastPlayedlength,        StatusEvent_PlayQueueChange},
  {"${CREDITS}",                            STAT_DESC_CRED, STATUS_VAR_CREDITS,                          STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcCredits,                 StatusEvent_CreditsChange},
  {"${SONGS_CREDITED}",                     STAT_DESC_SCRE, STATUS_VAR_SONGS_CREDITED,                   STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcSongsCredited,           StatusEvent_CreditsChange},
  {"${ATTRACT_MODE_GENRE}",                 STAT_DESC_ATMG, STATUS_VAR_ATTRACT_MODE_GENRE,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcAttractModeGenre,        StatusEvent_AttractModeModeChange},
  {"${CREDITS_PER_COIN1}",                  STAT_DESC_PPCR, STATUS_VAR_CREDITS_PER_COIN1,                STATUS_VAR_NULL,                             0x00,                       false, &StatusDisplayClass::funcCreditsPerCoin,          StatusEvent_FreeplayModeChange},
  {"${CREDITS_PER_COIN2}",                  STAT_DESC_PPCR, STATUS_VAR_CREDITS_PER_COIN2,                STATUS_VAR_NULL,                             0x01,                       false, &StatusDisplayClass::funcCreditsPerCoin,          StatusEvent_FreeplayModeChange},
  {"${CREDITS_PER_COIN3}",                  STAT_DESC_PPCR, STATUS_VAR_CREDITS_PER_COIN3,                STATUS_VAR_NULL,                             0x02,                       false, &StatusDisplayClass::funcCreditsPerCoin,          StatusEvent_FreeplayModeChange},
  {"${CREDITS_PER_COIN4}",                  STAT_DESC_PPCR, STATUS_VAR_CREDITS_PER_COIN4,                STATUS_VAR_NULL,                             0x03,                       false, &StatusDisplayClass::funcCreditsPerCoin,          StatusEvent_FreeplayModeChange},
  {"${CREDITS_PER_COIN5}",                  STAT_DESC_PPCR, STATUS_VAR_CREDITS_PER_COIN5,                STATUS_VAR_NULL,                             0x04,                       false, &StatusDisplayClass::funcCreditsPerCoin,          StatusEvent_FreeplayModeChange},
  {"${CREDITS_PER_COIN6}",                  STAT_DESC_PPCR, STATUS_VAR_CREDITS_PER_COIN6,                STATUS_VAR_NULL,                             0x05,                       false, &StatusDisplayClass::funcCreditsPerCoin,          StatusEvent_FreeplayModeChange},
  {"${CREDITS_PER_SONG}",                   STAT_DESC_SPCR, STATUS_VAR_CREDITS_PER_SONG,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcCreditsPerSong,          StatusEvent_FreeplayModeChange},
  {"${VOLUME}",                             STAT_DESC_VOLU, STATUS_VAR_VOLUME,                           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcVolume,                  StatusEvent_VolumeChange},
  {"${SELECT_CODE}",                        STAT_DESC_SELC, STATUS_VAR_SELECT_CODE,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcSelectCode,              StatusEvent_SelCodeChange},
  {"${NUM_SONGS}",                          STAT_DESC_NSON, STATUS_VAR_NUM_SONGS,                        STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNumSongs,                StatusEvent_None},
  {"${NUM_SEARCH_SONGS}",                   STAT_DESC_NSFS, STATUS_VAR_NUM_SEARCH_SONGS,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNumSearchSongs,          StatusEvent_NewDatabaseSearch},
  {"${PLAYQUEUE_SPACE}",                    STAT_DESC_PQSP, STATUS_VAR_PLAYQUEUE_SPACE,                  STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcPlayQueueRemainingSpace, StatusEvent_PlayQueueChange},
  {"${NUM_TITLE_STRIPS}",                   STAT_DESC_NPAG, STATUS_VAR_NUM_TITLE_STRIPS,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNumTitleStrips,          StatusEvent_None},
  {"${FIRST_VISIBLE_TITLE_STRIP}",          STAT_DESC_FVPA, STATUS_VAR_FIRST_VISIBLE_TITLE_STRIP,        STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcFirstVisibleTitleStrip,  StatusEvent_TitleStripMoveChange},
  {"${LAST_VISIBLE_TITLE_STRIP}",           STAT_DESC_LVPA, STATUS_VAR_LAST_VISIBLE_TITLE_STRIP,         STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcLastVisibleTitleStrip,   StatusEvent_TitleStripMoveChange},
  {"${TOTAL_PLAYED_SONGS}",                 STAT_DESC_TSPL, STATUS_VAR_TOTAL_SONGS_PLAYED,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcTotalPlayedSongs,        StatusEvent_SongUnload},
  {"${TOTAL_PLAYED_TIME}",                  STAT_DESC_TSTI, STATUS_VAR_TOTAL_SONGS_TIME,                 STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcTotalPlayedTime,         StatusEvent_SongUnload},
  {"${SET_GPIO_00_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_00_HI,                   STATUS_VAR_NULL,                             0x00,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_00_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_00_LO,                   STATUS_VAR_NULL,                             0x00,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_01_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_01_HI,                   STATUS_VAR_NULL,                             0x01,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_01_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_01_LO,                   STATUS_VAR_NULL,                             0x01,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_02_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_02_HI,                   STATUS_VAR_NULL,                             0x02,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_02_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_02_LO,                   STATUS_VAR_NULL,                             0x02,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_03_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_03_HI,                   STATUS_VAR_NULL,                             0x03,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_03_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_03_LO,                   STATUS_VAR_NULL,                             0x03,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_04_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_04_HI,                   STATUS_VAR_NULL,                             0x04,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_04_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_04_LO,                   STATUS_VAR_NULL,                             0x04,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_05_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_05_HI,                   STATUS_VAR_NULL,                             0x05,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_05_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_05_LO,                   STATUS_VAR_NULL,                             0x05,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_06_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_06_HI,                   STATUS_VAR_NULL,                             0x06,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_06_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_06_LO,                   STATUS_VAR_NULL,                             0x06,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_07_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_07_HI,                   STATUS_VAR_NULL,                             0x07,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_07_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_07_LO,                   STATUS_VAR_NULL,                             0x07,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_08_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_08_HI,                   STATUS_VAR_NULL,                             0x08,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_08_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_08_LO,                   STATUS_VAR_NULL,                             0x08,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_09_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_09_HI,                   STATUS_VAR_NULL,                             0x09,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_09_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_09_LO,                   STATUS_VAR_NULL,                             0x09,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_10_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_10_HI,                   STATUS_VAR_NULL,                             0x0a,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_10_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_10_LO,                   STATUS_VAR_NULL,                             0x0a,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_11_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_11_HI,                   STATUS_VAR_NULL,                             0x0b,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_11_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_11_LO,                   STATUS_VAR_NULL,                             0x0b,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_12_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_12_HI,                   STATUS_VAR_NULL,                             0x0c,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_12_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_12_LO,                   STATUS_VAR_NULL,                             0x0c,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_13_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_13_HI,                   STATUS_VAR_NULL,                             0x0d,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_13_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_13_LO,                   STATUS_VAR_NULL,                             0x0d,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_14_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_14_HI,                   STATUS_VAR_NULL,                             0x0e,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_14_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_14_LO,                   STATUS_VAR_NULL,                             0x0e,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_15_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_15_HI,                   STATUS_VAR_NULL,                             0x0f,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_15_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_15_LO,                   STATUS_VAR_NULL,                             0x0f,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_16_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_16_HI,                   STATUS_VAR_NULL,                             0x10,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_16_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_16_LO,                   STATUS_VAR_NULL,                             0x10,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_17_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_17_HI,                   STATUS_VAR_NULL,                             0x11,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_17_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_17_LO,                   STATUS_VAR_NULL,                             0x11,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_18_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_18_HI,                   STATUS_VAR_NULL,                             0x12,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_18_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_18_LO,                   STATUS_VAR_NULL,                             0x12,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_19_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_19_HI,                   STATUS_VAR_NULL,                             0x13,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_19_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_19_LO,                   STATUS_VAR_NULL,                             0x13,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_20_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_20_HI,                   STATUS_VAR_NULL,                             0x14,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_20_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_20_LO,                   STATUS_VAR_NULL,                             0x14,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_21_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_21_HI,                   STATUS_VAR_NULL,                             0x15,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_21_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_21_LO,                   STATUS_VAR_NULL,                             0x15,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_22_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_22_HI,                   STATUS_VAR_NULL,                             0x16,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_22_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_22_LO,                   STATUS_VAR_NULL,                             0x16,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_23_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_23_HI,                   STATUS_VAR_NULL,                             0x17,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_23_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_23_LO,                   STATUS_VAR_NULL,                             0x17,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_24_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_24_HI,                   STATUS_VAR_NULL,                             0x18,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_24_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_24_LO,                   STATUS_VAR_NULL,                             0x18,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_25_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_25_HI,                   STATUS_VAR_NULL,                             0x19,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_25_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_25_LO,                   STATUS_VAR_NULL,                             0x19,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_26_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_26_HI,                   STATUS_VAR_NULL,                             0x1a,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_26_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_26_LO,                   STATUS_VAR_NULL,                             0x1a,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_GPIO_27_HI}",                     STAT_DESC_GPHI, STATUS_VAR_SET_GPIO_27_HI,                   STATUS_VAR_NULL,                             0x1b,                       false, &StatusDisplayClass::funcGPIOSetPinHigh,          StatusEvent_None},
  {"${SET_GPIO_27_LO}",                     STAT_DESC_GPLO, STATUS_VAR_SET_GPIO_27_LO,                   STATUS_VAR_NULL,                             0x1b,                       false, &StatusDisplayClass::funcGPIOSetPinLow,           StatusEvent_None},
  {"${SET_FLAG_1_HI}",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_1_HI,                    STATUS_VAR_NULL,                             0x01,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_None},
  {"${SET_FLAG_1_LO}",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_1_LO,                    STATUS_VAR_NULL,                             0x01,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_None},
  {"${SET_FLAG_2_HI}",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_2_HI,                    STATUS_VAR_NULL,                             0x02,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_None},
  {"${SET_FLAG_2_LO}",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_2_LO,                    STATUS_VAR_NULL,                             0x02,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_None},
  {"${SET_FLAG_3_HI}",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_3_HI,                    STATUS_VAR_NULL,                             0x03,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_None},
  {"${SET_FLAG_3_LO}",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_3_LO,                    STATUS_VAR_NULL,                             0x03,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_None},
  {"${SET_FLAG_4_HI}",                      STAT_DESC_FGHI, STATUS_VAR_SET_FLAG_4_HI,                    STATUS_VAR_NULL,                             0x04,                       false, &StatusDisplayClass::funcSetFlagHigh,             StatusEvent_None},
  {"${SET_FLAG_4_LO}",                      STAT_DESC_FGLO, STATUS_VAR_SET_FLAG_4_LO,                    STATUS_VAR_NULL,                             0x04,                       false, &StatusDisplayClass::funcSetFlagLow,              StatusEvent_None},
  {"${NO_DRAW}",                            STAT_DESC_ENND, STATUS_VAR_NO_DRAW,                          STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcNoDraw,                  StatusEvent_None},
  {"${SET_VISIBLE}",                        STAT_DESC_SVIS, STATUS_VAR_SET_VISIBLE,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcSetVisible,              StatusEvent_None},
  {"${SET_NOT_VISIBLE}",                    STAT_DESC_SNVI, STATUS_VAR_SET_NOT_VISIBLE,                  STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcSetNotVisible,           StatusEvent_None},
  {"${DRAW_BITMAP}",                        STAT_DESC_BMPX, STATUS_VAR_DRAW_BITMAP,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcDrawBitmap,              StatusEvent_None},
  {"${DRAW_RANDOM_BITMAP}",                 STAT_DESC_BMPR, STATUS_VAR_DRAW_RANDOM_BITMAP,               STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcDrawRandomBitmap,        StatusEvent_None},
  {"${UNDRAW_BITMAP}",                      STAT_DESC_BMPU, STATUS_VAR_UNDRAW_BITMAP,                    STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcUndrawBitmap,            StatusEvent_None},
  {"${DRAW_VIDEO}",                         STAT_DESC_VIDX, STATUS_VAR_DRAW_VIDEO,                       STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcDrawVideo,               StatusEvent_None},
  {"${UNDRAW_VIDEO}",                       STAT_DESC_VIDU, STATUS_VAR_UNDRAW_VIDEO,                     STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcUndrawVideo,             StatusEvent_None},
  {"${START_VIDEO}",                        STAT_DESC_STRV, STATUS_VAR_START_VIDEO,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcStartVideo,              StatusEvent_None},
  {"${STOP_VIDEO}",                         STAT_DESC_STPV, STATUS_VAR_STOP_VIDEO,                       STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcStopVideo,               StatusEvent_None},
  {"${PAUSE_VIDEO}",                        STAT_DESC_PAUV, STATUS_VAR_PAUSE_VIDEO,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcPauseVideo,              StatusEvent_None},
  {"${UNPAUSE_VIDEO}",                      STAT_DESC_UNPV, STATUS_VAR_UNPAUSE_VIDEO,                    STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcUnPauseVideo,            StatusEvent_None},
  {"${STOP_TIMER}",                         STAT_DESC_STOT, STATUS_VAR_STOP_TIMER,                       STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcStopTimer,               StatusEvent_None},
  {"${START_TIMER}",                        STAT_DESC_STAT, STATUS_VAR_START_TIMER,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcStartTimer,              StatusEvent_None},
  {"${RESET_TIMER}",                        STAT_DESC_REST, STATUS_VAR_RESET_TIMER,                      STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcResetTimer,              StatusEvent_None},
  {"${PLAY_SOUND}",                         STAT_DESC_PSND, STATUS_VAR_PLAY_SOUND,                       STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcPlaySound,               StatusEvent_None},
  {"${STOP_SOUND}",                         STAT_DESC_SSND, STATUS_VAR_STOP_SOUND,                       STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcStopSound,               StatusEvent_None},
  {"${IF_FREEPLAY}",                        STAT_DESC_IFFP, STATUS_VAR_IF_FREEPLAY,                      STATUS_VAR_IF_NOT_FREEPLAY,                  STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfFreeplay,              StatusEvent_FreeplayModeChange},
  {"${IF_NOT_FREEPLAY}",                    STAT_DESC_INFP, STATUS_VAR_IF_NOT_FREEPLAY,                  STATUS_VAR_IF_FREEPLAY,                      STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotFreeplay,           StatusEvent_FreeplayModeChange},
  {"${IF_NO_CREDITS}",                      STAT_DESC_IFNC, STATUS_VAR_IF_NO_CREDITS,                    STATUS_VAR_IF_ANY_CREDITS,                   STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNoCredits,             StatusEvent_CreditsChange},
  {"${IF_ANY_CREDITS}",                     STAT_DESC_IFCA, STATUS_VAR_IF_ANY_CREDITS,                   STATUS_VAR_IF_NO_CREDITS,                    STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfAnyCredits,            StatusEvent_CreditsChange},
  {"${IF_SONG_PLAYING}",                    STAT_DESC_IFPL, STATUS_VAR_IF_SONG_PLAYING,                  STATUS_VAR_IF_NOT_SONG_PLAYING,              STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfSongPlaying,           StatusEvent_SongStart | StatusEvent_SongStop},
  {"${IF_NOT_SONG_PLAYING}",                STAT_DESC_IFNP, STATUS_VAR_IF_NOT_SONG_PLAYING,              STATUS_VAR_IF_SONG_PLAYING,                  STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotSongPlaying,        StatusEvent_SongStart | StatusEvent_SongStop},
  {"${IF_ATTRACT_PLAYING}",                 STAT_DESC_IFAP, STATUS_VAR_IF_ATTRACT_PLAYING,               STATUS_VAR_IF_NOT_ATTRACT_PLAYING,           STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfAttractPlaying,        StatusEvent_SongStart | StatusEvent_SongStop},
  {"${IF_NOT_ATTRACT_PLAYING}",             STAT_DESC_IFNA, STATUS_VAR_IF_NOT_ATTRACT_PLAYING,           STATUS_VAR_IF_ATTRACT_PLAYING,               STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotAttractPlaying,     StatusEvent_SongStart | StatusEvent_SongStop},
  {"${IF_FILE_PLAYING}",                    STAT_DESC_IFSF, STATUS_VAR_IF_FILE_PLAYING,                  STATUS_VAR_IF_NOT_FILE_PLAYING,              STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfFilePlaying,           StatusEvent_SongVideoShow},
  {"${IF_NOT_FILE_PLAYING}",                STAT_DESC_IFNF, STATUS_VAR_IF_NOT_FILE_PLAYING,              STATUS_VAR_IF_FILE_PLAYING,                  STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotFilePlaying,        StatusEvent_SongStart},
  {"${IF_VIDEO_PLAYING}",                   STAT_DESC_IFSV, STATUS_VAR_IF_VIDEO_PLAYING,                 STATUS_VAR_IF_NOT_VIDEO_PLAYING,             STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfVideoPlaying,          StatusEvent_SongVideoShow},
  {"${IF_NOT_VIDEO_PLAYING}",               STAT_DESC_IFNV, STATUS_VAR_IF_NOT_VIDEO_PLAYING,             STATUS_VAR_IF_VIDEO_PLAYING,                 STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotVideoPlaying,       StatusEvent_SongStart},
  {"${IF_STREAM_PLAYING}",                  STAT_DESC_IFSR, STATUS_VAR_IF_STREAM_PLAYING,                STATUS_VAR_IF_NOT_STREAM_PLAYING,            STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfStreamPlaying,         StatusEvent_SongStart | StatusEvent_SongStop},
  {"${IF_NOT_STREAM_PLAYING}",              STAT_DESC_IFNR, STATUS_VAR_IF_NOT_STREAM_PLAYING,            STATUS_VAR_IF_STREAM_PLAYING,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotStreamPlaying,      StatusEvent_SongStart | StatusEvent_SongStop},
  {"${IF_SONG_LOADING}",                    STAT_DESC_IFLO, STATUS_VAR_IF_SONG_LOADING,                  STATUS_VAR_IF_NOT_SONG_LOADING,              STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfSongLoading,           StatusEvent_SongStart | StatusEvent_SongLoad},
  {"${IF_NOT_SONG_LOADING}",                STAT_DESC_IFNL, STATUS_VAR_IF_NOT_SONG_LOADING,              STATUS_VAR_IF_SONG_LOADING,                  STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotSongLoading,        StatusEvent_SongStart | StatusEvent_SongLoad},
  {"${IF_SONG_UNLOADING}",                  STAT_DESC_IFUL, STATUS_VAR_IF_SONG_UNLOADING,                STATUS_VAR_IF_NOT_SONG_UNLOADING,            STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfSongUnloading,         StatusEvent_SongStop | StatusEvent_SongUnload},
  {"${IF_NOT_SONG_UNLOADING}",              STAT_DESC_IFNU, STATUS_VAR_IF_NOT_SONG_UNLOADING,            STATUS_VAR_IF_SONG_UNLOADING,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotSongUnloading,      StatusEvent_SongStop | StatusEvent_SongUnload},
  {"${IF_ANY_COMING_UP}",                   STAT_DESC_IFAC, STATUS_VAR_IF_ANY_COMING_UP,                 STATUS_VAR_IF_NONE_COMING_UP,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfAnyComingUp,           StatusEvent_PlayQueueChange},
  {"${IF_NONE_COMING_UP}",                  STAT_DESC_INCU, STATUS_VAR_IF_NONE_COMING_UP,                STATUS_VAR_IF_SONG_COMING_UP,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNoneComingUp,          StatusEvent_PlayQueueChange},
  {"${IF_SONG_COMING_UP}",                  STAT_DESC_ISCU, STATUS_VAR_IF_SONG_COMING_UP,                STATUS_VAR_IF_NONE_COMING_UP,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfSongComingUp,          StatusEvent_PlayQueueChange},
  {"${IF_ATTRACT_MODE}",                    STAT_DESC_IFRM, STATUS_VAR_IF_ATTRACT_MODE,                  STATUS_VAR_IF_NOT_ATTRACT_MODE,              STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfAttractModeMode,       StatusEvent_AttractModeModeChange},
  {"${IF_NOT_ATTRACT_MODE}",                STAT_DESC_INRM, STATUS_VAR_IF_NOT_ATTRACT_MODE,              STATUS_VAR_IF_ATTRACT_MODE,                  STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotAttractModeMode,    StatusEvent_AttractModeModeChange},
  {"${IF_LOOPQUEUE_MODE}",                  STAT_DESC_IFLM, STATUS_VAR_IF_LOOPQUEUE_MODE,                STATUS_VAR_IF_NOT_LOOPQUEUE_MODE,            STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfLoopMode,              StatusEvent_LoopModeChange},
  {"${IF_NOT_LOOPQUEUE_MODE}",              STAT_DESC_INLM, STATUS_VAR_IF_NOT_LOOPQUEUE_MODE,            STATUS_VAR_IF_LOOPQUEUE_MODE,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotLoopMode,           StatusEvent_LoopModeChange},
  {"${IF_TIMER_HI}",                        STAT_DESC_IFTY, STATUS_VAR_IF_TIMER_HI,                      STATUS_VAR_IF_TIMER_LO,                      STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfTimerHi,               StatusEvent_TimerChange},
  {"${IF_TIMER_LO}",                        STAT_DESC_IFTN, STATUS_VAR_IF_TIMER_LO,                      STATUS_VAR_IF_TIMER_HI,                      STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfTimerLo,               StatusEvent_TimerChange},
  {"${IF_TIMER_TICK}",                      STAT_DESC_IFTT, STATUS_VAR_IF_TIMER_TICK,                    STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfTimerTick,             StatusEvent_TimerChange},
  {"${IF_MUTE}",                            STAT_DESC_IFMU, STATUS_VAR_IF_MUTE,                          STATUS_VAR_IF_NOT_MUTE,                      STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfMute,                  StatusEvent_MuteChange},
  {"${IF_NOT_MUTE}",                        STAT_DESC_IFNM, STATUS_VAR_IF_NOT_MUTE,                      STATUS_VAR_IF_MUTE,                          STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotMute,               StatusEvent_MuteChange},
  {"${IF_TITLE_STRIP_MOVING}",              STAT_DESC_IFPM, STATUS_VAR_IF_TITLE_STRIP_MOVING,            STATUS_VAR_IF_NOT_TITLE_STRIP_MOVING,        STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfTitleStripMoving,      StatusEvent_TitleStripMoveChange},
  {"${IF_NOT_TITLE_STRIP_MOVING}",          STAT_DESC_IFPN, STATUS_VAR_IF_NOT_TITLE_STRIP_MOVING,        STATUS_VAR_IF_TITLE_STRIP_MOVING,            STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfTitleStripNotMoving,   StatusEvent_TitleStripMoveChange},
  {"${IF_PLAYQUEUE_EMPTY}",                 STAT_DESC_IFPE, STATUS_VAR_IF_PLAYQUEUE_EMPTY,               STATUS_VAR_IF_NOT_PLAYQUEUE_EMPTY,           STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfPlayQueueEmpty,        StatusEvent_PlayQueueChange},
  {"${IF_NOT_PLAYQUEUE_EMPTY}",             STAT_DESC_INPE, STATUS_VAR_IF_NOT_PLAYQUEUE_EMPTY,           STATUS_VAR_IF_PLAYQUEUE_EMPTY,               STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotPlayQueueEmpty,     StatusEvent_PlayQueueChange},
  {"${IF_PLAYQUEUE_FULL}",                  STAT_DESC_IFPF, STATUS_VAR_IF_PLAYQUEUE_FULL,                STATUS_VAR_IF_NOT_PLAYQUEUE_FULL,            STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfPlayQueueFull,         StatusEvent_PlayQueueChange},
  {"${IF_NOT_PLAYQUEUE_FULL}",              STAT_DESC_INPF, STATUS_VAR_IF_NOT_PLAYQUEUE_FULL,            STATUS_VAR_IF_PLAYQUEUE_FULL,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotPlayQueueFull,      StatusEvent_PlayQueueChange},
  {"${IF_STEREO}",                          STAT_DESC_IFST, STATUS_VAR_IF_STEREO,                        STATUS_VAR_IF_NOT_STEREO,                    STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfStereo,                StatusEvent_SongStart},
  {"${IF_NOT_STEREO}",                      STAT_DESC_INST, STATUS_VAR_IF_NOT_STEREO,                    STATUS_VAR_IF_STEREO,                        STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotStereo,             StatusEvent_SongStart},
  {"${IF_PAUSED}",                          STAT_DESC_IFPA, STATUS_VAR_IF_PAUSED,                        STATUS_VAR_IF_NOT_PAUSED,                    STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfPaused,                StatusEvent_SongPauseChange},
  {"${IF_NOT_PAUSED}",                      STAT_DESC_INPA, STATUS_VAR_IF_NOT_PAUSED,                    STATUS_VAR_IF_PAUSED,                        STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotPaused,             StatusEvent_SongPauseChange},
  {"${IF_INSTANT_PLAY}",                    STAT_DESC_IFIP, STATUS_VAR_IF_INSTANT_PLAY,                  STATUS_VAR_IF_NOT_INSTANT_PLAY,              STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfInstantPlay,           StatusEvent_None},
  {"${IF_NOT_INSTANT_PLAY}",                STAT_DESC_INIP, STATUS_VAR_IF_NOT_INSTANT_PLAY,              STATUS_VAR_IF_INSTANT_PLAY,                  STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotInstantPlay,        StatusEvent_None},
  {"${IF_INVALID_CHOICE}",                  STAT_DESC_IFIC, STATUS_VAR_IF_INVALID_CHOICE,                STATUS_VAR_IF_NOT_INVALID_CHOICE,            STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfInvalidChoice,         StatusEvent_ChooseSong},
  {"${IF_NOT_INVALID_CHOICE}",              STAT_DESC_INIC, STATUS_VAR_IF_NOT_INVALID_CHOICE,            STATUS_VAR_IF_INVALID_CHOICE,                STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotInvalidChoice,      StatusEvent_ChooseSong},
  {"${IF_DUPLICATE_CHOICE}",                STAT_DESC_IFDC, STATUS_VAR_IF_DUPLICATE_CHOICE,              STATUS_VAR_IF_NOT_DUPLICATE_CHOICE,          STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfDuplicateChoice,       StatusEvent_ChooseSong},
  {"${IF_NOT_DUPLICATE_CHOICE}",            STAT_DESC_INDC, STATUS_VAR_IF_NOT_DUPLICATE_CHOICE,          STATUS_VAR_IF_DUPLICATE_CHOICE,              STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotDuplicateChoice,    StatusEvent_ChooseSong},
  {"${IF_VISIBLE}",                         STAT_DESC_IFVI, STATUS_VAR_IF_VISIBLE,                       STATUS_VAR_IF_NOT_VISIBLE,                   STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfVisible,               StatusEvent_None},
  {"${IF_NOT_VISIBLE}",                     STAT_DESC_INVI, STATUS_VAR_IF_NOT_VISIBLE,                   STATUS_VAR_IF_VISIBLE,                       STATUS_CODE_PARAM_NONE,     true,  &StatusDisplayClass::funcIfNotVisible,            StatusEvent_None},
  {"${IF_FLAG_1_HI}",                       STAT_DESC_IFFH, STATUS_VAR_IF_FLAG_HI,                       STATUS_VAR_IF_FLAG_LO,                       0x01,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_FlagChange},
  {"${IF_FLAG_1_LO}",                       STAT_DESC_IFFL, STATUS_VAR_IF_FLAG_LO,                       STATUS_VAR_IF_FLAG_HI,                       0x01,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_FlagChange},
  {"${IF_FLAG_2_HI}",                       STAT_DESC_IFFH, STATUS_VAR_IF_FLAG_HI,                       STATUS_VAR_IF_FLAG_LO,                       0x02,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_FlagChange},
  {"${IF_FLAG_2_LO}",                       STAT_DESC_IFFL, STATUS_VAR_IF_FLAG_LO,                       STATUS_VAR_IF_FLAG_HI,                       0x02,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_FlagChange},
  {"${IF_FLAG_3_HI}",                       STAT_DESC_IFFH, STATUS_VAR_IF_FLAG_HI,                       STATUS_VAR_IF_FLAG_LO,                       0x03,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_FlagChange},
  {"${IF_FLAG_3_LO}",                       STAT_DESC_IFFL, STATUS_VAR_IF_FLAG_LO,                       STATUS_VAR_IF_FLAG_HI,                       0x03,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_FlagChange},
  {"${IF_FLAG_4_HI}",                       STAT_DESC_IFFH, STATUS_VAR_IF_FLAG_HI,                       STATUS_VAR_IF_FLAG_LO,                       0x04,                       true,  &StatusDisplayClass::funcIfFlagHigh,              StatusEvent_FlagChange},
  {"${IF_FLAG_4_LO}",                       STAT_DESC_IFFL, STATUS_VAR_IF_FLAG_LO,                       STATUS_VAR_IF_FLAG_HI,                       0x04,                       true,  &StatusDisplayClass::funcIfFlagLow,               StatusEvent_FlagChange},
  {"${END_IF}",                             STAT_DESC_ENIF, STATUS_VAR_END_IF,                           STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, &StatusDisplayClass::funcEndIf,                   StatusEvent_None},
  {"${ELSE}",                               STAT_DESC_ELSE, STATUS_VAR_ELSE,                             STATUS_VAR_NULL,                             STATUS_CODE_PARAM_NONE,     false, nullptr,                                          StatusEvent_None},
  {"${IF_ANY_BUTTON_PRESSED}",              STAT_DESC_IFAB, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_ANY,                 true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_ANY_BUTTON_PRESSED}",          STAT_DESC_INAB, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_ANY,                 true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_QUIT_PRESSED}",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_QUIT,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_QUIT_PRESSED}",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_QUIT,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_COIN1_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN1,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_COIN1_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN1,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_COIN2_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN2,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_COIN2_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN2,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_COIN3_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN3,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_COIN3_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN3,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_COIN4_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN4,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_COIN4_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN4,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_COIN5_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN5,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_COIN5_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN5,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_COIN6_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_INSERT_COIN6,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_COIN6_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_INSERT_COIN6,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_VOLUP_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_VOL_UP,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_VOLUP_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_VOL_UP,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_VOLDOWN_PRESSED}",          STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_VOL_DOWN,            true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_VOLDOWN_PRESSED}",      STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_VOL_DOWN,            true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_RANDOM_PRESSED}",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_ADD_RANDOM,          true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_RANDOM_PRESSED}",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_ADD_RANDOM,          true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_SELECT_PRESSED}",           STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_SELECT,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_SELECT_PRESSED}",       STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_SELECT,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_SKIP_PRESSED}",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_SKIP,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_SKIP_PRESSED}",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_SKIP,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_PAUSE_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_PAUSE,               true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_PAUSE_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_PAUSE,               true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_UP_PRESSED}",               STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_UP,                  true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_UP_PRESSED}",           STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_UP,                  true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_DOWN_PRESSED}",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_DOWN,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_DOWN_PRESSED}",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_DOWN,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_LEFT_PRESSED}",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LEFT,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_LEFT_PRESSED}",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LEFT,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_RIGHT_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_RIGHT,               true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_RIGHT_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_RIGHT,               true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_LEFT_SCREEN_PRESSED}",      STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LEFT_SCREEN,         true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_LEFT_SCREEN_PRESSED}",  STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LEFT_SCREEN,         true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_RIGHT_SCREEN_PRESSED}",     STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_RIGHT_SCREEN,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_RIGHT_SCREEN_PRESSED}", STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_RIGHT_SCREEN,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_LEFT_SORT_PRESSED}",        STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LEFT_SORT,           true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_LEFT_SORT_PRESSED}",    STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LEFT_SORT,           true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_RIGHT_SORT_PRESSED}",       STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_RIGHT_SORT,          true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_RIGHT_SORT_PRESSED}",   STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_RIGHT_SORT,          true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_ATTRACT_PRESSED}",          STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_ATTRACT_TOG,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_ATTRACT_PRESSED}",      STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_ATTRACT_TOG,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_LOOPQUEUE_PRESSED}",        STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_LOOPQUEUE_TOG,       true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_LOOPQUEUE_PRESSED}",    STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_LOOPQUEUE_TOG,       true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_FREEPLAY_PRESSED}",         STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FREEPLAY_TOG,        true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_FREEPLAY_PRESSED}",     STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FREEPLAY_TOG,        true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_CLEARQUEUE_PRESSED}",       STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_CLEARQUEUE,          true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_CLEARQUEUE_PRESSED}",   STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_CLEARQUEUE,          true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_MUTE_PRESSED}",             STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_MUTE,                true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_MUTE_PRESSED}",         STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_MUTE,                true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_0_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_0,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_0_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_0,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_1_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_1,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_1_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_1,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_2_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_2,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_2_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_2,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_3_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_3,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_3_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_3,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_4_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_4,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_4_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_4,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_5_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_5,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_5_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_5,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_6_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_6,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_6_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_6,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_7_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_7,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_7_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_7,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_8_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_8,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_8_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_8,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_9_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_9,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_9_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_9,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_A_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_A,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_A_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_A,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_B_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_B,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_B_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_B,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_C_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_C,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_C_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_C,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_D_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_D,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_D_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_D,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_E_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_E,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_E_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_E,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_F_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_F,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_F_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_F,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_G_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_G,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_G_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_G,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_H_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_H,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_H_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_H,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_I_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_I,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_I_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_I,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_J_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_J,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_J_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_J,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_K_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_K,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_K_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_K,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_L_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_L,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_L_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_L,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_M_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_M,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_M_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_M,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_N_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_N,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_N_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_N,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_O_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_O,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_O_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_O,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_P_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_P,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_P_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_P,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_Q_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_Q,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_Q_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_Q,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_R_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_R,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_R_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_R,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_S_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_S,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_S_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_S,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_T_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_T,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_T_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_T,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_U_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_U,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_U_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_U,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_V_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_V,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_V_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_V,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_W_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_W,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_W_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_W,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_X_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_X,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_X_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_X,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_Y_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_Y,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_Y_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_Y,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_Z_PRESSED}",                STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_Z,                   true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_Z_PRESSED}",            STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_Z,                   true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_POWER_OFF_PRESSED}",        STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_POWER_OFF,           true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_POWER_OFF_PRESSED}",    STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_POWER_OFF,           true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_FLAG1_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_1,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_FLAG1_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_1,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_FLAG2_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_2,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_FLAG2_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_2,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_FLAG3_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_3,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_FLAG3_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_3,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange},
  {"${IF_BUTTON_FLAG4_PRESSED}",            STAT_DESC_IFBP, STATUS_VAR_IF_BUTTON_PRESSED,                STATUS_VAR_IF_NOT_BUTTON_PRESSED,            BUTTON_FLAG_4,              true,  &StatusDisplayClass::funcIfButtonPressed,         StatusEvent_ButtonChange},
  {"${IF_NOT_BUTTON_FLAG4_PRESSED}",        STAT_DESC_INBP, STATUS_VAR_IF_NOT_BUTTON_PRESSED,            STATUS_VAR_IF_BUTTON_PRESSED,                BUTTON_FLAG_4,              true,  &StatusDisplayClass::funcIfNotButtonPressed,      StatusEvent_ButtonChange}
};

