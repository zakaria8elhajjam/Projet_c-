#include <iostream>
#include <sqlite3.h>
#include <cstdlib>
#include<cstring>
#include<vector>
#define red "\033[31m"
#define green "\033[32m"
#define blue "\033[34m"
#define yellow "\033[33m"
#define purple "\033[35m"
#define white "\033[0m"
#define black "\033[30m"
using namespace std ;
void space(int j);
// ! class ---------
class etudiant{
    public:
        int id;
        string c_name;
        string mail;
        string password;
        string filiere;
};
class professeur{
    public:
        int id;
        string c_name;
        string mail;
        string password;
        string filiere[3];
        string module[3];
        
};
class directeur{
    public:
        int id;
        string c_name;
        string mail;
        string password;
};
//! database fonction ------------------------------------------------------
int recherche_mail_password(sqlite3* db,char reponse,string mail,string password){
    int id= 0;
    int rc = sqlite3_open("database.db", &db);
    const char* sql;
    switch (reponse) {
        case 'P':
        case 'p':
            sql = "SELECT id FROM professeur WHERE mail = ? AND password = ?;";
            break;
        case 'D':
        case 'd':
            sql = "SELECT id FROM directeur WHERE mail = ? AND password = ?;";
            break;
        case 'E':
        case 'e':
            sql = "SELECT id FROM etudiant WHERE mail = ? AND password = ?;";
            break;
    }
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, mail.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id= sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return id;
}
std::string recherche_nom_prenom(sqlite3* db, char reponse, int id) {
    std::string first_name, last_name;
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    switch (reponse) {
        case 'P':
        case 'p':
            sql = "SELECT f_name, l_name FROM professeur WHERE id= ?;";
            break;
        case 'D':
        case 'd':
            sql = "SELECT f_name, l_name FROM directeur WHERE id= ?;";
            break;
        case 'E':
        case 'e':
            sql = "SELECT f_name, l_name FROM etudiant WHERE id= ?;";
            break;
    }

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        first_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        last_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    }
    sqlite3_finalize(stmt);

    return first_name + " " + last_name;
}
std::string prof_recherche_filiere(sqlite3* db, int id,int occ) {
    std::string filiere[3];
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    sql = "SELECT fillier FROM inf_prof WHERE id= ?;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    for(int i = 0; i < 3 && sqlite3_step(stmt) == SQLITE_ROW; i++){
        filiere[i] = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
    }
    sqlite3_finalize(stmt);
    return filiere[occ];
}
std::string prof_recherche_module(sqlite3* db, int id,int occ) {
    std::string module[3];
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    sql = "SELECT module FROM inf_prof WHERE id= ?;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    for(int i = 0; i < 3 && sqlite3_step(stmt) == SQLITE_ROW; i++){
        module[i] = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
    }
    sqlite3_finalize(stmt);
    return module[occ];
}
std::string etud_recherch_filiere(sqlite3* db, int id) {
    std::string filiere;
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    sql = "SELECT fillier FROM etudiant WHERE id = ?;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    filiere = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);
    return filiere;
}
int RechercheIdEtudiant(sqlite3 * db,int Rp,professeur *prof,int a){
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    if (prof->filiere[Rp-1]== "API1"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'API1';";
    }
    if (prof->filiere[Rp-1]== "API2"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'API2';";
    }
    if (prof->filiere[Rp-1]== "GI1"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'GI1';";
    }
    if (prof->filiere[Rp-1]== "GI2"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'GI2';";
    }
    if (prof->filiere[Rp-1]== "GI3"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'GI3';";
    }
    if (prof->filiere[Rp-1]== "IID1"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'IID1';";
    }
    if (prof->filiere[Rp-1]== "IID2"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'IID2';";
    }
    if (prof->filiere[Rp-1]== "IID3"){
        sql = "SELECT id FROM etudiant WHERE fillier= 'IID3';";
    }
    sqlite3_stmt* stmt;
    int id[10];
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, prof->filiere[Rp-1].c_str(), -1, SQLITE_STATIC);
    for(int i = 0; i < 9 && sqlite3_step(stmt) == SQLITE_ROW; i++){
        id[i] = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return id[a];
}
int affiche_note_etud(sqlite3 * db,int Rp,professeur *prof,int id){
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    if (prof->filiere[Rp-1]== "API1"){
        sql = "SELECT notes FROM API1 WHERE id= ? ;";
    }
    if (prof->filiere[Rp-1]== "API2"){
        sql = "SELECT notes FROM API2 WHERE id= ?;";
    }
    if (prof->filiere[Rp-1]== "GI1"){
        sql = "SELECT notes FROM GI1 WHERE id=?;";
    }
    if (prof->filiere[Rp-1]== "GI2"){
        sql = "SELECT notes FROM GI2 WHERE id= ?;";
    }
    if (prof->filiere[Rp-1]== "GI3"){
        sql = "SELECT notes FROM GI3 WHERE id= ?;";
    }
    if (prof->filiere[Rp-1]== "IID1"){
        sql = "SELECT notes FROM IID1 WHERE id= ?;";
    }
    if (prof->filiere[Rp-1]== "IID2"){
        sql = "SELECT notes FROM IID2 WHERE id= ?;";
    }
    if (prof->filiere[Rp-1]== "IID3"){
        sql = "SELECT notes FROM IID3 WHERE id= ?;";
    }
    sqlite3_stmt* stmt;
    int note;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        note= sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return note;
}
std::string search_name_etud(sqlite3* db, int Rp, professeur* prof, int i) {
    std::string first_name, last_name;
    const char* sql = "SELECT f_name, l_name FROM etudiant WHERE id= ?;";
    sqlite3_stmt* stmt = nullptr;
    int id= RechercheIdEtudiant(db, Rp, prof,i);
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        first_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        last_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    }
    sqlite3_finalize(stmt);
    return first_name + " " + last_name;
}
int RechercheIdEtudiantFD(sqlite3 * db,int Rp,int a){
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    if (Rp== 1){
        sql = "SELECT id FROM etudiant WHERE fillier= 'API1';";
    }
    if (Rp== 2){
        sql = "SELECT id FROM etudiant WHERE fillier= 'API2';";
    }
    if (Rp== 3){
        sql = "SELECT id FROM etudiant WHERE fillier= 'GI1';";
    }
    if (Rp== 4){
        sql = "SELECT id FROM etudiant WHERE fillier= 'GI2';";
    }
    if (Rp== 5){
        sql = "SELECT id FROM etudiant WHERE fillier= 'GI3';";
    }
    if (Rp== 6){
        sql = "SELECT id FROM etudiant WHERE fillier= 'IID1';";
    }
    if (Rp== 7){
        sql = "SELECT id FROM etudiant WHERE fillier= 'IID2';";
    }
    if (Rp== 8){
        sql = "SELECT id FROM etudiant WHERE fillier= 'IID3';";
    }
    sqlite3_stmt* stmt;
    int id[10];
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, Rp);
    for(int i = 0; i < 10 && sqlite3_step(stmt) == SQLITE_ROW; i++){
        id[i] = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return id[a];
}
std::string search_name_etudFD(sqlite3* db, int Rp,int g) {
    std::string first_name, last_name;
    const char* sql = "SELECT f_name, l_name FROM etudiant WHERE id= ?;";
    sqlite3_stmt* stmt = nullptr;
    int id= RechercheIdEtudiantFD(db, Rp,g);
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        first_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        last_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    }
    sqlite3_finalize(stmt);
    return first_name + " " + last_name;
}
int affiche_note_etudFD(sqlite3 * db,int Rp,int Rp_,int id){
    const char* sql;
    int rc = sqlite3_open("database.db", &db);
    if (Rp==1){
        if (Rp_==1){
            sql = "SELECT notes FROM API1 WHERE id= ? AND modules='algebre1';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM API1 WHERE id= ? AND modules='analyse1';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM API1 WHERE id= ? AND modules='mecanique1';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM API1 WHERE id= ? AND modules='informatique1';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM API1 WHERE id= ? AND modules='chimie1';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM API1 WHERE id= ? AND modules='electrostatique1';";
        }
    }
    if (Rp==2){
        if (Rp_==1){
            sql = "SELECT notes FROM API2 WHERE id= ? AND modules='algebre2';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM API2 WHERE id= ? AND modules='analyse2';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM API2 WHERE id= ? AND modules='mecanique2';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM API2 WHERE id= ? AND modules='informatique2';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM API2 WHERE id= ? AND modules='chimie2';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM API2 WHERE id= ? AND modules='electrostatique2';";
        }
    }
    if (Rp==3){
        if (Rp_==1){
            sql = "SELECT notes FROM GI1 WHERE id= ? AND modules='c++';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM GI1 WHERE id= ? AND modules='python';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM GI1 WHERE id= ? AND modules='probabilite';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM GI1 WHERE id= ? AND modules='algorithme';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM GI1 WHERE id= ? AND modules='java';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM GI1 WHERE id= ? AND modules='php';";
        }
    }
    if (Rp==4){
        if (Rp_==1){
            sql = "SELECT notes FROM GI2 WHERE id= ? AND modules='math pour les ingenieur';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM GI2 WHERE id= ? AND modules='recherche operationelle';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM GI2 WHERE id= ? AND modules='internet des objets';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM GI2 WHERE id= ? AND modules='analyse de données';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM GI2 WHERE id= ? AND modules='resaux';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM GI2 WHERE id= ? AND modules='programmation web';";
        }
    }
    if (Rp==5){
        if (Rp_==1){
            sql = "SELECT notes FROM GI3 WHERE id= ? AND modules='systeme d'exploitation';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM GI3 WHERE id= ? AND modules='gestion de projet';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM GI3 WHERE id= ? AND modules='UNIX';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM GI3 WHERE id= ? AND modules='XML';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM GI3 WHERE id= ? AND modules='IHM';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM GI3 WHERE id= ? AND modules='machine learning';";
        }
    }
    if (Rp==6){
        if (Rp_==1){
            sql = "SELECT notes FROM IID1 WHERE id= ? AND modules='Python';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM IID1 WHERE id= ? AND modules='algebre pour ingenieur';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM IID1 WHERE id= ? AND modules='analyse pour ingenieur';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM IID1 WHERE id= ? AND modules='traitement des données';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM IID1 WHERE id= ? AND modules='algorithme';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM IID1 WHERE id= ? AND modules='base de données';";
        }
    }
    if (Rp==7){
        if (Rp_==1){
            sql = "SELECT notes FROM IID2 WHERE id= ? AND modules=' machine learning';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM IID2 WHERE id= ? AND modules='Java EE';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM IID2 WHERE id= ? AND modules='recherche operationelle';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM IID2 WHERE id= ? AND modules='vision par ordinateur';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM IID2 WHERE id= ? AND modules='data werehouse';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM IID2 WHERE id= ? AND modules='modelisation oriente objet';";
        }
    }
    if (Rp==8){
        if (Rp_==1){
            sql = "SELECT notes FROM IID3 WHERE id= ? AND modules='Js mobile';";
        }
        if (Rp_==2){
            sql = "SELECT notes FROM IID3 WHERE id= ? AND modules='deep learning';";
        }
        if (Rp_==3){
            sql = "SELECT notes FROM IID3 WHERE id= ? AND modules='genie logiciel';";
        }
        if (Rp_==4){
            sql = "SELECT notes FROM IID3 WHERE id= ? AND modules='big data';";
        }
        if (Rp_==5){
            sql = "SELECT notes FROM IID3 WHERE id= ? AND modules='ingenierie des connaissances';";
        }
        if (Rp_==6){
            sql = "SELECT notes FROM IID3 WHERE id= ? AND modules='parriage au millieu profesionnel';";
        }
    }
    sqlite3_stmt* stmt;
    int note;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        note= sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return note;
}
void updateNotes(sqlite3* db ,int Rp,int Rp_,int idToUpdate, int newNote) {
    char* errorMessage = nullptr;
    string sqlStatement;
    std::string module;
    if (Rp==1){
        if (Rp_==1){
            module="algebre1";
        }
        if (Rp_==2){
            module="analyse1";
        }
        if (Rp_==3){
            module="mecanique1";
        }
        if (Rp_==4){
            module="informatique1";
        }
        if (Rp_==5){
            module="chimie1";
        }
        if (Rp_==6){
            module="electrostatique1";
        }
    }
    if (Rp==2){
        if (Rp_==1){
            module="algebre2";
        }
        if (Rp_==2){
            module="analyse2";
        }
        if (Rp_==3){
            module="mecanique2";
        }
        if (Rp_==4){
            module="informatique2";
        }
        if (Rp_==5){
            module="chimie2";
        }
        if (Rp_==6){
            module="electrostatique2";
        }
    }
    if (Rp==3){
        if (Rp_==1){
            module="c++";
        }
        if (Rp_==2){
            module="python";
        }
        if (Rp_==3){
            module="probabilite";
        }
        if (Rp_==4){
            module="algorithme";
        }
        if (Rp_==5){
            module="java";
        }
        if (Rp_==6){
            module="php";
        }
    }
    if (Rp==4){
        if (Rp_==1){
            module="math pour les ingenieur";
        }
        if (Rp_==2){
            module="recherche operationelle";
        }
        if (Rp_==3){
            module="internet des objets";
        }
        if (Rp_==4){
            module="analyse de données";
        }
        if (Rp_==5){
            module="resaux";
        }
        if (Rp_==6){
            module="programmation web";
        }
    }
    if (Rp==5){
        if (Rp_==1){
            module="systeme d'exploitation";
        }
        if (Rp_==2){
            module="gestion de projet";
        }
        if (Rp_==3){
            module="UNIX";
        }
        if (Rp_==4){
            module="XML";
        }
        if (Rp_==5){
            module="IHM";
        }
        if (Rp_==6){
            module="machine learning";
        }
    }
    if (Rp==6){
        if (Rp_==1){
            module="Python";
        }
        if (Rp_==2){
            module="algebre pour ingenieur";
        }
        if (Rp_==3){
            module="analyse pour ingenieur";
        }
        if (Rp_==4){
            module="traitement des données";
        }
        if (Rp_==5){
            module="algorithme";
        }
        if (Rp_==6){
            module="base de données";
        }
    }
    if (Rp==7){
        if (Rp_==1){
            module="machine learning";
        }
        if (Rp_==2){
            module="Java EE";
        }
        if (Rp_==3){
            module="recherche operationelle";
        }
        if (Rp_==4){
            module="vision par ordinateur";
        }
        if (Rp_==5){
            module="data werehouse";
        }
        if (Rp_==6){
            module="modelisation oriente objet";
        }
    }
    if (Rp==8){
        if (Rp_==1){
            module="Js mobile";
        }
        if (Rp_==2){
            module="deep learning";
        }
        if (Rp_==3){
            module="genie logiciel";
        }
        if (Rp_==4){
            module="big data";
        }
        if (Rp_==5){
            module="ingenierie des connaissances";
        }
        if (Rp_==6){
            module="parriage au millieu profesionnel";
        }
    }
    switch(Rp){
        case 1:
            sqlStatement = "UPDATE API1 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 2:
            sqlStatement = "UPDATE API2 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 3:
            sqlStatement = "UPDATE GI1 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 4:
            sqlStatement = "UPDATE I2 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 5:
            sqlStatement = "UPDATE GI3 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 6:
            sqlStatement = "UPDATE IID1 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 7:
            sqlStatement = "UPDATE IID2 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        case 8:
            sqlStatement = "UPDATE IID3 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
        default:
            sqlStatement = "UPDATE API1 SET notes = ? WHERE id = ? AND modules = ?;";
            break;
    }
    sqlite3_stmt* stmt;
    int resultCode = sqlite3_prepare_v2(db, sqlStatement.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, newNote);
    sqlite3_bind_int(stmt, 2, idToUpdate);
    sqlite3_bind_text(stmt, 3, module.c_str(), -1, SQLITE_STATIC);
    resultCode = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
void note_etudiant(int idToRetrieve,int Rp,sqlite3* db) {
    sqlite3_stmt* stmt;
    std::string sqlStatement;
    switch(Rp){
        case 1:
            sqlStatement = "SELECT modules , notes FROM API1 WHERE id = ?;";
            break;
        case 2:
            sqlStatement = "SELECT modules , notes FROM API2 WHERE id = ?;";
            break;
        case 3:
            sqlStatement = "SELECT modules , notes FROM GI1 WHERE id = ?;";
            break;
        case 4:
            sqlStatement = "SELECT modules , notes FROM GI2 WHERE id = ?;";
            break;
        case 5:
            sqlStatement = "SELECT modules , notes FROM GI3 WHERE id = ?;";
            break;
        case 6:
            sqlStatement = "SELECT modules , notes FROM IID1 WHERE id = ?;";
            break;
        case 7:
            sqlStatement = "SELECT modules , notes FROM IID2 WHERE id = ?;";
            break;
        case 8:
            sqlStatement = "SELECT modules , notes FROM IID3 WHERE id = ?;";
            break;
    }
    int resultCode = sqlite3_prepare_v2(db, sqlStatement.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idToRetrieve);
    while ((resultCode = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* module = sqlite3_column_text(stmt,0);
        int notes = sqlite3_column_int(stmt, 1);
        if(notes != -1){
            space(5);
            cout << module << " Notes: " << notes << std::endl;
        }else{
            space(5);
            cout << module << endl;
        }
    }
    sqlite3_finalize(stmt);
}

// ! ---------------------------------------------------
void clear_terminal(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void close_DB(sqlite3* db){
    sqlite3_close(db);
}
#define blue "\033[34m"
#define rescolor "\033[0m"
void print_blue_line(int j){
    for(int i = 0;i<j;i++){
        cout << blue << "-" << rescolor ;
    }
}
void endline(int j){
    for(int i = 0;i<j;i++){
        cout << "\n";
    }
}
void space(int j){
    for(int i = 0;i<j;i++){
        cout << "\t" ;
    }
}
