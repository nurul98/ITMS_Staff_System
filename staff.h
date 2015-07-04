typedef struct
{
	int ot_hours;
	int ot_income;

	char month[10];

}	overtime_data;

typedef struct
{
	int wages_per_hour;

	char supervisor_id[10];
	char staff_id[10];
	char name[30];
	char job_grade[6];

	overtime_data overtime;
	
}	staff_data;

void menu(void);
int counter_staff(int no_staff);

staff_data enter_staff_data(staff_data staff);
void enter_overtime(void);
void update_file(staff_data staff);
void subordinate(void);
void report(void);

int total_overtime_hours(char overtime_capture[]);
int total_overtime_income(char overtime_capture[]);
int month_counter(char overtime_capture[]);

staff_data capture_data[2];   /*Global variable*/

char space,answer;

int count_subordinate;        /*Global variable*/

staff_data staff;

FILE *fdata;
FILE *fovertime;
FILE *freport;