#ifndef __INSTRUCTION_HH__
#define __INSTRUCTION_HH__

class Instruction {
private:
	uint32_t raw_binary;
	Register *operand0;
	Register *returnReg;
public:
	Instruction(uint32_t binary);
	void decode();
	void execute();
};

#endif //__INSTRUCTION_HH__