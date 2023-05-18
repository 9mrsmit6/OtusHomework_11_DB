#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP


#include <memory>
#include <unordered_map>
#include <string>
#include "../Utils/Utils.hpp"
#include "../QueryHandler/QueryHandler.hpp"


//Обработчик запросов сети из предыдущей работы
//Вместо парсера просто разбор протокола и инициирование запросов к СУБД
struct Handler
{
    Handler():
        dbHandler{}
    {
        dbHandler.openDB("vax");  //Тут сама база
    }

    ~Handler()
    {
        dbHandler.close();
    }

    template <class P>
    std::string execute(std::istream& work, P& printer)
    {
        //Берем строку, разбиваем ее на части
        std::string s;
        std::getline(work, s);
        std::vector<std::string> parsedStr;
        Utils::split(s,parsedStr,' ');

    try
    {
        //Исполняем команды
        if(parsedStr.at(0)=="INSERT")
        {
            auto table  =   getTableNameByString    (   parsedStr.at(1));
            auto id     =   std::stoi               (   parsedStr.at(2));
            auto res    =   dbHandler.insert(table,id,  parsedStr.at(3));

            return res;
        }
        if(parsedStr.at(0)=="TRUNCATE")
        {
            auto table  =   getTableNameByString    (   parsedStr.at(1));
            auto res    =   dbHandler.trancateTable(table);
            return res;
        }
        if(parsedStr.at(0)=="INTERSECTION")
        {
            auto ret=dbHandler.intersection(printer);
            return ret;
        }
        if(parsedStr.at(0)=="SYMMETRIC_DIFFERENCE")
        {
            auto ret=dbHandler.symmDiff(printer);
            return ret;
        }
    }
    catch(...)
        {
            return "EXCEPTION"; //Что-то пошло не так
        }
        return "BAD CMD"; //Нет такой команды
    }

    private:       
        QueryHandler dbHandler;
};



#endif // CONTEXTMANAGER_HPP
