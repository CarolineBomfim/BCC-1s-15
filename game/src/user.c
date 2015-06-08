#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "ranking.h"
#include "user.h"

user setCurrentUser(char *name) {
	user current;
	current.name = name;
	current.points = 0;
	return current;
}
