int main(){
    // execl("grep",  "f ",  "ar.txt"); 
    //char* args[] = {"f", "ar.txt"};
    //execvp("grep", args);
    execl("/usr/bin/grep",  "grep","f ", "ar.txt", 0);
    return 0;
}