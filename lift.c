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
    int                 dat[6];
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
    char *pop;
    int person;

    pop = malloc(7);
    pop[6] = '\0';

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
        while (lift.floor != floor)
        {
            printf("датчики \n");
            while(read(0,pop,6) >0)
            {
                lift.dat[0] = pop[0] - 48;
                lift.dat[1] = pop[1] - 48;
                lift.dat[2] = pop[2] - 48;
                lift.dat[3] = pop[3] - 48;
                lift.dat[4] = pop[4] - 48;
                lift.dat[5] = pop[5] - 48;
            }
            if (lift.floor < floor)
            {
                if (lift.dat[lift.floor] == 1 && lift.dat[lift.floor + 1] == 1)
                {
                    printf("лифт едет с %d на %d\n", lift.floor, lift.floor + 1);
                    lift.floor = lift.floor + 1;
                }
                else
                {
                    printf("авария\n");
                    return(lift);
                }
            }
            else
            {
                if (lift.dat[lift.floor] == 1 && lift.dat[lift.floor - 1] == 1)
                {
                    printf("лифт едет с %d на %d\n", lift.floor, lift.floor - 1);
                    lift.floor = lift.floor - 1;
                }
                else
                {
                    printf("авария\n");
                    return(lift);
                }
            }
            
        }
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
    lift.dat[0] = 1;
    lift.dat[1] = 1;
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
            else
            {
                printf("произошла авария, вызываем диспетчера\n");
            }
            sleep(1);     
        }
        printf("Нажмите на кнопку\n");
    }
    return(0);
}