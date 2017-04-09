#pragma once
#include "StdHelper.hpp"


namespace SOAnswer01
{
    struct student
    {
        string name;
        string address;
        string number;
    };
    string n, a, nu;
    student KI[30];

    void Addinfo(student *KI)
    {
        cout << endl;
        cout << "Имя и фамилия студента" << endl;
        getline(cin, n);
        cout << "Домашний адресс студента" << endl;
        getline(cin, a);
        cout << "Телефонный номер студента" << endl;
        getline(cin, nu);
        KI[0].name = n;
        KI[0].address = a;
        KI[0].number = nu;
    }

//     void AddStudent()
//     {
// 
//         ofstream infodat("INFO.txt", ios::app);
//         if (infodat.fail())
//             cerr << "Ошибка открытия файла INFO.txt" << endl;
//         else
//         {
//             Addinfo(KI);
//             infodat.write((char *)&KI[0], sizeof(student));
//             infodat.close();
//         }
//         infodat.close();
//         main();
//     }

    void resolve()
    {
        AFUN;

        enum { e_counts = 5 };
        student students[e_counts];

        for (int i = 0; i < e_counts; ++i)
        {
            Addinfo(&students[i]);
        }
    }
}
