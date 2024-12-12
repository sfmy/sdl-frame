#include "../include//audio.h"
#include <stdlib.h>

GM_Sound* GM_CreateSound (const char* file, int volume) {
    GM_Sound* sound = malloc(sizeof(GM_Sound));
    sound->volume = volume;
    sound->file = file;
    sound->sound = Mix_LoadWAV(file);
    if (sound->sound == NULL) {
        printf("load wav %s fail %s\n", file, Mix_GetError());
    }
    return sound;
}

GM_Music* GM_CreateMusic (const char* file, int volume) {
    GM_Music* music = malloc(sizeof(GM_Music));
    music->volume = volume;
    music->file = file;
    music->music = Mix_LoadMUS(file);
    if (music->music == NULL) {
        printf("load music %s fail %s\n", file, Mix_GetError());
    }
    return music;
}

void GM_PlayMusic (GM_Music* music) { 
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music->music, -1);
    }
}

void GM_PauseMusic () {
    if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
    }
}

void GM_PlaySound (GM_Sound* sound) {
    if (sound->sound != NULL) {
        Mix_PlayChannel(-1, sound->sound, 0);
    }
}

void GM_FreeMusic (GM_Music* music) {
    if (music->music != NULL) {
        Mix_FreeMusic(music->music);
    }
    free(music);
}

void GM_FreeSound (GM_Sound* sound) {
    if (sound->sound != NULL) {
        Mix_FreeChunk(sound->sound);
    }
    free(sound);
}
