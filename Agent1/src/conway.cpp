#include "conway.h"
using namespace std;







void ConwayLife::state_randomize(int moves, int m, int n, bool state[], int *seed)
{
	int i;
	int j;
	int k;

	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			state[i + j*m] = false;
		}
	}

	for (k = 0; k < moves; k++)
	{
		i = i4_uniform(0, m - 1, seed);
		j = i4_uniform(0, n - 1, seed);
		state[i + j*m] = true;
	}

	return;
}




void ConwayLife::state_update(int m, int n, bool state[])
{
	bool *state_new;
	int i;
	int im;
	int ip;
	int j;
	int jm;
	int jp;
	int neighbors;

	state_new = new bool[m*n];

	if (wrap)
	{

		for (j = 0; j < n; j++)
		{
			jp = i4_wrap(j + 1, 0, n - 1);
			jm = i4_wrap(j - 1, 0, n - 1);
			for (i = 0; i < m; i++)
			{
				ip = i4_wrap(i + 1, 0, m - 1);
				im = i4_wrap(i - 1, 0, m - 1);
				neighbors = (int)state[im + jm*m]
					+ (int)state[im + j *m]
					+ (int)state[im + jp*m]
					+ (int)state[i + jm*m]
					+ (int)state[i + jp*m]
					+ (int)state[ip + jm*m]
					+ (int)state[ip + j *m]
					+ (int)state[ip + jp*m];

				if (neighbors == 3)
				{
					state_new[i + j*m] = true;
				}
				else if (neighbors == 2)
				{
					state_new[i + j*m] = state[i + j*m];
				}
				else
				{
					state_new[i + j*m] = false;
				}
			}
		}
	}
	else
	{
		for (j = 0; j < n; j++)
		{
			for (i = 0; i < m; i++)
			{
				neighbors = 0;
				if (0 < i && 0 < j)
				{
					neighbors = neighbors + (int)state[(i - 1) + (j - 1)*m];
				}
				if (0 < i)
				{
					neighbors = neighbors + (int)state[(i - 1) + (j)*m];
				}
				if (0 < i && j < n - 1)
				{
					neighbors = neighbors + (int)state[(i - 1) + (j + 1)*m];
				}
				if (0 < j)
				{
					neighbors = neighbors + (int)state[(i)+(j - 1)*m];
				}
				if (j < n - 1)
				{
					neighbors = neighbors + (int)state[(i)+(j + 1)*m];
				}
				if (i < m - 1 && 0 < j)
				{
					neighbors = neighbors + (int)state[(i + 1) + (j - 1)*m];
				}
				if (i < m - 1)
				{
					neighbors = neighbors + (int)state[(i + 1) + (j)*m];
				}
				if (i < m - 1 && j < n - 1)
				{
					neighbors = neighbors + (int)state[(i + 1) + (j + 1)*m];
				}

				if (neighbors == 3)
				{
					state_new[i + j*m] = true;
				}
				else if (neighbors == 2)
				{
					state_new[i + j*m] = state[i + j*m];
				}
				else
				{
					state_new[i + j*m] = false;
				}
			}
		}
	}
	//
	//  Update.
	//
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			state[i + j*m] = state_new[i + j*m];
		}
	}

	delete[] state_new;

	return;
}


void ConwayLife::state_reset(int m, int n, bool state[], int i, int j)
{
	if (i < 0 || m <= i)
	{
		cerr << "\n";
		cerr << "STATE_RESET - Fatal error!\n";
		cerr << "  Illegal row index I.\n";
	}

	if (j < 0 || n <= j)
	{
		cerr << "\n";
		cerr << "STATE_RESET - Fatal error!\n";
		cerr << "  Illegal column index J.\n";
	}
	state[i + j*m] = !state[i + j*m];

	return;
}



//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

int ConwayLife::i4_max(int i1, int i2)
{
	int value;

	if (i2 < i1)
	{
		value = i1;
	}
	else
	{
		value = i2;
	}
	return value;
}

int ConwayLife::i4_min(int i1, int i2)
{
	int value;

	if (i1 < i2)
	{
		value = i1;
	}
	else
	{
		value = i2;
	}
	return value;
}


int ConwayLife::i4_modp(int i, int j)
{
	int value;

	if (j == 0)
	{
		cerr << "\n";
		cerr << "I4_MODP - Fatal error!\n";
		cerr << "  I4_MODP ( I, J ) called with J = " << j << "\n";
	}

	value = i % j;

	if (value < 0)
	{
		value = value + abs(j);
	}

	return value;
}


int ConwayLife::i4_uniform(int a, int b, int *seed)
{
	int k;
	float r;
	int value;

	if (*seed == 0)
	{
		cerr << "\n";
		cerr << "I4_UNIFORM - Fatal error!\n";
		cerr << "  Input value of SEED = 0.\n";
	}

	k = *seed / 127773;

	*seed = 16807 * (*seed - k * 127773) - k * 2836;

	if (*seed < 0)
	{
		*seed = *seed + 2147483647;
	}

	r = (float)(*seed) * 4.656612875E-10;
	//
	//  Scale R to lie between A-0.5 and B+0.5.
	//
	r = (1.0 - r) * ((float)(i4_min(a, b)) - 0.5)
		+ r   * ((float)(i4_max(a, b)) + 0.5);
	//
	//  Use rounding to convert R to an integer between A and B.
	//
	value = r4_nint(r);

	value = i4_max(value, i4_min(a, b));
	value = i4_min(value, i4_max(a, b));

	return value;
}


int ConwayLife::i4_wrap(int ival, int ilo, int ihi)
{
	int jhi;
	int jlo;
	int value;
	int wide;

	jlo = i4_min(ilo, ihi);
	jhi = i4_max(ilo, ihi);

	wide = jhi + 1 - jlo;

	if (wide == 1)
	{
		value = jlo;
	}
	else
	{
		value = jlo + i4_modp(ival - jlo, wide);
	}

	return value;
}


float ConwayLife::r4_abs(float x)
{
	float value;

	if (0.0 <= x)
	{
		value = x;
	}
	else
	{
		value = -x;
	}
	return value;
}


int ConwayLife::r4_nint(float x)
{
	int value;

	if (x < 0.0)
	{
		value = -(int)(r4_abs(x) + 0.5);
	}
	else
	{
		value = (int)(r4_abs(x) + 0.5);
	}

	return value;
}




void ConwayLife::timestamp()
{
# define TIME_SIZE 40

	static char time_buffer[TIME_SIZE];
	const struct tm *tm;
	size_t len;
	time_t now;

	now = time(NULL);
	tm = localtime(&now);

	len = strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm);

	cout << time_buffer << "\n";

	return;
# undef TIME_SIZE
}