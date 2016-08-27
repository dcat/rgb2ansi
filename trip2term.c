#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define DELTA_E_K_L 2
#define DELTA_E_K_1 0.048
#define DELTA_E_K_2 0.014

float delta_e(float, float, float, float, float, float);
void  rgb2lab(float, float, float, float *, float *, float *);
int   closest(const uint32_t);

uint32_t set[] = {
	0x000000,
	0x00005f,
	0x000087,
	0x0000af,
	0x0000d7,
	0x0000ff,
	0x005f00,
	0x005f5f,
	0x005f87,
	0x005faf,
	0x005fd7,
	0x005fff,
	0x008700,
	0x00875f,
	0x008787,
	0x0087af,
	0x0087d7,
	0x0087ff,
	0x00af00,
	0x00af5f,
	0x00af87,
	0x00afaf,
	0x00afd7,
	0x00afff,
	0x00d700,
	0x00d75f,
	0x00d787,
	0x00d7af,
	0x00d7d7,
	0x00d7ff,
	0x00ff00,
	0x00ff5f,
	0x00ff87,
	0x00ffaf,
	0x00ffd7,
	0x00ffff,
	0x5f0000,
	0x5f005f,
	0x5f0087,
	0x5f00af,
	0x5f00d7,
	0x5f00ff,
	0x5f5f00,
	0x5f5f5f,
	0x5f5f87,
	0x5f5faf,
	0x5f5fd7,
	0x5f5fff,
	0x5f8700,
	0x5f875f,
	0x5f8787,
	0x5f87af,
	0x5f87d7,
	0x5f87ff,
	0x5faf00,
	0x5faf5f,
	0x5faf87,
	0x5fafaf,
	0x5fafd7,
	0x5fafff,
	0x5fd700,
	0x5fd75f,
	0x5fd787,
	0x5fd7af,
	0x5fd7d7,
	0x5fd7ff,
	0x5fff00,
	0x5fff5f,
	0x5fff87,
	0x5fffaf,
	0x5fffd7,
	0x5fffff,
	0x870000,
	0x87005f,
	0x870087,
	0x8700af,
	0x8700d7,
	0x8700ff,
	0x875f00,
	0x875f5f,
	0x875f87,
	0x875faf,
	0x875fd7,
	0x875fff,
	0x878700,
	0x87875f,
	0x878787,
	0x8787af,
	0x8787d7,
	0x8787ff,
	0x87af00,
	0x87af5f,
	0x87af87,
	0x87afaf,
	0x87afd7,
	0x87afff,
	0x87d700,
	0x87d75f,
	0x87d787,
	0x87d7af,
	0x87d7d7,
	0x87d7ff,
	0x87ff00,
	0x87ff5f,
	0x87ff87,
	0x87ffaf,
	0x87ffd7,
	0x87ffff,
	0xaf0000,
	0xaf005f,
	0xaf0087,
	0xaf00af,
	0xaf00d7,
	0xaf00ff,
	0xaf5f00,
	0xaf5f5f,
	0xaf5f87,
	0xaf5faf,
	0xaf5fd7,
	0xaf5fff,
	0xaf8700,
	0xaf875f,
	0xaf8787,
	0xaf87af,
	0xaf87d7,
	0xaf87ff,
	0xafaf00,
	0xafaf5f,
	0xafaf87,
	0xafafaf,
	0xafafd7,
	0xafafff,
	0xafd700,
	0xafd75f,
	0xafd787,
	0xafd7af,
	0xafd7d7,
	0xafd7ff,
	0xafff00,
	0xafff5f,
	0xafff87,
	0xafffaf,
	0xafffd7,
	0xafffff,
	0xd70000,
	0xd7005f,
	0xd70087,
	0xd700af,
	0xd700d7,
	0xd700ff,
	0xd75f00,
	0xd75f5f,
	0xd75f87,
	0xd75faf,
	0xd75fd7,
	0xd75fff,
	0xd78700,
	0xd7875f,
	0xd78787,
	0xd787af,
	0xd787d7,
	0xd787ff,
	0xd7af00,
	0xd7af5f,
	0xd7af87,
	0xd7afaf,
	0xd7afd7,
	0xd7afff,
	0xd7d700,
	0xd7d75f,
	0xd7d787,
	0xd7d7af,
	0xd7d7d7,
	0xd7d7ff,
	0xd7ff00,
	0xd7ff5f,
	0xd7ff87,
	0xd7ffaf,
	0xd7ffd7,
	0xd7ffff,
	0xff0000,
	0xff005f,
	0xff0087,
	0xff00af,
	0xff00d7,
	0xff00ff,
	0xff5f00,
	0xff5f5f,
	0xff5f87,
	0xff5faf,
	0xff5fd7,
	0xff5fff,
	0xff8700,
	0xff875f,
	0xff8787,
	0xff87af,
	0xff87d7,
	0xff87ff,
	0xffaf00,
	0xffaf5f,
	0xffaf87,
	0xffafaf,
	0xffafd7,
	0xffafff,
	0xffd700,
	0xffd75f,
	0xffd787,
	0xffd7af,
	0xffd7d7,
	0xffd7ff,
	0xffff00,
	0xffff5f,
	0xffff87,
	0xffffaf,
	0xffffd7,
	0xffffff,
	0x080808,
	0x121212,
	0x1c1c1c,
	0x262626,
	0x303030,
	0x3a3a3a,
	0x444444,
	0x4e4e4e,
	0x585858,
	0x606060,
	0x666666,
	0x767676,
	0x808080,
	0x8a8a8a,
	0x949494,
	0x9e9e9e,
	0xa8a8a8,
	0xb2b2b2,
	0xbcbcbc,
	0xc6c6c6,
	0xd0d0d0,
	0xdadada,
	0xe4e4e4,
	0xeeeeee,
};

void
usage(char *name) {
	fprintf(stderr, "usage: %s <-n | -f | -b> <hex triplet>\n", name);
	exit(0);
}

/*
 * convert color from RGB to LAB
 */
void
rgb2lab(float r1, float g1, float b1, float *l2, float *a2, float *b2)
{
	float x, y, z;

	r1 /= 255.0;
	g1 /= 255.0;
	b1 /= 255.0;

	if (r1 > 0.04045) 
		r1 = powf((r1 + 0.055) / 1.055, 2.4);
	else
		r1 /= 12.92;

	if (g1 > 0.04045)
		g1 = powf((g1 + 0.055) / 1.055, 2.4);
	else
		g1 /= 12.92;

	if (b1 > 0.04045) 
		b1 = powf((b1 + 0.055) / 1.055, 2.4);
	else 
		b1 /= 12.92;

	r1 *= 100.0;
	g1 *= 100.0;
	b1 *= 100.0;

	x = r1 * 0.4124 + g1 * 0.3576 + b1 * 0.1805;
	y = r1 * 0.2126 + g1 * 0.7152 + b1 * 0.0722;
	z = r1 * 0.0193 + g1 * 0.1192 + b1 * 0.9505;

	x /= 95.047;
	y /= 100.000;
	z /= 108.883;

	if (x > 0.008856) 
		x = powf(x, 0.3333);
	else
		x = (7.787 * x) + 0.1379;

	if (y > 0.008856)
		y = powf(y, 0.3333);
	else
		y = (7.787 * y) + 0.1379;

	if (z > 0.008856)
		z = powf(z, 0.3333);
	else
		z = (7.787 * z) + 0.1379;

	*l2 = (116.0 * y) - 16.0;
	*a2 = 500.0 * (x - y);
	*b2 = 200.0 * (y - z);
}

/*
 * calc delta E
 */
float
delta_e(float l1, float a1, float b1, float l2, float a2, float b2)
{
	float deltaL, c1, c2, deltaC, deltaA, deltaB, deltaHSquared, deltaH;
	float q1, q2, q3, deltaE;
	deltaL = l1 - l2;
	c1 = sqrtf(a1 * a1 + b1 * b1);
	c2 = sqrtf(a2 * a2 + b2 * b2);
	deltaC = c1 - c2;
	deltaA = a1 - a2;
	deltaB = b1 - b2;
	deltaHSquared = deltaA * deltaA + deltaB * deltaB - deltaC * deltaC;

	if (deltaHSquared > 0)
		deltaH = sqrtf(deltaHSquared);
	else
		deltaH = 0;

	q1 = deltaL / DELTA_E_K_L;
	q2 = deltaC / (1 + DELTA_E_K_1 * c1);
	q3 = deltaH / (1 + DELTA_E_K_2 * c2);
	deltaE = sqrtf(q1 * q1 + q2 * q2 + q3 * q3);

	return deltaE;
}

/*
 * find closest matching 256 equivalent of a hex triple
 */
int
closest(const uint32_t trp) {
	float l1, a1, b1;
	float l2, a2, b2;
	float delta, now, then = 255;
	int i, t = 0;

	rgb2lab(trp >> 16 & 0xFF, trp >> 8 & 0xFF, trp & 0xFF, &l1, &a1, &b1);

	for (i=0; i < sizeof(set)/sizeof(*set); i++) {
		rgb2lab(	set[i] >> 16 & 0xFF,
				set[i] >>  8 & 0xFF,
				set[i]       & 0xFF,
			&l2, &a2, &b2);
		now = delta_e(l1, a1, b1, l2, a2, b2);

		if (now < then) {
			then = now;
			t = i;
		}

	}

	return t + 16;
}

int
main(int argc, char **argv) {
	char gnd = '3';
	int color;

	if (argc != 3)
		usage(argv[0]);

	if ((strlen(argv[2]) != 6)) 
		usage(argv[0]);

	color = strtoul(argv[2], NULL, 16);

	if (argv[1][0] == '-')
		switch (argv[1][1]) {
		case 'n':
			printf("%d\n", closest(color));
			break;
		case 'b':
			gnd = '4';
		case 'f':
			printf("\033[%c8;5;%dm", gnd, closest(color));
			break;
		}

	return 0;
}

