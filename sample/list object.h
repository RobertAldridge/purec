
// client_potype.h
// POTYPE FOR LIST FUNCTIONS

#pragma warning( disable : 4201 )

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

	void *object;

}CLIENT_POTYPE,*CLIENT_PPOTYPE;

#pragma warning( default : 4201 )