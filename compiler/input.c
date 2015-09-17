void add(int a, int b)
{
	asm{
		"mov eax,[ebp + 12]"
		"add eax,[ebp + 8]"
		"add eax, 0x30"
		"mov[msg], eax"
		"mov eax, 4"
		"mov ebx, 1"
		"mov ecx, msg"
		"mov edx, 5"
		"int 80h"
	}
}

int main() 
{
	int a = 1 + 2 + 3 + 4 + 5 + 6;
	add(a, 1);
}

