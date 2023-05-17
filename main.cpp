#include <iostream>
#include "QueryHandler/QueryHandler.hpp"


using namespace std;




int main()
{
    LinePrinter printer;
    QueryHandler handler;
    if(!handler.openDB("/home/mrsmit/vax"))
    {
        std::cout<<"ERROR"<<std::endl;
        return -1;
    }

    handler.intersection(printer);
    std::cout<<std::endl;
    handler.symmDiff(printer);

//    std::cout<<handler.insert(TableName::A, 123, "LOAD").value_or("ER")<<std::endl;
//    std::cout<<handler.insert(TableName::A, 124, "LOAD1").value_or("ER")<<std::endl;
//    std::cout<<handler.insert(TableName::A, 125, "LOAD2").value_or("ER")<<std::endl;;

    handler.close();
//    const char* inst  =   "INSERT INTO A (\"Data\", \"Key\") VALUES('vvv88', 55);";
//    const char* tranc  =  "DELETE FROM A";
//    const char* db_name = "/home/mrsmit/vax";

//    sqlite3* handle = nullptr;

//    if (sqlite3_open(db_name, &handle))
//     {
//       std::cerr << "Can't open database: " << sqlite3_errmsg(handle) << std::endl;
//       sqlite3_close(handle);
//       return EXIT_FAILURE;
//     }

//    auto print_results = [](void *, int columns, char **data, char **names) -> int{
//      for (int i = 0; i < columns; ++i)
//        std::cout << names[i] << " = " << (data[i] ? data[i] : "NULL") << std::endl;
//      std::cout << std::endl;
//      return 0;
//    };

//    char *errmsg;
//    int rc = sqlite3_exec(handle, inst, print_results, 0, &errmsg);

//    if (rc != SQLITE_OK)
//    {
//      std::cerr << "Can't execute query: " << errmsg << std::endl;
//      sqlite3_free(errmsg); // <--- обратите внимание не C-style работу с памятью
//      return EXIT_FAILURE;
//    }

//    int rc1 = sqlite3_exec(handle, tranc, print_results, 0, &errmsg);

//    if (rc1 != SQLITE_OK)
//    {
//      std::cerr << "Can't execute query: " << errmsg << std::endl;
//      sqlite3_free(errmsg); // <--- обратите внимание не C-style работу с памятью
//      return EXIT_FAILURE;
//    }

//    sqlite3_close(handle);

//    cout << "Hello World!" << endl;
    return 0;
}
