#include "NoteState.h"

namespace MyNote {

NoteState::NoteState() {
}

NoteState::~NoteState() {
}

NoteState *NoteState::getInstance() {
    static NoteState state;
    return &state;
}

}
