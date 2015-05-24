#ifndef _AUDIO_H_
#define _AUDIO_H_
	typedef struct _audio {
		ALLEGRO_AUDIO_STREAM *music;
		ALLEGRO_MIXER *mixer;
	} audio;
	
	audio newAudio(ALLEGRO_AUDIO_STREAM *audio);
	void play(audio this);
	void stop(audio this);
#endif
