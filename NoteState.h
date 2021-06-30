#ifndef NOTESTATE_H
#define NOTESTATE_H

#include <Qstring>

namespace gnote {

class NoteState {

public:
    NoteState *getInstance();
    ~NoteState();


private:
    NoteState();

private:
    QString m_sCurNotePath;
    QString m_sDefOpenDirPath;
};

}

#endif // NOTESTATE_H
