/*#################
CONTROLLER EXERCISE B
#################*/
#include <iostream>
#include "controller.hh"
#include "timestamp.hh"
#include <math.h>
using namespace std;

/******************
Default constructor
******************/
Controller::Controller( const bool debug )
  : debug_( debug )
{}


/******************
Variables
******************/
unsigned int the_window_size = 12; //x
unsigned int increase = 4; // a
float cut = 0.5; //b



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
A datagram was sent
******************/
void Controller::datagram_was_sent( const uint64_t sequence_number,
				    /* of the sent datagram */
				    const uint64_t send_timestamp,
                                    /* in milliseconds */
				    const bool after_timeout
				    /* datagram was sent because of a timeout */ )
{
	/* Decreases the congestion window size if datagram was sent because of a timeout */
	if(after_timeout){
		unsigned int new_size = (unsigned int) floor(the_window_size * cut);
		if(new_size<12) new_size = 12;
		the_window_size = new_size;
	}
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
			       const uint64_t recv_timestamp_acked,
			       /* when the acknowledged datagram was received (receiver's clock)*/
			       const uint64_t timestamp_ack_received )
                               /* when the ack was received (by sender) */
{
	/* Get RTT*/
	uint64_t rtt = timestamp_ack_received - send_timestamp_acked;
	
	/* Increases the size of the window if RTT is less than the timeout, 
	otherwise the size of the congestion window decreases */
	if(rtt > timeout_ms()){
		unsigned int new_size = (unsigned int) floor(the_window_size * cut);
		if(new_size<12) new_size = 12;
		the_window_size = new_size;
	}else{
		the_window_size += increase;
	}
	

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
unsigned int Controller::timeout_ms(){
	return 50;
}

