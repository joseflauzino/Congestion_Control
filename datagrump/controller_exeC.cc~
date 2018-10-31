#include <iostream>

#include "controller.hh"
#include "timestamp.hh"

using namespace std;

//Variaveis Globais
double next_ack_expected = 0;
double the_window_size =14;
double dq = 0;
double srtt = 130; //smoothed rtt
double rtt_standing = 50;
double tau_start = 0.0;
double rtt_min = 50;
double delta = 0.3;
double v = 1.0;
double direction = 0;
double packet_count = 0;
double old_window_size= 13;
double slow_start = 1;
double rtt_avg = 50;
double rttlist[4] = {0};


/* Default constructor */
Controller::Controller( const bool debug )
  : debug_( debug )
{}

/* Get current window size, in datagrams */
unsigned int Controller::window_size()
{
  /* Default: fixed window size of 100 outstanding datagrams */

  if ( debug_ ) {
    cerr << "At time " << timestamp_ms()
	 << " window size is " << the_window_size << endl;
  }

  return the_window_size;
}

/* A datagram was sent */
void Controller::datagram_was_sent( const uint64_t sequence_number,
				    /* of the sent datagram */
				    const uint64_t send_timestamp,
            /* in milliseconds */
				    const bool after_timeout
				    /* datagram was sent because of a timeout */ )
{
  /* Default: take no action */
  if (after_timeout && the_window_size > 3) {
    the_window_size = the_window_size/3;
    //delta = 0.3;

    
  }

  if ( debug_ ) {
    cerr << "At time " << send_timestamp
	 << " sent datagram " << sequence_number << " (timeout = " << after_timeout << ")\n";
  }
}

/* An ack was received */
void Controller::ack_received( const uint64_t sequence_number_acked,
			       /* what sequence number was acknowledged */
			       const uint64_t send_timestamp_acked,
			       /* when the acknowledged datagram was sent (sender's clock) */
			       const uint64_t recv_timestamp_acked,
			       /* when the acknowledged datagram was received (receiver's clock)*/
			       const uint64_t timestamp_ack_received )
             /* when the ack was received (by sender) */
{
  /* Default: take no action */
  const uint64_t cur_rtt = timestamp_ack_received - send_timestamp_acked;

  double temp1 = rttlist[1];
  double temp2 = rttlist[2];
  double temp3 = rttlist[3];

  rttlist[0] = temp1;
  rttlist[1] = temp2;
  rttlist[2] = temp3;
  rttlist[3] = cur_rtt;
  double rttmax = rttlist[0];

  for(int i=1; i<=3; i = i+1){
    if(rttlist[i] > rttmax){
      rttmax = rttlist[i];
    }
  }


  if (timestamp_ack_received - tau_start >= srtt / 2.0) {
    rtt_standing = cur_rtt;
    tau_start = timestamp_ack_received;
  } else if (cur_rtt < rtt_standing){
    rtt_standing = cur_rtt;
  }

  if (cur_rtt < rtt_min) rtt_min = cur_rtt;

  srtt = 0.8 * srtt + 0.2 * cur_rtt;
  dq = rtt_standing - rtt_min;


  if(dq < 0.1*(rttmax - rtt_min)){
    delta = 0.3;
  }else{
    if(delta >= 0.1){
      delta = delta - 0.01;
    }
  }

  const float lambda_T = 1 / (delta * dq);
  const float lambda = float(the_window_size) / rtt_standing;

  if (lambda <= lambda_T) {
    the_window_size = the_window_size + (v / (delta * the_window_size));
  } else {
    the_window_size = the_window_size - (v / (delta * the_window_size));
  }

  packet_count = packet_count + 1;
  if (packet_count >= the_window_size) {
    if (slow_start == 0) {
        if (lambda <= lambda_T) {
          the_window_size = 2 * the_window_size;
          
        } else {
          slow_start = 1;
          
        }
    }

    if (the_window_size > old_window_size) {
    	// set "direction" to up
    	// if(delta >= 0.1){
    	// 	delta = delta - 0.08;

    	// 	if(delta < 0.1){
    	// 		delta = 0.1;
    	// 	}
    	// }
     
      if (direction > 0) {
        if (direction >= 3 && direction <= 5) {
          v = v * 2;
          
        }
        direction = direction + 1;
      } else {
        v = 1;
        direction = 1;
      }
    } else if (the_window_size < old_window_size) {
      // set "direction" to down
    	
      if (direction < 0) {
        if (direction <= -3 && direction >= -5) {
          v = v * 2;
        }
        direction = direction - 1;
      } else {
        v = 1;
        direction = -1;
      }
    }
    old_window_size = the_window_size;
    packet_count = 0;
  }

  rtt_avg = 0.8 * cur_rtt + 0.2 * rtt_avg;

  if ( debug_ ) {
    cerr << "At time " << timestamp_ack_received
	 << " received ack for datagram " << sequence_number_acked
	 << " (send @ time " << send_timestamp_acked
	 << ", received @ time " << recv_timestamp_acked << " by receiver's clock)"
	 << endl;
  }
}

/* How long to wait (in milliseconds) if there are no acks
   before sending one more datagram */
unsigned int Controller::timeout_ms()
{
  return 50; /* timeout of one second */
} 
