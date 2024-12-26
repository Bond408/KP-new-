#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#define MAX_RECORDS 100                            // ������������ ���������� ���������� ������� � ���� ������
#define FILE_NAME "PCcase.txt"                     // �������� �����

// ��������� ��� �������� ���������� � ������� ��
typedef struct {
    char developer[50];                            // ������������� ������� ��
    char form_factor[30];                          // ����-������ ����������� ����� � �������
    char size[30];                                 // ������ ������� �� (Full-Tower, Mid-Tower, Mini-Tower, Super-Tower)
    int height;                                    // ������ ������� ��
    char color[20];                                // ���� ������� ��
} pc_case_t;

// ����� ���������� �������
int add_records(pc_case_t records[], int* record_count);
int delete_record(pc_case_t records[], int* record_count);
int save_to_file(pc_case_t records[], int* record_count);
int load_from_file(pc_case_t records[], int* record_count);
int search_record(pc_case_t records[], int record_count);
int compare_by_color(const void* a, const void* b);
int sort_records(pc_case_t records[], int* record_count);
int print_all_records(pc_case_t records[], int record_count);
int menu(pc_case_t records[], int* record_count);

// �������� ���������
int main() {
    system("chcp 1251");
    pc_case_t records[MAX_RECORDS];                // ������� ������ �������, ������� ����� ������� ��� ������� � �� ����������������
    int record_count = 0;                          // ���������� ��� �������� ���������� ������� � ������� records
    menu(records, &record_count);                  // ����� ���� ���������
    return 0;
}

// ������� ���������� ����� ������
int add_records(pc_case_t records[], int* record_count) {
    int choice;
    printf("�������� ��������:\n");
    printf("1 - �������� ���� ������\n");
    printf("2 - �������� ��������� �������\n");
    printf("��� �����: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // ���������� ����� ������
        if (*record_count >= MAX_RECORDS) {                  // �������� �� �������� �� ����� ������� MAX_RECORDS         
            printf("���� ������ �����������!\n");            // ���� ����� ��������, �� ��������� �����������
            return 1;
        }

        printf("������� ������������: ");
        scanf("%s", records[*record_count].developer);
        printf("������� ����-������: ");
        scanf("%s", records[*record_count].form_factor);
        printf("������� ������: ");
        scanf("%s", records[*record_count].size);
        int valid = 0;
        while (!valid) {
            printf("������� ������ �������: ");
            if (scanf("%d", &records[*record_count].height) == 1) {
                valid = 1;                             // ���� ������������ ���� ���������� ����� �� ������������ 1
            }
            else {
                // ���� ������������ ���� ����� ��� ������ ������� �� ������������ 0 � ��������� ��������� �� ������
                printf("������: ������ ������ ���� ������!\n");
                // ������� �����, ����� �� ���� ������������ � ��������� ���������� ����������� ����, ���� ������������ �� ������ ���������� �����
                while (getchar() != '\n');
            }
        }
        printf("������� ����: ");
        scanf("%s", records[*record_count].color);

        (*record_count)++;                                  // ����� ����� ����������� ������
        printf("������ ������� ���������.\n");

        // �������������� � ����
        FILE* file = fopen("pc_cases.txt", "a");  // �������� ����� ��� ���������� ������
        if (file == NULL) {
            printf("������ ��� �������� ����� ��� ����������.\n");
            return -1;
        }

    }
    else if (choice == 2) {
        // ���������� ���������� �������
        int num_records;
        printf("������� ������� �� ������ ��������? ");
        scanf("%d", &num_records);

        if (*record_count + num_records > MAX_RECORDS) {    // �������� �� ����� �� �������� ����� ������� MAX_RECORDS ������ � ������ ��������
            printf("������������ ����� ��� ���������� �������.\n");
            return 1;
        }

        for (int i = 0; i < num_records; i++) {
            printf("\n���������� ������ %d:\n", i + 1);
            printf("������� ������������: ");
            scanf("%s", records[*record_count].developer);
            printf("������� ����-������: ");
            scanf("%s", records[*record_count].form_factor);
            printf("������� ������: ");
            scanf("%s", records[*record_count].size);
            int valid = 0;
            while (!valid) {
                printf("������� ������ �������: ");
                if (scanf("%d", &records[*record_count].height) == 1) {
                    valid = 1;
                }
                else {

                    printf("������: ������ ������ ���� ������!\n");

                    while (getchar() != '\n');
                }
            }
            printf("������� ����: ");
            scanf("%s", records[*record_count].color);

            (*record_count)++;                                   // ����� ����� ����������� ������
            printf("������ ������� ���������.\n");

            // �������������� � ����
            FILE* file = fopen("pc_cases.txt", "a");  // �������� ����� ��� ���������� ������
            if (file == NULL) {
                printf("������ ��� �������� ����� ��� ����������.\n");
                return -1;
            }
        }
        printf("��� ������ ������� ���������.\n");

    }
    else {
        printf("������������ �����. ������� � ����.\n");        // ������ � ������ ������ ����� ��� ���������
    }
}

// ������� �������� ������
int delete_record(pc_case_t records[], int* record_count) {
    if (*record_count == 0) {
        printf("��� �������.\n");
        return -1;                                            // ��� �������
    }

    int index;
    printf("������� ����� ������ ��� ��������: ");
    scanf("%d", &index);

    if (index < 1 || index > *record_count) {                         // �������� �� ������������ ������ ������
        printf("������������ ����� ������. ���������� �����.\n");
        return -1;               // ������������ ����� ������
    }

    for (int i = index - 1; i < *record_count - 1; i++) {            // �������� ������ ����� ������ ���������� �������
        records[i] = records[i + 1];
    }
    (*record_count)--;

    // �������������� � ����
    FILE* file = fopen("pc_cases.txt", "a");  // �������� ����� ��� ���������� ������
    if (file == NULL) {
        printf("������ ��� �������� ����� ��� ����������.\n");
        return -1;
    }

    printf("������ ��� ������� %d ������� �������.\n", index);
    return 0;                                                        // ������ ������� �������
}

// ������� ���������� ������� � ����
int save_to_file(pc_case_t records[], int* record_count) {
    FILE* file = fopen(FILE_NAME, "w");          // ��������� ���� � ������ ������
    if (!file) {                                 // ���� ���� �� ������� �������, �� ��������� ��������� �� ������
        printf("������ ��� �������� �����!\n");
        return 1;
    }

    for (int i = 0; i < record_count; i++) {     // ������ ������������ � ����
        fprintf(file, "%s %s %s %d %s\n",
            records[i].developer,
            records[i].form_factor,
            records[i].size,
            records[i].height,
            records[i].color);
    }
    fclose(file);                               // ���� �����������
    printf("������ ��������� � ����.\n");
    return 0;
}

// ������� �������� ������� �� �����
int load_from_file(pc_case_t records[], int* record_count) {
    FILE* file = fopen(FILE_NAME, "r");         // ��������� ���� � ������ ������
    if (!file) {                                // ���� ���� �� ������� �������, �� ��������� ��������� �� ������
        printf("���� �� ������.\n");
        return 1;
    }

    *record_count = 0;
    while (fscanf(file, "%s %s %s %d %s",
        records[*record_count].developer,
        records[*record_count].form_factor,
        records[*record_count].size,
        &records[*record_count].height,
        records[*record_count].color) == 5) {   // ������� fscanf() ������ ������� ������� ����� 5 �������� �� ����� ��� 1 ������
        (*record_count)++;
    }
    fclose(file);                              // ���� �����������
    printf("������ ��������� �� �����.\n");
    return 0;
}

// ������� ������ ������
int search_record(pc_case_t records[], int record_count) {
    int choice;                                // ����� ����������
    char developer_key[50];                    // ������ ��� ���������� �� �������������
    char size_key[30];                         // ������ ��� ���������� �� ������� �������
    int found = 0;

    printf("�������� �������� ������:\n");
    printf("1 - �� �������������\n");
    printf("2 - �� �������\n");
    printf("3 - �� ������������� � �������\n");
    printf("��� �����: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:                                   // ����� �� �������������
        printf("������� ������������� ��� ������: ");
        scanf("%s", developer_key);
        for (int i = 0; i < record_count; i++) {
            if (strcmp(records[i].developer, developer_key) == 0) {      // ������������ ������ ������������� � ������ � ������������� ������������
                printf("�������: %s %s %s %d %s\n",
                    records[i].developer,
                    records[i].form_factor,
                    records[i].size,
                    records[i].height,
                    records[i].color);
                found = 1;
            }
        }
        break;

    case 2:                                  // ����� �� �������
        printf("������� ���������� ��� ������: ");
        scanf("%s", size_key);
        for (int i = 0; i < record_count; i++) {
            if (strcmp(records[i].size, size_key) == 0) {             // ������������ ������� ������� � ������ � ������ ������� ������������
                printf("�������: %s %s %s %d %s\n",
                    records[i].developer,
                    records[i].form_factor,
                    records[i].size,
                    records[i].height,
                    records[i].color);
                found = 1;
            }
        }
        break;

    case 3:  // ����� �� ������������� � �������
        printf("������� ������������� ��� ������: ");
        scanf("%s", developer_key);
        printf("������� ���������� ��� ������: ");
        scanf("%s", size_key);
        for (int i = 0; i < record_count; i++) {
            if (strcmp(records[i].developer, developer_key) == 0 &&  /* ������������ ������� ������� c �������������� � ������ � ������ ������� � ������������� ������������
                                                                                                   */
                strcmp(records[i].size, size_key) == 0) {
                printf("�������: %s %s %s %d %s\n",
                    records[i].developer,
                    records[i].form_factor,
                    records[i].size,
                    records[i].height,
                    records[i].color);
                found = 1;
            }
        }
        break;

    default:
        printf("������������ �����. ���������� �����.\n");
        return 1;                                // ������ �����
    }

    if (!found) {
        printf("������ �� �������.\n");
        return 1;                               // ������ �� �������
    }
    return 0;                                   // �����
}


int sort_records(pc_case_t records[], int* record_count) {
    if (record_count == 0) {
        printf("��� ������� ��� ����������.\n");
        return 1;
    }
    qsort(records, record_count, sizeof(pc_case_t), compare_by_color);
    printf("������ ������������� �� �����.\n");
    return 0;
}

// ������� ������ ���� �������
int print_all_records(pc_case_t records[], int record_count) {
    if (record_count == 0) {
        printf("���� ������ �����.\n");
        return 1;
    }

    for (int i = 0; i < record_count; i++) {
        printf("%d. %s %s %s %d %s\n",
            i + 1,
            records[i].developer,
            records[i].form_factor,
            records[i].size,
            records[i].height,
            records[i].color);
    }
    return 0;
}

// ������� ���������� �� �����
int compare_by_color(const void* a, const void* b) {
    return strcmp(((pc_case_t*)a)->color, ((pc_case_t*)b)->color);
}

// ���� ���������
int menu(pc_case_t records[], int* record_count) {
    int choice;
    while (1) {
        printf("\n����:\n");
        printf("1 - �������� ������\n");
        printf("2 - �������� ������\n");
        printf("3 - ����� ������\n");
        printf("4 - ��������� � ����\n");
        printf("5 - ��������� �� �����\n");
        printf("6 - �������� ��� ������\n");
        printf("7 - ����������� �� �����\n");
        printf("8 - �����\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);

        // ���������� �������� ��������� �������������
        switch (choice) {
        case 1:
            add_records(records, record_count);                              // ���������� ������
            break;
        case 2:
            delete_record(records, record_count);                            // �������� ������
            break;
        case 3:
            search_record(records, *record_count);                           // ����� ������
            break;
        case 4:
            save_to_file(records, *record_count);                            // ���������� � ����
            break;
        case 5:
            load_from_file(records, record_count);                           // �������� �� �����
            break;
        case 6:
            print_all_records(records, *record_count);                       // ������ ���� �������
            break;
        case 7:
            sort_records(records, *record_count);                            // ���������� ������� �� ����� �������
            break;
        case 8:
            printf("�����...\n");                                            // ����� �� ���������
            return 0;
        default:
            printf("������������ ����. ������� ��� ���.\n");                 // ������ � ������ ������ ����� ��� ��������� �� 1 �� 8
        }
    }
    return 0;
}