#pragma once
#include <list>
#include <map>
#include <iostream>
#include <cctype>
#include <utility>
#include <vector>
#include <iomanip>
#include <sstream>
#include "LexAnalyse.h"


using namespace std;

class Symbol
{
    public:
        string segment;
        int offset;
        string label;
        string size;
};

class Memory
{
    public:
        string size;
        string segment;
        string identifier;
        string base;
        string mul;
        bool error;
};

class ListingLine
{
    public:
        string txt, error;
        int offset;
        string opcode_string;
        analysed_code* origin;
        ListingLine(analysed_code* o, int of = -1) : txt(o->origin), offset(of), origin(o) {}
};

class Compiler
{
    public:
        int offset = 0;
        map<string, Symbol> var_list;
        map<string, Symbol> label_table;
        list<analysed_code*> parsed_code;
        vector<ListingLine> listing;
        vector<string> segment_list;
        string active_segment;
        map<string, string> segments{ {"DS", ""},{"CS", ""},{"FS", ""},{"GS", ""},{"SS", ""} };


        Compiler(list<analysed_code*> code) : parsed_code(std::move(code)) {}
        void first_view();
        void second_view();
        string get_listing();

        Memory analyse_mem(vector<lexical_container>* operand);
        long int analyse_imm(vector<lexical_container>* operand);

        void save_label(string segment, int offset, string label);
        void save_var(string segment, int offset, string label, string size);

        bool check_imm(vector<lexical_container>* operand);
        bool check_mem(vector<lexical_container>* operand);
        bool check_reg(vector<lexical_container>* operand);
        bool check_farptr(vector<lexical_container>* operand);

        void declare_var(analysed_code* sentence);
        void segment(analysed_code* sentence);
        void assume(analysed_code* sentence);
        void declare_label(analysed_code* sentence);
        void std(analysed_code* sentence);
        void push(analysed_code* sentence);
        void sbb(analysed_code* sentence);
        void pop(analysed_code* sentence);
        void jna(analysed_code* sentence);
        void mov_reg(analysed_code* sentence);
        void imul(analysed_code* sentence);
        void cmp(analysed_code* sentence);
        void adc(analysed_code* sentence);
        void jmp_1(analysed_code* sentence);
        void jmp_2(analysed_code* sentence);
};



template<typename T>
std::string int_to_hex(T i, int w)
{
    std::stringstream stream;
    stream << uppercase << setfill('0') << std::setw(w) << hex << i;
    return stream.str().substr(stream.str().size() - w);
}

string get_segment_prefix(string segment_reg)
{
    if (segment_reg == "DS")
        return "3E";
    if (segment_reg == "ES")
        return "26";
    if (segment_reg == "CS")
        return "2E";
    if (segment_reg == "SS")
        return "36";
    if (segment_reg == "GS")
        return "65";
    if (segment_reg == "FS")
        return "64";
    return "";
}

unsigned short regs(string reg)
{
    if (reg == "AL" || reg == "EAX")
        return 0b000;
    if (reg == "AH" || reg == "ESP")
        return 0b100;
    if (reg == "BL" || reg == "EBX")
        return 0b011;
    if (reg == "BH" || reg == "EDI")
        return 0b111;
    if (reg == "CL" || reg == "ECX")
        return 0b001;
    if (reg == "CH" || reg == "EBP")
        return 0b101;
    if (reg == "DL" || reg == "EDX")
        return 0b010;
    if (reg == "DH" || reg == "ESI")
        return 0b110;
    return 0;
}

unsigned short mod_rm(unsigned short p1, unsigned short p2, unsigned short p3)
{
    unsigned short modrm;
    modrm = p1 << 6;
    modrm |= p2 << 3;
    modrm |= p3;
    return modrm;
}

string get_modrm(Memory mem, unsigned short op2)
{
    if (!mem.identifier.empty() && mem.base.empty())
    {
        return int_to_hex(mod_rm(0b00, op2, 0b101), 2);
    }
    else
    {
        string  mod_rm_sib = int_to_hex(mod_rm(0b00, op2, 0b100), 2);
        unsigned short sib = 0b00 << 6;
        if (mem.mul == "2")
            sib = 0b01 << 6;
        if (mem.mul == "4")
            sib = 0b10 << 6;
        if (mem.mul == "8")
            sib = 0b11 << 6;
        sib |= regs(mem.base) << 3;
        sib |= 0b101;
        return mod_rm_sib + " " + int_to_hex(sib, 2);
    }

    return "";
}

void Compiler::first_view() 
{
    this->offset = 0;

    for (auto parsed_line : this->parsed_code) 
    {
        string mnemonics = parsed_line->mnemField.lexeme;

        if (mnemonics == "DB" || mnemonics == "DW" || mnemonics == "DD") 
        {
            this->declare_var(parsed_line);
        }
        else if (mnemonics == "SEGMENT" || mnemonics == "ENDS") 
        {
            this->segment(parsed_line);
        }
        else if (mnemonics == "ASSUME")
        {
            this->assume(parsed_line);
        }
        else if (mnemonics == "STD") 
        {
            this->std(parsed_line);
        }
        else if (mnemonics == "PUSH") 
        {
            this->push(parsed_line);
        }
        else if (mnemonics == "POP")
        {
            this->pop(parsed_line);
        }
        else if (mnemonics == "JNA") 
        {
            this->jna(parsed_line);
        }
        else if (mnemonics == "SBB")
        {
            this->sbb(parsed_line);
        }
        else if (mnemonics == "CMP") 
        {
            this->cmp(parsed_line);
        }
        else if (mnemonics == "ADC") 
        {
            this->adc(parsed_line);
        }
        else if (mnemonics == "JMP") 
        {
            if (parsed_line->opFields->size() == 1 && this->check_mem(parsed_line->opFields->at(0))) 
            {
                this->jmp_2(parsed_line);
            }
            else 
            {
                this->jmp_1(parsed_line);
            }
        }
        else if (mnemonics == "IMUL") 
        {
            this->imul(parsed_line);
        }
        else if (!parsed_line->lblField.lexeme.empty() && mnemonics.empty() && parsed_line->opFields == nullptr) 
        {
            this->declare_label(parsed_line);
        }
        else 
        {
            ListingLine lst_line(parsed_line);
            this->listing.push_back(lst_line);
        }

    }
}

void Compiler::declare_var(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->lblField.lexeme.empty())
    {
        lst_line.error = "missing label";
    }
    else if (sentence->opFields->size() != 1) 
    {
        lst_line.error = "wrong operands";
    }
    else if (!this->check_imm(sentence->opFields->at(0))) 
    {
        lst_line.error = "invalid imm";
    }
    else 
    {
        vector<lexical_container>* operand = sentence->opFields->at(0);
        long int imm = this->analyse_imm(operand);
        string size = sentence->mnemField.lexeme;
        if (size == "DD" && (imm > 4294967295 || imm < -21474836480)) 
        {
            lst_line.error = "imm too big for DD";
        }
        else if (size == "DW" && (imm > 65535 || imm < -32767)) 
        {
            lst_line.error = "imm too big for DW";
        }
        else if (size == "DB" && (imm > 256 || imm < -128)) 
        {
            lst_line.error = "imm too big for DB";
        }
        else 
        {
            if (size == "DD") 
            {
                this->save_var(this->active_segment, this->offset, sentence->lblField.lexeme, "DWORD");
                this->offset += 4;
                lst_line.opcode_string = int_to_hex(imm, 8);
            }
            else if (size == "DW") 
            {
                this->save_var(this->active_segment, this->offset, sentence->lblField.lexeme, "WORD");
                this->offset += 2;
                lst_line.opcode_string = int_to_hex(imm, 4);
            }
            else
            {
                this->save_var(this->active_segment, this->offset, sentence->lblField.lexeme, "BYTE");
                this->offset += 1;
                lst_line.opcode_string = int_to_hex(imm, 2);
            }
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::save_label(string segment, int offset, string label) 
{
    Symbol symbol;
    symbol.segment = segment;
    symbol.offset = offset;
    symbol.label = label;
    this->label_table.insert({ label, symbol });
}

void Compiler::save_var(string segment, int offset, string label, string size) 
{
    Symbol symbol;
    symbol.segment = segment;
    symbol.offset = offset;
    symbol.label = label;
    symbol.size = size;
    this->var_list.insert({ label, symbol });
}

bool Compiler::check_imm(vector<lexical_container>* operand) 
{
    bool minus = false;

    if (operand->at(0).lexeme == "-") 
    {
        minus = true;
    }

    if ((minus && operand->size() != 2) || (!minus && operand->size() != 1))
    {
        return false;
    }
    if ((minus && operand->at(1).type != "imm_bin" && operand->at(1).type != "imm_hex" && operand->at(1).type != "imm_dec") ||
        (!minus && operand->at(0).type != "imm_bin" && operand->at(0).type != "imm_hex" && operand->at(0).type != "imm_dec"))
    {
        return false;
    }

    return true;
}

long int Compiler::analyse_imm(vector<lexical_container>* operand) 
{
    bool minus = false;
    int imm = 0;

    if (operand->at(0).lexeme == "-") 
    {
        minus = true;
    }

    lexical_container lexical_container = minus ? operand->at(1) : operand->at(0);

    if (lexical_container.type == "imm_bin")
    {
        string _str = lexical_container.lexeme.substr(0, lexical_container.lexeme.length() - 1);
        imm = (long int)stoul(_str, nullptr, 2);
    }
    else if (lexical_container.type == "imm_hex") 
    {
        string _str = lexical_container.lexeme.substr(0, lexical_container.lexeme.length() - 1);
        imm = (long int)stoul(_str, nullptr, 16);
    }
    else if (lexical_container.type == "imm_dec") 
    {
        string _str = lexical_container.lexeme.back() == 'D' ? lexical_container.lexeme.substr(0, lexical_container.lexeme.length() - 1) : lexical_container.lexeme;
        imm = (long int)stoul(_str, nullptr, 10);
    }

    return minus ? -1 * imm : imm;
}

bool Compiler::check_reg(vector<lexical_container>* operand) 
{
    if (operand->size() != 1)
        return false;
    if (operand->at(0).type != "reg32" && operand->at(0).type != "reg8")
        return false;
    return true;
}


bool Compiler::check_mem(vector<lexical_container>* operand) 
{
    vector<lexical_container> local = vector<lexical_container>(*operand);
    if (local.size() >= 2 && local[0].type == "seg-reg" && local[1].lexeme == ":")
        local = { local.begin() + 2, local.end() };
    if (local.size() == 1 && local.at(0).type == "identifier")
        return true;
    if (local.size() != 6)
        return false;
    if (local[0].type != "identifier" || local[1].lexeme != "[" || local[2].type != "reg32" ||
        local[3].lexeme != "*" ||
        !(local[4].lexeme == "2" || local[4].lexeme == "4" || local[4].lexeme == "8") ||
        local[5].lexeme != "]")
        return false;
    return true;
}

bool Compiler::check_farptr(vector<lexical_container>* operand) 
{
    if (operand->size() != 3)
        return false;
    if (operand->at(0).lexeme != "FAR" || operand->at(1).lexeme != "PTR" || operand->at(2).type != "identifier")
        return false;
    return true;
}

Memory Compiler::analyse_mem(vector<lexical_container>* operand) 
{
    vector<lexical_container> local = vector<lexical_container>(*operand);
    Memory mem;

    if (local.size() >= 2 && local[0].type == "seg-reg" && local[1].lexeme == ":") 
    {
        mem.segment = local[0].lexeme;
        local = { local.begin() + 2, local.end() };
    }

    mem.identifier = local[0].lexeme;
    if (local.size() > 1)
    {
        mem.base = local[2].lexeme;
        mem.mul = local[4].lexeme;
    }

    if (this->var_list.count(mem.identifier)) 
    {
        string seg = var_list[mem.identifier].segment;
        mem.size = var_list[mem.identifier].size;
        if (mem.segment.empty()) 
        {
            for (auto kv : this->segments) 
            {
                if (kv.second == seg) 
                {
                    mem.segment = kv.first;
                    break;
                }
            }
        }
    }

    return mem;
}

void Compiler::segment(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->lblField.lexeme.empty()) 
    {
        lst_line.error = "missing label";
    }
    else if (!sentence->opFields->empty()) 
    {
        lst_line.error = "no operands needed for segment";
    }
    else if (sentence->mnemField.lexeme == "SEGMENT" && find(this->segment_list.begin(), this->segment_list.end(), sentence->lblField.lexeme) != this->segment_list.end()) 
    {
        lst_line.error = "segment was defined before";
    }
    else {
        this->offset = 0;
        if (sentence->mnemField.lexeme == "SEGMENT") 
        {
            this->active_segment = sentence->lblField.lexeme;
            this->segment_list.push_back(this->active_segment);
        }
    }

    this->listing.push_back(lst_line);
}

string Compiler::get_listing() 
{
    string listing;

    for (auto line : this->listing) 
    {
        stringstream offset;
        string lineTxt;
        offset << hex << uppercase << setfill('0') << setw(4) << line.offset;
        if (line.offset < 0) 
        {
            lineTxt = "    ";
        }
        else 
        {
            lineTxt = offset.str();
        }
        if (!line.opcode_string.empty())
        {
            lineTxt += "\t" + line.opcode_string;
        }
        lineTxt += "\t" + line.txt;
        if (!line.error.empty()) 
        {
            lineTxt += " Error! " + line.error;
        }
        listing += lineTxt + "\n";
    }

    listing += "\n\nSymbols table:\n";
    stringstream symbol;
    for (auto var : this->var_list)
    {
        symbol << "Name:" << var.second.label << "\tSegment: " << var.second.segment
            << "\tSize:" << var.second.size << "\tOffset:" << hex << uppercase
            << setfill('0') << setw(4) << var.second.offset << "\n";
    }
    for (auto var : this->label_table)
    {
        symbol << "Name:" << var.second.label << "\tSegment:" << var.second.segment
            << "\tOffset:" << hex << uppercase << setfill('0') << setw(4) << var.second.offset << "\n";
    }

    listing += symbol.str();

    return listing;
}

void Compiler::assume(analysed_code* sentence) 
{
    ListingLine lst_line(sentence);

    if (sentence->opFields->empty()) 
    {
        lst_line.error = "at least one prefix:segment pair required";
    }
    else 
    {
        for (auto pair : *sentence->opFields) 
        {
            if (pair->size() != 3) {
                lst_line.error = "incorrect pair syntax";
            }
            else if (pair->at(0).type != "seg-reg" || pair->at(1).lexeme != ":" || pair->at(2).type != "identifier") 
            {
                lst_line.error = "incorrect pair syntax";
            }
            else if (find(this->segment_list.begin(), this->segment_list.end(), pair->at(2).lexeme) == this->segment_list.end()) 
            {
                lst_line.error = "reference to undefined segment";
            }
        }
    }

    if (lst_line.error.empty()) 
    {
        for (auto pair : *sentence->opFields)
        {
            this->segments[pair->at(0).lexeme] = pair->at(2).lexeme;
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::std(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (!sentence->opFields->empty()) 
    {
        lst_line.error = "no operands needed for STD";
    }
    else 
    {
        this->offset++;
        lst_line.opcode_string = "FD";
    }

    this->listing.push_back(lst_line);
}

void Compiler::push(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 1) 
    {
        lst_line.error = "operand missing";
    }
    else if (!this->check_reg(sentence->opFields->at(0)))
    {
        lst_line.error = "wrong operand syntax";
    }
    else if (sentence->opFields->at(0)->at(0).type == "reg8") 
    {
        lst_line.error = "reg8 is forbidden";
    }
    else 
    {
        lexical_container reg1 = sentence->opFields->at(0)->at(0);

        this->offset += 1;
        if (reg1.lexeme == "EAX") 
        {
            lst_line.opcode_string += "50";
        }
        else if (reg1.lexeme == "ECX") 
        {
            lst_line.opcode_string += "51";
        }
        else if (reg1.lexeme == "EDX")
        {
            lst_line.opcode_string += "52";
        }
        else if (reg1.lexeme == "EBX") 
        {
            lst_line.opcode_string += "53";
        }
        else if (reg1.lexeme == "ESP") 
        {
            lst_line.opcode_string += "54";
        }
        else if (reg1.lexeme == "EBP") 
        {
            lst_line.opcode_string += "55";
        }
        else if (reg1.lexeme == "ESI") 
        {
            lst_line.opcode_string += "56";
        }
        else if (reg1.lexeme == "EDI") 
        {
            lst_line.opcode_string += "57";
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::sbb(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 2) 
    {
        lst_line.error = "expected 2 operands";
    }
    else if (!this->check_reg(sentence->opFields->at(0)) || !this->check_reg(sentence->opFields->at(1))) 
    {
        lst_line.error = "wrong reg syntax";
    }
    else if (sentence->opFields->at(0)->at(0).type != sentence->opFields->at(1)->at(0).type) 
    {
        lst_line.error = "op types do not match";
    }
    else 
    {
        this->offset += 2;
        lst_line.opcode_string += sentence->opFields->at(0)->at(0).type == "reg8" ? "1A " : "1B ";
        lst_line.opcode_string += int_to_hex(mod_rm(0b11,regs(sentence->opFields->at(0)->at(0).lexeme),regs(sentence->opFields->at(1)->at(0).lexeme)), 2);
    }

    this->listing.push_back(lst_line);
}

void Compiler::pop(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 1) 
    {
        lst_line.error = "expected 1 operand";
    }
    else if (!this->check_mem(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong memory syntax";
    }
    else 
    {
        Memory memory = this->analyse_mem(sentence->opFields->at(0));
        if (memory.size.empty()) 
        {
            lst_line.error = "Unknown variable " + memory.identifier;
        }
        else if (memory.size != "DWORD") 
        {
            lst_line.error = "Wrong OP size for pop";
        }
        else if (memory.segment.empty()) 
        {
            lst_line.error = "Variable located in unmapped segment";
        }
        else 
        {
            string base_segment = memory.base == "EBP" || memory.base == "ESP" ? "SS" : "DS";
            if (memory.segment != base_segment) 
            {
                this->offset++;
                lst_line.opcode_string = get_segment_prefix(memory.segment) + ": " + lst_line.opcode_string;
            }
            this->offset += 6;
            if (!memory.base.empty())
                this->offset++;

            lst_line.opcode_string += "8F "; 
            lst_line.opcode_string += get_modrm(memory, 0b000); 
            lst_line.opcode_string += " " + int_to_hex(var_list[memory.identifier].offset, 8) + "r";
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::declare_label(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    this->save_label(this->active_segment, this->offset, sentence->lblField.lexeme);
    this->listing.push_back(lst_line);
}

void Compiler::jna(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 1) 
    {
        lst_line.error = "wrong operands for JNA";
    }
    else if (sentence->opFields->at(0)->size() != 1) 
    {
        lst_line.error = "wrong operand syntax";
    }
    else 
    {
        if (!this->label_table.count(sentence->opFields->at(0)->at(0).lexeme)) 
        {
            this->offset += 6;
        }
        else 
        {
            Symbol label = this->label_table[sentence->opFields->at(0)->at(0).lexeme];
            this->offset += (this->offset - label.offset <= 128) ? 2 : 6;
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::mov_reg(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 2) 
    {
        lst_line.error = "wrong operands for MOV";
    }
    else if (!this->check_reg(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong first operand";
    }
    else if (!this->check_imm(sentence->opFields->at(1))) 
    {
        if (this->check_mem(sentence->opFields->at(1))) 
        {
            this->imul(sentence);
            return;
        }
        else 
        {
            lst_line.error = "wrong second operand";
        }
    }
    else 
    {
        lexical_container reg = sentence->opFields->at(0)->at(0);
        vector<lexical_container>* imm = sentence->opFields->at(1);
        if (imm->at(0).type == "imm_txt") 
        {
            int txt_len = imm->at(0).len - 2;
            if (reg.type == "reg32" && txt_len > 4) 
            {
                lst_line.error = txt_len + " wrong size for DD";
            }
            else if (reg.type == "reg8" && txt_len > 1) 
            {
                lst_line.error = txt_len + " wrong size for DB";
            }
            else 
            {
                this->offset += reg.type == "reg32" ? 5 : 2;
            }
        }
        else 
        {
            long int val = this->analyse_imm(imm);
            if (reg.type == "reg32" && (val > 4294967295 || val < -21474836481)) 
            {
                lst_line.error = val + " wrong size for DD";
            }
            else if (reg.type == "reg8" && (val > 255 or val < -128)) 
            {
                lst_line.error = val + " wrong size for DB";
            }
            else 
            {
                this->offset += reg.type == "reg32" ? 5 : 2;
            }
        }

    }

    this->listing.push_back(lst_line);
}

void Compiler::imul(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 2) 
    {
        lst_line.error = "wrong operands";
    }
    else if (!this->check_reg(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong first operand";
    }
    else if (!this->check_mem(sentence->opFields->at(1))) 
    {
        lst_line.error = "wrong second operand";
    }
    else 
    {
        Memory memory = this->analyse_mem(sentence->opFields->at(1));
        lexical_container reg = sentence->opFields->at(0)->at(0);

        if (memory.size.empty()) 
        {
            lst_line.error = "Unknown variable " + memory.identifier;
        }
        else if (memory.segment.empty()) 
        {
            lst_line.error = "Variable located in unmapped segment";
        }
        else if ((memory.size == "DWORD" && reg.type != "reg32") || (memory.size == "BYTE" && reg.type != "reg8")) 
        {
            lst_line.error = "Operands sizes do not match";
        }
        else if (memory.size == "BYTE")
        {
            lst_line.error = "BYTE not supported for IMUL";
        }
        else 
        {
            string base_segment = memory.base == "EBP" || memory.base == "ESP" ? "SS" : "DS";
            if (memory.segment != base_segment) 
            {
                this->offset++;
                lst_line.opcode_string = get_segment_prefix(memory.segment) + ": " + lst_line.opcode_string;
            }
            this->offset += 7;
            if (!memory.base.empty())
                this->offset++;

            lst_line.opcode_string += "0F AF "; 
            lst_line.opcode_string += get_modrm(memory, regs(reg.lexeme));
            lst_line.opcode_string += " " + int_to_hex(var_list[memory.identifier].offset, 8) + "r";
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::jmp_1(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 1) 
    {
        lst_line.error = "wrong operands";
    }
    else if (!this->check_farptr(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong first operand";
    }
    else 
    {
        this->offset += 7;
    }
    this->listing.push_back(lst_line);
}

void Compiler::jmp_2(analysed_code* sentence)
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 1) 
    {
        lst_line.error = "wrong operands";
    }
    else if (!this->check_mem(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong memory syntax";
    }
    else 
    {
        Memory memory = this->analyse_mem(sentence->opFields->at(0));
        if (memory.size.empty()) 
        {
            lst_line.error = "Unknown variable " + memory.identifier;
        }
        else if (memory.size != "DWORD") 
        {
            lst_line.error = "Wrong OP size for jmp";
        }
        else if (memory.segment.empty()) 
        {
            lst_line.error = "Variable located in unmapped segment";
        }
        else 
        {
            string base_segment = memory.base == "EBP" || memory.base == "ESP" ? "SS" : "DS";
            if (memory.segment != base_segment) 
            {
                this->offset++;
                lst_line.opcode_string = get_segment_prefix(memory.segment) + ": " + lst_line.opcode_string;
            }
            this->offset += 6;
            if (!memory.base.empty())
                this->offset++;
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::cmp(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 2) 
    {
        lst_line.error = "wrong operands";
    }
    else if (!this->check_reg(sentence->opFields->at(1))) 
    {
        lst_line.error = "wrong second operand";
    }
    else if (!this->check_mem(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong first operand";
    }
    else 
    {
        Memory memory = this->analyse_mem(sentence->opFields->at(0));
        lexical_container reg = sentence->opFields->at(1)->at(0);

        if (memory.size.empty()) 
        {
            lst_line.error = "Unknown variable " + memory.identifier;
        }
        else if (memory.segment.empty()) 
        {
            lst_line.error = "Variable located in unmapped segment";
        }
        else if ((memory.size == "DWORD" && reg.type != "reg32") || (memory.size == "BYTE" && reg.type != "reg8")) 
        {
            lst_line.error = "Operands sizes do not match";
        }
        else 
        {
            string base_segment = memory.base == "EBP" || memory.base == "ESP" ? "SS" : "DS";
            if (memory.segment != base_segment) 
            {
                this->offset++;
                lst_line.opcode_string = get_segment_prefix(memory.segment) + ": " + lst_line.opcode_string;
            }
            this->offset += 6;
            if (!memory.base.empty())
                this->offset++;
            lst_line.opcode_string += memory.size == "BYTE" ? "38 " : "39 "; 
            lst_line.opcode_string += get_modrm(memory, regs(reg.lexeme)); 
            lst_line.opcode_string += " " + int_to_hex(var_list[memory.identifier].offset, 8) + "r";
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::adc(analysed_code* sentence) 
{
    ListingLine lst_line(sentence, this->offset);

    if (sentence->opFields->size() != 2) 
    {
        lst_line.error = "wrong operands";
    }
    else if (!this->check_mem(sentence->opFields->at(0))) 
    {
        lst_line.error = "wrong memory syntax";
    }
    else if (!this->check_imm(sentence->opFields->at(1))) 
    {
        lst_line.error = "wrong imm operand";
    }
    else 
    {
        vector<lexical_container>* imm = sentence->opFields->at(1);
        Memory memory = this->analyse_mem(sentence->opFields->at(0));

        if (memory.size.empty()) 
        {
            lst_line.error = "Size for mem not specified";
        }
        else if (memory.segment.empty()) 
        {
            lst_line.error = "Segmentation error";
        }
        else 
        {
            int imm_val = this->analyse_imm(imm);
            if (!(imm_val < 256 && imm_val > -128 && memory.size == "BYTE") && !(imm_val < 4294967295 && imm_val > -21474836480 && memory.size == "DWORD")) 
            {
                lst_line.error = "imm too big for " + memory.size;
            }
            else 
            {
                string base_segment = memory.base == "EBP" || memory.base == "ESP" ? "SS" : "DS";
                if (memory.segment != base_segment) 
                {
                    this->offset++;
                    lst_line.opcode_string = get_segment_prefix(memory.segment) + ": " + lst_line.opcode_string;
                }
                this->offset += 6;
                if (!memory.base.empty())
                    this->offset++;

                lst_line.opcode_string += memory.size == "BYTE" ? "80 " : (imm_val < 256 && imm_val > -128) ? "83 " : "81 ";
                lst_line.opcode_string += get_modrm(memory, 0b010);
                lst_line.opcode_string += " " + int_to_hex(var_list[memory.identifier].offset, 8) + "r";

                if (imm_val < 256 && imm_val > -128) 
                {
                    this->offset++;
                    lst_line.opcode_string += " " + int_to_hex(imm_val, 2);
                }
                else 
                {
                    this->offset += 4;
                    lst_line.opcode_string += " " + int_to_hex(imm_val, 8);
                }
            }
        }
    }

    this->listing.push_back(lst_line);
}

void Compiler::second_view() 
{
    vector<ListingLine> new_listing;

    for (auto line : this->listing) 
    {
        analysed_code* parsed_line = line.origin;
        string mnemonics = parsed_line->mnemField.lexeme;

        if (mnemonics == "JNA" && line.error.empty()) 
        {
            string ident = parsed_line->opFields->at(0)->at(0).lexeme;

            if (this->label_table.count(ident)) 
            {
                Symbol symb = label_table[ident];
                if (symb.offset > line.offset)
                {
                    int length = symb.offset - line.offset;
                    line.opcode_string = "76 ";
                    if (length < 128) 
                    {
                        line.opcode_string += int_to_hex(length - 2, 2) + " 90 90 90 90";
                    }
                    else 
                    {
                        line.opcode_string += int_to_hex(length - 6, 6);
                    }
                }
                else 
                {
                    int length = line.offset - symb.offset;
                    if (length < 128) 
                    {
                        line.opcode_string = "76 ";
                        line.opcode_string += int_to_hex(256 - length - 2, 2);
                    }
                    else 
                    {
                        line.opcode_string = "0F 83 ";
                        line.opcode_string += int_to_hex(-(length + 4), 6);
                    }
                }
            }
            else 
            {
                line.error = "Undefined label " + ident;
            }
        }
        else if (mnemonics == "JMP" && line.error.empty()) 
        {
            if (parsed_line->opFields->size() == 1 && parsed_line->opFields->at(0)->size() == 1) 
            {
                string ident = parsed_line->opFields->at(0)->at(0).lexeme;

                if (this->label_table.count(ident)) 
                {
                    Symbol symb = label_table[ident];
                    if (symb.offset > line.offset) 
                    {
                        int length = symb.offset - line.offset;
                        line.opcode_string = "EB ";
                        if (length < 128) 
                        {
                            line.opcode_string += int_to_hex(length - 2, 2) + " 90 90 90";
                        }
                        else 
                        {
                            line.opcode_string += int_to_hex(length - 3, 4);
                        }
                    }
                    else 
                    {
                        int length = line.offset - symb.offset;
                        if (length < 128) 
                        {
                            line.opcode_string = "EB ";
                            line.opcode_string += int_to_hex(256 - length - 2, 2);
                        }
                        else
                        {
                            line.opcode_string = "E9 ";
                            line.opcode_string += int_to_hex(-(length + 4), 4);
                        }
                    }
                }
                else
                {
                    line.error = "Undefined label " + ident;
                }
            }
            else 
            {
                string ident = parsed_line->opFields->at(0)->at(2).lexeme;

                if (this->label_table.count(ident)) 
                {
                    Symbol symb = label_table[ident];
                    line.opcode_string = "EA " + int_to_hex(symb.offset, 8) + "sr";
                }
                else 
                {
                    line.error = "Undefined label " + ident;
                }
            }
        }
        new_listing.push_back(line);
    }
    listing = new_listing;
}
