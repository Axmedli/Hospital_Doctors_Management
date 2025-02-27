#pragma once
#include "models.h"
#include <conio.h>  
#include <cstdlib> 

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_ENTER 13
#define KEY_RIGHT 77


const char* getSpecialtyName(Specialty sp) {
    switch (sp) {
    case Cardiolog:    return "ICARDIolog";
    case UrekHekimi:   return "Urek Hekimi";
    case BeyinCerrahi: return "Beyin Cerrahi";
    case Cerrah:       return "Cerrah";
    case Psixoloq:     return "Psixoloq";
    case Nevroloq:     return "Nevroloq";
    default:           return "Bilinmir";
    }
}

Hospital* createHospital() {
    Hospital* hospital = new Hospital;
    hospital->id = hospitalId++;

    hospital->name = new char[] { "3 Sayli Xestexana" };
    hospital->address = new char[] { "Gence, 136 Ali Mammadov" };
    hospital->doctors = nullptr;
    hospital->size = 0;

    return hospital;
}

Specialty chooseSpecialty() {
    int choice = 0;
    while (true) {
        system("cls || clear");
        cout << "Doctorun ixtisasini daxil edin:\n";

        cout << (choice == 0 ? "\033[32mCardiolog <<\033[0m\n" : "Cardiolog\n");
        cout << (choice == 1 ? "\033[32mUrek Hekimi <<\033[0m\n" : "Urek Hekimi\n");
        cout << (choice == 2 ? "\033[32mBeyin Cerrahi <<\033[0m\n" : "Beyin Cerrahi\n");
        cout << (choice == 3 ? "\033[32mCerrah <<\033[0m\n" : "Cerrah\n");
        cout << (choice == 4 ? "\033[32mPsixoloq <<\033[0m\n" : "Psixoloq\n");
        cout << (choice == 5 ? "\033[32mNevroloq <<\033[0m\n" : "Nevroloq\n");

        int c = _getch();
        switch (c) {
        case KEY_UP:
            choice = (choice == 0) ? 5 : choice - 1;
            break;
        case KEY_DOWN:
            choice = (choice == 5) ? 0 : choice + 1;
            break;
        case KEY_ENTER:
        case KEY_RIGHT:
            return static_cast<Specialty>(choice);
        default:
            break;
        }
    }
}

Doctor* createDoctor() {
    Doctor* doctor = new Doctor;
    doctor->id = doctorId++;

    cout << "Doctorun adini daxil edin: ";
    cin >> doctor->name;

    cout << "Doctorun soyadini daxil edin: ";
    cin >> doctor->surname;

    doctor->specialty = chooseSpecialty();

    cout << "Doctorun tecrubesini daxil edin: ";
    cin >> doctor->experience;

    cout << "Doctorun telefon nomresini daxil edin: ";
    cin >> doctor->phone;

    cout << "Doctorun mailini daxil edin: ";
    cin >> doctor->mail;

    cout << endl;
    return doctor;
}

void printDoctor(Doctor* doctor) {
    cout << "\n------ Doctor Info ------\n";
    cout << "Id:         " << doctor->id << endl;
    cout << "Name:       " << doctor->name << endl;
    cout << "Surname:    " << doctor->surname << endl;
    cout << "Specialty:  " << getSpecialtyName(doctor->specialty) << endl;
    cout << "Experience: " << doctor->experience << endl;
    cout << "Phone:      " << doctor->phone << endl;
    cout << "Mail:       " << doctor->mail << endl;
    cout << "-------------------------\n";
}

void addDoctorToHospital(Hospital* hospital, Doctor* doctor) {
    if (!hospital) return;

    Doctor* newDoctors = new Doctor[hospital->size + 1];

    for (size_t i = 0; i < hospital->size; i++) {
        newDoctors[i] = hospital->doctors[i];
    }
    newDoctors[hospital->size] = *doctor;
    hospital->size++;

    delete[] hospital->doctors;
    hospital->doctors = newDoctors;
}

void printHospital(Hospital* hospital) {
    if (!hospital) return;

    cout << "\n----------------------------\n";
    cout << "Hospital Info\n";
    cout << "Id:      " << hospital->id << endl;
    cout << "Name:    " << hospital->name << endl;
    cout << "Address: " << hospital->address << endl;

    cout << "\nHospital Doctors:\n";
    for (size_t i = 0; i < hospital->size; i++) {
        printDoctor(&hospital->doctors[i]);
    }
    cout << "----------------------------\n";
}

Doctor* findDoctorById(Hospital* hospital, size_t id) {
    if (!hospital) return nullptr;

    for (size_t i = 0; i < hospital->size; i++) {
        if (hospital->doctors[i].id == id) {
            return &hospital->doctors[i];
        }
    }
    return nullptr;
}

void findDoctorsBySpecialty(Hospital* hospital, Specialty specialty) {
    if (!hospital) {
        cout << "Hospital yoxdur!\n";
        return;
    }

    bool foundAny = false;
    for (size_t i = 0; i < hospital->size; i++) {
        if (hospital->doctors[i].specialty == specialty) {
            printDoctor(&hospital->doctors[i]);
            foundAny = true;
        }
    }

    if (!foundAny) {
        cout << "Bu ixtisasa sahib h?kim tapýlmadý.\n";
    }
}

void updateDoctor(Hospital* hospital, size_t id) {
    if (!hospital) return;

    Doctor* d = findDoctorById(hospital, id);
    if (!d) {
        cout << "Bu ID ye uygun doktor tapilmadi\n";
        return;
    }

    cout << "Doctorun teze adini daxil edin: ";
    cin >> d->name;

    cout << "Doctorun teze soyadini daxil edin: ";
    cin >> d->surname;

    d->specialty = chooseSpecialty();

    cout << "Doctorun teze tecrubesini daxil edin: ";
    cin >> d->experience;

    cout << "Doctorun teze telefon nomresini daxil edin: ";
    cin >> d->phone;

    cout << "Doctorun teze mailini daxil edin: ";
    cin >> d->mail;

    cout << "Doctor tezelendi.\n";
}

void deleteDoctor(Hospital* hospital, size_t id) {
    if (!hospital) return;

    int index = -1;
    for (size_t i = 0; i < hospital->size; i++) {
        if (hospital->doctors[i].id == id) {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1) {
        cout << "Bu ID ye uygun doktor tapilmadi\n";
        return;
    }

    Doctor* newDoctors = new Doctor[hospital->size - 1];
    size_t j = 0;

    for (size_t i = 0; i < hospital->size; i++) {
        if ((int)i == index) continue;
        newDoctors[j++] = hospital->doctors[i];
    }

    delete[] hospital->doctors;
    hospital->doctors = newDoctors;
    hospital->size--;

    cout << id << " ID li doctor silindi\n";
}