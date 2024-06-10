#include "function.cpp"
#include <iostream>
#include <sqlite3.h>
#include<vector>
// *****************
using namespace std;
#define red "\033[31m"
#define green "\033[32m"
#define blue "\033[34m"
#define yellow "\033[33m"
#define purple "\033[35m"
#define white "\033[0m"
#define black "\033[30m"
// ! ########################
void home_page(bool);
void login_page(char,bool);
void acceuil_professeur(bool);
void acceuil_directeur(bool,bool,int);
void acceuil_etudiant();
professeur* prof;
directeur* direct;
etudiant* etud;
// ! ########################
sqlite3* db;
int main() {
    clear_terminal();
    //! -------------------------- CREATE DATABASE --------------------------------------
    int rc = sqlite3_open("database.db",&db);
    // prof tables ------------------------------
    const char* professeur = "CREATE TABLE IF NOT EXISTS professeur (id INT, f_name TEXT, l_name INT , mail TEXT , password TEXT);";
    const char* inf_prof = "CREATE TABLE IF NOT EXISTS inf_prof (id INT ,module TEXT ,fillier TEXT);";
    rc = sqlite3_exec(db, professeur, 0, 0, 0);
    rc = sqlite3_exec(db, inf_prof, 0, 0, 0);
    // student tables --------------------------
    const char* etudiant = "CREATE TABLE IF NOT EXISTS etudiant (id INT, f_name TEXT, l_name INT , mail TEXT , password TEXT , fillier TEXT);";
    rc = sqlite3_exec(db, etudiant, 0, 0, 0);
    // IID table --------------------------
    const char* directeur = "CREATE TABLE IF NOT EXISTS directeur (id INT, f_name TEXT, l_name INT , mail TEXT , password TEXT);";
    rc = sqlite3_exec(db,directeur, 0, 0, 0);
    //  ? FILLIER ----------------------------------------
    const char* API1 = "CREATE TABLE IF NOT EXISTS API1 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,API1, 0, 0, 0);
    const char* API2 = "CREATE TABLE IF NOT EXISTS API2 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,API2, 0, 0, 0);
    const char* GI1 = "CREATE TABLE IF NOT EXISTS GI1 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,GI1, 0, 0, 0);
    const char* GI2 = "CREATE TABLE IF NOT EXISTS GI2 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,GI2, 0, 0, 0);
    const char* GI3 = "CREATE TABLE IF NOT EXISTS GI3 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,GI3, 0, 0, 0);
    const char* IID1 = "CREATE TABLE IF NOT EXISTS IID1 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,IID1, 0, 0, 0);
    const char* IID2 = "CREATE TABLE IF NOT EXISTS IID2 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,IID2, 0, 0, 0);
    const char* IID3 = "CREATE TABLE IF NOT EXISTS IID3 (id INT ,modules TEXT , notes INT );";
    rc = sqlite3_exec(db,IID3, 0, 0, 0);
    home_page(true);
    return 0;
}
void home_page(bool reponse_=true){
    cout<<"\a";
    clear_terminal();
    print_blue_line(130);
    endline(1);
    space(14);
    cout << blue << "ENSA" ;
    endline(1);
    space(14);
    cout << blue << "  KHOURIBGA" ;
    endline(2);
    space(6);
    cout<<green<<"SERVICE SCOLARITÉ";
    endline(7);
    space(3);
    cout << black << "Étudiant (E)";
    space(2);
    cout << black << " Professeur (P)";
    space(2);
    cout << black << "  Directeur Scolarité (D)";
    endline(3);
    char reponse;
    if(reponse_==false){
        space(3);
        cout<<red<<" E / P / D \n";
    }
    space(3);
    cout<<">";
    cin>>reponse;
    if(reponse!='P'&&reponse!='E'&&reponse!='D'&&reponse!='p'&&reponse!='e'&&reponse!='d'){
        home_page(false);
    }else{
        login_page(reponse,true);
    }
}
void login_page(char reponse,bool mail_pasword = true){
    clear_terminal();
    print_blue_line(130);
    endline(1);
    space(14);
    cout << blue << "ENSA" ;
    endline(1);
    space(14);
    cout << blue << "  KHOURIBGA" ;
    endline(2);
    space(6);
    cout<<green<<"SERVICE SCOLARITÉ";
    endline(4);
    space(3);
    if (mail_pasword == false){
        cout << red << "Mail or Password incorrect !";
    }
    string e_mail ;
    string password ;
    cout<<white<<"E-mail :";
    cin >> e_mail;
    endline(3);
    space(3);
    cout<<white<<"Password :";
    cin >> password;
    int id=recherche_mail_password(db,reponse,e_mail,password);
    if (recherche_mail_password(db,reponse,e_mail,password) == 0){
        login_page(reponse,false);
    }
    else{
        switch (reponse) {
        case 'P':
        case 'p':
            prof=new professeur();
            prof->mail=e_mail;
            prof->password=password;
            prof->id=id;
            prof->c_name=recherche_nom_prenom( db,  reponse,  id);
            for(int i=0;i<3;i++){
                prof->filiere[i]=prof_recherche_filiere(db,id,i);
                prof->module[i]=prof_recherche_module(db,id,i);
            }
            for(int i=0;i<3;i++){
            cout<<prof->module[i]; cout<<" "<<prof->filiere[i]<<endl;
        }
            acceuil_professeur(true);
            break;
        case 'D':
        case 'd':
            direct=new directeur();
            direct->mail=e_mail;
            direct->password=password;
            direct->id=id;
            direct->c_name=recherche_nom_prenom( db,  reponse,  id);
            acceuil_directeur(true,true,0);
            break;
        case 'E':
        case 'e':
            etud=new etudiant();
            etud->mail=e_mail;
            etud->password=password;
            etud->id=id;
            etud->c_name=recherche_nom_prenom( db,  reponse,  id);
            etud->filiere=etud_recherch_filiere(db,id);
            acceuil_etudiant();
            break;
    }
    }
    
}
void acceuil_professeur(bool Rp_test=true){
    clear_terminal();
    print_blue_line(130);
    endline(1);
    space(14);
    cout << blue << "ENSA" ;
    endline(1);
    space(14);
    cout << blue << "  KHOURIBGA" ;
    endline(1);
    cout << yellow << "   Bienvenue " << prof-> c_name ;
    endline(5);
    for(int i=0;i<3;i++){
        if (Rp_test == true ){
            space(5);
            cout << green << "(" << i+1 << ") " << white << prof -> filiere[i] << "    " << prof -> module[i] ;
            endline(4);
        }else{
            space(5);
            cout << red << "(" << i+1 << ") " << white << prof -> filiere[i] << "    " << prof -> module[i] ;
            endline(4);
        }
    }
    int Rp ;
    endline(2);
    space(5);
    cout << ">";
    cin >> Rp ;
    clear_terminal();
    print_blue_line(130);
    endline(1);
    space(14);
    cout << blue << "ENSA" ;
    endline(1);
    space(14);
    cout << blue << "  KHOURIBGA" ;
    endline(1);
    cout << yellow << "   Bienvenue " << prof-> c_name ;
    endline(5);
    cout<<white;
    if(Rp!= 1&& Rp!=2 && Rp!=3){
        acceuil_professeur(false);
    }
    else{
        for(int i=0;i<9;i++){
            space(6);
            int id=RechercheIdEtudiant(db,Rp,prof,i);
            cout<<search_name_etud(db,Rp,prof,i)<<" | ";
            if (affiche_note_etud( db,Rp,prof,id)== -1){
            cout << endl;
            }
            if (affiche_note_etud( db,Rp,prof,id)!= -1){
                cout << affiche_note_etud( db,Rp,prof,id)<<endl;
            }
        }
}
delete prof;
}
void acceuil_directeur(bool Rp_test=true,bool Rp_test2=true, int Rp=0){
    clear_terminal();
    print_blue_line(130);
    endline(1);
    space(14);
    cout << blue << "ENSA" ;
    endline(1);
    space(14);
    cout << blue << "  KHOURIBGA";
    endline(1);
    cout << yellow << "   Bienvenue " <<direct-> c_name ;
    endline(5);
    if(Rp_test2){
        if (Rp_test == true ){
            space(5);
            cout<<white<<"(1) API1 "<<endl;
            space(5);
            cout<<"(2) API2 "<<endl;
            space(5);
            cout<<"(3) GI1 "<<endl;
            space(5);
            cout<<"(4) GI2 "<<endl;
            space(5);
            cout<<"(5) GI3 "<<endl;
            space(5);
            cout<<"(6) IID1 "<<endl;
            space(5);
            cout<<"(7) IID2 "<<endl;
            space(5);
            cout<<"(8) IID3 "<<endl;
            endline(4);
        }else{
            space(5);
            cout<<red<<"(1)"<<white<<" API1 "<<endl;
            space(5);
            cout<<red<<"(2)"<<white<< "API2 "<<endl;
            space(5);
            cout<<red<<"(3)"<<white<<" GI1 "<<endl;
            space(5);
            cout<<red<<"(4)"<<white<<" GI2 "<<endl;
            space(5);
            cout<<red<<"(5)"<<white<<" GI3 "<<endl;
            space(5);
            cout<<red<<"(6)"<<white<<"IID1 "<<endl;
            space(5);
            cout<<red<<"(7)"<<white<<" IID2 "<<endl;
            space(5);
            cout<<red<<"(8)"<<white<<"IID3 "<<endl;
            endline(4);
        }
        endline(2);
        space(5);
        cout << ">";
        cin >> Rp ;
    }
    if(Rp>8 || Rp<1){
        acceuil_directeur(false,true);
    }
    else{
        clear_terminal();
        print_blue_line(130);
        endline(1);
        space(14);
        cout << blue << "ENSA" ;
        endline(1);
        space(14);
        cout << blue << "  KHOURIBGA" ;
        endline(1);
        cout << yellow << "   Bienvenue " << direct-> c_name ;
        endline(5);
        int Rp_ ;
        if(Rp_test2==true){
            switch(Rp){
            case 1:
                space(5);
                cout<<white<<"(1) Algèbre 1 "<<endl;
                space(5);
                cout<<white<<"(2) analyse 1 "<<endl;
                space(5);
                cout<<white<<"(3) mecanique 1 "<<endl;
                space(5);
                cout<<white<<"(4) informatique 1 "<<endl;
                space(5);
                cout<<white<<"(5) chimie 1 "<<endl;
                space(5);
                cout<<white<<"(6) electrostatique 1 "<<endl;
                space(5);
                break;
            case 2:
                space(5);
                cout<<white<<"(1) Algèbre 2 "<<endl;
                space(5);
                cout<<white<<"(2) analyse 2 "<<endl;
                space(5);
                cout<<white<<"(3) mecanique 2 "<<endl;
                space(5);
                cout<<white<<"(4) informatique 2 "<<endl;
                space(5);
                cout<<white<<"(5) chimie 2 "<<endl;
                space(5);
                cout<<white<<"(6) electrostatique 2 "<<endl;
                break;
            case 3:
                space(5);
                cout<<white<<"(1) c++ "<<endl;
                space(5);
                cout<<white<<"(2) python "<<endl;
                space(5);
                cout<<white<<"(3) probabilite "<<endl;
                space(5);
                cout<<white<<"(4) algorithme  "<<endl;
                space(5);
                cout<<white<<"(5) java  "<<endl;
                space(5);
                cout<<white<<"(6) php "<<endl;
                break;
            case 4:
                space(5);
                cout<<white<<"(1) math pour les ingenieur "<<endl;
                space(5);
                cout<<white<<"(2) recherche operationelle  "<<endl;
                space(5);
                cout<<white<<"(3) internet des objets  "<<endl;
                space(5);
                cout<<white<<"(4) analyse de données  "<<endl;
                space(5);
                cout<<white<<"(5) reseau  "<<endl;
                space(5);
                cout<<white<<"(6) programmation web  "<<endl;
                break;
            
            case 5:
                space(5);
                cout<<white<<"(1) systeme d'exploitation  "<<endl;
                space(5);
                cout<<white<<"(2) gestion de projet  "<<endl;
                space(5);
                cout<<white<<"(3) UNIX  "<<endl;
                space(5);
                cout<<white<<"(4) XML  "<<endl;
                space(5);
                cout<<white<<"(5) IHM "<<endl;
                space(5);
                cout<<white<<"(6) machine learning "<<endl;
                break;
            case 6:
                space(5);
                cout<<white<<"(1) Python "<<endl;
                space(5);
                cout<<white<<"(2) algebre pour ingenieur "<<endl;
                space(5);
                cout<<white<<"(3) analyse pour ingenieur "<<endl;
                space(5);
                cout<<white<<"(4) traitement des données "<<endl;
                space(5);
                cout<<white<<"(5) algorithme "<<endl;
                space(5);
                cout<<white<<"(6) base de données "<<endl;
                space(5);
                break;
            case 7:
                space(5);
                cout<<white<<"(1) machine learning "<<endl;
                space(5);
                cout<<white<<"(2) Java EE "<<endl;
                space(5);
                cout<<white<<"(3) recherche operationelle "<<endl;
                space(5);
                cout<<white<<"(4) vision par ordinateur "<<endl;
                space(5);
                cout<<white<<"(5) data werehouse "<<endl;
                space(5);
                cout<<white<<"(6) modelisation oriente objet "<<endl;
                break;
            case 8:
                space(5);
                cout<<white<<"(1) Js mobile "<<endl;
                space(5);
                cout<<white<<"(2) deep learning "<<endl;
                space(5);
                cout<<white<<"(3) genie logiciel "<<endl;
                space(5);
                cout<<white<<"(4) big data "<<endl;
                space(5);
                cout<<white<<"(5) ingenierie des connaissances "<<endl;
                space(5);
                cout<<white<<"(6) parriage au millieu profesionnel "<<endl;
                break;
            }
        }
        else{
            switch(Rp){
            case 1:
                space(5);
                cout<<red<<"(1)"<<white<<"Algèbre 1 "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"analyse 1 "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"mecanique 1 "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"informatique 1 "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"chimie 1 "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"electrostatique 1 "<<endl;
                break;
            case 2:
                space(5);
                cout<<red<<"(1)"<<white<<"Algèbre 2 "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"analyse 2 "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"mecanique 2 "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"informatique 2 "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"chimie 2 "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"electrostatique 2 "<<endl;
                break;
            case 3:
                space(5);
                cout<<red<<"(1)"<<white<<"c++ "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"python "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"probabilite "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"algorithme  "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"java  "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"php "<<endl;
                break;
            case 4:
                space(5);
                cout<<red<<"(1)"<<white<<"math pour les ingenieur "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"recherche operationelle  "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"internet des objets  "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"analyse de données  "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"resaux  "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"programmation web  "<<endl;
                break;
            case 5:
                space(5);
                cout<<red<<"(1)"<<white<<"systeme d'exploitation  "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"gestion de projet  "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"UNIX  "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"XML  "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"IHM "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"machine learning "<<endl;
                break;
            case 6:
                space(5);
                cout<<red<<"(1)"<<white<<"Python "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"algebre pour ingenieur "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"analyse pour ingenieur "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"traitement des données "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"algorithme "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"base de données "<<endl;
                break;
            case 7:
                space(5);
                cout<<red<<"(1)"<<white<<"machine learning "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"Java EE "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"recherche operationelle "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"vision par ordinateur "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"data werehouse "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"modelisation oriente objet "<<endl;
                break;
            case 8:
                space(5);
                cout<<red<<"(1)"<<white<<"Js mobile "<<endl;
                space(5);
                cout<<red<<"(2)"<<white<<"deep learning "<<endl;
                space(5);
                cout<<red<<"(3)"<<white<<"genie logiciel "<<endl;
                space(5);
                cout<<red<<"(4)"<<white<<"big data "<<endl;
                space(5);
                cout<<red<<"(5)"<<white<<"ingenierie des connaissances "<<endl;
                space(5);
                cout<<red<<"(6)"<<white<<"parriage au millieu profesionnel "<<endl;
                break;
            }
        }
        endline(2);
        space(5);
        cout << ">";
        cin >> Rp_ ;
        if(Rp_>6 || Rp_<1){
            acceuil_directeur(true,false,Rp);
        }
        else{
            clear_terminal();
            print_blue_line(130);
            endline(1);
            space(14);
            cout << blue << "ENSA" ;
            endline(1);
            space(14);
            cout << blue << "  KHOURIBGA";
            endline(1);
            cout << yellow << "   Bienvenue " <<direct-> c_name ;
            endline(5);
            cout<<white;
            for(int i=0;i<10;i++){
                space(6);
                int id=RechercheIdEtudiantFD(db, Rp,i);
                    cout<<id<<" | ";
                    cout<<search_name_etudFD( db,Rp,i)<<" | ";
                    if (affiche_note_etudFD( db,Rp,Rp_,id)== -1){
                        cout<<endl;
                    }
                    if (affiche_note_etudFD( db,Rp,Rp_,id)!= -1){
                        cout<<affiche_note_etudFD( db,Rp,Rp_,id)<<endl;
                    }
            }
            cout<<endl;
            int IdEnt ;
            cout << white << "donner id de l'etudiant :";
            cin >> IdEnt ;
            int Note;
            cout << white << "veuillez saisir la note :";
            cin >> Note ;
            updateNotes(db,Rp,Rp_,IdEnt,Note);
        }
    }
}
void acceuil_etudiant(){
    clear_terminal();
    print_blue_line(130);
    endline(1);
    space(14);
    cout << blue << "ENSA" ;
    endline(1);
    space(14);
    cout << blue << "  KHOURIBGA";
    endline(1);
    cout << yellow << "   Bienvenue " <<etud-> c_name ;
    endline(5);
    int Rp=0;
    endline(1);
    space(4);
    cout <<purple<< etud->filiere;
    endline(2);
    cout<<white;
    string filiere = etud->filiere ;
    if (filiere == "API1") {
        Rp = 1;
    } else if (filiere == "API2") {
        Rp = 2;
    } else if (filiere == "GI1") {
        Rp = 3;
    } else if (filiere == "GI2") {
        Rp = 4;
    } else if (filiere == "GI3") {
        Rp = 5;
    } else if (filiere == "IID1") {
        Rp = 6;
    } else if (filiere == "IID2") {
        Rp = 7;
    } else if (filiere == "IID3") {
        Rp = 8;
    }
    note_etudiant(etud->id,Rp,db);
}