//note that this SHOULD be run in user space and is NOT part of the kernel
void logo(void){
changeColor((char*)0x80);
clear();
const char *wolf = "                      .\n                     / V\\ \n                   / `  /\n                  <<   |\n                  /    |\n                /      |\n              /        |\n            /    \\  \\ /\n           (      ) | |\n   ________|   _/_  | |\n <__________\\______)\\__)\n\nWelcome to Wolf OS\nPress any key to continue...\n";
print(wolf);
return;
}
