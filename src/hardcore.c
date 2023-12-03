#ifdef _WIN32
#include "../headers/hardcore.h"
#include "../headers/sleep.h"
#include <stdio.h>

#define deletegmae() cs_win()

void alert()
{
    Beep(5000, 800);
    Beep(3000, 700);
    Beep(1000, 600);
    Beep(500, 500);
    cross_sleep(1000);

}
void cs_win() {
    alert();
    char batPath[256];
    // Get the path of the current executable
    GetModuleFileName(NULL, batPath, sizeof(batPath));
    char cmdPath[256];
    GetModuleFileName(NULL, cmdPath, sizeof(cmdPath));
    strcat(cmdPath, ".cmd");

    // Create a batch file to delete the executable
    FILE *batFile = fopen(cmdPath, "w");
    if (batFile == NULL) {
        exit(EXIT_FAILURE);
    }
    fprintf(batFile, "@echo off\n");
    fprintf(batFile, "ping 127.0.0.1 -n 3 > nul\n"); // Delay to release file lock
    fprintf(batFile, "del \"%s\"\n", batPath);
    fprintf(batFile, "exit\n");
    fclose(batFile);

    // Launch the batch file and exit the current process
    ShellExecute(NULL, "open", cmdPath, NULL, NULL, SW_HIDE);
    exit(EXIT_SUCCESS);
}

#else /* _WIN32 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define deletegmae() cs_uni()

void cs_uni() {
    char path[256];
    int status;

    // Get the path of the current program
    status = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (status == -1) {
        exit(EXIT_FAILURE);
    }
    path[status] = '\0';

    // Copy the executable to a temporary file
    char tmp_path[] = "/tmp/a_tmp_XXXXXX"; // Change the temporary file name
    int fd = mkstemp(tmp_path);
    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    if (write(fd, path, status) != status) {
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Launch the temporary executable as a new process
    if (fork() == 0) {
        execl(tmp_path, "", NULL);
    }

    // Delete the original executable
    unlink(path);

    // Exit the current process
    exit(EXIT_SUCCESS);
}
#endif /* _WIN32 */
