#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>
#include "ustinovaPipeline.h"
#include "Header.h"
#include "GTS.h"
#include <unordered_map>
#include <map>
using namespace std;


void saveAll(unordered_map <int, Pipe> truby, unordered_map <int, Stantia> stantii)
{
    ofstream fout;
    cout << "??????? ???????? ?????: ";
    string ofileName;
    cin >> ws;
    getline(cin, ofileName);
    fout.open(ofileName+".txt", ios::out);
  
    if (fout.is_open()) {
        fout << Pipe::maxId<<endl;
        fout << Stantia::maxId << endl;
        for (auto& [id,t]:truby) {
            fout << t << endl;
        }
        for (auto& [id,s] : stantii) {
            fout << s << endl;
        }
        fout.close();
    }
}

void loadAll(unordered_map <int, Pipe>& truby, unordered_map <int, Stantia>& stantii)
{
    ifstream fin;
    cout << "??????? ???????? ?????: ";
    string ifileName;
    cin >> ws;
    getline(cin, ifileName);
    fin.open(ifileName + ".txt", ios::in);
    if (fin.is_open())
    {
        int wpId;
        int wsId;
        string type;
        truby.clear();
        stantii.clear(); 
        fin >> wpId;
        fin >> wsId;
        while (!fin.eof()) {
            getline(fin, type);
            if (type == "Truba") {
                Pipe p;
                fin >> p;
                truby.emplace(p.getId(), p);
            }
            if (type == "Stantia") {
                Stantia s;
                fin >> s;
                stantii.emplace(s.getId(), s);
            }
        }
        Pipe::maxId = wpId;
        Stantia::maxId = wsId;
        fin.close();
    }
    else cout << "?? ???????????." << endl;
}
void menu()
{
    cout << " 1. ???????? ????? \n 2. ???????? ?? \n 3. ???????? ???? ???????? \n 4. ????????????? ????? \n"
         <<" 5. ????????????? ?? \n 6. ????????? \n 7. ????????? \n 8. ????? ???? ? ??????? \n"
         <<" 9. ????? ??????? ?? ???????? ????????? ?????(?????? ??????????) \n 10. ????? ??????? ?? ???????? \n"
         <<" 11. ?????????? ????? \n 12. ??????????? ????? \n 13. ??????? ????? \n 14. ??????? ?? \n 15. ?????????????? ?????????? \n 16. ?????????? ???? \n 17. \n 0. ????? \n";
    cout << "________________________________" << endl;
}

void command(int& com)
{
    cout << "???????: ";
    cin >> com;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "???????: ";
        cin >> com;
    };
}

template<typename T, typename Obj>

using filter = bool(*)(const Obj& truba, T param);

bool checkRem(const Pipe& truba, bool param) {
    return truba.rem == param;
}
bool checkCehNrab(const Stantia& stan, int param) {
    return ((stan.ceh - stan.cehRab) * 100 / stan.ceh) >= param;
}
bool checkName(const Stantia& stan, string param) {
    return stan.name == param;
}
template<typename T, typename Obj>

vector<int> findObject(const unordered_map<int, Obj>& object, filter<T,Obj> f, T param)
{
    vector<int> found;
    for (auto [id,o] : object)
    {
        if (f(o, param))
            found.push_back(id);
    }

    return found;
}

int main()
{
    GTS gts;
    setlocale(LC_ALL, "Russian");
    int com;
    while (1) {
        menu();
        command(com);

        switch (com)
        {
        case 1: {
            Pipe p;
            cin >> p;
            gts.truby.emplace(p.getId(), p);
            cout<< gts.truby[p.getId()]<<endl;
            break;
        }
        case 2: {
            Stantia s;
            cin >> s;
            gts.stantii.emplace(s.getId(), s);
            cout << gts.stantii[s.getId()] << endl;
            break;
        }
        case 3: {
            if (gts.truby.size() == 0)
                cout << endl << "????? ?? ???????" << endl;
            else  for (auto [id,p] : gts.truby)
                cout << p;
             if (gts.stantii.size()==0)
                 cout <<endl<< "??????? ?? ???????" << endl;
             else  for (auto [id, s] : gts.stantii)
                 cout << s;
            break;
        }
        case 4: {
            if (gts.truby.size() == 0)
                cout << endl << "????? ?? ???????" << endl;
            else {
                cout << endl << "??????? id ?????: ";
                int id;
                id=getInt();
                auto p = gts.truby.find(id);
                if (p != gts.truby.end())
                    gts.truby[id].changePipe();
            }
            break;
        }
        case 5: {
            if (gts.stantii.size() == 0)
                cout << endl << "??????? ?? ???????" << endl;
            else {
                cout << endl << "??????? id ??????: ";
                int id;
                id = getInt();
                auto st = gts.stantii.find(id);
                if (st != gts.stantii.end())
                    gts.stantii[id].changeStan();
            }
            break;
        }
        case 0: {
            return 0;
            break;
        }
        
        case 6: {
            saveAll(gts.truby, gts.stantii);
            cout << "?????????!" << endl;
            break;
        }
        case 7: {
            loadAll(gts.truby, gts.stantii);
            cout << "?????????!" << endl;
            break;
        }
        case 8: {
            bool vremonte=true;
            vector <int> TR= findObject(gts.truby, checkRem, vremonte);
            if (TR.size() == 0) {
                cout << "??? ????? ? ??????" << endl;
                break;
            }
            else {
            for (int i : TR) cout << gts.truby[i];
            int com2;
            cout << "0.?????\n1.??????? ????? \n2.????????? ?????\n";
            command(com2);
            switch (com2) {
            case 0: {
                break;
            }

            case 1: {
                for (int i : findObject(gts.truby, checkRem, vremonte)) {
                    if (gts.truby[i].idIn == 0) {
                        gts.truby.erase(i);
                        cout << "????? " <<i<<" ???????." << endl;
                    }
                    else cout << "????? " << i << " ????????? ???????, ??????? ??????." << endl;
                    
                }
                break;
            }
            case 2: {
                for (int i : findObject(gts.truby, checkRem, vremonte))
                    gts.truby[i].changePipe();
                break;
            }
            default: {
                cout << "??? ????? ???????.\n";
                break;
            }
            }
            }
            break;
        }
        case 9: {
            int perCehNrab;
            cout << "??????? ??????? ????????? ?????: ";
            perCehNrab=getInt();
            for (int i :findObject(gts.stantii, checkCehNrab, perCehNrab))
                cout << gts.stantii[i];
            break;
        }
        
        case 10: {
            string name = "";
            do {
                cout << "??????? ???????? ??????? (?? ??????????):";
                getline(cin >> ws, name);

            } while (cin.fail());
            for (int i : findObject(gts.stantii, checkName, name))
                cout << gts.stantii[i];
            break;
        }
        case 11: {
            if (gts.truby.size() == 0)
                cout << endl << "????? ?? ???????" << endl;
            else {
                cout << endl << "??????? id ?????: ";
                int id;
                id = getInt();
                auto p = gts.truby.find(id);
                if (p != gts.truby.end()) {
                    cout << endl << "??????? id ???????-??????: ";
                    int fromId;
                    fromId = getInt();
                    auto s1 = gts.stantii.find(fromId);
                    if (s1 == gts.stantii.end()) {
                        cout << "????? ??????? ???." << endl;
                        break;
                    }
                    cout << endl << "??????? id ???????-?????: ";
                    int toId;
                    toId = getInt();
                    auto s2 = gts.stantii.find(toId);
                    if (s2 == gts.stantii.end()) {
                        cout << "????? ??????? ???." << endl;
                        break;
                    }
                    if (gts.stantii[fromId].PipOut.size() < gts.stantii[fromId].ceh && gts.stantii[toId].PipIn.size() < gts.stantii[toId].ceh) {
                        gts.connectPipe(gts.stantii[fromId], gts.truby[id], gts.stantii[toId]);
                        GTS::pairCS pairi;
                        pairi.fromCSid = fromId;
                        pairi.toCSid = toId;
                        gts.CPC.emplace(id, pairi);
                    }
                      
                    else cout << "???? ?????????." << endl;
                }
            }
            break;
        }
        case 12: {
            if (gts.truby.size() == 0)
                cout << endl << "????? ?? ???????" << endl;
            else {
                cout << endl << "??????? id ?????: ";
                int id;
                id = getInt();
                auto p = gts.truby.find(id);
                if (p != gts.truby.end()) {
                    if (gts.truby[id].idIn == 0) {
                        cout << "????? ?? ???????????." << endl;
                        break;
                    }
                    gts.disconnectPipe(gts.stantii[gts.truby[id].idOut], gts.truby[id], gts.stantii[gts.truby[id].idIn]);
                    gts.CPC.erase(id);
                }
            }
            break;
        }
        case 13: {
            cout << endl << "??????? id ?????: ";
            int id;
            id = getInt();
            if (gts.truby[id].idIn == 0) {
                gts.truby.erase(id);
                cout << "????? ???????." << endl;
            }
            else cout << "????? ????????? ???????, ??????? ??????."<<endl;
            break;
        }
        case 14: {
            cout << endl << "??????? id ???????: ";
            int id;
            id = getInt();
            if (gts.stantii[id].PipIn.size() == 0 && gts.stantii[id].PipOut.size() == 0) {
                gts.stantii.erase(id);
                cout << "??????? ???????." << endl;
            }
            else cout << "??????? ????????? ? ???????, ??????? ??????." << endl;
            break;
        }
        case 15: {
            map <int, Stantia> res=gts.sort(gts.stantii);
            for (auto [i, s] : res)
            {
                cout << i << endl;
                cout << s << endl;
            }
            break;
        }
        case 16: {
            cout << "Id ????????? ???????: ";
            int from = getInt();
            unordered_map<int, Node> nodesMap;
            unordered_map<int, Verge> vergesMap;
            nodesMap = gts.toNodesMap(gts.stantii);
            vergesMap = gts.toVergesMap(gts.truby);
            gts.findMinWay(nodesMap, vergesMap, from);
            break;
        }
        case 17: {
            vector <vector<int>> mS=gts.makeMatrSmezh(gts.stantii, gts.truby);
            for (int i = 1; i < mS.size(); i++) 
            { 
                for (int j = 1; j < mS[i].size(); j++) {
                    cout << mS[i][j] << "   ";
                }
                cout << endl;
            }
            break;
        }
        default: {
            cout << "??? ????? ???????.\n";
            break;
        }
        
        }
        cout << "________________________________" <<endl;
        
    }
}
//?????????? ? ????????
