#include<stdio.h>
#include<string.h>
#include"staff.h"

void main(void)
{
	int choice,no_of_staff,staff_counter;

	menu();

	printf("Enter your choice  :  ");
	scanf("%d",&choice);
	printf("\n\n");

	while(choice!=4)
	{
		switch(choice)
		{
		
			case 1 : 

				scanf("%c",&space);

				staff_counter=0;

				fdata=fopen("staff.txt","a+");

				printf("Please state the number of staff to enter the data : ");
				scanf("%d",&no_of_staff);
				printf("\n");

				counter_staff(no_of_staff);  /*call recursion function*/

				fclose(fdata);

			break;

			case 2 : 

				answer='Y';

				while(answer=='Y'||answer=='y')
				{
				enter_overtime();
					
				printf("\n");
				scanf("%c",&space);
				printf("Do you want to continue enter staff's overtime data? (Y/N)  :  ");
				scanf("%c",&answer);
				printf("\n\n");
				}

			break;

			case 3 : 

				report();

			default : 

				printf("\nThank you.\n\n");

		}/*End Switch*/
		
	menu();

	printf("Enter your choice  :  ");
	scanf("%d",&choice);
	printf("\n\n");


	}/*End while*/
	
} /* End main */

void menu(void)
{
	printf("\n-----------------ITMS Staff System---------------------\n\n\n");
	printf("   1.	Enter Staff Data\n");
	printf("   2.	Enter Overtime Data\n");
	printf("   3.	View Report\n");
	printf("   4.	End\n\n");
}

int counter_staff(int no_staff)    /*Recursion function*/
{
	while(no_staff>0)
	{
		staff=enter_staff_data(staff);
		update_file(staff);
		return counter_staff(no_staff-1);
	}
	return 0;
}

staff_data enter_staff_data(staff_data staff)
{
	scanf("%c",&space);
	printf("Enter Staff No \t         : \t ");
    gets(staff.staff_id);

	printf("Enter Name \t         : \t ");
	gets(staff.name);

	printf("Enter Job Grade \t : \t ");
	gets(staff.job_grade);

	printf("Immediate Supervisor \t : \t ");
	gets(staff.supervisor_id);

	printf("Enter Wages per hour \t : \t ");
	scanf("%d",&staff.wages_per_hour);
	
	printf("\n\n");
	 
    return staff;   
}

void update_file(staff_data staff)
{
	fprintf(fdata,"%s\t\t\t",staff.name);
	fprintf(fdata,"%s\t\t\t",staff.job_grade);
	fprintf(fdata,"%s\t\t\t",staff.staff_id);
	fprintf(fdata,"%s\t\t\t",staff.supervisor_id);
	fprintf(fdata,"%d\t\t\n\n",staff.wages_per_hour);
}	

void enter_overtime(void)
{	
	scanf("%c",&space);
	printf("Enter Staff No \t         : \t ");
    gets(capture_data[0].staff_id);

	printf("Enter Month \t         : \t ");
	gets(capture_data[0].overtime.month);

	printf("Enter OT (hours) \t : \t ");
	scanf("%d",&capture_data[0].overtime.ot_hours);

	fovertime = fopen ("overtime.txt", "a+");

	fdata = fopen ("staff.txt", "r");

	while (!feof(fdata))
	{
		fscanf (fdata, "%s %s %s %s %d", &capture_data[1].name, &capture_data[1].job_grade, &capture_data[1].staff_id, &capture_data[1].supervisor_id, &capture_data[1].wages_per_hour);

		if (strcmp (capture_data[0].staff_id, capture_data[1].staff_id) == 0)

		break;
			
	}
	fclose(fdata);

	capture_data[0].overtime.ot_income = capture_data[1].wages_per_hour*capture_data[0].overtime.ot_hours;

	fprintf(fovertime, "%s\t%s\t%d\t%d\n", capture_data[0].staff_id, capture_data[0].overtime.month, capture_data[0].overtime.ot_hours, capture_data[0].overtime.ot_income);

	fclose(fovertime);

	printf("\nData successfully added. \n\n");

	printf("Total OT (RM) for this month's is    : RM %d\n\n",capture_data[0].overtime.ot_income);
	printf("Total OT (hours) for %s to date is   : %d hours\n",capture_data[0].staff_id,total_overtime_hours(capture_data[0].staff_id));
	printf("Total OT (RM) for %s to date is      : RM %d\n\n",capture_data[0].staff_id,total_overtime_income(capture_data[0].staff_id));
	printf("Average OT for %s to date is         : RM %d\n\n",capture_data[0].staff_id,total_overtime_income(capture_data[0].staff_id)/month_counter(capture_data[0].staff_id));
	
	printf("\n");
}

int total_overtime_hours(char overtime_capture[])
{
	int total=0;

	fovertime = fopen ("overtime.txt", "r");

	fscanf(fovertime, "%s %s %d %d", &capture_data[1].staff_id, &capture_data[1].overtime.month, &capture_data[1].overtime.ot_hours, &capture_data[1].overtime.ot_income);

	while (!feof (fovertime)) 
	{
		if (strcmp (overtime_capture, capture_data[1].staff_id)==0)
			total = total+capture_data[1].overtime.ot_hours;
		
		fscanf(fovertime, "%s %s %d %d", &capture_data[1].staff_id, &capture_data[1].overtime.month, &capture_data[1].overtime.ot_hours, &capture_data[1].overtime.ot_income);	
	}
	fclose(fovertime);

	return total;
}

int total_overtime_income(char overtime_capture[])
{
	int total=0;

	fovertime = fopen ("overtime.txt", "r");

	fscanf(fovertime, "%s %s %d %d", &capture_data[1].staff_id, &capture_data[1].overtime.month, &capture_data[1].overtime.ot_hours, &capture_data[1].overtime.ot_income);

	while (!feof (fovertime)) 
	{
		if (strcmp (overtime_capture, capture_data[1].staff_id)==0)
			total = total+capture_data[1].overtime.ot_income;
		
		fscanf(fovertime, "%s %s %d %d", &capture_data[1].staff_id, &capture_data[1].overtime.month, &capture_data[1].overtime.ot_hours, &capture_data[1].overtime.ot_income);	
	}
	fclose(fovertime);

	return total;
}

int month_counter(char overtime_capture[])
{
	int counter=0;

	fovertime = fopen ("overtime.txt", "r");

	fscanf(fovertime, "%s %s %d %d", &capture_data[1].staff_id, &capture_data[1].overtime.month, &capture_data[1].overtime.ot_hours, &capture_data[1].overtime.ot_income);

	while (!feof (fovertime)) 
	{
		if (strcmp (capture_data[0].staff_id, capture_data[1].staff_id) ==0)
		counter++;

		fscanf(fovertime, "%s %s %d %d", &capture_data[1].staff_id, &capture_data[1].overtime.month, &capture_data[1].overtime.ot_hours, &capture_data[1].overtime.ot_income);
	}
	fclose(fovertime);

	return counter;
}

void subordinate (void)
{
	fdata=fopen ("staff.txt", "r");

	fscanf (fdata, "%s %s %s %d %s", &capture_data[0].staff_id, &capture_data[0].name, &capture_data[0].job_grade, &capture_data[0].wages_per_hour, &capture_data[0].supervisor_id);

	while (!feof(fdata))
	{
		count_subordinate=0;

		freport=fopen ("staff.txt", "r");

		fscanf (freport, "%s %s %s %d %s", &capture_data[1].staff_id, &capture_data[1].name, &capture_data[1].job_grade, &capture_data[1].wages_per_hour, &capture_data[1].supervisor_id);

		while (!feof(freport))
		{
			if (strcmp(capture_data[0].staff_id,capture_data[1].supervisor_id)==0)
				count_subordinate++;

			fscanf (freport, "%s %s %s %d %s", &capture_data[1].staff_id, &capture_data[1].name, &capture_data[1].job_grade, &capture_data[1].wages_per_hour, &capture_data[1].supervisor_id);
		}

		fclose(freport);
		
		freport=fopen ("report.txt", "a+");

		fprintf(freport, "%s %s %s %d\n", capture_data[0].staff_id, capture_data[0].name, capture_data[0].job_grade, count_subordinate);

		fclose(freport);

		fscanf (fdata, "%s %s %s %d %s", &capture_data[0].staff_id, &capture_data[0].name, &capture_data[0].job_grade, &capture_data[0].wages_per_hour, &capture_data[0].supervisor_id);
	}

	fclose(fdata);

}

void report(void)
{
	freport = fopen ("staff.txt", "r");

	printf("\n\nStaff ID\tName\t\tJob Grade\tNo Of Subordinate\n");
	
	fscanf (freport, "%s %s %s %d %s", &capture_data[0].staff_id, &capture_data[0].name, &capture_data[0].job_grade, &count_subordinate);

	while (!feof(freport))
	{
		printf("%s\t\t%s\t\t%s\t\t\t%d\t\t%s\n", capture_data[0].staff_id, capture_data[0].name, capture_data[0].job_grade, capture_data[0].wages_per_hour, capture_data[0].supervisor_id);
		
		fscanf (freport, "%s %s %s %d %s", &capture_data[0].staff_id, &capture_data[0].name, &capture_data[0].job_grade, &count_subordinate);
	}

	fclose(freport);
}












