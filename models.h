#pragma once

enum Specialty {
    Cardiolog = 0,
    UrekHekimi,
    BeyinCerrahi,
    Cerrah,
    Psixoloq,
    Nevroloq,
    SpecialtyCount 
};

struct Doctor {
    size_t id;
    char name[50];
    char surname[50];
    Specialty specialty; 
    char experience[100];
    char phone[50];
    char mail[50];
};

struct Hospital {
    size_t id = 0;
    char* name = nullptr;
    char* address = nullptr;
    Doctor* doctors = nullptr;
    size_t size = 0;
};

const char* getSpecialtyName(Specialty sp);
