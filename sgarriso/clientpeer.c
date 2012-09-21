#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <netdb.h>

#include <netinet/in.h> 
#include <arpa/inet.h>
int reading(int sock, char * message) {
	 int numread;
	 char buf[255] = "";
     
    if ((numread = read(sock, buf, sizeof(buf) - 1)) == -1) // read in the data
    {
        perror("read"); // if we are having a read error
        pthread_exit(NULL);
    }

   if (numread == 0) // nothing was read
      return -1;

    buf[numread] = '\0';
    printf("the server sent: %s\r\n",buf);  
    
	
	
	return 1; // if it is found return true else
	
	
	
}
struct connection_data{ // a struct that holds the name of the machine and the port number
// the only way I could figure out how to pass many parameters to connection

 char * machine_name; // the name of the machine
 int port;  // the port name
}; 
char ** lookup(int);
void connection(void *);
int writing(int sock, char * buffer,int length){ // returns -1 if failed if good returns 0
	int c = write(sock, buffer, length);
	 if(c < 0){
	     
	 
	 return -1;
	 }
	return 0;
}
void connection(void * args){
 //TODO given a name of a machine create a socket and open a socket 
struct connection_data *  p = (struct connection_data*) args; 
char * name;
name = p->machine_name; // note it should be the case that we know the list of the ip address.
// note if  the name of the machine: like sslab01.cs.purdue.edu then you need to do a look up
int port = p->port;
int sock = 0;
struct hostent *he;
struct in_addr **addr_list;
struct sockaddr_in addr;
struct sockaddr_in Addr;

// look up  code if we need to do a look up:
  /* resolve the domain name into a list of addresses */
  he =  gethostbyname( name ) ; // get the infomation  from the name of the machine: IE: sslab01.cs.purdue.edu
    if  (he== NULL) {  // get the host info 
        herror("gethostbyname");
			pthread_exit(NULL);
        
    }
	
	
	  char* ip;
	   struct in_addr * address=( struct in_addr * )he->h_addr; // put the address in address
	  ip = inet_ntoa(* address); // translate the address into a char * form
	
if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) // open a socket
	{
		perror("socket creation error\r\n"); // pthread exit should kill only this thread
		pthread_exit(NULL); // if an error occurs kill this thread but the program does not need to end
	}
	memset(&Addr, 0, sizeof(Addr));     /* Zero out structure */
    	Addr.sin_family      = AF_INET;             /* Internet address family */
    	Addr.sin_addr.s_addr = inet_addr(ip); //use name if name will be the ip   /* Server IP address */
    	Addr.sin_port        = htons(port); /* Server port */
	if (connect(sock, (struct sockaddr *) &Addr, sizeof(Addr)) < 0) // make a connection with sock
	{
	 	perror(  " 0467 connection failed\r\n"); // connection failed going to say 467 error
		pthread_exit(NULL);
	}

// when created and open write to the socket.
 int c = writing(sock,"hello\r\n\0",7);
	if(c == -1){
		// test the socket connection
			// if socket connection failed try to reconnect
			pthread_exit(NULL);
		}
		else{
			while(1){
				int c = reading(sock,"hello\r\n\0");
				if(c == 1)
					break;
			}
		}
}
char ** lookup(int file){ // a function that looks up all the names that we can connect to
 char ** name;
 // TO DO read in a text file and store the names into a double pointer
 return name;
}
int total(char **list){ // given a list of names of the machines find the count
int count = 0;
//TODO get the count

return count;
}
int main( int argc, char ** argv ) //  first argv filename second args a port
{
	int port = atoi(argv[2]);
	
	int file = open(argv[1], O_RDONLY);
	 if (file < 0) { // open error
    perror("error on opening file:");
    exit(10);
  }
  // get the name of all the machines
	char ** list = lookup(file); //
	
	//create a dynamic  sized array based on the number of machines lookup returns.
	pthread_t * t1; //used to create a resizable threads list
	int count = total(list); // the total count for the machines
	t1 = (pthread_t *) malloc(count*sizeof(pthread_t));
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	
	int i = 0;
	struct connection_data  * args;
	 args = ( struct connection_data  *) malloc (count*sizeof( struct connection_data ));
	
	for(i = 0; i < count; i++){
		args[i].machine_name = list[i]; 
		args[i].port=port;
		pthread_create( &t1[i], &attr,(void * (*)(void *))connection, (void *)args); // set up the threads to call connection
	}



	
}
