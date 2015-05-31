#ifndef _TRACK_H_
#define _TRACK_H_
	void track(global_var *global, int **positions);
	unsigned char ***getSnapshot(global_var *global);
	void freeSnapshot(unsigned char ***snapshot);
#endif
