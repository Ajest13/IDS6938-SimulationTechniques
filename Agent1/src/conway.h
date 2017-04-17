
#include <stdlib.h>
#include <math.h>

# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>


class ConwayLife {
	bool wrap;   // 1 for wrap 0 for no wrap


public:
	ConwayLife() { wrap = 1; };  // 1 for wrap 0 for no wrap
	~ConwayLife() {};

	int i4_max(int i1, int i2);
	int i4_min(int i1, int i2);
	int i4_modp(int i, int j);
	int i4_uniform(int a, int b, int *seed);
	int i4_wrap(int ival, int ilo, int ihi);

	float r4_abs(float x);
	int r4_nint(float x);
	void state_randomize(int moves, int m, int n, bool state[], int *seed);
	void state_reset(int m, int n, bool state[], int i, int j);
	void state_update(int m, int n, bool state[]);
	void timestamp();

};