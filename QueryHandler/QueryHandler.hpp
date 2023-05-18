#ifndef QUERYHANDLER_HPP
#define QUERYHANDLER_HPP

#include "../sqlite/sqlite3.h"
#include <sstream>
#include <iostream>

#include <memory>
#include <utility>

//В этом модуле обертка над sqlite в обьеме необходимом для решения задач самостоятельной работы

//Имена таблиц
enum class TableName
{
    A=0,
    B,
    ER
};


//Конвертер строки в имя таблицы
TableName getTableNameByString(const std::string& sv)
{
    if(sv=="A"){return TableName::A;}
    if(sv=="B"){return TableName::B;}
    return TableName::ER;
}


//Формировалка запросов к СУБД
struct QueryHandler
{
    QueryHandler()  =   default;
    ~QueryHandler() =   default;

   //Открываем БД
    bool openDB(const char* dbFileName)
    {
        if (sqlite3_open(dbFileName, &handle))
        {
            sqlite3_close(handle);
            return false;
        }
        return true;
    }

    //Закрываем БД
    void close()
    {
        sqlite3_close(handle);
    }

    //Требуемые в задании запросы
    //Они возвращают строку с результатом который я отдаю по сети назад
    std::string trancateTable(TableName table)
    {
        int r{0};
        auto print_results = [](void *, int columns, char **data, char **names) -> int{  return 0;  };
        char *errmsg;

        switch(table)
        {
            case TableName::A:
                r=sqlite3_exec(handle, "DELETE FROM A", print_results, 0, &errmsg);
                break;
            case TableName::B:
                r=sqlite3_exec(handle, "DELETE FROM B", print_results, 0, &errmsg);
                break;
            default:
                return "ERR";
        }

        if (r != SQLITE_OK)
        {
            sqlite3_free(errmsg);
            return "ERR";
        }
        return "OK";
    }

    std::string insert(TableName table, unsigned int id, std::string& load)
    {
        std::stringstream ss;
        ss<<"INSERT INTO";

        switch(table)
        {
            case TableName::A   :ss<<" A ";    break;
            case TableName::B   :ss<<" B ";    break;
            default:  return "ER inval table Name";
        }

        ss<<"(\"Data\", \"Key\") VALUES('"<<load<<"', "<<id<<");";

        auto print_results = [](void *, int columns, char **data, char **names) -> int{  return 0;  };
        char *errmsg;

        int r=sqlite3_exec(handle, ss.str().c_str(), print_results, 0, &errmsg);
        if (r != SQLITE_OK)
        {
            std::stringstream ret;
            ret<<"ERR "<<errmsg;
            sqlite3_free(errmsg);
            return ret.str();
        }

        return "OK";
    }

    template <class E>
    std::string intersection(E& printer)
    {
        return query(printer, "SELECT A.Key, A.Data, B.Data  FROM A, B WHERE A.Key=B.Key");
    }

    template <class E>
    std::string symmDiff(E& printer)
    {
        return query(printer, "SELECT A.Key, A.Data, NULL  FROM A WHERE A.Key NOT IN (SELECT Key FROM B) UNION SELECT B.Key, NULL, B.DATA  FROM B WHERE B.Key NOT IN (SELECT Key FROM A)");
    }

    private:
        sqlite3* handle{nullptr};
        std::string response;

        template <class E>
        std::string query(E& printer, std::string q)
        {
            char *errmsg;
            int r=sqlite3_exec(handle, q.c_str(), printTable<E>, &printer, &errmsg);
            if (r != SQLITE_OK)
            {
               sqlite3_free(errmsg);
                return "ERR";
            }
            return "OK";
        }

        template <class E>
        static inline int printTable (void *printer, int columns, char **data, char **names)
        {
            std::stringstream ss;
            for (int i{0}; i != columns; i++)
            {
                if(i!=0){ss<<", ";}
                ss<<(data[i] ? data[i] : "NULL");
            }
            static_cast<E*>(printer)->executeResponse(std::move(ss.str()));
            return 0;
        }

};

#endif // QUERYHANDLER_HPP
