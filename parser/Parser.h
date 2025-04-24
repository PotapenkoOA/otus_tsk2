#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <list>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

using namespace std;


string getContentFromFile( string filePath )
{
    string content, line;
    ifstream in_file(filePath);

    if (!in_file.is_open()) {
        cout<<( "Error opening file\n");
        return "";
    }

    // Читаем весь файл в строку
    while (getline(in_file, line)) {
        content += line + "\n";
    }

    in_file.close();
    return content;
}

struct funcDescription
{
    string returnType;
    list<string> *argumentDescription;
    list<string> *argumentType;
};

map<string, map<string,funcDescription*>*> mapInterfaces;

inline void ParseClassIn( string class_in, map<string,funcDescription*>* _funcs )
{
    regex propertyPattern(R"(.*virtual\s+(.*?)\s+(\w+)\s*\(\s*([^\s^)]*)\s*([^)]*)\)\s*=\s*0\s*;)");
    smatch _match;
    string::const_iterator searchStart2 = class_in.cbegin();
    while (regex_search( searchStart2, class_in.cend(), _match, propertyPattern )) {

        string funcName = (string)_match[2];
        (*_funcs)[funcName] = new funcDescription{(string)_match[1], new list<string>(), new list<string>() };
        (*_funcs)[funcName]->argumentDescription->push_back(_match[4]);
        (*_funcs)[funcName]->argumentType->push_back(_match[3]);

        searchStart2 = _match.suffix().first;
    }
}

bool Parser( string filePath,
            map<string, map<string,funcDescription*>*>* pMapInterfaces)
{
    string content = getContentFromFile(filePath);

    // Регулярное выражение для поиска класса
    regex classPattern(R"(.*class\s+\I?([^{^:^\n]+)\s*(:\s*[^{]+)?\{((?:[^\}]|}(?!;))*)\}\s*;)");
    smatch match;

    string::const_iterator searchStart = content.cbegin();
    while (regex_search(searchStart, content.cend(), match, classPattern)) {

        map<string,funcDescription*>* _funcs = new map<string,funcDescription*>();
        string class_in = match[3];

        ParseClassIn(class_in, _funcs);

        if(_funcs->size() > 0)
        {
            string className = (string)match[1];
            (*pMapInterfaces)[className] = _funcs;
        }

        searchStart = match.suffix().first;
    }

    return 1;
}

string GetRequerement( string className, string funcName )
{
    if( funcName.find("get") != string::npos)
        return "\""+className+"."+ funcName.substr(3) +".get\"";

    if( funcName.find("set") != string::npos)
        return "\""+className+"."+ funcName.substr(3) +".set\"";

    return "\""+className+"."+ funcName+"\"";
}

void CreateAdapterFile( string AdapterName, string FileContent )
{
    ofstream ofile(AdapterName+".h");

    ofile<<FileContent;

    ofile.close();
}

string toUpper( string str )
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string toLower( string str )
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool CreateAdapters( map<string, map<string,funcDescription*>*>* pMapInterfaces, string outPath )
{
    for (auto pair : *pMapInterfaces) {

        string content = "#ifndef "+toUpper(pair.first)+"_ADAPTER\n#define "+toUpper(pair.first)+"_ADAPTER\n\n#include \"../IoCcontainer.h\"\n#include \"../interfaces_obj/"+toLower(pair.first)+".h\"\n\n class "+pair.first+"Adapter: public I" + pair.first + " {\n";
        content += "\n\tIResolverContainer* m_pObj;\n\n\tpublic:\n\t"+pair.first+"Adapter( IResolverContainer* pObj ) {\n\t\tm_pObj = pObj;\n\t}\n\n";

        for (auto func: *pair.second) {

            content += "\t"+func.second->returnType + " " + func.first + "( ";

            string setTypes = "";
            for( auto type: *func.second->argumentType )
            {
                content += type ;
                if(!type.empty())
                    setTypes += " ,"+type;
            }

            string setNames = "";
            for( auto param:*func.second->argumentDescription )
            {
                content += " "+param ;
                if(!param.empty())
                    setNames += " ,"+param;
            }

            content += "){\n\t\t";
            if( func.second->returnType != "void"  )
                content += "return ";

            content += "IoC::Resolve<"+func.second->returnType+",IResolverContainer*"+ setTypes +" >("+GetRequerement(pair.first,func.first)+", m_pObj"+ setNames +");\n\t}\n\n";
        }
        content += "};\n\n";
        content += "class "+pair.first+"AdapterRegistration: public ICommand\n{\n\tpublic:\n\t"+pair.first+"AdapterRegistration()\n\t{\n\t\n\t}\n\t\n\tvoid Execute()\n\t";
        content += "{\n\t\tIoC::Resolve<ICommand*, string, IResolverContainer*>(\"IoC.Register\",\"Adapter.I"+pair.first+"\", new ResolverContainer<function<"+pair.first+"Adapter*(IResolverContainer*)>>";
        content += " (\n\t\t\tfunction<"+pair.first+"Adapter*(IResolverContainer*)>([&](IResolverContainer* obj){\n\t\t\t\treturn new "+pair.first+"Adapter(obj);\n\t\t\t})\n\t\t) )->Execute();\n\t}\n};\n";
        content += "\n#endif\n";
        CreateAdapterFile(outPath+"/"+pair.first+"Adapter", content);
    }

    return true;
}

#endif // PARSER_H
