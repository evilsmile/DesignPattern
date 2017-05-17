#include <string>
#include <iostream>

class Scanner {
    public:
        void scan() { std::cout << "Lex analysis" << std::endl; }
};

class Parser {
    public:
        void parse() { std::cout << "Syntax parse" << std::endl; }
};

class MidCodeGenerator {
    public:
        void genMidCode() { std::cout << "Gen middle code" << std::endl; }
};

class MachineCodeGenerator {
    public:
        void genMachCode() { std::cout << "Gen machine code" << std::endl; }
};

class Compiler {
    public:
        void run() {
            Scanner scanner;
            Parser parser;
            MidCodeGenerator midCodeGenerator;
            MachineCodeGenerator machCodeGenerator;

            scanner.scan();
            parser.parse();
            midCodeGenerator.genMidCode();
            machCodeGenerator.genMachCode();
        }
};

int main()
{
    Compiler compiler;
    compiler.run();

    return 0;
}
