#ifndef _USER_H_
#define _USER_H_

typedef struct _user {
	char *name;
	int points;
}user;
user setCurrentUser(char *name);

#endif
