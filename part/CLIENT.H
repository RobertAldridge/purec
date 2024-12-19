
// client.h
// POTYPE FOR MENU LIST FUNCTIONS

typedef union __CLIENT_POTYPE
{
	int           integer;

	unsigned char array[256];

	struct
	{
		char          name[82];
		unsigned char arg1;
		unsigned char arg2;
		unsigned char arg3;
		void          *particleSystem;
	};

}CLIENT_POTYPE,*CLIENT_PPOTYPE;