#include <stdint.h>
#include <stdio.h>
#include <string.h>

int max_record = 10;

typedef struct{
	uint32_t rollNumber;
	uint8_t studentName[50];
	uint8_t branch[50];
	uint8_t dateOf[15];
	uint32_t semester;
}Student_info_t;

Student_info_t studentInfo[10];

void display_all_records(Student_info_t *record, int8_t max_record);
int add_new_record(Student_info_t *record,int8_t max_record);
int delete_record(Student_info_t *record, int8_t max_record);
void display_menu(void);
int read_menu_code(void);
void decode_menu_code(int8_t menu_code);
int check_roll_number(int roll_number, Student_info_t *record, int8_t max_record);

int main()
{

    int8_t menu_code;
    int8_t app_continue = 1;

    printf("Student record management program\n");

     while(app_continue)
     {
		//1. display menu
		display_menu();

		//read the menu code
		menu_code = read_menu_code();

		if(menu_code){
			//Decode the menu code
			decode_menu_code(menu_code);
		}else{
			//end the application if menu_code = 0;
			app_continue = 0;
			printf("Exiting application\n");
		}

     }

    return 0;
}

void display_all_records(Student_info_t *record, int8_t max_record){
    int record_found = 0;
    for(int i = 0 ; i < max_record ; i++)
    {
        if( record[i].rollNumber)
        {
        	record_found = 1;
            //display the record
            printf("***********\n");
            printf("rollNumber        : %u\n",record[i].rollNumber);
            printf("studentSemister   : %u\n",record[i].semester);
            printf("studentDOB        : %s\n",record[i].dateOf);
            printf("studentBranch     : %s\n",record[i].branch);
            printf("studentName       : %s\n",record[i].studentName);
            printf("***********\n");
        }
    }

    if(! record_found)
        printf("No records found\n");

}

int add_new_record(Student_info_t *record,int8_t max_record){
    int add_status=0;
    int is_exist=0;
    int roll_number;
    int i;

    for( i = 0 ; i < max_record ; i++)
    {
        if( ! record[i].rollNumber)
        {

                //add the record
                printf("Enter the rollNumber : ");
                scanf("%d",&roll_number);
                is_exist = check_roll_number(roll_number,studentInfo,max_record);
                if(! is_exist)
                {
                	add_status = 1; //adding new record
                    record[i].rollNumber = roll_number;
                    printf("Enter the studentSemister   : ");
                    scanf("%d",&record[i].semester);
                    printf("Enter the DOB(mm/dd/yyyy)    : ");
                    scanf("%s",record[i].dateOf);
                    getchar();
                    printf("Enter the studentBranch     : ");
                    scanf("%50[^\n]s",record[i].branch);
                    getchar();
                    printf("Enter the studentName       : ");
                    scanf("%50[^\n]s",record[i].studentName);

                }else
                {
                    printf("roll number already exist\n");
                }

                break;
        }

    }

    if(i == max_record)
        printf("No space available\n");

    return add_status;

}

int delete_record(Student_info_t *record, int8_t max_record)
{
    int8_t delete_flag = 0;
    int roll_number;

    printf("Enter the roll number of the student:");
    scanf("%d",&roll_number);

     for(int i = 0 ; i < max_record ; i++)
    {
         if( roll_number == record[i].rollNumber)
        {
            delete_flag = 1;
            memset(&record[i],0,sizeof(Student_info_t));
            break;
        }
    }

    return delete_flag;

}

void display_menu(void)
{
    printf("Display all records  -->1\n");
    printf("Add new record       -->2\n");
    printf("Delete a record      -->3\n");
    printf("Exit application     -->0\n");
    printf("Enter your option here:");
}

int read_menu_code(void)
{
    int input;
    scanf("%d",&input);
    return input;
}

void decode_menu_code(int8_t menu_code)
{
    int8_t ret;

    switch(menu_code)
    {
        case 1:
        printf("Displaying all students record\n");
        display_all_records(studentInfo,max_record);
        break;
        case 2:
        printf("Add a new record\n");
        ret = add_new_record(studentInfo,max_record);
        !ret ? printf("Record add unsuccessful\n") : printf("Record added successfully\n");
        break;
        case 3:
        printf("Delete a record\n");
        ret = delete_record(studentInfo,max_record);
        ret ? printf("Record deleted successfully\n") : printf("Record not found\n");
        break;
        default:
			printf("Invalid input\n");
    }
}

int check_roll_number(int roll_number, Student_info_t *record, int8_t max_record)
{

    int is_exist = 0;
    for(int i = 0 ; i < max_record ; i++)
    {
        if ( record[i].rollNumber == roll_number)
        {
            is_exist = 1;
            break;
        }
    }

    return is_exist;

}
