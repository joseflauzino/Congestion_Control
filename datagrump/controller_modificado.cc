#include <iostream>

#include "controller.hh"
#include "timestamp.hh"
#include <math.h>
using namespace std;

/* Default constructor */
Controller::Controller( const bool debug )
  : debug_( debug )
{}

/* */
unsigned int the_window_size = 13;
unsigned int increment = 1;
unsigned int cut = 0.5;

/* Get current window size, in datagrams */
unsigned int Controller::window_size()
{
  /* Default: fixed window size of 100 outstanding datagrams */
  //unsigned int the_window_size = 350;

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
 // cout<<"Aqui!"<<endl;
  if(after_timeout){
//	cout<<"Deu timeout: "<<send_timestamp<<endl;
	//unsigned int new_size = floor(the_window_size * cut);
//	cout<<"Cortando window para: "<<new_size<<endl;
	//if(new_size < 13) new_size = 13;
//	the_window_size = 55;
//	if(the_window_size < 55) the_window_size += increment;
//	cout<<"WIndow: "<<the_window_size<<endl;
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
  uint64_t rtt = timestamp_ack_received - send_timestamp_acked;
//  uint64_t rtt = recv_timestamp_acked - send_timestamp_acked;
  //cout<<"rtt: "<<rtt<<endl;
  //best rtt= 105
  //best window size= 55
  if((rtt < 105) && (the_window_size < 55)){
  	the_window_size += increment;
	//cout<<"the_window_size= "<<the_window_size<<endl;
  }else{
	unsigned int new_size = floor(the_window_size * cut);
	if(new_size < 13) new_size = 13;
	the_window_size = new_size;
	//cout<<"Cortando window: "<<the_window_size<<endl;
  }
  //cout<<"the_window_size= "<<the_window_size<<endl;
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
  return 1000; /* timeout of one second */
}
