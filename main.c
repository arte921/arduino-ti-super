#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

const int SCENEGROOTTE = 2;
float renderafstand = 10000000.0;
float minimumafstand = 0.0001;

int breedte = 100;
int hoogte = 40;


struct Vector3 {
	float x;
	float y;
	float z;
};

struct Bol {
	float straal;
	struct Vector3 positie;
};

struct Camera {
	float lat;
	float lon;
	struct Vector3 positie;
};

struct Bol *scene[SCENEGROOTTE];
struct Camera *camera;

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
	float kleinsteAfstand = renderafstand;

	for (int i = 0; i < SCENEGROOTTE; i++) {
		float afstand = bolAfstand(positie, scene[i]);
		kleinsteAfstand = (afstand < kleinsteAfstand) ? afstand : kleinsteAfstand;	
	}

	return kleinsteAfstand;
}

bool raakt (int x, int y) {
	float lat = (*camera).lat + ((float) y / (float) hoogte - 0.5) * M_PI;
	float lon = (*camera).lon + ((float) x / (float) breedte - 0.5) * M_PI;

	struct Vector3 koers = {
		cos(lon) * sin(lat),
		sin(lon) * sin(lat),
		cos(lat)
	};

	float totaleafstand = 0;
	struct Vector3 straalPositie = (*camera).positie;
	float afstand = dichtsbijzijndeBolAfstand(&straalPositie);
	// printf("positie: %.4f, %.4f, %.4f\n",straalPositie.x, straalPositie.y, straalPositie.z );

	while (true) {
		straalPositie.x += koers.x * afstand;
		straalPositie.y += koers.y * afstand;
		straalPositie.z += koers.z * afstand;

		totaleafstand += afstand;
		afstand = dichtsbijzijndeBolAfstand(&straalPositie);

		// printf("%.6f, %.6f \n", afstand, minimumafstand);

		if (afstand < minimumafstand) {
			return true;
		}

		if (totaleafstand >= renderafstand) {
			return false;
		}
	}
}

void tekenframe () {
	for (int y = 0; y < hoogte; y++) {
		for (int x = 0; x < breedte; x++) {
			if (raakt(x, y)) {
				printf("X");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}

	(*camera).positie.x += 0.125;
	(*camera).positie.y += 0.8;
	(*camera).positie.z += 0.0;

	(*camera).lat += 0.0;
	(*camera).lon += 0.01745;
}

int main () {
	struct Vector3 centrum = {
		0.0,
		0.0,
		0.0
	};

	struct Bol bol1 = {
		3.0,
		{
			10.0,
			0.0,
			0.0
		}
	};

	struct Bol bol2 = {
		5.0,
		{
			5.0,
			10.0,
			0.0
		}
	};

	struct Camera camera1 = {
		1.570796,
		0.0,
		{
			0.0,
			0.0,
			0.0
		}
	};

	camera = malloc(sizeof(struct Camera));
	*camera = camera1;

	for (int i = 0; i < SCENEGROOTTE; i++) {
		scene[i] = malloc(sizeof(struct Bol));
	}

	*scene[0] = bol1;
	*scene[1] = bol2;

	for (int frame = 0; frame < 50; frame++) {
		printf("\e[1;1H\e[2J");	
		usleep(100000);

		tekenframe();	
	}
}


