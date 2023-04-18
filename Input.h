//
//  Input.h
//  MarkovChain - Galton-Watson
//
//  Created by Broos  Maenhout on 22/09/2017.
//  Copyright © 2017 Broos  Maenhout. All rights reserved.
//

#include <ctime>

#ifndef Input_h
#define Input_h


#endif /* Input_h */




class personnel{

private:

public:

#define max(a,b) (((a)>(b)?(a):(b)))
#define min(a,b) (((a)>(b)?(b):(a)))
    // Definition of static parameters to define memory requirements
#define max_C   20000                   // max jobs
#define max_run   10                    // max number of runs
#define max_S   10                      // max number of servers per station
#define max_AS  5                       // max number of arrival sources
#define max_nr_stations 10              // max number of stations
#define max_nr_job_types    10          // max number of job types

    FILE *file1;


    /* COUNTER */
    int i1, i2, i6, run, i3;                                // define counters (integers)

    double j1, j2, j3, l1;                                  // define float numbers
    int K, s0, L;
    double avg[30];
    char naam[300], sproblem[10];

    double left_var_Triangular, right_var_Triangular;   // inputs for triangular distribution

    /* INPUT DATA RELATED TO RADIOLOGY DPT */
    int nr_stations;                            //Number of workstations
    int nr_servers[max_nr_stations];            //Number of servers per workstation

    /* INPUT DATA RELATED TO SYSTEM JOBS */
    int nr_job_types;                           // Number of job types
    int nr_workstations_job[max_nr_job_types];  // Number of workstations per job type
    int route[max_nr_job_types][max_nr_stations];   // Route to follow for each job type
    int current_station[max_C];                 // Matrix that denotes the current station of a scan (sequence number)


    /* GENERAL DISCRETE EVENT SIMULATION PARAMETERS */

    double t;                                     // Simulation time
    int N;                                        // Max number of scans (Stop criterion)

    /* VARIABLES RELATED TO system SCANS */
    int n;                                         // Number of scans in the system
    int n_ws[max_nr_stations];                     // Number of scans at a particular workstation

    double mean_customers_system[max_run];
    double tot_n[max_run];                         // Number of customers in the system over time
    double tot_n_ws[max_run][max_nr_stations];      // Number of customers in a workstation over time


    /* PARAMETERS RELATED TO ARRIVAL OF SCANS */
    int nr_arrival_sources;                         // Number of arrival sources
    double lambda[max_AS];                                  // Arrival rate
    double cum_distr_scans[max_AS][max_nr_job_types];       // Cumulative(!) Distribution of job types per source
    int n_a;                                        // Number of scans arrived to the system
    int n_a_ws[max_nr_stations];                    // Number of scans arrived to a particular workstation
    double t_a[max_AS];                             // Time of next arrival for each source
    double first_ta;                                // First arrival time over all sources;
    int index_arr;                                  // Source of next arrival;
    double t_lambda, tot_lambda[max_run][max_AS];
    int scan_type[max_C];                                  // Type of scan arriving
    double time_arrival[max_run][max_C];                // Time of arrival of the scan to the ancillary services
    double time_arrival_ws[max_run][max_nr_stations][max_C]; // Time of arrival of a particular scan to a particular workstation

    double mean_interarrival_time[max_run];

    /* PARAMETERS RELATED TO Processing OF SCANS */
    double mu[max_nr_stations][max_nr_job_types];   // Processing rate per station and job type
    double var[max_nr_stations][max_nr_job_types];   // Variance per station and job type
    double sigma[max_nr_stations][max_nr_job_types];   // Standard deviation per station and job type
    int n_d;                                        // Number of scans handled
    int n_d_ws[max_nr_stations];                    // Number of scans handled in a particular workstation
    double t_d[max_nr_stations][max_S];             // Time of next departure for each server in each workstation
    double first_td;                                   // First departure time over all sources
    int index_dep_station;                          // Station with first departure
    int index_dep_server;                           // Server with first departure
    double mean_service_time[max_run];              // Calculated average service time
    double t_mu;                                    // Generated service time
    double tot_mu[max_run];                         // Total service time generated
    double time_service[max_run][max_nr_stations][max_C];   // Service time per customer and workstation
    int current_cust[max_nr_stations][max_S];       // Customer handles by a particular workstation and server
    int list_scan[max_nr_stations][max_C];          // list of customers processed at a particular workstation on a particular point in time
    /* PARAMETERS RELATED TO waiting OF SCANS */

    double mean_waiting_time[max_run];
    double waiting_time[max_run];
    double waiting_time_job_ws[max_run][max_nr_stations][max_C];    // Waiting time for a job on a particular workstation

    double mean_customers_queue[max_run];
    double tot_n_queue[max_run];
    double tot_n_queue_ws[max_run][max_nr_stations];    // Total number of scans in queue at workstation over time

    /* VARIABLES RELATED TO Processed SCANS */

    double time_departure[max_run][max_C];
    double time_departure_ws[max_run][max_nr_stations][max_C];

    double time_system[max_run][max_C];
    double time_system_job_ws[max_run][max_nr_stations][max_C];

    int order_out[max_C];                           // Order in which jobs are coming out of the system
    double mean_system_time[max_run];

    /* OTHER PARAMETERS */
    int infinity;                                       // value for infinity
    double idle[max_run][max_nr_stations][max_S];// Idle time for server s at workstation w
    double rho_ws_s[max_nr_stations][max_S];    // utilisation of server s at workstation w
    double rho_ws[max_nr_stations];             //utilisation of workstation w
    double rho;                                         // overall utilisation

    /* VARIABLES RELATED TO CLOCK TIME */
    double elapsed_time, time_subproblem; clock_t start_time; clock_t inter_time;clock_t project_start_time; //Time measurements to compute run times


    /* constructor/destructor */
    personnel();

    ~personnel();


    /* FUNCTION DEFINITION */
    int Poisson_distribution(double lambda);
    int Bernouilli_distribution(double prob);
    int Uniform_distribution(double a, double b);
    int Normal_distribution(double mean, double stdev);
    int Triangular_distribution(int a, int b, int c);
    double Exponential_distribution(double lambda);
    void procedure();
    void initialize_functions();
    void arrival_event();
    void departure_event();
    void radiology_system();
    void output();
    void init();



};

