#include <curses.h>
#include <stdlib.h>
#include <pthread.h>

#define UP    1
#define DOWN  -1
#define LEFT  2
#define RIGHT -2
 
struct Snake
{
	int hang;
	int lie;
	struct Snake* next;

};


struct Snake* head=NULL;
struct Snake* tail=NULL;
int key;
int dir;

struct Snake food;


void initNcurse()
{
	initscr();
	keypad(stdscr,1);
	noecho();	
}

void addNode()
{
        struct Snake* new=(struct  Snake*)malloc(sizeof(struct Snake));
        new->next=NULL;
	switch(dir){
		case UP:
	new->hang=tail->hang-1;
        new->lie=tail->lie;
	break;

		case DOWN:
	new->hang=tail->hang+1;
        new->lie=tail->lie;
	break;
		
		case LEFT:
       new->hang=tail->hang;
        new->lie=tail->lie-1;
	break;

		case RIGHT:
	 new->hang=tail->hang;
        new->lie=tail->lie+1;
	break;
}
        tail->next=new;
        tail=new;

}


void initFood()
{
        int i=rand()%20;
        int j=rand()%20;
        food.hang=i;
        food.lie=j;
	

}


void initSnake()
{

        struct Snake* p=NULL;
	dir=RIGHT;
	initFood();
	while(head!=NULL)
	{
	
	p=head;
	head=head->next;

	free(p);
	
	
	}



	head=(struct Snake*)malloc(sizeof(struct Snake));
	head->hang=2;
	head->lie=2;
	head->next=NULL;
	tail=head;	

	addNode();
	addNode();
}



int whetherHaveSnake(int i,int j)
{
	struct Snake* p=head;
	while(p!=NULL){

		if (i==p->hang&&j==p->lie){
			return 1;
	
		}
	p=p->next;
	}
	return 0;
}



int whetherHaveFood(int i,int j)
{
	if(food.hang==i&&food.lie==j){
	return 1;
	
	}
	return 0;

}

void gamePic()
{
	int hang;
	int lie;
	move(0,0);
	for (hang=0;hang<20;hang++){
		if (hang==0 ){
			for (lie=0;lie<20;lie++){
			printw("--");
			}	
			printw("\n");
			}

		 if(hang>=0&&hang<=19){
			for (lie=0;lie<=20;lie++){
				if (lie==0||lie==20){
				printw("|");
				}
				else if (whetherHaveSnake(hang,lie)){
				
				printw("[]");
				}else if(whetherHaveFood(hang,lie)){
				printw("##");
				}

				else{
					printw("  ");
					}
			}
			printw("\n");
		}

		if (hang==19){
		for(lie=0;lie<20;lie++)
		{
			printw("--");
		}
			printw("\n");
			printw("MADE BY ZYX");
		}
	}
}

void deleteNode()
{

	struct Snake* p=head;
	
	head=head->next;
	free(p);


}


int whetherItDie()
{

	struct Snake *p;
	p=head;
	if(tail->hang<0||tail->lie==20||tail->hang==20||tail->lie==0){

        return 1;

        }
	
	while(p->next!=NULL){
		if(p->hang==tail->hang && p->lie==tail->lie){
		
			return 1;
		}
	p=p->next;

	}
	return 0;


}


void moveSnake()
{
	addNode();

	if(whetherHaveFood(tail->hang,tail->lie)){

	initFood();


}else{
	deleteNode();
}
	if(whetherItDie()){

	initSnake();

	}

}


void* refreshUI()
{

	while(1){


          gamePic();
          moveSnake();
          refresh();
          usleep(100000);
}



}

void straightSolution(int direction)
{

	if(abs(direction)!=abs(dir))
	{

	dir=direction;
	}




}

void* changeDir()
{
	
	 while(1){
        key=getch();
        switch(key){
                case KEY_DOWN:
                        straightSolution(DOWN);
                        break;
                case KEY_UP:
                        straightSolution(UP);
                        break;
                case KEY_LEFT:
                        straightSolution(LEFT);
                        break;
                case KEY_RIGHT:
                        straightSolution(RIGHT);
                        break;
        }
        }




}

int main()
{

	pthread_t t1;
	pthread_t t2;
	

	initNcurse();
	initSnake();
	gamePic();
	
	pthread_create(&t1,NULL,refreshUI,NULL);
	pthread_create(&t2,NULL,changeDir,NULL);
	
	while(1);

	
	getch();
	endwin();
	return 0;
}
