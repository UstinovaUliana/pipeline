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
    int sortNum = 0;
    vector <int> sToChange;

    int counter = 0;
    int kolvoStan = stantii.size();
    while (sortResults.size() != kolvoStan) {
        sToChange.clear();
        for (auto [id, s] : stantii) {
            if (s.PipIn.size() == 0) {
                sToChange.push_back(id);
            }
        }
        for (int i : sToChange) {
            sortNum++;
            sortResults[sortNum] = stantii[i];
            for (auto j : stantii[i].PipOut) {
                for (auto& [id, s1] : stantii) {
                    s1.PipIn.erase(j);
                }
            }
        }
        for (auto i : sToChange)
            stantii.erase(i);
        /*cout << ++counter << " Action, ";
        for (int i : sToChange) {
            cout << "ID: " << i << std::endl;
        }*/

        if (sToChange.size() == 0) {
            cout << "� ����� ���� ����. " << endl;
            sortResults.clear();
            break;
        }

        return sortResults;
    }
}
//    int GTS::potok (unordered_map<int, Stantia> stantii, unordered_map<int, Pipe> truby) {
//
//        int stream;
//        int pometka;
//        map <int, Stantia> versh;
//        /*for (auto [id, s] : stantii)
//        {
//            versh.emplace(0, s);
//        }*/
//        std::cout << "������� id ��������� �������: \n";
//        int startId = getInt();
//        std::cout << "������� id ��������� �������: \n";
//        int endId = getInt();
//        int rassm = startId;
//        for (int i : ) {
//            for (auto j : stantii[i].PipOut) {
//                  for (auto& [id, s1] : stantii) {
//                 ids=find(s1.PipIn =j);
//          truby[j].perf= sqrt(power(truby[j].d,5)/truby[j].l);
//                  versh[ids].first= min(versh[i].first,versh[--].first - truby[j].perf)
  //              }
//            }
//        }
//}
