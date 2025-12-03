#ifndef MUSIC_H_
#define MUSIC_H_

#include "NucleoImp/Sound/DACSound.h"

namespace ELE3312{

struct Tone {
  Note note;
  uint16_t duration;
};

Tone melody[32] = {
    {{NoteName::E, 5}, 1}, {{NoteName::E, 5}, 1}, {{NoteName::E, 5}, 1},

    {{NoteName::C, 5}, 1}, {{NoteName::E, 5}, 1}, {{NoteName::G, 5}, 3},

    {{NoteName::C, 4}, 3},

    {{NoteName::C, 5}, 1}, {{NoteName::G, 4}, 1}, {{NoteName::E, 4}, 3},

    {{NoteName::A, 4}, 1}, {{NoteName::B, 4}, 1}, {{NoteName::AS, 4}, 1},
    {{NoteName::A, 4}, 1},

    {{NoteName::G, 4}, 1}, {{NoteName::E, 5}, 1}, {{NoteName::G, 5}, 1},
    {{NoteName::A, 5}, 3},

    {{NoteName::F, 5}, 1}, {{NoteName::G, 5}, 1}, {{NoteName::E, 5}, 1},
    {{NoteName::C, 5}, 1}, {{NoteName::D, 5}, 1}, {{NoteName::B, 4}, 3},

    {{NoteName::C, 5}, 1}, {{NoteName::G, 4}, 1}, {{NoteName::E, 4}, 3},

    {{NoteName::A, 4}, 1}, {{NoteName::B, 4}, 1}, {{NoteName::AS, 4}, 1},
    {{NoteName::A, 4}, 3}};



}

#endif
