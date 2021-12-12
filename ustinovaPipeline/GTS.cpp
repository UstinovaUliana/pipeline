#include "GTS.h"
void GTS::connectPipe(Stantia& sout, Pipe& p, Stantia& sin ) {
    p.idOut = sout.getId();
    p.idIn = sin.getId();
    sout.PipOut.emplace(p.getId());
    sin.PipIn.emplace(p.getId());

}
void GTS::disconnectPipe(Stantia& sout, Pipe& p, Stantia& sin) {
    sout.PipOut.erase(p.getId());
    sin.PipIn.erase(p.getId());
    p.idOut = 0;
    p.idIn = 0;
    
}
map <int, Stantia> GTS::sort(unordered_map<int, Stantia> stantii) {
    map <int, Stantia> sortResults;
    int sortNum=0;
    vector <int> sToChange;
    while (sortResults.size() != stantii.size()) {
        for (auto [id,s] : stantii) {
            if (s.PipIn.size() == 0) {
                sToChange.push_back(id);
            }
        }
        for (int i : sToChange) {
            sortNum++;
            sortResults[sortNum] = stantii[i];
            for (auto j : stantii[i].PipOut) {
                for (auto [id, s1] : stantii) {
                    s1.PipIn.erase(j);
                }
            }
        }
    }
    return sortResults;
}
