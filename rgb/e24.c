#include <stdio.h>
#include <math.h>
#include <glib.h>

static const double mult[] = {
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000
};

static const double e24[] = {
	1.0,
	1.1,
	1.2,
	1.3,
	1.5,
	1.6,
	1.8,
	2.0,
	2.2,
	2.4,
	2.7,
	3.0,
	3.3,
	3.6,
	3.9,
	4.3,
	4.7,
	5.1,
	5.6,
	6.2,
	6.8,
	7.5,
	8.2,
	9.1
};

void parallel(double value)
{
	double err = 1e6;

	for (int i = 0; i < G_N_ELEMENTS(mult); i++) {
		for (int j = 0; j < G_N_ELEMENTS(e24); j++) {
			const double R1 = e24[j] * mult[i];

			if (R1 < value) {
				continue;
			}
			for (int k = 0; k < G_N_ELEMENTS(mult); k++) {
				for (int l = 0; l < G_N_ELEMENTS(e24); l++) {
					const double R2 = e24[l] * mult[k];
					const double R = R1 * R2 / (R1 + R2);
					const double new_err = fabs((R - value) / value);

					if (new_err < err) {
						err = new_err;
						if (err < 0.20) {
							printf("%lf | %lf = %lf (err: %lf)\n", R1, R2, R, err);
						}
					}
				}
			}
		}
	}
}

int main()
{
	parallel(1005);
	return 0;
}
