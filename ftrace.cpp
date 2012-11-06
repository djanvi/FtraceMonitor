#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<math.h>
#include<string.h>
#include <sstream>
using namespace std;
 
struct process
{
    GLfloat y;
    int sleep;
    int run;
    int xc;
    int dormant;
    char processname[20];
    long int total_time;
    long int sleep_time;
    long int run_time;	
}parray[200];
std::ifstream fp("file.txt");
 
GLfloat j=40.0f,p=40.0f,k=60.0f,y2=40.0f,y3=60.0f,y4=80.0f;
GLfloat a1=1.0f,b1=0.0f,c1=0.0f,a2=1.0f,b2=0.0f,c2=0.0f,y;
int graphvalue1=0,wcounter=1,var,DR,RR,RD,RRW,DDW,mflag=0;
long int counter=0,that_index,i=0,that_index2,current_pie;
char *endptr;
GLint t=50;
GLfloat s=20.0f,current_ts,ycoordinate=40.0f,currentx=60.0f,currenty=40.0f,pc=0.0f;
char procname[20],temp[30],ts[30],ts2[30],activity1[20],activity2[20],arrow[5],nextproc2[30],procname2[20],ts1[15],activity1state[20],activity2state[20],intpart[10],temp_name[40];
long int timestamp1,timestamp2,graphvalue;
int SR, RS,SS,currentfp,len,len1,len2,len_arrow,XR;

void readfile();
 
			/*initializing the main window*/
void init(void)
 {
    glClearColor(0.0,0.0,0.0,0.0); //set display-window color to black
    glMatrixMode(GL_PROJECTION); //set projection parameters
    gluOrtho2D(0.0,1000.0,0.0,500.0);
    glClear(GL_COLOR_BUFFER_BIT);
 }

			/*initializing the pie window*/
void init2(void)
 {
    glClearColor(0.0,0.0,0.0,0.0); //set display-window color to black
    glMatrixMode(GL_PROJECTION); //set projection parameters
    gluOrtho2D(0.0,200.0,0.0,200.0);
    glClear(GL_COLOR_BUFFER_BIT);
 }

			/* checking the conditions and drawing graph*/
void checkcondition(void)
{
    for(i=0;i<=counter;i++)
   {

    if(parray[i].sleep==1)
    {     
	parray[i].sleep_time=parray[i].sleep_time+graphvalue;
	parray[i].total_time=parray[i].total_time+graphvalue;
        cout<<"\nIn sleep"<<parray[i].processname<<" sleep="<<parray[i].sleep;
        glPointSize(6.0);
        glLineWidth(5.0);
        //currenty=parray[i].x;     
        currenty=parray[i].y;     
        glColor3f(0.5f,0.5f,0.5f);
        cout<<"\ncurrntx="<<currentx;
        cout<<"\ncurrnty="<<currenty;
        cout<<"\ncurrntx+cts="<<currentx+current_ts<<"\n";
        glBegin(GL_LINES);
         glVertex3f(currentx,currenty,0.0f);
         glVertex3f(currentx+current_ts,currenty,0.0f);
        glEnd();
        glFlush();
    }
    else if(parray[i].run==1)
    {   
	parray[i].run_time=parray[i].run_time+graphvalue;  
	parray[i].total_time=parray[i].total_time+graphvalue;
        cout<<"In run"<<parray[i].processname<<" run=  "<<parray[i].run;
        glPointSize(6.0);
        glLineWidth(5.0);
        currenty=parray[i].y;     
        glColor3f(1.00f,0.0f,0.0f);
        cout<<"\ncurrntx"<<currentx;
        cout<<"\ncurrnty"<<currenty;
        cout<<"\ncurrntx+cts"<<currentx+current_ts<<"\n";     

        glBegin(GL_LINES);
         glVertex3f(currentx,currenty,0.0f);
         glVertex3f(currentx+current_ts,currenty,0.0f);
        glEnd();
        glFlush();
    }
    else if(parray[i].xc==1)
    {     
         cout<<"In XC"<<parray[i].processname<<"   "<<parray[i].xc;
         currenty=parray[i].y;     
        glColor3f(1.0f,1.0f,0.0f);
        glBegin(GL_LINES);
         glVertex3f(currentx,currenty,0.0f);
         glVertex3f(currentx+current_ts,currenty,0.0f);
        glEnd();
        glFlush();
    }
    else if(parray[i].dormant==1)
    {     
         cout<<"In dormant"<<parray[i].processname<<"   "<<parray[i].dormant;
        currenty=parray[i].y;     
        glColor3f(0.0f,1.0f,0.0f);
         
        glBegin(GL_LINES);
         glVertex3f(currentx,currenty,0.0f);
         glVertex3f(currentx+current_ts,currenty,0.0f);
        glEnd();
        glFlush();
    }
 
 }
 currentx=currentx+current_ts;
 for(i=0;i<counter;i++)
    {
        cout<<"i: "<<i;
        cout<<"pid: "<<parray[i].processname;
    }
}
 
				/* Printing the text */
void glutPrint(float x, float y, char* text, float r, float g, float b, float a) 
{ 
    if(!text || !strlen(text)) return; 
    bool blending = false; 
    if(glIsEnabled(GL_BLEND)) blending = true; 
    glEnable(GL_BLEND); 
    glColor4f(r,g,b,a); 
    glRasterPos2f(x,y); 
    while (*text) { 
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *text); 
        text++; 
    } 
    if(!blending) glDisable(GL_BLEND); 
} 

			/*Drawing the output on screen*/
 
void drawProject(void)
{     
    glColor3f(0.0f,0.3f,0.0f);
    glBegin(GL_LINES);
    glEnd();
    glFlush();     
  	glLineWidth(1.0);
 	int rows=500,columns=1000;
     glBegin(GL_LINES);
    /* Horizontal lines. */
    for (int I=0; I<=rows; I=I+12)
    {
	if(I==36)
	{
		glColor3f(0.0,0.8,0.0);
		glLineWidth(1.5);
	}
	else
	{
		glColor3f(0.0,0.3,0.0);
		glLineWidth(1.0);
	}
     	glVertex2f(0, I);
      	glVertex2f(columns, I);
    }
    /* Vertical lines. */
    for (int I=0; I<=columns; I=I+12) {
      glVertex2f(I, 0);
      glVertex2f(I, rows);
    }
  glEnd();
	glutPrint(24,24,"Scale: 1 square= 12x12 pixel", 1.0f,1.0f,0.0f,0.0f);
 	glutPrint(51,12,"1 pixel = 10 nano second", 1.0f,1.0f,0.0f,0.0f);
	glutPrint(180,24,"RED => Running", 1.0f,0.0f,0.0f,0.0f);
	glutPrint(180,12,"GRAY => Sleep", 0.5f,0.5f,0.5f,0.0f);	
    while(wcounter<60)
    {     
         
        cout<<"\n\n\nLOOP "<<wcounter;
     
        readfile();
        cout<<"\nGRAPTHVALUE===="<<graphvalue;
        checkcondition();
     
    wcounter++;
    }
    
 }
 
				/*Drawing the piechart*/
void piechart()
{
	float in_red,in_sleep;
	float x,y;
	double run_per,sleep_per;
	glColor3f(1.0,0.0,0.0);
	int r=30;
	
	in_red=parray[current_pie].run_time*360/parray[current_pie].total_time;
	in_sleep=360-in_red;
	cout<<"\nruntime "<<parray[current_pie].run_time<<"\n sleep"<<parray[current_pie].sleep_time<<"red"<<in_red<<"  slpee"<<in_sleep<<"\n\nCurremt pie="<<current_pie;

	run_per=parray[current_pie].run_time*100.0/parray[current_pie].total_time;
	sleep_per=100.0-run_per;

	cout<<"run_per+"<<run_per;

	
	char run[32],sleep[32];
	sprintf(run,"%f",run_per);
	sprintf(sleep,"%f",sleep_per);
	strcat(run,"%");
	strcat(sleep,"%");

	glutPrint(10.0, 20.0, "Run  ", 1.0,0.0, 0.0, 0.0);
	glutPrint(10.0, 10.0, "Sleep", 0.5,0.5, 0.5, 0.0);
	glutPrint(40.0, 20.0, run, 0.0,0.8, 0.0, 0.0); 
	glutPrint(50.0, 10.0, sleep, 0.0,0.8, 0.0, 0.0); 
	
	glBegin(GL_LINE_LOOP);

	
	for(float i=0;i<360;i+=1)
	{	if(i<=in_red)
                	glColor3f(1.0,0.0,0.0);
		else
                	glColor3f(0.5,0.5,0.5);
		glVertex3f(100.0f,100.0f,0.0f);
		x=100.0f+r*cos(i*3.1415/180);
		y=100.0f+r*sin(i*3.1415/180);
		glVertex3f(x,y,0.0f);
	}
	
	glEnd();
	glFlush();
}     

			/*Handling the mouse click event*/
 void window2(int button, int state, int x, int y)
{
	current_pie=0;
	cout<<"in window2"<<"\nX="<<x<<"\n Y="<<y<<"counter"<<counter;
	y=500-y;
	if(button==GLUT_LEFT_BUTTON)
	{
		for(int i=0;i<counter;i++)
		{
			if(y>=(25*i+60)&&y<(25*(i+1)+60))
				{ current_pie=i;break;}
		}
		cout<<"currtent pie after loop"<<current_pie;
		glutInitWindowPosition(0,0);
		glutInitWindowSize(200,200);
		glutCreateWindow("piechart");
		glutDisplayFunc(piechart);
		//glClearColor(0.0f,0.0f,0.0f,0.0f);
		init2();		
		glutMainLoop();	
	}
}

			/*reading the file*/
void readfile()
 {           

	    cout<<"******************************>>>><<<<<<<counter"<<counter;	
	    	  
            int flag=0;
            fp.getline(temp_name,30,'-');
             
            fp.getline(procname,20,' ');
            //we can concat it
	    //strcat(procname,temp);
	    	
            fp.getline(temp,20,']');
            cout<<"\ntemp="<<temp;
           
            currentfp=fp.tellg();
            //cout<<"current Fp in"<<currentfp<<"\n";
 
            fp.getline(temp,10,' ');
            //cout<<"temp="<<temp;
 
            fp.getline(temp,30,' ');
            fp.getline(intpart,10,'.');
 
 	    cout<<"...intpart"<<intpart;
            fp.getline(ts1,20,':');
	    strcat(intpart,ts1);	
            cout<<"\n ts="<<ts1;
	    
            timestamp1=strtol(intpart,NULL,0);
            cout<<"timestamp1=="<<timestamp1;
             
 
            fp.getline(temp,10,' ');
            cout<<" those temp="<<temp;
            fp.getline(temp,10,' ');
            cout<<" those temp="<<temp;
            fp.getline(temp,10,' ');
            cout<<" those temp="<<temp;
 
 
            fp.getline(activity1,20,':');
            cout<<"\nACTIVITY1="<<activity1;
            fp.getline(activity1state,20,' ');
            cout<<"\nas1=="<<activity1state;     
 
            //cout<<"\nacti1=="<<activity1;*/
            len=strlen(activity1state);     
           
            that_index=counter;
            //cout<<"\n Tellg="<<
            currentfp=fp.tellg();
            cout<<"\nFr cufp="<<currentfp;
            for(i=0;i<=counter;i++)//for activity 1
            {
                if(strcmp(parray[i].processname,activity1)==0)
                {
                    flag=1;
                    that_index=i;
                }
            }
            parray[that_index].run=0;
            parray[that_index].sleep=0;
            parray[that_index].xc=0;
 
            if(flag==0)//new process
            {
                strcpy(parray[that_index].processname,activity1);
                counter++;
                parray[that_index].y=(25.0f*that_index)+60.0f;
		parray[that_index].total_time=0;
		parray[that_index].run_time=0;
		parray[that_index].sleep_time=0;
		cout<<"************************for "<<parray[that_index].processname<<"***********Y="<<parray[that_index].y;
                pc=parray[that_index].y;
		//strcat(activity1,temp_name);
                glutPrint(1.0f, pc, activity1, 1.0f, 1.0f,0.0f,0.0f);
                
		
            }
 
             
            var=fp.tellg();
            
            fp.getline(temp,20,']');cout<<"temp1="<<temp;
            fp.getline(temp,4,' ');cout<<"temp2="<<temp;
            fp.getline(temp,4,' ');cout<<"temp3="<<temp;
            //cout<<"\n\n temp after aarow--"<<temp<<"hi";
 
            fp.getline(activity2,20,':');
            fp.getline(activity2state,20,' ');
            cout<<"\n\nACTI="<<activity2;
            len2=strlen(activity2state);
            fp.getline(temp,30,'\n');
	    cout<<"bBHHHHHHHHHHHHHHHHHHHHHHHHHHHH++++++++++++++"<<temp;	
            currentfp=fp.tellg();     
            cout<<"CURRENTFP="<<currentfp;
            //cout<<"\n\n arrow[len_arrow-1]"<<arrow[len_arrow-1];
            flag=0;
            that_index2=counter;         
            for(i=0;i<=counter;i++)                                        //for activity 2
            {
                if(strcmp(parray[i].processname,activity2)==0)
                {
                    flag=1;
                    that_index2=i;
                }
            }
            if(flag==0)//new process
            {
                strcpy(parray[that_index2].processname,activity2);
                counter++;
                parray[that_index2].y=(25.0f*that_index2)+60.0f;  
		parray[that_index2].total_time=0;
		parray[that_index2].run_time=0;
		parray[that_index2].sleep_time=0; 
                pc=parray[that_index2].y;
               glutPrint(1.0f, pc, activity2, 1.0f, 1.0f,0.0f,0.0f);
                //cout<<"\n\n in 2nd array of Proceess-"<<parray[that_index2].processname;
            }
            //cout<<"\nthatindex2"<<that_index2;
 
             
            cout<<"\n\n activity1state[]????????????????????????"<<activity1state[len-1];
            cout<<"\n\n activity2state[]????????????????????????"<<activity2state[len-1];
            //cout<<"\n\n act2"<<activity2[len2-1];
            if(/*arrow[len_arrow-1]=='+'*/activity1state[len-1]=='R'&&activity2state[len2-1]=='S')
            {
                    RS=1;
                    parray[that_index].run=1;
                    parray[that_index2].sleep=1;
                    cout<<"\nIn RS";
             }
            else if(/*arrow[len_arrow-1]=='>'&&*/activity1state[len-1]=='S'&&activity2state[len2-1]=='R')
             {  
                    //cout<<"\n\n Wee are in ==> ";
                    SR=1;
                    parray[that_index].sleep=1;
                    parray[that_index2].run=1;
                    cout<<"\nIn SR1";
                     
             }
            else if(/*arrow[len_arrow-1]=='>'&&*/activity1state[len-1]=='X'&&activity2state[len2-1]=='R') 
             {
                    XR=1;
                    parray[that_index].xc=1;
                    parray[that_index2].run=1;
                    cout<<"\nIn XR>";
             }
            else if(/*arrow[len_arrow-1]=='>'&&*/activity1state[len-1]=='R'&&activity2state[len2-1]=='R')     
            {
                    RR=1;
                    parray[that_index].run=1;
                    parray[that_index2].run=1;
                    cout<<"\nIn RR>";
            } 
 
            else if(/*arrow[len_arrow-1]=='>'&&*/activity1state[len-1]=='D'&&activity2state[len2-1]=='R') 
             {
                    DR=1;
                    parray[that_index].dormant=1;
                    parray[that_index2].run=1;
                    cout<<"\nIn DR>";
 
            }     
            else if(/*arrow[len_arrow-1]=='>'&&*/activity1state[len-1]=='R'&&activity2state[len2-1]=='D') 
            {
                    RD=1;
                    parray[that_index].run=1;
                    parray[that_index2].dormant=1;
                    cout<<"\nIn RD>";
            }     
            else if(/*arrow[len_arrow-1]=='+'&&*/activity1[len-1]=='D'&&activity2[len2-1]=='D') 
            {
                    DDW=1;
                    parray[that_index].dormant=1;
                    parray[that_index2].dormant=1;
                    cout<<"\nIn DD+";
            }
         
 
//fp.getline(temp,20,'\n');
            //currentfp=fp.tellg();
            cout<<"\n\n Fp after first line"<<currentfp<<"\n";
 
            fp.getline(temp,30,'-');
            fp.getline(procname2,20,' ');
            cout<<"\nsec pname="<<procname2;
            //cout<<"\n\n parray[that_index].processname 2"<<parray[that_index].processname;
            fp.getline(temp,10,']');
            fp.getline(temp,10,' ');
            fp.getline(temp,10,' ');
            
		

	    fp.getline(intpart,10,'.');
 
 	    cout<<"...intpart"<<intpart;
            fp.getline(ts2,20,':');
	    strcat(intpart,ts2);	
            cout<<"\n ts="<<ts2;
	    
            timestamp2=strtol(intpart,NULL,0);
             cout<<"timestamp2=="<<timestamp2;
                    	
            graphvalue=timestamp2-timestamp1;
 
            cout<<"*************************************graph value="<<graphvalue;
           

        current_ts=graphvalue/100;

        cout<<"ata ethw="<<fp.tellg();
        fp.seekg(currentfp);
        cout<<"mag alo="<<fp.tellg();
     
     
}

			/*the main function*/
int main(int argc, char**argv)
 {
 	glutInit(&argc, argv);  //initialize GLUT
 	glutInitWindowPosition(50,20); //set top-left display-window position
 	glutInitWindowSize(800,500); //set display-window width and height to 500
 	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //set display mode
 
 	//Now display the window with a title
 	glutCreateWindow("Graphical Representation of ftrace utility");
 
 	init(); //execute initialization procedure of OpenGL
 	glutDisplayFunc(drawProject); //send graphics to display window
 	glutMouseFunc(window2); 
 	glutMainLoop();//display everything and wait
 	return 0;
 }
