//
//  Procedure.cpp
//  M/M/2 - n independent simulation runs
//
//  Created by Broos  Maenhout on 11/12/2017.
//  Copyright © 2017 Broos  Maenhout. All rights reserved.
//

#include "general.h"


personnel::personnel()
{


}

personnel::~personnel()
{


}

void personnel::procedure()
{   L = 1;
    for (i3 = 0; i3 < L; i3++)                          // Count number of runs
    {   K = 1;
        for (run = 0; run < K; run++)                  // Count number of replications per run
        {   init();
            radiology_system();
            output();
        }
    }

    strcpy(naam, "/Users/broosmaenhout/Documents/Radiology_avg_runs.txt");
    file1=fopen(naam,"w");

    /* PRINT HERE OUTPUT of Multiple runs */
    fclose(file1);
}

void personnel::init()                      // Initialisation function
{
    /* PUT ALL VARIABLES TO ZERO */

    initialize_functions();


    /* SET INPUT VALUES */

    srand(0);//((i3+1)*K-run);                    // Ensure you each time use a different seed to get IID replications

    /* INPUT RADIOLOGY DPT */

    nr_stations = 5;                        // Number of workstations

    nr_servers[0] = 3;                     // Input number of servers per workstation
    nr_servers[1] = 2;
    nr_servers[2] = 4;
    nr_servers[3] = 3;
    nr_servers[4] = 1;

    /* INPUT JOB TYPES */
    nr_job_types = 4;                       // Number of scans types
    nr_workstations_job[0] = 4;             // Number of workstations per job type
    nr_workstations_job[1] = 3;
    nr_workstations_job[2] = 5;
    nr_workstations_job[3] = 3;

    route[0][0] = 2;                        // Route to follow for each job type (JOB = 1)
    route[0][1] = 0;                        // Note: Workstation i in assignment corresponds to workstation i-1 in code as here we start counting from 0
    route[0][2] = 1;
    route[0][3] = 4;

    route[1][0] = 3;                        // Route to follow for each job type (JOB = 2)
    route[1][1] = 0;
    route[1][2] = 2;

    route[2][0] = 1;                        // Route to follow for each job type (JOB = 3)
    route[2][1] = 4;
    route[2][2] = 0;
    route[2][3] = 3;
    route[2][4] = 2;

    route[3][0] = 1;                        // Route to follow for each job type (JOB = 4)
    route[3][1] = 3;
    route[3][2] = 4;

    /* INPUT ARRIVAL PROCESS */
    nr_arrival_sources = 2;                 // Number of arrival sources
    // Arrival from radiology department
    lambda[0] = 1/0.25;                     // Input arrival rate = 1/mean interarrival time
    cum_distr_scans[0][0] = 0.2;                   // Distribution scans (SOURCE = 1) - Cumulative distribution
    cum_distr_scans[0][1] = 0.4;
    cum_distr_scans[0][2] = 0.5;
    cum_distr_scans[0][3] = 1;

    // Arrival from other services
    lambda[1] = 1/1;                        // Input arrival rate = 1/mean interarrival time
    cum_distr_scans[1][0] = 0;                   // Distribution scans (SOURCE = 2) - Cumulative distribution
    cum_distr_scans[1][1] = 0.4;
    cum_distr_scans[1][2] = 0.4;
    cum_distr_scans[1][3] = 1;


    /* INPUT SERVICE PROCESS */

    mu[0][0] = 12;                               //Processing time per ws and job type (WS1, J1)
    mu[0][1] = 15;
    mu[0][2] = 15;
    mu[0][3] = 0;
    mu[1][0] = 20;                               //Processing time per ws and job type (WS2, J1)
    mu[1][1] = 0;
    mu[1][2] = 21;
    mu[1][3] = 18;
    mu[2][0] = 16;                               //Processing time per ws and job type (WS3, J1)
    mu[2][1] = 14;
    mu[2][2] = 10;
    mu[2][3] = 0;
    mu[3][0] = 0;                               //Processing time per ws and job type (WS4, J1)
    mu[3][1] = 20;
    mu[3][2] = 24;
    mu[3][3] = 13;
    mu[4][0] = 25;                               //Processing time per ws and job type (WS5, J1)
    mu[4][1] = 0;
    mu[4][2] = 20;
    mu[4][3] = 25;
    var[0][0] = 2;                               //Processing variance per ws and job type (WS1, J1)
    var[0][1] = 2;
    var[0][2] = 3;
    var[0][3] = 0;
    var[1][0] = 4;                               //Processing variance per ws and job type (WS2, J1)
    var[1][1] = 0;
    var[1][2] = 3;
    var[1][3] = 3;
    var[2][0] = 4;                               //Processing variance per ws and job type (WS3, J1)
    var[2][1] = 2;
    var[2][2] = 1;
    var[2][3] = 0;
    var[3][0] = 0;                               //Processing variance per ws and job type (WS4, J1)
    var[3][1] = 3;
    var[3][2] = 4;
    var[3][3] = 2;
    var[4][0] = 5;                               //Processing variance per ws and job type (WS5, J1)
    var[4][1] = 0;
    var[4][2] = 3;
    var[4][3] = 5;
    sigma[0][0] = sqrt(var[0][0]);               //Processing stdev per ws and job type (WS1, J1)
    sigma[0][1] = sqrt(var[0][1]);
    sigma[0][2] = sqrt(var[0][2]);
    sigma[0][3] = sqrt(var[0][3]);
    sigma[1][0] = sqrt(var[1][0]);               //Processing stdev per ws and job type (WS2, J1)
    sigma[1][1] = sqrt(var[1][1]);
    sigma[1][2] = sqrt(var[1][2]);
    sigma[1][3] = sqrt(var[1][3]);
    sigma[2][0] = sqrt(var[2][0]);               //Processing stdev per ws and job type (WS3, J1)
    sigma[2][1] = sqrt(var[2][1]);
    sigma[2][2] = sqrt(var[2][2]);
    sigma[2][3] = sqrt(var[2][3]);
    sigma[3][0] = sqrt(var[3][0]);               //Processing stdev per ws and job type (WS4, J1)
    sigma[3][1] = sqrt(var[3][1]);
    sigma[3][2] = sqrt(var[3][2]);
    sigma[3][3] = sqrt(var[3][3]);
    sigma[4][0] = sqrt(var[4][0]);               //Processing stdev per ws and job type (WS5, J1)
    sigma[4][1] = sqrt(var[4][1]);
    sigma[4][2] = sqrt(var[4][2]);
    sigma[4][3] = sqrt(var[4][3]);


    /* STOP CRITERION */
    N = 1000;                                // Number of scans

    infinity = 999999999;


    /* 3. INITIALISE SYSTEM */
    /************************/

    /* DETERMINE FIRST ARRIVAL + FIRST DEPARTURE */
    for (i2 = 0; i2 < max_nr_stations; i2++)
    {   for (i1 = 0; i1 < max_S; i1++)
            t_d[i2][i1] =infinity;          // Put all departure times for all servers to +infty (system is idle and no departures have been scheduled yet
    }

    for (i1 = 0; i1 < nr_arrival_sources; i1++)
        t_a[i1] = Exponential_distribution(lambda[i1]);                     // Generate first arrival for all sources
    index_arr = 0;                                                                  // Initialise arrival source indicator
    first_ta = infinity;
    for(i1 = 0; i1 < nr_arrival_sources; i1++)                             // Get next arrival = Smallest arrival time
    {   //printf("%lf\t", t_a[i1]);
        if (first_ta > t_a[i1])
        {   first_ta = t_a[i1];
            index_arr = i1;
        }

    }
    //printf("\n");


    tot_lambda[run][index_arr] = first_ta;                                  // Add interarrival time to the counter for calculating the average interarrival time


}

void personnel::radiology_system()
{

    while (n_d < N)                                                         // Perform simulation until prespecified number of customers have departed
    {
        first_td = infinity;                                                //Identify next departure event = The customer that leaves the soonest (=minimum departure time)
        for (i2 = 0; i2 < nr_stations; i2++)
        {   for(i1 = 0; i1 < nr_servers[i2]; i1++)      // Loop over all servers and workstations
            {
                if (first_td > t_d[i2][i1])
                {   first_td = t_d[i2][i1];
                    index_dep_server = i1;
                    index_dep_station = i2;

                }
            }
        }

        //printf("First departure time %lf\n", first_td);                // You may want to print the first departure time

        index_arr = 0;                                                      // Identify next arrival event
        first_ta = infinity;
        for(i1 = 0; i1 < nr_arrival_sources; i1++)
        {   if (first_ta > t_a[i1])
            {   first_ta = t_a[i1];
                index_arr = i1;
            }
        }



        if (t_a[index_arr] < t_d[index_dep_station][index_dep_server])                 // Is first event an arrival or a departure?
        {   arrival_event();                                                                                // Arrival event
        }
        else                                                                                                        // Departure event
        {
            /* UPDATE STATISTICS FOR PERIOD [t,t_d]*/
            tot_n[run] += (t_d[index_dep_station][index_dep_server] - t) * n;                                     // Update statistics: continuous time statistics to count the average number of jobs in process for specific workstation and server
            for (i2 = 0; i2 < nr_stations; i2++)
                tot_n_ws[run][i2] += (t_d[index_dep_station][index_dep_server] - t) * n_ws[i2];         // Update statistics: continuous time statistics to count the average number of jobs in process for specific workstation


            for (i2 = 0; i2 < nr_stations; i2++)
            {   if (n_ws[i2] >= nr_servers[i2])
                {    tot_n_queue_ws[run][i2] += (t_d[index_dep_station][index_dep_server] - t) * (n_ws[i2] - nr_servers[i2]); tot_n_queue[run] += (t_d[index_dep_station][index_dep_server] - t) * (n_ws[i2] - nr_servers[i2]);
                }
            }// Update statistics: continuous time statistics to count the average number of jobs in queue for specific workstation and server

            // Calculate idle time servers
            for (i2 = 0; i2 < nr_stations; i2++)
            {   for (i1 = 0; i1 < nr_servers[i2]; i1++)
                {   if (t_d[i2][i1] == infinity)
                    {   idle[run][i2][i1] += (t_d[index_dep_station][index_dep_server] - t);
                    }
                }
            }   // If no departure is planned, the workstation/server is idle (continuous time statistic)

            /* Increment simulation time t = t_d*/
            t = t_d[index_dep_station][index_dep_server];

            time_departure_ws[run][index_dep_station][current_cust[index_dep_station][index_dep_server]] = t;                    // Store departure time customer n_d in source center
            time_system_job_ws[run][index_dep_station][current_cust[index_dep_station][index_dep_server]] += (t-time_arrival_ws[run][index_dep_station][current_cust[index_dep_station][index_dep_server]]);                                        // Calculate system time in source center of served customer

            n_d_ws[index_dep_station]++;    // Count number of departures at a particular station
            n_ws[index_dep_station]--;      // Count number of scans at the station

            current_station[current_cust[index_dep_station][index_dep_server]]++;                                               //Selected scan should go to next station


            for (i3 = 0; i3 < n_ws[index_dep_station]+1; i3++)                                                                  // Selected customer is identified from scan list current station
            {   if (list_scan[index_dep_station][i3] == current_cust[index_dep_station][index_dep_server])
                    break;
            }


            list_scan[index_dep_station][i3] = -1;      // Selected customer is removed from scan list current station

            for (i2 = i3; i2 < n_ws[index_dep_station]; i2++)                                                                   // Scan list should be updated
                list_scan[index_dep_station][i2] = list_scan[index_dep_station][i2+1];  // Move all customers one position up
            list_scan[index_dep_station][i2] = -1;
            printf("Departure event\tJob %d\tWorkstation %d\tServer %d\tTime %lf\tCurrent station %d of %d\tReal %d\n",current_cust[index_dep_station][index_dep_server], index_dep_station, index_dep_server, t, current_station[current_cust[index_dep_station][index_dep_server]],nr_workstations_job[scan_type[current_cust[index_dep_station][index_dep_server]]], route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]-1]);



            // Does the finished job has more tasks to be done on if route?
            // Evaluate number of tasks done versus required number

            if (current_station[current_cust[index_dep_station][index_dep_server]] < nr_workstations_job[scan_type[current_cust[index_dep_station][index_dep_server]]])
            { // For this customer there are still jobs to do
                n_ws[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]]++;   // Count number of scans at a particular workstation, defined by the route (scan type and current                                                            station)
                n_a_ws[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]]++;// Count the number of arrivals at a particular workstation
                time_arrival_ws[run][route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][current_cust[index_dep_station][index_dep_server]]=t;// Set the time of arrival at a particular workstation of a particular job



                if (n_ws[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]] <= nr_servers[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]])  // Arrival to a system where one of the servers is idle?
                {   for (i1 = 0; i1 < nr_servers[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]]; i1++)                      // Identify the system that was idle
                    {   if (t_d[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][i1] == infinity)
                            break;
                    }

                    for (i2 = 0; i2 < nr_servers[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]]; i2++)
                    {   if (list_scan[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][i2] == -1)
                            list_scan[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][i2] = current_cust[index_dep_station][index_dep_server];
                    }// change scan list



                    //list_scan[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][i1] = current_cust[index_dep_station][index_dep_server];// CHANGE

                    t_mu = Normal_distribution(mu[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][scan_type[current_cust[index_dep_station][index_dep_server]]], sigma[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][scan_type[current_cust[index_dep_station][index_dep_server]]]);                        // Derive service time of the system that was idle determine the departure time for the newly arrived scan
                    t_mu = t_mu/60;             // Change service time to an hourly basis
                    time_service[run][route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][current_cust[index_dep_station][index_dep_server]] = t_mu;       // Store service time

                    waiting_time_job_ws[run][route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][current_cust[index_dep_station][index_dep_server]] = 0;       /* Tally a delay of 0 for this job*/
                    /* Make a machine for this workstation busy */
                    t_d[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][i1] = t + t_mu; tot_mu[run] += t_mu;// Calculate departure time
                    current_cust[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][i1] = current_cust[index_dep_station][index_dep_server];                                     // Track the current customer being served
                    t_d[index_dep_station][index_dep_server] = infinity;                                                // Set departure time of current station to infty
                }
                else
                {   list_scan[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][n_ws[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]]-1] = current_cust[index_dep_station][index_dep_server];// Add new scan to the last place n the scan list

                }




            }
            else
            {
                order_out[n_d] = current_cust[index_dep_station][index_dep_server];                             // Store the order in which scans leave the system

                n_d++;                                                                                          // Increment the number of orders that have left the system

                n--;                                                                                            // Decrease the number of items in the system
                time_departure[run][current_cust[index_dep_station][index_dep_server]] = t;                     // Set time of departure
                time_system[run][current_cust[index_dep_station][index_dep_server]] = t-time_arrival[run][current_cust[index_dep_station][index_dep_server]];// Calculate system time
                printf("Job %d has left\tTime %lf\n", current_cust[index_dep_station][index_dep_server], t);
            }




            // Determine next scan in departure station or idle status
            if (n_ws[index_dep_station] >= nr_servers[index_dep_station])
            {   // Compute next job by calculating the waiting time: Select the job with the largest waiting time
                // Job with the largest waiting time = Next job on the scan list of workstation
                current_cust[index_dep_station][index_dep_server] = list_scan[index_dep_station][nr_servers[index_dep_station]-1];

                // Make idle server busy with next job and generate next departure event

                t_mu = Normal_distribution(mu[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][scan_type[current_cust[index_dep_station][index_dep_server]]], sigma[route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][scan_type[current_cust[index_dep_station][index_dep_server]]]);                        // For the system that was idle determine the departure time for the newly arrived scan
                t_mu = t_mu/60;
                time_service[run][route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][current_cust[index_dep_station][index_dep_server]] = t_mu;           // Store service time
                /* Calculate the delay for this job and workstation*/
                waiting_time_job_ws[run][route[scan_type[current_cust[index_dep_station][index_dep_server]]][current_station[current_cust[index_dep_station][index_dep_server]]]][current_cust[index_dep_station][index_dep_server]] = t - time_arrival_ws[run][index_dep_station][current_cust[index_dep_station][index_dep_server]];



                /* Make a machine for this workstation busy */
                t_d[index_dep_station][index_dep_server] = t + t_mu;
                tot_mu[run] += t_mu;

            }
            else
            {   // Make server in this station idle
                t_d[index_dep_station][index_dep_server] = infinity;

            }



        }
    }

}

void personnel:: arrival_event()
{
    /* UPDATE STATISTICS FOR PERIOD [t,t_a]*/
    tot_n[run] += (t_a[index_arr] - t) * n;                                                     // Number of scans in system (Continuous time statistic)
    for (i2 = 0; i2 < nr_stations; i2++)
        tot_n_ws[run][i2] += (t_a[index_arr] - t) * n_ws[i2];                           // Number of scans in workstation (Continuous time statistic)

    for (i2 = 0; i2 < nr_stations; i2++)
    {   if (n_ws[i2] >= nr_servers[i2])                                                         // Number of scans in queues
        {    tot_n_queue_ws[run][i2] += (t_a[index_arr] - t) * (n_ws[i2] - nr_servers[i2]);
            tot_n_queue[run] += (t_a[index_arr] - t) * (n_ws[i2] - nr_servers[i2]);
        }
    }

    // Calculate idle time servers
    for (i2 = 0; i2 < nr_stations; i2++)
    {   for (i1 = 0; i1 < nr_servers[i2]; i1++)
        {   if (t_d[i2][i1] == infinity)
            {   idle[run][i2][i1] += (t_a[index_arr] - t);
            }
        }
    }


    /* Increment simulation time */
    t = t_a[index_arr];


    /* Generate the job type*/
    j1 = rand()%1000;                                                               // Use a random number to determine the scan type
    j1 = double (j1)/1000;
    scan_type[n_a] = 0;
    while (j1 > cum_distr_scans[index_arr][scan_type[n_a]])     // Inversion method for discrete distribution
        scan_type[n_a]++;                                                           // Determine scan type of arrival

    /* Set task = 1 for this job */
    /* Determine the station for this job*/
    current_station[n_a] = 0;                                               // New arrival needs to go to first station


    for (i1 = 0; i1 < n_ws[route[scan_type[n_a]][current_station[n_a]]]; i1++)
    {   if (list_scan[route[scan_type[n_a]][current_station[n_a]]][i1] == -1)
            break;

    }
    list_scan[route[scan_type[n_a]][current_station[n_a]]][i1] = n_a;//add new arrival to the scan list
    time_arrival_ws[run][route[scan_type[n_a]][current_station[n_a]]][n_a]=t;       // Set the time of arrival at a particular workstation of a particular job
    if (n_a <= N)
    {   time_arrival[run][n_a] = t;                                                 // store time of arrival
    }


    n_a_ws[route[scan_type[n_a]][current_station[n_a]]]++;                          // Count the number of arrivals at a particular workstation

    n_ws[route[scan_type[n_a]][current_station[n_a]]]++;                        // Count number of scans at a particular workstation, defined by the route (scan type and current station)

    /* Are all machine busy on this station?*/
    if (n_ws[route[scan_type[n_a]][current_station[n_a]]] <= nr_servers[route[scan_type[n_a]][current_station[n_a]]])  // Arrival to a system where one of the servers was idle
    {   for (i1 = 0; i1 < nr_servers[route[scan_type[n_a]][current_station[n_a]]]; i1++)                      // Identify the server that was idle
        {   if (t_d[route[scan_type[n_a]][current_station[n_a]]][i1] == infinity)
                break;
        }
        t_mu = Normal_distribution(mu[route[scan_type[n_a]][current_station[n_a]]][scan_type[n_a]], sigma[route[scan_type[n_a]][current_station[n_a]]][scan_type[n_a]]);                                                       // For the system that was idle determine the departure time for the newly arrived scan
        t_mu = t_mu/60;
        time_service[run][route[scan_type[n_a]][current_station[n_a]]][n_a] = t_mu;
        /* Tally a delay of 0 for this job*/
        waiting_time_job_ws[run][route[scan_type[n_a]][current_station[n_a]]][n_a] = 0;
        /* Make a machine for this workstation busy */
        t_d[route[scan_type[n_a]][current_station[n_a]]][i1] = t + t_mu; tot_mu[run] += t_mu;
        current_cust[route[scan_type[n_a]][current_station[n_a]]][i1] = n_a;        // Track the current customer being served
    }
    printf("Arrival event\tJob %d\tSource %d\tTime %lf\tScan Type %d\n", n_a, index_arr, t, scan_type[n_a]);

    n++;                    // Increase number of jobs in system
    n_a++;                  // Increase the number of arrivals

    /* Schedule next arrival*/
    t_lambda = Exponential_distribution(lambda[index_arr]);
    t_a[index_arr] = t + t_lambda;
    tot_lambda[run][index_arr] += t_lambda;


}

void personnel::departure_event()
{

}



void personnel::output()
{


    strcpy(naam, "/Users/broosmaenhout/Documents/Output_Radiology.txt");                    // Open output file (CHANGE DIRECTORY)
    file1=fopen(naam,"w");

    for (i1=0; i1<nr_stations; i1++)                                                        // PRINT Utilisation
    {   fprintf(file1, "Utilisation servers Station WS %d:\t", i1);
        for(i2=0;i2<nr_servers[i1]; i2++)
        {   j1 = (idle[run][i1][i2]/t);
            rho_ws_s[i1][i2] = 1-j1;
            fprintf(file1, "%lf\t", rho_ws_s[i1][i2]);
        }
        fprintf(file1, "\n");

    }
    fprintf(file1, "\n");

    for (i1=0; i1<nr_stations; i1++)
    {   fprintf(file1, "Avg utilisation Station WS %d:\t", i1);
        for(i2=0;i2<nr_servers[i1]; i2++)
        {   rho_ws[i1] += rho_ws_s[i1][i2];
        }
        rho_ws[i1] = rho_ws[i1]/nr_servers[i1];
        fprintf(file1, "%lf\n", rho_ws[i1]);
    }
    fprintf(file1, "\n");

    for (i1=0; i1<nr_stations; i1++)
    {
        rho += rho_ws[i1];

    }
    rho /= nr_stations;
    fprintf(file1, "Overall avg utilisation: %lf\n", rho);

    fprintf(file1, "\n");

    for (i1 = 0; i1 < N; i1++)                                                              // PRINT system time = cycle time (observations and running average)
    {
        mean_system_time[run] += time_system[run][order_out[i1]];

    }
    fprintf(file1, "Cycle time\n\n");
    j1 = mean_system_time[run]/N;
    fprintf(file1, "Avg cycle time: %lf\n\n", j1);

    mean_system_time[run] = 0;
    fprintf(file1, "Number\tObservation\tRunning Average\n");

    for (i1 = 0; i1 < N; i1++)
    {
        mean_system_time[run] += time_system[run][order_out[i1]];
        j1 = mean_system_time[run]/(i1+1);
        fprintf(file1, "%d\t%lf\t%lf\n",i1,time_system[run][order_out[i1]],j1);

    }
    fclose(file1);

}
