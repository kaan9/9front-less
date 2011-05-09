#include "astro.h"

double	mercfp[] =
{
	0.013,		0.6807,
	0.048,		0.6283,
	0.185,		0.6231,
	0.711,		0.6191,
	0.285,		0.5784,
	0.075,		0.5411,
	0.019,		0.5585,
	0.010,		2.8449,
	0.039,		2.8117,
	0.147,		2.8135,
	0.552,		2.8126,
	2.100,		2.8126,
	3.724,		2.8046,
	0.729,		2.7883,
	0.186,		2.7890,
	0.049,		2.7943,
	0.013,		2.7402,
	0.033,		1.8361,
	0.118,		1.8396,
	0.431,		1.8391,
	1.329,		1.8288,
	0.539,		4.8686,
	0.111,		4.8904,
	0.027,		4.8956,
	0.012,		3.9794,
	0.056,		3.9636,
	0.294,		3.9910,
	0.484,		3.9514,
	0.070,		3.9270,
	0.018,		3.9270,
	0.013,		6.1261,
	0.050,		6.1052,
	0.185,		6.1069,
	0.685,		6.1011,
	2.810,		6.1062,
	7.356,		6.0699,
	1.471,		6.0685,
	0.375,		6.0687,
	0.098,		6.0720,
	0.026,		6.0476,
	0.062,		5.1540,
	0.122,		5.1191,
	0.011,		0.9076,
	0.074,		1.0123,
	0.106,		0.9372,
	0.017,		0.9425,
	0.020,		0.0506,
	0.052,		0.0384,
	0.052,		3.0281,
	0.012,		3.0543,
	0.011,		2.1642,
	0.016,		2.2340,
	0.040,		4.3912,
	0.080,		4.4262,
	0.016,		4.4506,
	0,

	0.014,		1.0996,
	0.056,		1.1153,
	0.219,		1.1160,
	0.083,		1.0734,
	0.024,		0.9442,
	0.018,		3.8432,
	0.070,		3.8293,
	0.256,		3.8230,
	0.443,		3.8132,
	0.080,		3.7647,
	0.020,		3.7734,
	0.019,		0.0000,
	0.133,		0.1134,
	0.129,		6.2588,
	0.026,		6.2413,
	0.026,		2.6599,
	0.087,		2.6232,
	0.374,		2.6496,
	0.808,		2.5470,
	0.129,		2.5587,
	0.019,		2.5534,
	0.012,		2.1642,
	0,

	0.014,		3.1416,
	0.047,		3.1625,
	0.179,		3.1695,
	0.697,		3.1603,
	0.574,		4.1315,
	0.181,		4.2537,
	0.047,		4.2481,
	0.013,		4.2062,
	0.018,		0.6650,
	0.069,		0.6405,
	0.253,		0.6449,
	0.938,		0.6454,
	3.275,		0.6458,
	0.499,		0.5569,
	0.119,		0.5271,
	0.032,		0.5184,
	0.030,		0.4939,
	0.106,		0.4171,
	0.353,		0.4510,
	0.056,		0.3840,
	0.013,		0.3142,
	0.028,		0.2531,
	0,

	0.034,		0.9512,
	0.060,		4.7962,
	0.028,		4.7124,
	0.028,		4.1836,
	0.102,		4.1871,
	0.380,		4.1864,
	0.059,		4.1818,
	0.015,		4.2185,
	0.012,		4.1713,
	0.050,		4.1870,
	0,

	0.218e-6,	5.3369,
	0.491e-6,	5.3281,
	0.172e-6,	2.1642,
	0.091e-6,	2.1084,
	0.204e-6,	1.2460,
	0.712e-6,	1.2413,
	2.370e-6,	1.2425,
	0.899e-6,	1.2303,
	0.763e-6,	4.3633,
	0.236e-6,	4.3590,
	0.163e-6,	0.2705,
	0.541e-6,	0.2710,
	1.157e-6,	0.2590,
	0.099e-6,	0.1798,
	0.360e-6,	2.4237,
	0.234e-6,	2.3740,
	0.253e-6,	4.5365,
	0.849e-6,	4.5293,
	2.954e-6,	4.5364,
	0.282e-6,	4.4581,
	1.550e-6,	1.3570,
	0.472e-6,	1.3561,
	0.135e-6,	1.3579,
	0.081e-6,	3.5936,
	0.087e-6,	3.5500,
	0.087e-6,	5.7334,
	0,

	0.181e-6,	5.8275,
	0.095e-6,	2.2427,
	0.319e-6,	2.2534,
	0.256e-6,	2.2403,
	0.157e-6,	4.8292,
	0.106e-6,	1.0332,
	0.397e-6,	1.0756,
	0.143e-6,	4.0980,
	0,

	0.222e-6,	1.6024,
	0.708e-6,	1.5949,
	0.191e-6,	5.7914,
	0.100e-6,	5.3564,
	0.347e-6,	5.3548,
	1.185e-6,	5.3576,
	3.268e-6,	5.3579,
	0.371e-6,	2.2148,
	0.160e-6,	2.1241,
	0.134e-6,	5.1260,
	0.347e-6,	5.1620,
	0,
};

char	merccp[] =
{
	 4,	1,
	 3,	1,
	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	-2,	1,
	 6,	2,
	 5,	2,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	-2,	2,
	-3,	2,
	 5,	3,
	 4,	3,
	 3,	3,
	 2,	3,
	 1,	3,
	 0,	3,
	-1,	3,
	 5,	4,
	 4,	4,
	 3,	4,
	 2,	4,
	 1,	4,
	 0,	4,
	 7,	5,
	 6,	5,
	 5,	5,
	 4,	5,
	 3,	5,
	 2,	5,
	 1,	5,
	 0,	5,
	-1,	5,
	-2,	5,
	 4,	6,
	 3,	6,
	 5,	7,
	 4,	7,
	 3,	7,
	 2,	7,
	 5,	8,
	 4,	8,
	 3,	8,
	 2,	8,
	 5,	9,
	 4,	9,
	 5,	10,
	 4,	10,
	 3,	10,

	 3,	1,
	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 3,	3,
	 2,	3,
	 1,	3,
	 0,	3,
	 4,	4,
	 3,	4,
	 2,	4,
	 1,	4,
	 0,	4,
	-1,	4,
	 2,	5,

	 4,	1,
	 3,	1,
	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	-2,	1,
	-3,	1,
	 5,	2,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	-2,	2,
	 3,	3,
	 2,	3,
	 1,	3,
	 0,	3,
	-1,	3,
	 1,	4,

	 1,	1,
	 0,	1,
	-1,	1,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 2,	3,
	 1,	3,

	 2,	1,
	 1,	1,
	 0,	1,
	-1,	1,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 4,	3,
	 3,	3,
	 2,	3,
	 0,	3,
	 3,	4,
	 2,	4,
	 5,	5,
	 4,	5,
	 3,	5,
	 2,	5,
	 1,	5,
	 0,	5,
	-1,	5,
	 4,	6,
	 3,	6,
	 4,	7,

	 1,	1,
	 3,	2,
	 2,	2,
	 1,	2,
	 2,	3,
	 3,	4,
	 2,	4,
	 0,	4,

	 2,	1,
	 1,	1,
	-1,	1,
	 4,	2,
	 3,	2,
	 2,	2,
	 1,	2,
	 0,	2,
	-1,	2,
	 2,	3,
	 1,	3,
};
