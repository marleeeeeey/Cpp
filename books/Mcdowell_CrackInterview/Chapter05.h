#include "StdHelper.hpp"

namespace McdowellChapter05
{
	void p106()
	{
		AFUN;

		AVAR(to_stringHex((short)4));
		AVAR(to_stringHex((short)-4));

		AVAR(to_stringHex((short)5));
		AVAR(to_stringHex((short)-5));
	}

	void p109_05_02()
	{
		AFUN;

		AVAR(sizeof(double));
		AVAR(sizeof(int));

		union DoubleAndInt
		{
			int i[2];
			double d;
		};

		DoubleAndInt di;
		AVAR(sizeof(DoubleAndInt));
		AVAR(sizeof(di));
		di.d = 0.02;

		int length = 10;
		double step = (double)1 / 10;
		for (int i = 0; i < length; i++)
		{
			string dii = to_stringHex(di.i[0]) + to_stringHex(di.i[1]);
			AVAR(di.d);
			AVAR(dii);
			di.d += step;
		}
	}

    void resolve()
    {
        AFUN;
		p106();
		p109_05_02();

    }
}