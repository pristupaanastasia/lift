#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_PER 8
#define NUM_FLOOR 5

typedef struct			s_lift
{
	int					opened;
    int                 floor;
    int                 person;
}						t_lift;

void openorclose(t_lift lift)
{
    if (lift.opened == 0)
    {
        printf("Дверь закрыта\n");
    }
    else
    {
        printf("Дверь открыта\n");
    } 
}

t_lift head(t_lift lift, int floor)
{
    int person;
    printf("Введите количество пассажиров\n");
    scanf("%d",&person);
    if (person > MAX_PER)
    {
        printf("Превышена максимальная весовая нагрузка на лифт\n");
    }
    else
    {
        lift.opened = 0;
        openorclose(lift);
        printf("с %d этажа лифт едет на %d\n",lift.floor,floor);
        sleep(1);
        lift.floor = floor;
    }
    return(lift);
}

t_lift konez(t_lift lift)
{
    lift.opened = 1;
    openorclose(lift);
    sleep(1);
    printf("Вы приехали на нужный этаж\n");
    sleep(1);
    lift.opened = 0;
    openorclose(lift);
    sleep(1);
    return(lift);
}


int main(int argc, char **argv)
{
    int floor;
    char *pop;
    t_lift lift;
    lift.opened = 0;
    lift.floor = 1;
    pop = (char*)malloc(2);
    pop[1] = '\0';
    printf("Нажмите на кнопку\n");
    while(read(0,pop,1) >0)
    {
        printf("Вы вызвали лифт\n");
        sleep(1);
        printf("Введите номер этажа\n");
        scanf("%d",&floor);
        if (floor > NUM_FLOOR || floor == lift.floor || floor < 1)
        {
            if (floor == lift.floor)
                printf("Вы приехали\n");
            else
                printf("Этаж не верный, введите этаж от 1 до %d\n", NUM_FLOOR);
        }
        else
        {
            lift.opened = 1;
            openorclose(lift);
            lift = head(lift,floor);
            if (lift.opened == 1)
                lift.opened = 0;
            if (lift.floor == floor)
            {
                lift = konez(lift);
            }
            sleep(1);     
        }
        printf("Нажмите на кнопку\n");
    }
    return(0);
}
