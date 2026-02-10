char* loadEnvironment ();

char** parseInput(char buffer[]);

void execute (char* args[]);

void executeBuiltIn (char* args[]);

void getPath (char* args[]);

void setPath (char* args[]);

void cd (char* args[]);

char* history (char* arg, char* hist[]);

void listHistory (char* args[]);

void exitShell (char* path);
