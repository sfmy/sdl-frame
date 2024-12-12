#ifndef __audio_h_
#define __audio_h_
#include "list.h" 
#include "SDL2/SDL_mixer.h" 

typedef struct GM_Sound {
    int volume;
    Mix_Chunk* sound;
    const char* file;
} GM_Sound;

typedef struct GM_Music {
    int volume;
    Mix_Music* music;
    const char* file;
} GM_Music;

GM_Sound* GM_CreateSound (const char* file, int volume);
GM_Music* GM_CreateMusic (const char* file, int volume);
void GM_PlayMusic (GM_Music*);
void GM_PauseMusic ();
void GM_PlaySound (GM_Sound*);
void GM_FreeMusic (GM_Music*);
void GM_FreeSound (GM_Sound*);

#endif
