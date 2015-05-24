#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "global.h"
#include "logger.h"
#include "audio.h"

audio newAudio(ALLEGRO_AUDIO_STREAM *song) {
	if(!song) {
		erro("Falha ao carregar arquivo de aúdio.");
	}
	audio newAudio;
	newAudio.music = song;
	
	if(!al_attach_audio_stream_to_mixer(newAudio.music,al_get_default_mixer())) {
		erro("Falha ao instanciar audio ao mixer.");
	}
	return newAudio;
}

void play(audio this) {
	al_set_audio_stream_playing(this.music, true);
}

void stop(audio this) {
	al_set_audio_stream_playing(this.music, false);
}
