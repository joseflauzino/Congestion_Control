/*#################
CONTROLLER EXERCISE C
#################*/
#include <iostream>
#include "controller.hh"
#include "timestamp.hh"
using namespace std;
#define FLT_MAX 3.402e+38
#define INT_MAX +2147483647

/******************
Default constructor
******************/
Controller::Controller( const bool debug )
  : debug_( debug )
{}



/******************
Global variables
******************/
float the_window_size = 1;
int64_t travel_time_min = INT_MAX;
float RTT_min = FLT_MAX;



/******************
Get current window size, in datagrams
******************/
unsigned int Controller::window_size(){
	if ( debug_ ) {
		cerr << "At time " << timestamp_ms()
		<< " window size is " << the_window_size << endl;
	}
	return the_window_size;
}



/******************
Congestion Control
******************/
void Controller::congestion_control(float RTT, int64_t travel_time){
	if(travel_time < travel_time_min) travel_time_min = travel_time;
	if(RTT < RTT_min) RTT_min = RTT;

    float est_travel_time_min = (RTT_min * 0.5);
    float est_travel_time = est_travel_time_min + (travel_time - travel_time_min);
	
	if (est_travel_time > 1.4 * est_travel_time_min){
        the_window_size -= 0.3;
    }else{
        the_window_size += 0.5;
	}
	if (the_window_size < 1){
		the_window_size = 1; 
    }else{
		if(the_window_size > 70){
        	the_window_size = 70;
		}
	}
}



/******************
A datagram was sent
******************/
void Controller::datagram_was_sent( const uint64_t sequence_number,
				    /* of the sent datagram */
				    const uint64_t send_timestamp,
                                    /* in milliseconds */
				    const bool after_timeout
				    /* datagram was sent because of a timeout */ )
{
	if ( debug_ ) {
		cerr << "At time " << send_timestamp
		<< " sent datagram " << sequence_number << " (timeout = " << after_timeout << ")\n";
	}
}



/******************
An ack was received 
******************/
void Controller::ack_received( const uint64_t sequence_number_acked,
			       /* what sequence number was acknowledged */
			       const uint64_t send_timestamp_acked,
			       /* when the acknowledged datagram was sent (sender's clock) */
				   /* quando o datagrama ack foi enviado (horario do emissor)*/
			       const uint64_t recv_timestamp_acked,
			       /* when the acknowledged datagram was received (receiver's clock)*/
					/* quando o datagrama ack foi recebido (horario do receptor) */
			       const uint64_t timestamp_ack_received )
                               /* when the ack was received (by sender) */
								/* quando o ack foi recebido (pelo emissor) */
{
	/* Get travel time to the receiver */
	int64_t travel_time = recv_timestamp_acked - send_timestamp_acked;
	
	
	/* Get current RTT */
    float RTT =  timestamp_ack_received - send_timestamp_acked;
	
	
	/* Call congestion control function */
	congestion_control(RTT, travel_time);

	if ( debug_ ) {
		cerr << "At time " << timestamp_ack_received
		<< " received ack for datagram " << sequence_number_acked
		<< " (send @ time " << send_timestamp_acked
		<< ", received @ time " << recv_timestamp_acked << " by receiver's clock)"
		<< endl;
	}
}



/******************
How long to wait (in milliseconds) if there are no acks
before sending one more datagram
******************/
unsigned int Controller::timeout_ms(){ return 60; }

