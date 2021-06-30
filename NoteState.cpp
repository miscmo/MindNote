#include "NoteState.h"

namespace gnote {

NoteState::NoteState() {
}

NoteState::~NoteState() {
}

NoteState *NoteState::getInstance() {
    static NoteState state;
    return &state;
}

}
