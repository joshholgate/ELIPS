// ELIPS.cc - Electrohydrodynamic Linear Stability of Plasma Surface
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

#define IMAX 10000
#define WALL_PHI -10.0L // Normalized potential at wall. Must be negative for normal sheath.

# define TOL 0.00001L	// Maximum error for PHI1 at wall. Decreasing this will significantly increase runtime...



int main ()
{

	long double H = -WALL_PHI/(long double)(IMAX);
	long double PHI1, F1, GAMMA1, U1, PHI1_TARGET, TEMP1[4], TEMP2[4], TEMP3[4], TEMP4[4];
	long double PHI0, N0, F0, SMALL_NUMBER;

	long double KSQ = 1.0L;		// Input wavenumber as (k lambda_D)^2

	bool has_target_been_reached;

	ostringstream fileNameStream("A");
	fileNameStream << "RK4-loopXi-Phi" << WALL_PHI << ".dat";
	string fileName = fileNameStream.str();
	ofstream myfile;
	myfile.open ( fileName.c_str() );

	for ( long double XI = 0.01L; XI <= 0.051L; XI += 0.01L ) {	// Loop over (xi / lambda_D) values

		F0 = - sqrt( 2.0L * sqrt(1.0L - 2.0L * WALL_PHI) + 2.0L * exp(WALL_PHI) - 4.0L);
		PHI1_TARGET = XI * F0;
		SMALL_NUMBER = 1.0e-140L;

		do {
			has_target_been_reached = false;
			cout << SMALL_NUMBER << endl;
			PHI1 = -SMALL_NUMBER;
			F1 = -SMALL_NUMBER;
			GAMMA1 = -SMALL_NUMBER;
			U1 = SMALL_NUMBER;

			for (int i=1; i<IMAX; i++) {

				PHI0 = - H*(long double)(i);
				N0 =  1.0L / sqrt(1.0L - 2.0L * PHI0);
				F0 = - sqrt( 2.0L * sqrt(1.0L - 2.0L * PHI0) + 2.0L * exp(PHI0) - 4.0L);
				TEMP1[0] = F1 / F0;							// PHI1
				TEMP1[1] = ( (-N0*N0*N0 + exp(PHI0) + KSQ)*PHI1 + N0*GAMMA1) / F0;	// E_Z1
				TEMP1[2] = - KSQ * N0 * U1 / F0;					// Gamma_1
				TEMP1[3] = - N0 * PHI1 / F0;						// i u_x1 / (k lambda_D)

				PHI0 = - H*((long double)(i)+0.5L);
				N0 =  1.0L / sqrt(1.0L - 2.0L * PHI0);
				F0 = - sqrt( 2.0L * sqrt(1.0L - 2.0L * PHI0) + 2.0L * exp(PHI0) - 4.0L);
				TEMP2[0] = (F1 - 0.5L*H*TEMP1[1]) / F0;
				TEMP2[1] = ( (-N0*N0*N0 + exp(PHI0) + KSQ)*(PHI1 - 0.5L*H*TEMP1[0])
											+ N0*(GAMMA1 - 0.5L*H*TEMP1[2]) ) / F0;
				TEMP2[2] = - KSQ * N0 * (U1 - 0.5L*H*TEMP1[3]) / F0;
				TEMP2[3] = - N0 * (PHI1 - 0.5L*H*TEMP1[0]) / F0;

				TEMP3[0] = (F1 - 0.5L*H*TEMP2[1]) / F0;
				TEMP3[1] = ( (-N0*N0*N0 + exp(PHI0) + KSQ)*(PHI1 - 0.5L*H*TEMP2[0])
											+ N0*(GAMMA1 - 0.5L*H*TEMP2[2]) ) / F0;
				TEMP3[2] = - KSQ * N0 * (U1 - 0.5L*H*TEMP2[3]) / F0;
				TEMP3[3] = - N0 * (PHI1 - 0.5L*H*TEMP2[0]) / F0;

				PHI0 = - H*((long double)(i)+1.0L);
				N0 =  1.0L / sqrt(1.0L - 2.0L * PHI0);
				F0 = - sqrt( 2.0L * sqrt(1.0L - 2.0L * PHI0) + 2.0L * exp(PHI0) - 4.0L);
				TEMP4[0] = (F1 - H*TEMP3[1]) / F0;
				TEMP4[1] = ( (-N0*N0*N0 + exp(PHI0) + KSQ)*(PHI1 - H*TEMP3[0]) + N0*(GAMMA1 - H*TEMP3[2]) ) / F0;
				TEMP4[2] = - KSQ * N0 * (U1 - H*TEMP3[3]) / F0;
				TEMP4[3] = - N0 * (PHI1 - H*TEMP3[0]) / F0;


				PHI1 = PHI1 - H*(TEMP1[0] + 2.0L*TEMP2[0] + 2.0L*TEMP3[0] + TEMP4[0]) / 6.0L;
				F1 = F1 - H*(TEMP1[1] + 2.0L*TEMP2[1] + 2.0L*TEMP3[1] + TEMP4[1]) / 6.0L;
				GAMMA1 = GAMMA1 - H*(TEMP1[2] + 2.0L*TEMP2[2] + 2.0L*TEMP3[2] + TEMP4[2]) / 6.0L;
				U1 = U1 - H*(TEMP1[3] + 2.0L*TEMP2[3] + 2.0L*TEMP3[3] + TEMP4[3]) / 6.0L;

				if ( PHI1 <= PHI1_TARGET ) {
					if (i == IMAX-1 && PHI1 > PHI1_TARGET*(1.0L+TOL) ) {
						has_target_been_reached = true;
						break;
					} else {
						SMALL_NUMBER *= 0.75L;
						break;
					}
				}
			}

			if ( PHI1 > PHI1_TARGET ) {
				SMALL_NUMBER *= 2.0L;
			} else if ( PHI1 > PHI1_TARGET*(1.0L-TOL) ) {
				has_target_been_reached = true;
			}

		} while ( has_target_been_reached == false );


		cout << "Perturbation height (XI): \t\t\t" << XI << endl
		     << "Unperturbed wall potential: \t\t\t" << PHI0 << endl
		     << "Perturbed potential at wall: \t\t\t" << PHI1 << endl
		     << "Fractional error in perturbed potential: \t" << (PHI1 - PHI1_TARGET) / PHI1_TARGET << endl
		     << "Pertubed field at wall: \t\t\t" << F1 << endl
		     << "Perturbed ion flux at wall: \t\t\t" << GAMMA1 << endl
		     << "Perturbed parallel ion velocity at wall: \t" << U1 << endl
		     << "Perturbed perpendicular stress at wall: \t"  << F0*F1 + (N0 - exp(PHI0))*PHI1 + GAMMA1/N0 << endl;

		myfile << XI << "\t" << (PHI1 - PHI1_TARGET) / PHI1_TARGET << "\t" << F1 << "\t" << GAMMA1 << "\t" << U1 << "\t"
							<< F0*F1 + (N0 - exp(PHI0))*PHI1 + GAMMA1/N0 << endl;

	}


	return 0;
}

