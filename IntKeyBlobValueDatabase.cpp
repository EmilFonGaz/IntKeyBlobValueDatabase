// IntKeyBlobValueDatabase.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sqlite/sqlite3.h>

void err_message(char*mes) {
    std::cout << "erorr: " << mes << std::endl;
}

class IntKeyBlobValueDatabase {
public:
    sqlite3* db;
    sqlite3_stmt* stmt;
    char* err; //error marker SQLite 3
    uint64_t name; // Name of point
    //uint64_t start_key; //
    uint64_t stop_key;
    std::vector<uint8_t> data;
    const char *sql;
    std::string comm;
    

    void init() {
        int rc = sqlite3_open("database.db", &db);
        if (rc != SQLITE_OK) {
            err_message(err);
        }
        else {
            std::cout << "Data Base open" << std::endl;
        }
        rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS points(name INT, data INT);", NULL, NULL, &err);
        if (rc != SQLITE_OK) {
            err_message(err);
        }
        else {
            std::cout << "Data Base initialized" << std::endl;
        }
    }
    /*/
    void remove_all() {
        sql = "DELETE from points; " \ "SELECT * from points";
        sqlite3* db;
        sqlite3_stmt* stmt;
        sqlite3_exec(db, sql, NULL, NULL, &err);
        std::cout << "Data Base removed" << std::endl;
    }
    /*
    void remove(start_key, stop_key) { //удалить все начиная от ключа start_key заканчивая stop_key
        for (start_key <= stop_key; start_key++) {
            int rc = sqlite3_exec(db, "CREATE TABEL IF NOT EXIST points(name INT, data BLOB)", NULL, NULL, &err);
            if (rc != SQLITE_OK) {
                cout << "erorr: " << err << endl;
            }
        }
    }
    
    void read(key, data) {// получить по ключу данные в дата

    }
  */
    void write(uint64_t name, uint64_t ds){//std::vector<uint8_t> data) { // записать в БД по ключу данные из data
        comm = "INSERT INTO points (name, data) VALUES ("+ std::to_string(name) +", '"+ std::to_string(ds) +"')";

        int rc = sqlite3_exec(db, comm.c_str(), NULL, NULL, &err);

        if (rc != SQLITE_OK) {
            err_message(err);
        }
        else {
            std::cout << "Data Base write - OK" << std::endl;
        }
    }

    void write(std::string list) { // записать список пар "ключ-значение"
        std::ifstream fin;
        fin.open(list);
        uint64_t a;
        uint64_t b;

        if (!fin.is_open()) {
            std::cout << "Open file error" << std::endl;
        }
        else {
            std::cout << "File is open!" << std::endl;

            std::string str;
            bool fl = false;
            while (!fin.eof())
            {
                fin >> str;
                if (!fl) {
                    a = std::stoi(str);
                }
                else
                {
                    b = std::stoi(str);        

                    comm = "INSERT INTO points (name, data) VALUES (" + std::to_string(a) + ", '" + std::to_string(b) + "')";

                    int rc = sqlite3_exec(db, comm.c_str(), NULL, NULL, &err);

                    if (rc != SQLITE_OK) {
                        err_message(err);
                    }
                    else {
                        std::cout << "Data Base write - OK" << std::endl;
                    }
                }
                fl = !fl;
                std::cout << str << std::endl;

            }
        }
        fin.close();
    }
    /*
    void read(start_key, stop_key, list) { // прочитать список пар "ключ-значение" в диапазоне от start_key до stop_key

    }

    void get_min_max(min_key, max_key) { // получить минимальный и максимальный ключ

    }

    bool check(key) { // проверить наличие данных по ключу

    }

    void remove(key) { // удалить данные по ключу

    }*/
};

void callfunc() {
    IntKeyBlobValueDatabase base;

}

int main()
{
    uint64_t a;
    uint64_t b;
    IntKeyBlobValueDatabase base;
    base.init();
    
    
    /*для WRITE (List)*/
    std::string path = "list.txt";
    base.write(path);

    /* для WRITE (NAME, DATA)*/
    while (1) {
        std::cout << "Enter name" << std::endl;
        std::cin >> a;
        std::cout << "Enter data" << std::endl;
        std::cin >> b;
        if (a && b) {
            base.write(a, b);
        }
    }
    return 0;
    
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
