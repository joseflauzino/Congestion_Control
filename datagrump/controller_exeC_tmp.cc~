/*#################
CONTROLLER EXERCISE C
#################*/
#include <iostream>
#include "controller.hh"
#include "timestamp.hh"
using namespace std;



/******************
Default constructor
******************/
Controller::Controller( const bool debug )
  : debug_( debug )
{}



/******************
Global variables
******************/
float cwnd = 12; //---------------> the congestion window size
float dq = 0; //------------------>
float srtt = 0; //--------------> smoothed RTT
float standing_rtt = 50; //------->
float tau_start = 0.0; //--------->
unsigned int min_rtt = 50; //----->
float delta = 0.3; //------------->
float v = 1.0; //----------------->
float direction = 0; //----------->
unsigned int packet_count = 0; //->
float old_cwnd= 13; //------------>
bool slow_start = true; //-------->
float rtt_avg = 50; //------------>
unsigned int list_rtt[4] = {0}; //>



/******************
Get current window size, in datagrams
******************/
unsigned int Controller::window_size(){
	if ( debug_ ) {
		cerr << "At time " << timestamp_ms()
		<< " window size is " << cwnd << endl;
	}
	return cwnd;
}



/******************
Congestion Control
******************/
void Controller::congestion_control(uint64_t current_rtt, uint64_t timestamp_ack_received){
	//cout<<"cwnd= "<<cwnd<<endl;
	unsigned int aux[3] = {0};
	aux[0] = list_rtt[1];
	aux[1] = list_rtt[2];
	aux[2] = list_rtt[3];

	list_rtt[0] = aux[0];
	list_rtt[1] = aux[1];
	list_rtt[2] = aux[2];
	list_rtt[3] = current_rtt;
	unsigned int max_rtt = list_rtt[0];

	for(int i=1; i<=3; i++){
		if(list_rtt[i] > max_rtt) max_rtt = list_rtt[i];
	}

	if (timestamp_ack_received - tau_start >= srtt / 2.0) {
		standing_rtt = current_rtt;
		tau_start = timestamp_ack_received;
	}else if (current_rtt < standing_rtt){
		standing_rtt = current_rtt;
	}

	if (current_rtt < min_rtt) min_rtt = current_rtt;
	srtt = 0.8 * srtt + 0.2 * current_rtt;
	dq = standing_rtt - min_rtt;


	if(dq < 0.1*(max_rtt - min_rtt)){
		delta = 0.3;
	}else{
		if(delta >= 0.1){
			delta = delta - 0.01;
		}
	}
	const float lambda_T = 1 / (delta * dq);
	const float lambda = cwnd / standing_rtt;

	if (lambda <= lambda_T) {
		cwnd += v / (delta * cwnd);
	} else {
		cwnd -= v / (delta * cwnd);
	}

	packet_count++;
	//cout<<"packet_count= "<<packet_count<<endl;
	if (packet_count >= cwnd) {
		if (slow_start) {
			cout<<"slow_start= "<<slow_start<<endl;
			if (lambda <= lambda_T) {
				cwnd = 2 * cwnd;
			} else {
				slow_start = false;
			}
		}

		if (cwnd > old_cwnd) {
			if (direction > 0) {
				if (direction >= 3 && direction <= 5) v = v * 2;
				direction++;
			} else {
				v = 1;
				direction = 1;
			}
		} else if (cwnd < old_cwnd) {
			if (direction < 0) {
				if (direction <= -3 && direction >= -5) v = v * 2;
				direction--;
			} else {
				v = 1;
				direction = -1;
			}
		}

		old_cwnd = cwnd;
		packet_count = 0;
	}
	rtt_avg = 0.8 * current_rtt + 0.2 * rtt_avg;
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
	if (after_timeout && cwnd > 12) cwnd = cwnd * 0.2;
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
	/* Get current RTT */
	const uint64_t current_rtt = timestamp_ack_received - send_timestamp_acked;

	/* Calls the congestion control function */
	congestion_control(current_rtt, timestamp_ack_received);

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

