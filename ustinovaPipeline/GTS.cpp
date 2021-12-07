#include "GTS.h"
void GTS::connectPipe(Stantia sout, Pipe p, Stantia sin ) {
    p.idOut = sout.getId();
    p.idIn = sin.getId();
    sout.PipOut.emplace(p.getId());
    sin.PipIn.emplace(p.getId());

}
void GTS::disconnectPipe(Stantia sout, Pipe p, Stantia sin) {
    sout.PipOut.erase(p.getId());
    sin.PipIn.erase(p.getId());
    p.idOut = 0;
    p.idIn = 0;
    
}
