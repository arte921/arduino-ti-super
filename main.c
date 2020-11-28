#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int SCENEGROOTTE = 2;

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Bol {
	float straal;
	struct Vector3 positie;
};

struct Bol *scene[SCENEGROOTTE];

float afstand3 (struct Vector3 *a, struct Vector3 *b) {
	float ongeworteldeAfstand = 
		pow((*a).x - (*b).x, 2) + 
		pow((*a).y - (*b).y, 2) + 
		pow((*a).z - (*b).z, 2)
	;
	return sqrt(ongeworteldeAfstand);
}

float bolAfstand (struct Vector3 *positie, struct Bol *bol) {
	struct Vector3 *bolPositie = &(*bol).positie;
	return afstand3(bolPositie, positie) - (*bol).straal;

}

float dichtsbijzijndeBolAfstand (struct Vector3 *positie) {
	int kleinsteAfstand = 10000000.0; // come at me 

	for (int i = 0; i < SCENEGROOTTE; i++) {
		
	}
}

int main () {
	struct Vector3 centrum = {
		0.0,
		0.0,
		0.0
	};

	struct Bol bol1 = {
		5.0,
		{
			10.0,
			10.0,
			10.0
		}
	};

	struct Bol bol2 = {
		3.0,
		{
			4.0,
			4.0,
			4.0
		}
	};

	for (int i = 0; i < SCENEGROOTTE; i++) {
		scene[i] = malloc(sizeof(struct Bol));
	}

	*scene[0] = bol1;
	*scene[1] = bol2;

	float afstand = bolAfstand(&centrum, &bol1);
	printf("%.6f\n", afstand);	
}


