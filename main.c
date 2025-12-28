#include "scanner.h"
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int total_files_scanned = 0;
int total_threats_found = 0;
clock_t scan_start, scan_end;

int main(int argc, char *argv[]) {
    if (argc<2) {
        printf("\033[2J\033[H");
        printf("\033[36m[adrscan v0.1]\033[0m\n");
        printf("Usage: %s <command> [options]\n", argv[0]);
        printf("Commands:\n");
        printf("  rules [file]           Run rule-based scan\n");
        printf("  --scan-dir <dir>       Recursively scan directory\n");
        return 1;
    }

    if (strcmp(argv[1], "rules")==0) {
        create_test_file();

        if (argc==3) {
            run_rules_test(argv[2]);
        } else {
            run_rules_test(NULL);
        }
        return 0;
    }

    if (strcmp(argv[1], "--scan-dir")==0){
        if (argc<3){
            printf("Error: missing directory\n");
            printf("Usage: %s --scan-dir <path>\n", argv[0]);
            return 1;
        }

        if (load_signatures("rules.txt")<0) {
            printf("Nao foi possivel carregar regras\n");
            return 1;
        }

        total_files_scanned = 0;
        total_threats_found = 0;

        printf("Iniciando varredura em %s\n", argv[2]);

        scan_start = clock();
		 scan_directory(argv[2]);
        scan_end = clock();
		
        double scan_time = (double)(scan_end - scan_start) / CLOCKS_PER_SEC;

        printf("Varredura completa: %d arquivos, %d ameaça %s, %.2fs\n",
               total_files_scanned,
               total_threats_found,
               total_threats_found == 1 ? "" : "s",
               scan_time);

        return 0;
    }
	
    printf("Erro: comando desconhecido '%s'\n", argv[1]);
    return 1;
}
