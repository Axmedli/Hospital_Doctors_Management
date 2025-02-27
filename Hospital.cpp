#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

size_t hospitalId = 1;
size_t doctorId = 1;

#include "models.h"
#include "functions.h"

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_ENTER 13
#define KEY_RIGHT 77

int main()
{
    Hospital* hospital = createHospital();

    {
        Doctor* basHekim = new Doctor;
        basHekim->id = doctorId++;
        strcpy_s(basHekim->name, "Murad");
        strcpy_s(basHekim->surname, "Axmedli");
        basHekim->specialty = Cardiolog;
        strcpy_s(basHekim->experience, "18");
        strcpy_s(basHekim->phone, "0553480074");
        strcpy_s(basHekim->mail, "ahmedli.murad06@bk.ru");

        addDoctorToHospital(hospital, basHekim);
        delete basHekim;
    }

    int choice = 0;

    while (true) {
        system("cls || clear");

        cout << (choice == 0 ? "\033[32mAdd doctor <<\033[0m\n" : "Add doctor\n");
        cout << (choice == 1 ? "\033[32mUpdate doctor <<\033[0m\n" : "Update doctor\n");
        cout << (choice == 2 ? "\033[32mDelete doctor <<\033[0m\n" : "Delete doctor\n");
        cout << (choice == 3 ? "\033[32mShow doctors <<\033[0m\n" : "Show doctors\n");
        cout << (choice == 4 ? "\033[32mGet doctor by Specialty <<\033[0m\n" : "Get doctor by Specialty\n");
        cout << (choice == 5 ? "\033[32mGet doctor by id <<\033[0m\n" : "Get doctor by id\n");
        cout << (choice == 6 ? "\033[32mExit <<\033[0m\n" : "Exit\n");

        int c = _getch();
        switch (c) {
        case KEY_UP:
            if (choice > 0)
                choice--;
            else
                choice = 6;
            break;
        case KEY_DOWN:
            if (choice < 6)
                choice++;
            else
                choice = 0;
            break;
        case KEY_ENTER:
        case KEY_RIGHT:
            switch (choice) {
            case 0: {
                system("cls || clear");
                cout << "Add doctor secdiniz\n";
                Doctor* d = createDoctor();
                addDoctorToHospital(hospital, d);
                delete d;
                system("pause");
                break;
            }
            case 1: {
                system("cls || clear");
                cout << "Update doctor secdiniz\n";
                size_t id;
                cout << "Tezelemek isdediyiniz doctorun ID sini girin: ";
                cin >> id;
                updateDoctor(hospital, id);
                system("pause");
                break;
            }
            case 2: {
                system("cls || clear");
                cout << "Delete doctor secdiniz\n";
                size_t id;
                cout << "Silmek isdediyiniz doctorun ID sini girin: ";
                cin >> id;
                deleteDoctor(hospital, id);
                system("pause");
                break;
            }
            case 3: {
                system("cls || clear");
                cout << "Show doctors secdiniz\n";
                printHospital(hospital);
                system("pause");
                break;
            }
            case 4: {
                system("cls || clear");
                cout << "Axtardiginiz ixtisasi secin:\n";
                Specialty sp = chooseSpecialty();
                findDoctorsBySpecialty(hospital, sp);
                system("pause");
                break;
            }
            case 5: {
                system("cls || clear");
                cout << "Get doctor by id secdiniz\n";
                size_t id;
                cout << "Tapmaq isdediyiniz doctorun ID sini girin: ";
                cin >> id;
                Doctor* found = findDoctorById(hospital, id);
                if (found)
                    printDoctor(found);
                else
                    cout << "Doctor tapilmadi.\n";
                system("pause");
                break;
            }
            case 6: {
                system("cls || clear");
                cout << "Cixilir..." << endl;
                return 0;
            }
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
