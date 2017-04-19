#pragma once
#include <iomanip>

namespace LevaHelp
{    
    struct Point
    {
        float U  = 0;
        float H  = 0; 
        float R  = 0;
        float P  = 0;
        float RP = 0;
    };
    
	const int matrix_height = 10;
	const int matrix_widht  = 10;

    Point matrix[matrix_height][matrix_widht];
    const std::string g_moveUp    = "  Move UP";
    const std::string g_moveRight = "  Move RIGHT";

    float Func_kgms(float x) // - плотность воздуха в кг/м^3
    {		
        float y = 3 * (pow(10, -9) * pow(x, 2)) - 0.0001 * x + 1.2192;
        return y;
    }

    void printHUIJMsg(int i, int j, std::string msg)
    {
        std::cout
            << "\n"
            << " H =" << std::setw(4) << matrix[i][j].H
            << " U =" << std::setw(4) << matrix[i][j].U
            << " i =" << i
            << " j =" << j
            << msg
            ;
    }

    void makeMatrix()
    {

        int U;                        // начальная скорость
        int H;                        // высота в м
        float Hmax      = 6500;
        float Hstep     = 677.7777777777777777777777777778;
        float Umin      = 320;
        float Ustep     = 44.444444444444444444444444444444;
        float P         = 78453.2;    // тяга в Н
        float m         = 47000;      // масса самолёта в кг
        float S         = 127;        // площадь крыла в м^2
        float Cy0       = 0;
        float Cya       = 14.394;
        float g         = 9.80665;    // ускорение свободного падения в м^2
        float ro        = 1.29;       // плотность воздуха в кг/м^3
        float q         = 0;          // скоростной напор
        float alpha     = 0;          // угол атаки
        float t         = 0;
        float teta      = 0;          // угол тангажа
        float sinusTeta = 0;
        float tpod      = 0;          // время на подъём

        float a1;
        float a2;
        float t1;
        float t2;
        float teta1;
        float teta2;
        float tpod1;
        float tpod2;

        float ar;
        float ap;
        float arp;

        float br;
        float bp;
        float brp;

        float vr;
        float vp;
        float vrp;

        float c = 0.0655737705;
        float tetapr = 0;
        float teta1pr = 0;
        float teta2pr = 0;
        float sintetapr = 0;
        float tpr = 0; // время подъём-разгон	

        int imin;
        int jmax;
        int imax;
        int jmin;

        float X = 0; // сила лобового сопротивления
        float Cx = 0; // 
        float Cy = 0; //
        int madness = 0;


        for (int i = 0; i <= 9; i++)
        {
            H = Hmax - (i * Hstep);
            ro = Func_kgms(H);
            U = 0;

            for (int j = 0; j <= 9; j++)
            {
                U = Umin + (j * Ustep);

                //std::cout << "\n| q =" << q << " |";

                matrix[i][j].H = H;
                matrix[i][j].U = U;
                q              = (ro * (U * U)) / 2;
                a1             = (m * g) - (q * S * Cy0);
                a2             = P + (q * S * Cya);
                alpha          = a1 / a2;
                Cy             = 7.013 * (alpha * alpha) + 5.1981 * alpha + 1.2355;
                Cx             = 0.1989 * (Cy * Cy) - 0.056 * Cy + 0.0017;

                //std::cout << "\nCx =" << Cx;

                teta1          = P - (q * S * Cx);
                teta2          = m * g;
                teta           = teta1 / teta2;
                tpod1          = 6100;
                sinusTeta      = sin(teta);
                tpod2          = U * sinusTeta;
                tpod           = tpod1 / tpod2;
                matrix[i][j].P = abs(tpod);
                X              = Cx * q * S;

                //	std::cout << "\nalpha =" << alpha;

                t1              = m * 400;
                t2              = (P * cos(alpha)) - X;
                t               = t1 / t2;
                matrix[i][j].R  = abs(t);
                teta1pr         = P - (q * S * Cx);
                teta2pr         = (m * c * U) + (m * g);
                tetapr          = teta1pr / teta2pr;
                sintetapr       = tetapr;
                tpr             = (1 / (c * sintetapr)) * log(2.25);
                matrix[i][j].RP = abs(tpr);

                //cout << "\n  H =" << H << "  U =" << U << "  R =" << matrix[i][j].R << "  P =" << matrix[i][j].P << "  RP =" << matrix[i][j].RP << "\n";			
                //std::cout << "\n| H =" << H << "| U =" << U << " |" << "| q =" << q << " |" << "| alpha =" << alpha << " |" << "| Cy =" << Cy << " |" << "| Cx =" << Cx << " |" << "| X =" << X << " |" << "| t =" << abs(t) << " |";

            }
        }
        //std::cout << "\n| Hr =" << matrix[0][9].H << "| Ur =" << matrix[0][9].U << "\n| Hr =" << matrix[9][0].H << "| Ur =" << matrix[9][0].U;
    }
	    
	void printMatrix()
	{
		for (int i = 0; i < matrix_height; ++i)
		{
			for (int j = 0; j < matrix_widht; ++j)
			{
				Point curPoint = matrix[i][j];
				
				std::cout
					<< "(" << std::setw(2) << (int)curPoint.R << ", "
					<< std::setw(2) << (int)curPoint.P
					<< ") "
					;
			}
			std::cout << "\n";
		}
	}


	void newCalc()
	{
		int hPos = matrix_height - 1;
		int wPos = 0;

		int hPosNext = hPos-1;
		int wPosNext = wPos+1;
		
		int hPosEnd = 0;
		int wPosEnd = matrix_widht-1;

		while (true/*hPosNext != hPosEnd || wPosNext != wPosEnd*/)
		{
			Point curPoint = matrix[hPos][wPos];
			std::cout
				<< "(" << hPos << ", " << wPos << ") ";
			Point nextPoint;

			float hDiff = 0;
			float wDiff = 0;

			if (hPos == hPosEnd && wPos == wPosEnd)
			{
				break;
			}

			if (hPosNext >= hPosEnd)
			{
				// мы не уперлись в небо
				nextPoint = matrix[hPosNext][wPos];
				hDiff = abs(nextPoint.P - curPoint.P);
			}

			if (wPosNext <= wPosEnd)
			{
				// мы не уперлись в правый край
				nextPoint = matrix[hPos][wPosNext];
				wDiff = abs(nextPoint.R - curPoint.R);
			}
			
			if (hDiff != 0 && wDiff != 0)
			{
				if (hDiff < wDiff)
				{
					nextPoint = matrix[hPosNext][wPos];
					hPos = hPosNext;
				}
				else
				{
					nextPoint = matrix[hPos][wPosNext];
					wPos = wPosNext;
				}
			}
			else if (hDiff == 0 && wDiff != 0)
			{
				nextPoint = matrix[hPos][wPosNext];
				wPos = wPosNext;
			}
			else if (wDiff == 0 && hDiff != 0)
			{
				nextPoint = matrix[hPosNext][wPos];
				hPos = hPosNext;
			}
			else
			{
				std::cout << "error";
				break;
			}

			hPosNext = hPos - 1;
			wPosNext = wPos + 1;
		}		
	}

    void resolve()
    {
        makeMatrix();
		printMatrix();
		std::cout << "-----------------------------\n";
		newCalc();

		std::cin.get(); // джем нажатия клавиши
		return;

        int i = 9;
        int j = 0;

        for (int qq = 0; (i >= 0) && (j <= 9); qq++) 
        {
            float thr = matrix[i][j + 1].R - matrix[i][j].R;
            float tvp = matrix[i - 1][j].P - matrix[i][j].P;

            if (thr < tvp && i != -1 && j != 10) 
            {
                printHUIJMsg(i, j, g_moveRight);
                j++;
            }
            if (thr > tvp && i != -1 && j != 10) 
            {
                printHUIJMsg(i, j, g_moveUp);
                i--;
            }

        }

        std::cout << "\n" << "Hand Made Correct!";

        for (int mm = 0; mm < 6; mm++) 
        {
            i = 0;
            printHUIJMsg(i, j, g_moveRight);
            j++;
        }

        //std::cout << "\n";
        std::cin.get(); // джем нажатия клавиши
    }
    
}