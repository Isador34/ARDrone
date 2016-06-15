/*
 ============================================================================
 Name        : AR_Drone.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <RT_ARDrone/RT_ARDrone.h>

float* interval(float d, float prct)
{
	float* inter;

	inter[0] = d-(d*(prct/100));
	inter[1] = d+(d*(prct/100));
	return inter;
}

void test(ARDrone* bob){
	printf("Avance en cours...\n");
		sleep(4);
		ARDrone_move(bob, 1, 0, -1, 0, 0 ) ;
		sleep(1);
		ARDrone_move(bob, 0, 0, 0, 0, 0 ) ;

		printf("Rotation en cours...\n");
		sleep(3);
		ARDrone_move(bob, 0, 0, 0, 4.5, 0 ) ;

		sleep(2);
		ARDrone_move(bob, 0, 0, 0, 0, 0 ) ;

		printf("Avance en cours...\n");
		sleep(3);
		ARDrone_move(bob, 1, 0, -1, 0, 0 ) ;
		sleep(2);
		ARDrone_move(bob, 0, 0, 0, 0, 0 ) ;
}

void line(ARDrone* bob, NavData start) // erreur segmentation
{
	printf("YOYOYO");
	NavData rotData;
	float minPhi = interval(start.phi, 5)[0];
	float maxPhi = interval(start.phi, 5)[1];

	float minPsi = interval(start.psi, 5)[0];
	float maxPsi = interval(start.psi, 5)[1];
	printf("yolo");
	while(1)
	{
		ARDrone_get_navdata(bob, &rotData);

		ARDrone_move(bob, 1, 0, -1, 0, 0);

		printf("test: ");

		if(rotData.phi < minPhi || rotData.phi > maxPhi)
		{
			printf("roll: s:%lf c:%lf\n", start.phi, rotData.phi);
			if(rotData.phi > maxPhi)
			{
				printf("roll -0.1\n");
				ARDrone_move(bob, 0, -0.1, -1, 0, 0);
			}
			else if(rotData.phi < minPhi)
			{
				printf("roll + 0.1\n");
				ARDrone_move(bob, 0, 0.1, -1, 0, 0);
			}
		}

		if(rotData.psi < minPsi || rotData.psi > maxPsi)
		{
			printf("yaw: s:%lf c:%lf\n", start.psi, rotData.psi);
			if(rotData.psi > maxPsi)
			{
				printf("yaw +0.1\n");
				ARDrone_move(bob, 0, 0, -1, 0.1, 0);
			}
			else if(rotData.psi < minPsi)
			{
				printf("yaw - 0.1\n");
				ARDrone_move(bob, 0, 0, -1, -0.1, 0);
			}
		}
	}
}


int main ( int argc, char** argv, char** envv ) {

	ARDrone* bob ;
	NavData  data ;

	bob = ARDrone_new( "192.168.1.1" ) ;

	ARDrone_connect( bob ) ;

	ARDrone_trim ( bob ) ;

	sleep(5) ;

	printf("Décollage en cours...\n");
	ARDrone_takeoff( bob );
	sleep(5);
	ARDrone_get_navdata( bob, &data ) ;
	sleep(5);
	//test(bob);

	line(bob, data);
	//video(bob);

	printf("Attérissage en cours...\n");
	sleep(3);
	ARDrone_land( bob );
	sleep(6);

	ARDrone_reset_defaults( bob ) ;
	sleep(5);

	ARDrone_get_navdata( bob, &data ) ;
	printf( "state %d - bat %d \n", data.state, data.bat );

	ARDrone_free( bob );



	return 0 ;

}
