#include <iostream>
#include "sqlite/sqlite3.h"


using namespace std;



int main()
{


//      const char* db_name = ":memory:"; // <--- без файла, БД размещается в памяти
    const char* db_name = "cpp_sqlite_db.sqlite";
    sqlite3* handle = nullptr;

    if (sqlite3_open(db_name, &handle))
     {
       std::cerr << "Can't open database: " << sqlite3_errmsg(handle) << std::endl;
       sqlite3_close(handle);
       return EXIT_FAILURE;
     }

    sqlite3_close(handle);

    cout << "Hello World!" << endl;
    return 0;
}
