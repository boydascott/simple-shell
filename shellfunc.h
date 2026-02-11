char* loadEnvironment ();

char** parseInput(char buffer[]);

void execute (char* args[]);

void executeBuiltIn (char* args[], char* history[]);

void getPath (char* args[]);

void setPath (char* args[]);

void cd (char* args[]);

char* invokeHistory (char* arg, char* hist[]);

void listHistory (char* args[], char* hist[]);

void exitShell (char* path);
