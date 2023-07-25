#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class lexical_container
{
public:
    string lexeme;
    string type;
    string error;
    int len;
    lexical_container() {};
    lexical_container(string l, string t, int s, string e = "") : lexeme(l), type(t), len(s), error(e) {};
};

class analysed_code
{
public:
    string origin;
    string error;
    lexical_container lblField;
    lexical_container mnemField;
    int pusto = 0;
    vector<vector<lexical_container>*>* opFields;
    vector<lexical_container> lexical_containers;
    void make_struct_sentense();
    analysed_code(string _origin) : origin(_origin) {}
};

class analyser
{
public:
    list<analysed_code*> processedCode;
    list<string> originalCode;
    analyser(list<string> lines) : originalCode(std::move(lines)) { }
    void analyse_code();
    void print();
private:
    lexical_container makeLexemeContainer(string tmp, string type, int len, string error = "");
    lexical_container makeLexemeContainerForNum(string tmp); \
    bool isNum(char ch);
    bool isSymb(char ch);
    string LexType(string lex);
};




void analyser::analyse_code()
{
    for (string line : this->originalCode)
    {
        int len = line.length() + 1;
        const char* Chars = line.c_str();
        analysed_code* codeLine = new analysed_code(line);
        int i = 0;

        while (i < len)
        {
            char ch1 = Chars[i];
            if (ch1 == '1' || ch1 == '2' || ch1 == '3' || ch1 == '4' || ch1 == '5' || ch1 == '6' || ch1 == '7' || ch1 == '8' || ch1 == '9' || ch1 == '0')
            {
                string tmp(1, toupper(ch1));
                i++;
                while (i < len)
                {
                    char ch2 = toupper(Chars[i]);
                    if (this->isNum(ch2))
                    {
                        tmp += ch2;
                        i++;
                    }
                    else
                    {
                        i--;
                        break;
                    }
                }
                codeLine->lexical_containers.push_back(this->makeLexemeContainerForNum((tmp)));
            }
            else if (isalpha(ch1))
            {
                string tmp(1, toupper(ch1));
                i++;
                while (i < len)
                {
                    char ch2 = Chars[i];
                    if (isalnum(ch2))
                    {
                        tmp += toupper(ch2);
                        i++;
                    }
                    else
                    {
                        i--;
                        break;
                    }
                }
                codeLine->lexical_containers.push_back(this->makeLexemeContainer(tmp, this->LexType(tmp), tmp.length()));
            }
            else if (this->isSymb(ch1))
            {
                codeLine->lexical_containers.push_back(this->makeLexemeContainer(string(1, ch1), "symbol", 1));
            }
            else if (ch1 == ';')
            {
                return;
            }
            i++;
        }
        codeLine->make_struct_sentense();
        this->processedCode.push_back(codeLine);
    }
}



bool analyser::isNum(char ch)
{
    if (isdigit(ch) || ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E' || ch == 'F' || ch == 'H')
        return true;
    else return false;
}

lexical_container analyser::makeLexemeContainerForNum(string tmp)
{
    string type;
    string number = tmp.substr(0, tmp.length() - 1);
    char endChar = tmp.back();
    int len = tmp.length();
    string error = "";

    if (tmp.back() == 'B')
    {
        type = "imm_bin";
        for (int i = 0; i < number.size(); i++)
        {
            if (number[i] != '1' && number[i] != '0')
                error = tmp + " is not binary";
        }
    }
    else if (tmp.back() == 'H')
    {
        type = "imm_hex";
        for (int i = 0; i < number.size(); i++)
        {
            if (!this->isNum(number[i]) || number[i] == 'H')
                error = tmp + " is not hex";
        }
    }
    else
    {
        type = "imm_dec";
        string num_str = endChar == 'D' ? number : tmp;
        for (int i = 0; i < number.size(); i++)
        {
            if (!isdigit(number[i]))
                error = tmp + " is not dec";
        }
    }
    return lexical_container(tmp, type, len, error);
}

bool analyser::isSymb(char ch)
{
    if (ch == '+' || ch == '-' || ch == ':' || ch == '*' || ch == '[' || ch == ']' || ch == ',' || ch == '.' || ch == '=')
        return  true;
    else return false;
}



lexical_container analyser::makeLexemeContainer(string tmp, string type, int len, string error)
{
    return lexical_container(tmp, type, len);
}

string analyser::LexType(string lex) {
    list<string> commands({ "STD", "PUSH", "POP", "SBB", "IMUL", "CMP", "ADC", "JNA", "JMP" });
    if (find(commands.begin(), commands.end(), lex) != commands.end())
        return "command";
    list<string> reg32({ "EAX", "EBX", "ECX", "EDX", "ESI", "EDI", "EBP", "ESP" });
    if (find(reg32.begin(), reg32.end(), lex) != reg32.end())
        return "reg32";
    list<string> reg8({ "AH", "AL", "BH", "BL", "CH", "CL", "DH", "DL" });
    if (find(reg8.begin(), reg8.end(), lex) != reg8.end())
        return "reg8";
    list<string> segments({ "CS", "DS", "ES" ,"GS","FS","SS"});
    if (find(segments.begin(), segments.end(), lex) != segments.end())
        return "seg-reg";
    list<string> varsizes({ "DB", "DW", "DD" ,"FAR" });
    if (find(varsizes.begin(), varsizes.end(), lex) != varsizes.end())
        return "var-size";
    list<string> directives({ "END", "ENDS" , "ASSUME", "SEGMENT", "PTR"  });
    if (find(directives.begin(), directives.end(), lex) != directives.end())
        return "directive";
    return "identifier";
}

void analysed_code::make_struct_sentense()
{
    vector<lexical_container> localLex = vector<lexical_container>(this->lexical_containers);
    if (localLex.size() == 0)
    {
        this->pusto = 1;
        return;
    }
    int flag = 0;
    if (localLex.size() == 2 && localLex[0].type == "identifier" && localLex[1].lexeme == ":")
    {
        this->lblField = lexical_container(localLex[0]);
        localLex.erase(localLex.begin());
        flag = 1;
    }
    else if (localLex[0].type == "identifier")
    {
        this->lblField = lexical_container(localLex[0]);
        localLex.erase(localLex.begin());
    }
    if (localLex[0].type == "command" || localLex[0].type == "directive" || localLex[0].type == "var-size")
    {
        this->mnemField = lexical_container(localLex[0]);
        localLex.erase(localLex.begin());
    }
    vector<vector<lexical_container>*>* op = new vector<vector<lexical_container>*>;
    vector<lexical_container>* subOP = new vector<lexical_container>;
    if (flag == 0)
    {
        if (localLex.size() > 0)
        {
            for (lexical_container lexeme : localLex)
            {
                if (lexeme.lexeme == ",")
                {
                    op->push_back(subOP);
                    subOP = new vector<lexical_container>;
                }
                else
                {
                    subOP->push_back(lexeme);
                }
            }
            if (subOP->size() > 0)
            {
                op->push_back(subOP);
            }
        }
        this->opFields = op;
    }
    
}

void analyser::print()
{
    int i = 1;
    ofstream fout;
    fout.open("lexer.txt");
    for (analysed_code* k : this->processedCode)
    {
        int j = 1;
        fout << i++ << ") " << k->origin << (k->error != "" ? ("\t|" + k->error) : "") << "\n";
        for (lexical_container lexeme : k->lexical_containers)
        {
            fout << "\t" << j++ << ") '" << lexeme.lexeme << "' (" << lexeme.len << ") " << lexeme.type << "\n";
            if (lexeme.error != "")
                fout << "Error" + lexeme.error << "\n";
        }
        fout << "\t Sentence struct: ";
        int s = 1;
        if (k->lblField.len > 0)
            fout << "(label: " << s++ << ", 1) ,";
        if (k->mnemField.len > 0)
            fout << "(mnem: " << s++ << ", 1) ,";
        if (k->opFields)
            for (vector<lexical_container>* op : *k->opFields)
            {
                fout << "(op: " << s << ", " << op->size() << ") , ";
                s += op->size() + 1;
            }
        if (k->pusto == 1)
            fout << "pusto";
        fout << "\n";
    }
    fout.close();
}