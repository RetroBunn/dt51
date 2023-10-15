// Audio.h
#if defined(__cplusplus)
extern "C" {
#endif

void AudioOutOpen( void );
short * AudioOutPlayBuffer(short * data, long flag);
void AudioOutPlay(short *data, int samples);
void AudioOutClose( void );

#if defined(__cplusplus)
}
#endif
